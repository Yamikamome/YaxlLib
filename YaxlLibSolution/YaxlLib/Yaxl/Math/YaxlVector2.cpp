#include "YaxlVector2.h"

#include "YaxlMath.h"

using namespace Yaxl;

Vector2::Vector2() {
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

void Vector2::Set(float x, float y) {
	this->x = x;
	this->y = y;
}

float Vector2::Magnitude() const {
	return Math::Sqrt(x * x + y * y);
}

float Vector2::SqrMagnitude() const {
	return x * x + y * y;
}

Vector2 Vector2::Normalized() const {
	float mag = Magnitude();
	if (mag > 0.00001f) {
		return Vector2(x / mag, y / mag);
	}
	return Vector2::Zero();
}

void Vector2::Normalize() {
	float mag = Magnitude();
	if (mag > 0.00001f) {
		x = x / mag;
		y = y / mag;
	}
	else {
		x = 0.0f;
		y = 0.0f;
	}
}

Vector2 Vector2::Zero() {
	return Vector2(0.0f, 0.0f);
}

Vector2 Vector2::One() {
	return Vector2(1.0f, 1.0f);
}

Vector2 Vector2::Up() {
	return Vector2(0.0f, 1.0f);
}

Vector2 Vector2::Down() {
	return Vector2(0.0f, -1.0f);
}

Vector2 Vector2::Left() {
	return Vector2(-1.0f, 0.0f);
}

Vector2 Vector2::Right() {
	return Vector2(1.0f, 0.0f);
}

Vector2 Vector2::PositiveInfinity() {
	return Vector2(Math::Infinity, Math::Infinity);
}

Vector2 Vector2::NegativeInfinity() {
	return Vector2(Math::NegativeInfinity, Math::NegativeInfinity);
}

float Vector2::Dot(const Vector2& lhs, const Vector2& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Vector2::Distance(const Vector2& a, const Vector2& b) {
	return (a - b).Magnitude();
}

float Vector2::Angle(const Vector2& from, const Vector2& to) {
	float denominator = Math::Sqrt(from.SqrMagnitude() * to.SqrMagnitude());
	if (denominator < Math::Epsilon) {
		return 0.0f;
	}
	float dot = Math::Clamp(Dot(from, to) / denominator, -1.0f, 1.0f);
	return Math::Acos(dot) * Math::Rad2Deg;
}

float Vector2::SignedAngle(const Vector2& from, const Vector2& to) {
	float angle = Angle(from, to);
	float sign = Math::Sign(from.x * to.y - from.y * to.x);
	return angle * sign;
}

Vector2 Vector2::ClampMagnitude(const Vector2& vector, float maxLength) {
	float sqrMag = vector.SqrMagnitude();
	if (sqrMag > maxLength * maxLength) {
		float mag = Math::Sqrt(sqrMag);
		float normalizedX = vector.x / mag;
		float normalizedY = vector.y / mag;
		return Vector2(normalizedX * maxLength, normalizedY * maxLength);
	}
	return vector;
}

Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t) {
	t = Math::Clamp01(t);
	return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
}

Vector2 Vector2::LerpUnclamped(const Vector2& a, const Vector2& b, float t) {
	return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
}

Vector2 Vector2::Max(const Vector2& lhs, const Vector2& rhs) {
	return Vector2(Math::Max(lhs.x, rhs.x), Math::Max(lhs.y, rhs.y));
}

Vector2 Vector2::Min(const Vector2& lhs, const Vector2& rhs) {
	return Vector2(Math::Min(lhs.x, rhs.x), Math::Min(lhs.y, rhs.y));
}

Vector2 Vector2::MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta) {
	float toVector_x = target.x - current.x;
	float toVector_y = target.y - current.y;
	float sqrDist = toVector_x * toVector_x + toVector_y * toVector_y;

	if (sqrDist == 0.0f || (maxDistanceDelta >= 0.0f && sqrDist <= maxDistanceDelta * maxDistanceDelta)) {
		return target;
	}

	float dist = Math::Sqrt(sqrDist);
	return Vector2(current.x + toVector_x / dist * maxDistanceDelta,
		current.y + toVector_y / dist * maxDistanceDelta);
}

Vector2 Vector2::Perpendicular(const Vector2& inDirection) {
	return Vector2(-inDirection.y, inDirection.x);
}

Vector2 Vector2::Reflect(const Vector2& inDirection, const Vector2& inNormal) {
	float factor = -2.0f * Dot(inNormal, inDirection);
	return Vector2(factor * inNormal.x + inDirection.x,
		factor * inNormal.y + inDirection.y);
}

Vector2 Vector2::Scale(const Vector2& a, const Vector2& b) {
	return Vector2(a.x * b.x, a.y * b.y);
}

Vector2 Vector2::operator+(const Vector2& rhs) const {
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const {
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator*(float d) const {
	return Vector2(x * d, y * d);
}

Vector2 Vector2::operator/(float d) const {
	return Vector2(x / d, y / d);
}

Vector2& Vector2::operator+=(const Vector2& rhs) {
	x += rhs.x; y += rhs.y; return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs) {
	x -= rhs.x; y -= rhs.y; return *this;
}

Vector2& Vector2::operator*=(float d) {
	x *= d; y *= d; return *this;
}

Vector2& Vector2::operator/=(float d) {
	x /= d; y /= d; return *this;
}

bool Vector2::operator==(const Vector2& rhs) const {
	return Math::Approximately(x, rhs.x) && Math::Approximately(y, rhs.y);
}

bool Vector2::operator!=(const Vector2& rhs) const {
	return !(*this == rhs);
}

Vector2 Yaxl::operator*(float d, const Vector2& rhs) {
	return Vector2(rhs.x * d, rhs.y * d);
}
