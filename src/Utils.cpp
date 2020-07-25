#include <cmath>
#include "Utils.h"

bool IsEqual(float x, float y) {
	return fabs(x - y) < EPSILON;
}

bool IsGreaterThanOrEqual(float x, float y) {
	return x > y || IsEqual(x, y);
}

bool IsLessThanOrEqual(float x, float y) {
	return x < y || IsEqual(x, y);
}
