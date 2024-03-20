#pragma once

namespace signals {
    struct Signal {
        int type;
        float value;

        Signal() {}
        Signal(int t) {
            type = t;
        }
        Signal(int t, float v) {
            type = t;
            value = v;
        }
    };
    enum SignalType : int {
        Ignore = 0,
        Failed = 1,
        Success = 2,
        Invalid = 3, // used primarily when responding to say that a sent signal wasn't supported
        Delete = 4,
        Update = 5, // value indicates time since last update
        Interact = 6, // value may specify update type
        Damage = 7, // value specifies damage amount
    };
}

using namespace signals;
class SignalReceiver {
    protected: 
        Signal returnSignal;

    public:
        SignalReceiver();
        Signal signal(Signal); // signal to send
};