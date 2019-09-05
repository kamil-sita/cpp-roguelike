#include <random>

double getRandom(double min, double max) {
    std::uniform_real_distribution<double> uniformRealDistribution(min, max);
    static std::default_random_engine randomEngine;
    return uniformRealDistribution(randomEngine);
}

int getRandomInt(int min, int max) {
    std::uniform_int_distribution<int> uniformIntDistribution(min, max);
    static std::default_random_engine randomEngine;
    return uniformIntDistribution(randomEngine);
}

int doubleToInt(int min, int max, double v) {
    if (v == 1) v = 0;
    int rangeSize = max - min;
    int value = rangeSize * v + min;
    return value;
}
