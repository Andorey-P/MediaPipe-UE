// Include the core MediaPipe calculator framework
// This provides CalculatorBase, CalculatorContext, CalculatorContract,
// and the REGISTER_CALCULATOR macro
#include "mediapipe/framework/calculator_framework.h"

// Include protobuf definitions for hand landmarks
// Provides NormalizedLandmark and NormalizedLandmarkList classes
#include "mediapipe/framework/formats/landmark.pb.h"

// Include Abseil logging utilities used by MediaPipe
// Allows logging with severity levels (INFO, WARNING, ERROR, etc.)
#include "absl/log/absl_log.h"

// Include standard C++ I/O stream for console output
#include <iostream>

// Include OSC libraries for sending UDP packets
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"


// All MediaPipe calculators MUST live inside the mediapipe namespace
namespace mediapipe {

// Define a custom MediaPipe calculator class
// It must inherit from CalculatorBase
class MySimpleCalculator : public CalculatorBase {
 private:
  std::unique_ptr<UdpTransmitSocket> socket_;
  IpEndpointName destination_;
 
  public:

  // GetContract is a static method called once when the graph is built
  // It declares what input/output streams this calculator expects
  static absl::Status GetContract(CalculatorContract* cc) {

    // Declare an input stream with tag "LANDMARKS"
    // Each packet contains a vector of NormalizedLandmarkList
    // (one list per detected hand)
    cc->Inputs()
        .Tag("LANDMARKS")
        .Set<std::vector<NormalizedLandmarkList>>();

    // Return OK to indicate the contract is valid
    return absl::OkStatus();
  }

  // Open is called once when the graph starts running
  // This is used for initialization or debug logging
  // It is kind of like the BeginPlay() method in unreal engine
  absl::Status Open(CalculatorContext* cc) override {

    // Log that the calculator opened
  ABSL_LOG(INFO) << "MySimpleCalculator OPENED";

  // OSC destination: local Unreal Engine server on port 8000
  destination_ = IpEndpointName("127.0.0.1", 8000);

  // Create UDP socket
  socket_ = std::make_unique<UdpTransmitSocket>(destination_);

  ABSL_LOG(INFO) << "OSC sender initialized";

  return absl::OkStatus();
  }

  // Process is called once per incoming packet (usually once per frame)
  // This is where the main logic of the calculator runs
  // It is kind of like the Tick() method in unreal engine
  absl::Status Process(CalculatorContext* cc) override {

    // Retrieve the input packet tagged "LANDMARKS"
    // The packet contains a vector of hand landmark lists
    const auto& hands =
        cc->Inputs()
            .Tag("LANDMARKS")
            .Get<std::vector<NormalizedLandmarkList>>();

    // Loop over each detected hand
    for (int hand_idx = 0; hand_idx < hands.size(); ++hand_idx) {

      // Get the landmark list for the current hand
      const auto& hand = hands[hand_idx];

      // Ensure the hand contains at least one landmark
      // (defensive check to avoid invalid access)

      //create place holders for the x, y, z values of the first landmark
      float x,y,z;
     
      if (hand.landmark_size() > 0) {

        // Access landmark 0 (wrist in MediaPipe Hands)
        const auto& lm8 = hand.landmark(8);

        // Create a buffer for the OSC packet
        char buffer[2048];
        osc::OutboundPacketStream p(buffer, sizeof(buffer));

        p << osc::BeginMessage(("/hand/" + std::to_string(hand_idx) + "/landmarks").c_str());

        for (int i = 0; i < hand.landmark_size(); ++i) {
            const auto& lm = hand.landmark(i);
            // float x = (lm.x() - 0.5f) * 2.0f;
            // float y = 1.0f - lm.y();
            // float z = lm.z() * 1000000.0f;

            float x = lm8.x();
            float y = lm8.y();
            float z = lm8.z() * 1000000.0f;

            p << x << y << z;
        }

        p << osc::EndMessage;
        socket_->Send(p.Data(), p.Size());

        // Send the packet
        socket_->Send(p.Data(), p.Size());

      }
    }

    // Return OK to indicate successful processing of this packet
    return absl::OkStatus();
  }
};

// Force linker to pull in UdpSocket / UdpTransmitSocket symbols
extern void ForceLinkOscPack();
void ForceLinkOscPack() {
    volatile UdpSocket* s = nullptr;
    (void)s;
}

// Register the calculator so MediaPipe can instantiate it from a graph
// Without this macro, the calculator will not be found at runtime
REGISTER_CALCULATOR(MySimpleCalculator);


}  // namespace mediapipe