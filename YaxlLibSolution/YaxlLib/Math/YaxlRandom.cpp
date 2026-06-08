#include "YaxlRandom.h"

#include <random>
#include "YaxlVector2.h"
#include "YaxlVector3.h"

using namespace Yaxl;

namespace {
	inline unsigned int& GetSeedInternal() {
		static thread_local unsigned int seed = std::random_device{}();
		return seed;
	}

	inline std::mt19937& GetEngine() {
		static thread_local std::mt19937 engine{ GetSeedInternal() };
		return engine;
	}
}

void Random::Init(unsigned int seed) {
	GetSeedInternal() = seed;
	GetEngine().seed(seed);
}

unsigned int Random::GetSeed() {
	return GetSeedInternal();
}

float Random::Value() {
	return Range(0.0f, 1.0f);
}

int Random::Range(int min, int max) {
	if (min >= max) {
		return min;
	}

	std::uniform_int_distribution<int> dist(min, max);
	return dist(GetEngine());
}

float Random::Range(float min, float max) {
	if (min >= max) {
		return min;
	}

	std::uniform_real_distribution<float> dist(min, max);
	return dist(GetEngine());
}

Vector2 Random::Range(const Vector2& min, const Vector2& max) {
	return Vector2(Range(min.x, max.x), Range(min.y, max.y));
}

Vector3 Random::Range(const Vector3& min, const Vector3& max) {
	return Vector3(Range(min.x, max.x), Range(min.y, max.y), Range(min.z, max.z));
}

Vector3 Random::InsideUnitSphere() {
	// 立方体の中でランダム値を生成し、球体の中であれば返す
	while (true) {
		Vector3 point(Range(-1.0f, 1.0f),Range(-1.0f, 1.0f),Range(-1.0f, 1.0f));

		if (point.SqrMagnitude() <= 1.0f) {
			return point;
		}
	}
}
