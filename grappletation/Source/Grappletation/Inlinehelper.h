#ifndef __INLINEHELPERS_H__
#define __INLINEHELPERS_H__
#include <cstdlib>
#include <string>
#include <sstream>
inline int GetRandom(int lowerBoundary, int upperBoundary)
{
	rand();
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
inline float LinearProgression(float x, float xBound1, float xBound2)
{
	float y = (xBound2 * x) + (xBound1 * (1 - x));
	return y;
}

inline float QuadraticSlowProgression(float x, float xBound1, float xBound2)
{
	float y = ((xBound2 - xBound1) * (x * x)) + xBound1;
	return y;
}

inline float QuadraticFastProgression(float x, float xBound1, float xBound2)
{
	float y = ((xBound1 - xBound2) * (((x * x) - 1) * ((x * x) - 1))) + xBound2;
	return y;
}

inline std::string Vector2ToString(int x, int y)
{
	std::ostringstream ss;
	ss << x << ", " << y;
	return ss.str();
}

#endif // __INLINEHELPERS_H__