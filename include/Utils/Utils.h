#ifndef __UTILS_H__
#define __UTILS_H__

static const float EPSILON = 0.0001f;

const float PI = 3.14159;
const float TWO_PI = 2.0f * PI;

bool IsEqual(float x, float y);
bool IsGreaterThanOrEqual(float x, float y);
bool IsLessThanOrEqual(float x, float y);

float MillisToSecs(unsigned int millis);

#endif
