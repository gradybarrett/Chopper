#include "animationclock.h"

#include <cstdio>

AnimationClock::AnimationClock() :
        nextSample(0), numSamples(0), currentTime(0.0), m_deltaT(0.0)
{
    for( int i = 0 ; i < ANIMATIONCLOCK_SAMPLES_MAX; i++ ) samples[i] = 0.0;
    rebase();
}

void AnimationClock::rebase() {
    currentTime = 0.0;
    gettimeofday(&baseTime,0);
    nextSample = 0;
    numSamples = 0;
    update();
}

double AnimationClock::now() const {
    struct timeval time;
    gettimeofday(&time,0);

    return (time.tv_sec - baseTime.tv_sec) +
            (time.tv_usec - baseTime.tv_usec) * 1.0e-6;
}

double AnimationClock::deltaT() const {
    return m_deltaT;
}

double AnimationClock::time() const {
    return currentTime;
}

void AnimationClock::update() {
    // Take a time sample
    samples[nextSample] = now();

    numSamples = ((numSamples + 1) > ANIMATIONCLOCK_SAMPLES_MAX) ?
                 ANIMATIONCLOCK_SAMPLES_MAX : numSamples + 1;

    // The previous value of the time (needed to compute deltaT)
    double lastTime = currentTime;

    // Average of the samples is the current time
    double sum = 0.0;
    for( int i = 0; i < numSamples; i++ ) sum += samples[i];
    currentTime = sum / numSamples;

    // Change since last update
    m_deltaT = currentTime - lastTime;

    // Point nextSample to the next slot (for the next sample)
    nextSample = (nextSample + 1) % ANIMATIONCLOCK_SAMPLES_MAX;
}
