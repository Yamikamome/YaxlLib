#include "YaxlVector4.h"

#include "YaxlMath.h"
#include "YaxlVector2.h"
#include "YaxlVector3.h"

using namespace Yaxl;

Vector4::Vector4() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	w = 0.0f;
}

Vector4::Vector4(const Vector3& v) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	w = 0.0f;
}

void Vector4::Set(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Vector4::Magnitude() const {
	return Math::Sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::SqrMagnitude() const {
	return x * x + y * y + z * z + w * w;
}

Vector4 Vector4::Normalized() const {
	float mag = Magnitude();
	if (mag > Math::Epsilon) {
		return Vector4(x / mag, y / mag, z / mag, w / mag);
	}
	return Vector4::Zero();
}

void Vector4::Normalize() {
	float mag = Magnitude();
	if (mag > Math::Epsilon) {
		x = x / mag;
		y = y / mag;
		z = z / mag;
		w = w / mag;
	}
	else {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
}

Vector4 Vector4::Zero() {
	return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

Vector4 Vector4::One() {
	return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

Vector4 Vector4::PositiveInfinity() {
	return Vector4(Math::Infinity, Math::Infinity, Math::Infinity, Math::Infinity);
}

Vector4 Vector4::NegativeInfinity() {
	return Vector4(Math::NegativeInfinity, Math::NegativeInfinity, Math::NegativeInfinity, Math::NegativeInfinity);
}

float Vector4::Dot(const Vector4& lhs, const Vector4& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

float Vector4::Distance(const Vector4& a, const Vector4& b) {
	return (a - b).Magnitude();
}

Vector4 Vector4::ClampMagnitude(const Vector4& vector, float maxLength) {
	float sqrMag = vector.SqrMagnitude();
	if (sqrMag > maxLength * maxLength) {
		float mag = Math::Sqrt(sqrMag);
		float normalizedX = vector.x / mag;
		float normalizedY = vector.y / mag;
		float normalizedZ = vector.z / mag;
		float normalizedW = vector.w / mag;
		return Vector4(normalizedX * maxLength, normalizedY * maxLength, normalizedZ * maxLength, normalizedW * maxLength);
	}
	return vector;
}

Vector4 Vector4::Lerp(const Vector4& a, const Vector4& b, float t) {
	t = Math::Clamp01(t);
	return Vector4(
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t,
		a.w + (b.w - a.w) * t
	);
}

Vector4 Vector4::LerpUnclamped(const Vector4& a, const Vector4& b, float t) {
	return Vector4(
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t,
		a.w + (b.w - a.w) * t
	);
}

Vector4 Vector4::Max(const Vector4& lhs, const Vector4& rhs) {
	return Vector4(
		Math::Max(lhs.x, rhs.x),
		Math::Max(lhs.y, rhs.y),
		Math::Max(lhs.z, rhs.z),
		Math::Max(lhs.w, rhs.w)
	);
}

Vector4 Vector4::Min(const Vector4& lhs, const Vector4& rhs) {
	return Vector4(
		Math::Min(lhs.x, rhs.x),
		Math::Min(lhs.y, rhs.y),
		Math::Min(lhs.z, rhs.z),
		Math::Min(lhs.w, rhs.w)
	);
}

Vector4 Vector4::MoveTowards(const Vector4& current, const Vector4& target, float maxDistanceDelta) {
	Vector4 toVector = target - current;
	float dist = toVector.Magnitude();

	if (dist <= maxDistanceDelta || dist < Math::Epsilon) {
		return target;
	}
	return current + toVector / dist * maxDistanceDelta;
}

Vector4 Vector4::Project(const Vector4& vector, const Vector4& onNormal) {
	float sqrMag = onNormal.SqrMagnitude();
	if (sqrMag < Math::Epsilon) {
		return Vector4::Zero();
	}
	float dot = Dot(vector, onNormal);
	return onNormal * (dot / sqrMag);
}

Vector4 Vector4::Scale(const Vector4& a, const Vector4& b) {
	return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

Vector4 Vector4::operator+(const Vector4& rhs) const {
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Vector4 Vector4::operator-(const Vector4& rhs) const {
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

Vector4 Vector4::operator*(float d) const {
	return Vector4(x * d, y * d, z * d, w * d);
}

Vector4 Vector4::operator/(float d) const {
	return Vector4(x / d, y / d, z / d, w / d);
}

Vector4& Vector4::operator+=(const Vector4& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}

Vector4& Vector4::operator*=(float d) {
	x *= d;
	y *= d;
	z *= d;
	w *= d;
	return *this;
}

Vector4& Vector4::operator/=(float d) {
	x /= d;
	y /= d;
	z /= d;
	w /= d;
	return *this;
}

bool Vector4::operator==(const Vector4& rhs) const {
	return Math::Approximately(x, rhs.x) &&
		Math::Approximately(y, rhs.y) &&
		Math::Approximately(z, rhs.z) &&
		Math::Approximately(w, rhs.w);
}

bool Vector4::operator!=(const Vector4& rhs) const {
	return !(*this == rhs);
}

Vector4 Yaxl::operator*(float d, const Vector4& rhs) {
	return Vector4(rhs.x * d, rhs.y * d, rhs.z * d, rhs.w * d);
}
