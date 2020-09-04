#include <cmath>
#include "Utils/Utils.h"

bool IsEqual(float x, float y) {
	return fabs(x - y) < EPSILON;
}

bool IsGreaterThanOrEqual(float x, float y) {
	return x > y || IsEqual(x, y);
}

bool IsLessThanOrEqual(float x, float y) {
	return x < y || IsEqual(x, y);
}

float MillisToSecs(unsigned int millis) {
	return static_cast<float>(millis) / 1000.0f;
}
