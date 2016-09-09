//
// Created by styvaether on 12/29/15.
//

#include "../../include/Core/Time.hh"

float Pulse::Utils::Time::DeltaTime;

Pulse::Utils::Time::Time() {
    _clock = clock();
}

Pulse::Utils::Time::~Time() {

}

void Pulse::Utils::Time::Update() {
    _clockSinceLastFrame = clock() - _clock;
    DeltaTime = static_cast<float>(_clockSinceLastFrame) / static_cast<float>(CLOCKS_PER_SEC);
    _clock = clock();
}
