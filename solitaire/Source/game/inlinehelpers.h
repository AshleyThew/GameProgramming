#ifndef __INLINEHELPERS_H__
#define __INLINEHELPERS_H__
#include <cstdlib>
inline int GetRandom(int lowerBoundary, int upperBoundary)
{
	int range = (upperBoundary - lowerBoundary + 1);
	return (rand() % range) + lowerBoundary;
}
inline float GetRandomPercentage()
{
	int percent = GetRandom(0, 100);
	return percent / 100.0f;
}
inline float GetPositiveOrNegative()
{
	int coinToss = rand() % 2;
	float result = (coinToss == 0) ? -1.0f : 1.0f;
	return result;
}
#endif // __INLINEHELPERS_H__