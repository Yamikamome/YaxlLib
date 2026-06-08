#include "YaxlMath.h"

#include <cmath>
#include <algorithm>

using namespace Yaxl;

float Math::Abs(float f) {
	return std::abs(f);
}

int Math::Abs(int value) {
	return std::abs(value);
}

float Math::Sign(float f) {
	return (f >= 0.0f) ? 1.0f : -1.0f;
}

float Math::Min(float a, float b) {
	return (a < b) ? a : b;
}

int Math::Min(int a, int b) {
	return (a < b) ? a : b;
}

float Math::Max(float a, float b) {
	return (a > b) ? a : b;
}

int Math::Max(int a, int b) {
	return (a > b) ? a : b;
}

float Math::Ceil(float f) {
	return std::ceil(f);
}

int Math::CeilToInt(float f) {
	return static_cast<int>(std::ceil(f));
}

float Math::Floor(float f) {
	return std::floor(f);
}

int Math::FloorToInt(float f) {
	return static_cast<int>(std::floor(f));
}

float Math::Round(float f) {
	return std::round(f);

}
int Math::RoundToInt(float f) {
	return static_cast<int>(std::round(f));
}

float Math::Clamp(float value, float min, float max) {
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

int Math::Clamp(int value, int min, int max) {
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

float Math::Clamp01(float value) {
	return Clamp(value, 0.0f, 1.0f);
}

float Math::Lerp(float a, float b, float t) {
	return a + (b - a) * Clamp01(t);
}

float Math::LerpUnclamped(float a, float b, float t) {
	return a + (b - a) * t;
}

float Math::LerpAngle(float a, float b, float t) {
	float delta = Repeat((b - a), 360.0f);
	if (delta > 180.0f) {
		delta -= 360.0f;
	}
	return a + delta * Clamp01(t);
}

float Math::InverseLerp(float a, float b, float value) {
	if (a != b) {
		return Clamp01((value - a) / (b - a));
	}
	return 0.0f;
}

float Math::SmoothStep(float from, float to, float t) {
	t = Clamp01(t);
	t = -2.0f * t * t * t + 3.0f * t * t;
	return to * t + from * (1.0f - t);
}

float Math::MoveTowards(float current, float target, float maxDelta) {
	if (Abs(target - current) <= maxDelta) {
		return target;
	}
	return current + Sign(target - current) * maxDelta;
}

float Math::MoveTowardsAngle(float current, float target, float maxDelta) {
	float deltaAngle = DeltaAngle(current, target);
	if (-maxDelta < deltaAngle && deltaAngle < maxDelta) {
		return target;
	}
	target = current + deltaAngle;
	return MoveTowards(current, target, maxDelta);
}

float Math::Repeat(float t, float length) {
	return Clamp(t - std::floor(t / length) * length, 0.0f, length);
}

float Math::PingPong(float t, float length) {
	t = Repeat(t, length * 2.0f);
	return length - Abs(t - length);
}

float Math::DeltaAngle(float current, float target) {
	float delta = Repeat((target - current), 360.0f);
	if (delta > 180.0f) {
		delta -= 360.0f;
	}
	return delta;
}

float Math::Sin(float f) {
	return std::sin(f);
}

float Math::Cos(float f) {
	return std::cos(f);
}

float Math::Tan(float f) {
	return std::tan(f);
}

float Math::Asin(float f) {
	return std::asin(f);
}

float Math::Acos(float f) {
	return std::acos(f);
}

float Math::Atan(float f) {
	return std::atan(f);
}

float Math::Atan2(float y, float x) {
	return std::atan2(y, x);
}

float Math::Pow(float f, float p) {
	return std::pow(f, p);
}

float Math::Exp(float power) {
	return std::exp(power);
}

float Math::Log(float f) {
	return std::log(f);
}

float Math::Log10(float f) {
	return std::log10(f);
}

float Math::Sqrt(float f) {
	return std::sqrt(f);
}

bool Math::Approximately(float a, float b) {
	return Abs(b - a) < Max(0.000001f * Max(Abs(a), Abs(b)), Epsilon * 8.0f);
}

bool Math::IsPowerOfTwo(int value) {
	return (value > 0) && ((value & (value - 1)) == 0);
}

int Math::ClosestPowerOfTwo(int value) {
	int next = NextPowerOfTwo(value);
	int prev = next >> 1;
	if (value - prev < next - value) {
		return prev;
	}
	return next;
}

int Math::NextPowerOfTwo(int value) {
	value--;
	value |= value >> 1;
	value |= value >> 2;
	value |= value >> 4;
	value |= value >> 8;
	value |= value >> 16;
	value++;
	return value;
}
