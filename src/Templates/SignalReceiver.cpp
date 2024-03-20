#include "Templates/SignalReceiver.hpp"

SignalReceiver::SignalReceiver() {}

Signal SignalReceiver::signal(Signal s) {
    returnSignal.type = SignalType::Failed;
    returnSignal.value = 0.0;

    return returnSignal;
}