#ifndef MEDIAPIPE_FRAMEWORK_LEGACY_CALCULATOR_SUPPORT_H_
#define MEDIAPIPE_FRAMEWORK_LEGACY_CALCULATOR_SUPPORT_H_

#include "mediapipe/framework/calculator_context.h"
#include "mediapipe/framework/calculator_contract.h"

namespace mediapipe {

class LegacyCalculatorSupport {
 public:
  template <class C>
  class Scoped {
   public:
    explicit Scoped(C* cc) {
      saved_ = current_;
      current_ = cc;
    }
    ~Scoped() { current_ = saved_; }

    static C* current() { return current_; }

   private:
    C* saved_;

    // Make the static thread_local variable inline to fix MSVC linker errors
    inline static thread_local C* current_ = nullptr;
  };
};
}  // namespace mediapipe
#endif  // MEDIAPIPE_FRAMEWORK_LEGACY_CALCULATOR_SUPPORT_H_
