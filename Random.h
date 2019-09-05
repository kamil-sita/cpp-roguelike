#ifndef ROGUELIKE_RANDOM_H
#define ROGUELIKE_RANDOM_H

double getRandom(double min, double max);
int getRandomInt(int min, int max);
/**
 * converts double (for example randomly generated one) into an integer value <min, max - 1>.
 * double can be only from range of <0, 1>
 *
 * If used properly, for arguments min = 0, max = 5 it can generate values 0, 1, 2, 3, 4.
 *
 */
int doubleToInt(int min, int max, double v);

#endif
