#pragma once


/// type for storing time in microseconds
typedef uint64_t Time;


/** returns the local system timestamp in microseconds */
static inline Time timestamp()
{
    struct timeval time;
    gettimeofday(&time, 0);

    return (Time)time.tv_sec * 1000000 + (Time)time.tv_usec;
}
