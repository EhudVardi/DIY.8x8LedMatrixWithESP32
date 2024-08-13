#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <Arduino.h>

class RandomGenerator {
public:
    // Static initializer to seed the random number generator
    static void initialize() {
        static bool isSeeded = false;
        if (!isSeeded) {
            randomSeed(analogRead(0)); // Seed the RNG with analog input
            isSeeded = true;
        }
    }

    // Generate a random integer in the range [min, max)
    static int nextInt(int min, int max) {
        initialize();
        return random(min, max);
    }

    // Generate a random floating-point number in the range [0.0, 1.0)
    static float nextFloat() {
        initialize();
        return random(10000) / 10000.0;
    }

    // Generate a random floating-point number in the range [min, max)
    static float nextFloat(float min, float max) {
        initialize();
        return min + (random(10000) / 10000.0) * (max - min);
    }
};

#endif // RANDOMGENERATOR_H
