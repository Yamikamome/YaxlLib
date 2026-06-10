#include "YaxlVector3.h"

#include "YaxlMath.h"
#include "YaxlVector2.h"

using namespace Yaxl;

Vector3::Vector3() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(float x, float y) {
	this->x = x;
	this->y = y;
	z = 0.0f;
}

Vector3::Vector3(const Vector2& v) {
	this->x = v.x;
	this->y = v.y;
	z = 0.0f;
}

void Vector3::Set(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3::Magnitude() const {
	return Math::Sqrt(x * x + y * y + z * z);
}

float Vector3::SqrMagnitude() const {
	return x * x + y * y + z * z;
}

Vector3 Vector3::Normalized() const {
	float mag = Magnitude();
	if (mag > Math::Epsilon) {
		return Vector3(x / mag, y / mag, z / mag);
	}
	return Vector3::Zero();
}

void Vector3::Normalize() {
	float mag = Magnitude();
	if (mag > Math::Epsilon) {
		x = x / mag;
		y = y / mag;
		z = z / mag;
	}
	else {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
}

Vector3 Vector3::Zero() {
	return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 Vector3::One() {
	return Vector3(1.0f, 1.0f, 1.0f);
}

Vector3 Vector3::Up() {
	return Vector3(0.0f, 1.0f, 0.0f);
}

Vector3 Vector3::Down() {
	return Vector3(0.0f, -1.0f, 0.0f);
}

Vector3 Vector3::Left() {
	return Vector3(-1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::Right() {
	return Vector3(1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::Forward() {
	return Vector3(0.0f, 0.0f, 1.0f);
}

Vector3 Vector3::Back() {
	return Vector3(0.0f, 0.0f, -1.0f);
}

Vector3 Vector3::PositiveInfinity() {
	return Vector3(Math::Infinity, Math::Infinity, Math::Infinity);
}

Vector3 Vector3::NegativeInfinity() {
	return Vector3(Math::NegativeInfinity, Math::NegativeInfinity, Math::NegativeInfinity);
}

float Vector3::Dot(const Vector3& lhs, const Vector3& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs) {
	return Vector3(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x
	);
}

float Vector3::Distance(const Vector3& a, const Vector3& b) {
	return (a - b).Magnitude();
}

float Vector3::Angle(const Vector3& from, const Vector3& to) {
	float denominator = Math::Sqrt(from.SqrMagnitude() * to.SqrMagnitude());
	if (denominator < Math::Epsilon) {
		return 0.0f;
	}
	float dot = Math::Clamp(Dot(from, to) / denominator, -1.0f, 1.0f);
	return Math::Acos(dot) * Math::Rad2Deg;
}

float Vector3::SignedAngle(const Vector3& from, const Vector3& to, const Vector3& axis) {
	float angle = Angle(from, to);
	Vector3 cross = Cross(from, to);
	float sign = Math::Sign(Dot(axis, cross));
	return angle * sign;
}

Vector3 Vector3::ClampMagnitude(const Vector3& vector, float maxLength) {
	float sqrMag = vector.SqrMagnitude();
	if (sqrMag > maxLength * maxLength) {
		float mag = Math::Sqrt(sqrMag);
		float normalizedX = vector.x / mag;
		float normalizedY = vector.y / mag;
		float normalizedZ = vector.z / mag;
		return Vector3(normalizedX * maxLength, normalizedY * maxLength, normalizedZ * maxLength);
	}
	return vector;
}

Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t) {
	t = Math::Clamp01(t);
	return Vector3(
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t
	);
}

Vector3 Vector3::LerpUnclamped(const Vector3& a, const Vector3& b, float t) {
	return Vector3(
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t
	);
}

Vector3 Vector3::Slerp(const Vector3& a, const Vector3& b, float t) {
	t = Math::Clamp01(t);
	return SlerpUnclamped(a, b, t);
}

Vector3 Vector3::SlerpUnclamped(const Vector3& a, const Vector3& b, float t) {
	float magA = a.Magnitude();
	float magB = b.Magnitude();

	if (magA < Math::Epsilon || magB < Math::Epsilon) {
		return LerpUnclamped(a, b, t);
	}

	Vector3 normA = a / magA;
	Vector3 normB = b / magB;

	float dot = Dot(normA, normB);
	dot = Math::Clamp(dot, -1.0f, 1.0f);

	float theta = Math::Acos(dot);
	if (theta < Math::Epsilon) {
		return LerpUnclamped(a, b, t);
	}

	float sinTheta = Math::Sin(theta);
	float w1 = Math::Sin((1.0f - t) * theta) / sinTheta;
	float w2 = Math::Sin(t * theta) / sinTheta;

	Vector3 resultDir = (normA * w1) + (normB * w2);
	float resultMag = Math::LerpUnclamped(magA, magB, t);

	return resultDir * resultMag;
}

Vector3 Vector3::Max(const Vector3& lhs, const Vector3& rhs) {
	return Vector3(Math::Max(lhs.x, rhs.x), Math::Max(lhs.y, rhs.y), Math::Max(lhs.z, rhs.z));
}

Vector3 Vector3::Min(const Vector3& lhs, const Vector3& rhs) {
	return Vector3(Math::Min(lhs.x, rhs.x), Math::Min(lhs.y, rhs.y), Math::Min(lhs.z, rhs.z));
}

Vector3 Vector3::MoveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta) {
	Vector3 toVector = target - current;
	float dist = toVector.Magnitude();

	if (dist <= maxDistanceDelta || dist < Math::Epsilon) {
		return target;
	}
	return current + toVector / dist * maxDistanceDelta;
}

Vector3 Vector3::Project(const Vector3& vector, const Vector3& onNormal) {
	float sqrMag = onNormal.SqrMagnitude();
	if (sqrMag < Math::Epsilon) {
		return Vector3::Zero();
	}
	float dot = Dot(vector, onNormal);
	return onNormal * (dot / sqrMag);
}

Vector3 Vector3::ProjectOnPlane(const Vector3& vector, const Vector3& planeNormal) {
	float sqrMag = planeNormal.SqrMagnitude();
	if (sqrMag < Math::Epsilon) {
		return vector;
	}
	float dot = Dot(vector, planeNormal);
	return vector - planeNormal * (dot / sqrMag);
}

Vector3 Vector3::Reflect(const Vector3& inDirection, const Vector3& inNormal) {
	float factor = -2.0f * Dot(inNormal, inDirection);
	return Vector3(
		factor * inNormal.x + inDirection.x,
		factor * inNormal.y + inDirection.y,
		factor * inNormal.z + inDirection.z
	);
}

Vector3 Vector3::Scale(const Vector3& a, const Vector3& b) {
	return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

void Vector3::OrthoNormalize(Vector3& normal, Vector3& tangent) {
	normal.Normalize();
	Vector3 proj = Project(tangent, normal);
	tangent = (tangent - proj).Normalized();
}

Vector3 Vector3::operator+(const Vector3& rhs) const {
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3 Vector3::operator-(const Vector3& rhs) const {
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3 Vector3::operator*(float d) const {
	return Vector3(x * d, y * d, z * d);
}

Vector3 Vector3::operator/(float d) const {
	return Vector3(x / d, y / d, z / d);
}

Vector3& Vector3::operator+=(const Vector3& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector3& Vector3::operator*=(float d) {
	x *= d;
	y *= d;
	z *= d;
	return *this;
}

Vector3& Vector3::operator/=(float d) {
	x /= d;
	y /= d;
	z /= d;
	return *this;
}

bool Vector3::operator==(const Vector3& rhs) const {
	return Math::Approximately(x, rhs.x) && Math::Approximately(y, rhs.y) && Math::Approximately(z, rhs.z);
}

bool Vector3::operator!=(const Vector3& rhs) const {
	return !(*this == rhs);
}

Vector3 Yaxl::operator*(float d, const Vector3& rhs) {
	return Vector3(rhs.x * d, rhs.y * d, rhs.z * d);
}
