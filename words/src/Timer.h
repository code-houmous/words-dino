#ifndef TIMER_H
#define TIMER_H

/**
 * A tool to manipulate time, like getting time elapsed
 */
struct Timer
{

private:
    // Currrent time since the reset of the timer
    unsigned long currentMillis;

    // last checked milliseconds
    unsigned long previousMillis = 0;

public:
    /**
     * Returns the elapsed time since last reset
     */
    unsigned long getElapsedTime() const
    {
        return (this->currentMillis - this->previousMillis);
    }

    /**
     * Update the previous time
     */
    void updatePreviousTime()
    {
        this->previousMillis = this->currentMillis;
    }

    /**
     * update the current time to current milliseconds
     */
    void updateCurrentTime()
    {
        this->currentMillis = millis();
    }
};

#endif
