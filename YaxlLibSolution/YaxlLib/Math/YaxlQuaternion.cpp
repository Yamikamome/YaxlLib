#include "YaxlQuaternion.h"

#include "YaxlMath.h"
#include "YaxlVector3.h"

using namespace Yaxl;

Quaternion::Quaternion() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Quaternion::Quaternion(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Quaternion::Set(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Quaternion::Magnitude() const {
	return Math::Sqrt(x * x + y * y + z * z + w * w);
}

float Quaternion::SqrMagnitude() const {
	return x * x + y * y + z * z + w * w;
}

Quaternion Quaternion::Normalized() const {
	float mag = Magnitude();
	if (mag > Math::Epsilon) {
		return Quaternion(x / mag, y / mag, z / mag, w / mag);
	}
	return Quaternion::Identity();
}

void Quaternion::Normalize() {
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
		w = 1.0f;
	}
}

Vector3 Quaternion::EulerAngles() const {
	float sinr_cosp = 2.0f * (w * x + y * z);
	float cosr_cosp = 1.0f - 2.0f * (x * x + y * y);
	float pitch = Math::Atan2(sinr_cosp, cosr_cosp);

	float sinp = 2.0f * (w * y - z * x);
	float yaw = 0.0f;
	if (Math::Abs(sinp) >= 1.0f) {
		yaw = Math::Sign(sinp) * (Math::PI / 2.0f);
	}
	else {
		yaw = Math::Asin(sinp);
	}

	float sinycosp = 2.0f * (w * z + x * y);
	float cosycosp = 1.0f - 2.0f * (y * y + z * z);
	float roll = Math::Atan2(sinycosp, cosycosp);

	return Vector3(pitch * Math::Rad2Deg, yaw * Math::Rad2Deg, roll * Math::Rad2Deg);
}

void Quaternion::ToAngleAxis(float& angle, Vector3& axis) const {
	Quaternion q = Normalized();
	if (q.w > 1.0f) {
		q.Normalize();
	}

	angle = 2.0f * Math::Acos(q.w) * Math::Rad2Deg;
	float s = Math::Sqrt(1.0f - q.w * q.w);

	if (s < 0.001f) {
		axis.x = q.x;
		axis.y = q.y;
		axis.z = q.z;
	}
	else {
		axis.x = q.x / s;
		axis.y = q.y / s;
		axis.z = q.z / s;
	}
}

Quaternion Quaternion::Identity() {
	return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

float Quaternion::Angle(const Quaternion& a, const Quaternion& b) {
	float dot = Dot(a, b);
	float acosValue = Math::Acos(Math::Min(Math::Abs(dot), 1.0f));
	return acosValue * 2.0f * Math::Rad2Deg;
}

Quaternion Quaternion::AngleAxis(float angle, const Vector3& axis) {
	Vector3 normAxis = axis.Normalized();
	float rad = angle * Math::Deg2Rad * 0.5f;
	float s = Math::Sin(rad);

	return Quaternion(
		normAxis.x * s,
		normAxis.y * s,
		normAxis.z * s,
		Math::Cos(rad)
	);
}

float Quaternion::Dot(const Quaternion& a, const Quaternion& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Quaternion Quaternion::Euler(float x, float y, float z) {
	float radX = x * Math::Deg2Rad * 0.5f;
	float radY = y * Math::Deg2Rad * 0.5f;
	float radZ = z * Math::Deg2Rad * 0.5f;

	float cX = Math::Cos(radX);
	float sX = Math::Sin(radX);
	float cY = Math::Cos(radY);
	float sY = Math::Sin(radY);
	float cZ = Math::Cos(radZ);
	float sZ = Math::Sin(radZ);

	Quaternion q;
	q.w = cY * cX * cZ + sY * sX * sZ;
	q.x = cY * sX * cZ + sY * cX * sZ;
	q.y = sY * cX * cZ - cY * sX * sZ;
	q.z = cY * cX * sZ - sY * sX * cZ;

	return q;
}

Quaternion Quaternion::Euler(const Vector3& euler) {
	return Euler(euler.x, euler.y, euler.z);
}

Quaternion Quaternion::FromToRotation(const Vector3& fromDirection, const Vector3& toDirection) {
	Vector3 from = fromDirection.Normalized();
	Vector3 to = toDirection.Normalized();

	float dot = Vector3::Dot(from, to);
	if (dot >= 1.0f - Math::Epsilon) {
		return Quaternion::Identity();
	}

	if (dot <= -1.0f + Math::Epsilon) {
		Vector3 axis = Vector3::Cross(Vector3::Right(), from);
		if (axis.SqrMagnitude() < Math::Epsilon) {
			axis = Vector3::Cross(Vector3::Up(), from);
		}
		axis.Normalize();
		return AngleAxis(180.0f, axis);
	}

	Vector3 cross = Vector3::Cross(from, to);
	Quaternion q(cross.x, cross.y, cross.z, dot + 1.0f);
	q.Normalize();
	return q;
}

Quaternion Quaternion::Inverse(const Quaternion& rotation) {
	return Quaternion(-rotation.x, -rotation.y, -rotation.z, rotation.w);
}

Quaternion Quaternion::LerpUnclamped(const Quaternion& a, const Quaternion& b, float t) {
	Quaternion res;
	float dot = Dot(a, b);
	float sign = 1.0f;

	if (dot < 0.0f) {
		sign = -1.0f;
	}

	res.x = a.x + t * (b.x * sign - a.x);
	res.y = a.y + t * (b.y * sign - a.y);
	res.z = a.z + t * (b.z * sign - a.z);
	res.w = a.w + t * (b.w * sign - a.w);

	res.Normalize();
	return res;
}

Quaternion Quaternion::Lerp(const Quaternion& a, const Quaternion& b, float t) {
	return LerpUnclamped(a, b, Math::Clamp01(t));
}

Quaternion Quaternion::SlerpUnclamped(const Quaternion& a, const Quaternion& b, float t) {
	float dot = Dot(a, b);
	Quaternion target = b;

	if (dot < 0.0f) {
		dot = -dot;
		target.x = -b.x;
		target.y = -b.y;
		target.z = -b.z;
		target.w = -b.w;
	}

	if (dot > 0.9995f) {
		return LerpUnclamped(a, target, t);
	}

	float theta_0 = Math::Acos(dot);
	float theta = theta_0 * t;
	float sin_theta = Math::Sin(theta);
	float sin_theta_0 = Math::Sin(theta_0);

	float s0 = Math::Cos(theta) - dot * sin_theta / sin_theta_0;
	float s1 = sin_theta / sin_theta_0;

	return Quaternion(
		a.x * s0 + target.x * s1,
		a.y * s0 + target.y * s1,
		a.z * s0 + target.z * s1,
		a.w * s0 + target.w * s1
	);
}

Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, float t) {
	return SlerpUnclamped(a, b, Math::Clamp01(t));
}

Quaternion Quaternion::RotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta) {
	float angle = Angle(from, to);
	if (angle == 0.0f) {
		return to;
	}
	return SlerpUnclamped(from, to, Math::Min(1.0f, maxDegreesDelta / angle));
}

Quaternion Quaternion::LookRotation(const Vector3& forward, const Vector3& upwards) {
	Vector3 forwardNorm = forward.Normalized();
	Vector3 rightNorm = Vector3::Cross(upwards, forwardNorm).Normalized();
	Vector3 upNorm = Vector3::Cross(forwardNorm, rightNorm);

	float m00 = rightNorm.x; float m01 = upNorm.x; float m02 = forwardNorm.x;
	float m10 = rightNorm.y; float m11 = upNorm.y; float m12 = forwardNorm.y;
	float m20 = rightNorm.z; float m21 = upNorm.z; float m22 = forwardNorm.z;

	float num8 = (m00 + m11) + m22;
	Quaternion q;

	if (num8 > 0.0f) {
		float num = Math::Sqrt(num8 + 1.0f);
		q.w = num * 0.5f;
		num = 0.5f / num;
		q.x = (m12 - m21) * num;
		q.y = (m20 - m02) * num;
		q.z = (m01 - m10) * num;
		return q;
	}

	if ((m00 >= m11) && (m00 >= m22)) {
		float num7 = Math::Sqrt(((1.0f + m00) - m11) - m22);
		float num4 = 0.5f / num7;
		q.x = 0.5f * num7;
		q.y = (m01 + m10) * num4;
		q.z = (m02 + m20) * num4;
		q.w = (m12 - m21) * num4;
		return q;
	}

	if (m11 > m22) {
		float num6 = Math::Sqrt(((1.0f + m11) - m00) - m22);
		float num3 = 0.5f / num6;
		q.x = (m10 + m01) * num3;
		q.y = 0.5f * num6;
		q.z = (m21 + m12) * num3;
		q.w = (m20 - m02) * num3;
		return q;
	}

	float num5 = Math::Sqrt(((1.0f + m22) - m00) - m11);
	float num2 = 0.5f / num5;
	q.x = (m20 + m02) * num2;
	q.y = (m21 + m12) * num2;
	q.z = 0.5f * num5;
	q.w = (m01 - m10) * num2;
	return q;
}

Quaternion Quaternion::operator*(const Quaternion& rhs) const {
	return Quaternion(
		w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
		w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z,
		w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x,
		w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z
	);
}

Vector3 Quaternion::operator*(const Vector3& point) const {
	Vector3 qVec(x, y, z);
	Vector3 cross1 = Vector3::Cross(qVec, point);
	Vector3 cross2 = Vector3::Cross(qVec, cross1);

	return point + (cross1 * w + cross2) * 2.0f;
}

Quaternion& Quaternion::operator*=(const Quaternion& rhs) {
	*this = *this * rhs;
	return *this;
}

bool Quaternion::operator==(const Quaternion& rhs) const {
	return Math::Approximately(x, rhs.x) &&
		Math::Approximately(y, rhs.y) &&
		Math::Approximately(z, rhs.z) &&
		Math::Approximately(w, rhs.w);
}

bool Quaternion::operator!=(const Quaternion& rhs) const {
	return !(*this == rhs);
}
