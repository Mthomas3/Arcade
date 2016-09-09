//
// Created by styvaether on 12/29/15.
//

#ifndef PULSE_ENGINE_TIME_H
#define PULSE_ENGINE_TIME_H

#include "Singleton.hh"

namespace Pulse
{
    namespace Utils
    {
        class Time : public Singleton<Time> {
        public:
            Time();
            ~Time();

            void Update();

            static float DeltaTime;

        private:
            clock_t _clock;
            clock_t _clockSinceLastFrame;
        };
    }
}

#endif //PULSE_ENGINE_TIME_H
