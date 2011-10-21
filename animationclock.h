#ifndef ANIMATIONCLOCK_H
#define ANIMATIONCLOCK_H

#define ANIMATIONCLOCK_SAMPLES_MAX 10

#include <sys/time.h>

class AnimationClock
{
private:
    double samples[ANIMATIONCLOCK_SAMPLES_MAX];
    int nextSample;
    int numSamples;
    double currentTime;
    double m_deltaT;
    struct timeval baseTime;

    double now() const;

public:
    /**
      * Initializes this clock with default settings, and calls
      * rebase().
      */
    AnimationClock();

    /**
      * Resets the clock to an initial state.  time() will return
      * numbers relatively close to zero shortly after calling this
      * method.  You don't need to call this method unless
      * this is a long running program, or if you just want to
      * reset the clock to zero.
      */
    void rebase();

    /**
      * Returns the elapsed time between the last two calls
      * to update().  The time is returned in seconds, with microsecond
      * resolution.
      */
    double deltaT() const;

    /**
      * Returns the elapsed time since the base time at the time
      * of the most recent call to update().  The
      * base time is the time that this object was constructed or the
      * time since the last call to rebase().  The time is returned
      * in seconds with microsecond resolution.
      */
    double time() const;

    /**
      * Updates this timer by taking a new time sample.  It recomputes
      * the current time as the average over all of the time samples.
      * Call this method just prior to calling time() or deltaT().
      */
    void update();
};

#endif // ANIMATIONCLOCK_H
