#include "YaxlMatrix3x3.h"

#include <cstring>
#include "YaxlMath.h"
#include "YaxlVector2.h"
#include "YaxlVector3.h"

using namespace Yaxl;

Matrix3x3::Matrix3x3() {
	std::memset(m, 0, sizeof(float) * 9);
	m[0] = 1.0f;
	m[4] = 1.0f;
	m[8] = 1.0f;
}

float Matrix3x3::Determinant() const {
	float det = m[0] * (m[4] * m[8] - m[7] * m[5])
		- m[3] * (m[1] * m[8] - m[7] * m[2])
		+ m[6] * (m[1] * m[5] - m[4] * m[2]);
	return det;
}

Matrix3x3 Matrix3x3::Inverse() const {
	float det = Determinant();
	if (Math::Abs(det) < Math::Epsilon) {
		return Matrix3x3::Zero();
	}

	float invDet = 1.0f / det;
	Matrix3x3 res;

	// 余因子行列の転置を計算して行列式で割る
	res.m[0] = (m[4] * m[8] - m[5] * m[7]) * invDet;
	res.m[1] = -(m[1] * m[8] - m[2] * m[7]) * invDet;
	res.m[2] = (m[1] * m[5] - m[2] * m[4]) * invDet;
	res.m[3] = -(m[3] * m[8] - m[5] * m[6]) * invDet;
	res.m[4] = (m[0] * m[8] - m[2] * m[6]) * invDet;
	res.m[5] = -(m[0] * m[5] - m[2] * m[3]) * invDet;
	res.m[6] = (m[3] * m[7] - m[4] * m[6]) * invDet;
	res.m[7] = -(m[0] * m[7] - m[1] * m[6]) * invDet;
	res.m[8] = (m[0] * m[4] - m[1] * m[3]) * invDet;

	return res;
}

Matrix3x3 Matrix3x3::Transpose() const {
	Matrix3x3 res;
	res.m[0] = m[0];
	res.m[1] = m[3];
	res.m[2] = m[6];
	res.m[3] = m[1];
	res.m[4] = m[4];
	res.m[5] = m[7];
	res.m[6] = m[2];
	res.m[7] = m[5];
	res.m[8] = m[8];
	return res;
}

Vector3 Matrix3x3::GetColumn(int index) const {
	int i = index * 3;
	return Vector3(m[i], m[i + 1], m[i + 2]);
}

Vector3 Matrix3x3::GetRow(int index) const {
	return Vector3(m[index], m[index + 3], m[index + 6]);
}

void Matrix3x3::SetColumn(int index, const Vector3& column) {
	int i = index * 3;
	m[i] = column.x;
	m[i + 1] = column.y;
	m[i + 2] = column.z;
}

void Matrix3x3::SetRow(int index, const Vector3& row) {
	m[index] = row.x;
	m[index + 3] = row.y;
	m[index + 6] = row.z;
}

Vector3 Matrix3x3::MultiplyVector(const Vector3& vector) const {
	Vector3 res;
	res.x = m[0] * vector.x + m[3] * vector.y + m[6] * vector.z;
	res.y = m[1] * vector.x + m[4] * vector.y + m[7] * vector.z;
	res.z = m[2] * vector.x + m[5] * vector.y + m[8] * vector.z;
	return res;
}

Vector2 Matrix3x3::MultiplyPoint2D(const Vector2& point) const {
	Vector2 res;
	res.x = m[0] * point.x + m[3] * point.y + m[6] * 1.0f;
	res.y = m[1] * point.x + m[4] * point.y + m[7] * 1.0f;
	return res;
}

Vector2 Matrix3x3::MultiplyVector2D(const Vector2& vector) const {
	Vector2 res;
	res.x = m[0] * vector.x + m[3] * vector.y;
	res.y = m[1] * vector.x + m[4] * vector.y;
	return res;
}

Vector2 Yaxl::Matrix3x3::GetPosition() const {
	return Vector2(m[6], m[7]);
}

void Yaxl::Matrix3x3::SetPosition(const Vector2& value) {
	m[6] = value.x;
	m[7] = value.y;
}

float Yaxl::Matrix3x3::GetRotation() const {
	Vector2 scale = GetScale();

	// スケール0対策
	if (Math::Approximately(scale.x, 0.0f)) {
		return 0.0f;
	}

	float cos_theta = m[0] / scale.x;
	float sin_theta = m[1] / scale.x;

	return Math::Atan2(sin_theta, cos_theta) * Math::Rad2Deg;
}

void Yaxl::Matrix3x3::SetRotation(float degrees) {
	SetTRS(GetPosition(), degrees, GetScale());
}

Vector2 Yaxl::Matrix3x3::GetScale() const {
	return Vector2(Vector2(m[0], m[1]).Magnitude(), Vector2(m[3], m[4]).Magnitude());
}

void Yaxl::Matrix3x3::SetScale(const Vector2& value) {
	SetTRS(GetPosition(), GetRotation(), value);
}

void Yaxl::Matrix3x3::SetTRS(const Vector2& pos, float degrees, const Vector2& scale) {
	*this = Matrix3x3::TRS(pos, degrees, scale);
}

Matrix3x3 Matrix3x3::Identity() {
	return Matrix3x3();
}

Matrix3x3 Matrix3x3::Zero() {
	Matrix3x3 res;
	std::memset(res.m, 0, sizeof(float) * 9);
	return res;
}

Matrix3x3 Matrix3x3::TRS(const Vector2& pos, float rotation_degrees, const Vector2& scale) {
	Matrix3x3 res;
	float rad = rotation_degrees * Math::Deg2Rad;
	float s = Math::Sin(rad);
	float c = Math::Cos(rad);

	res.m[0] = c * scale.x;
	res.m[1] = s * scale.x;
	res.m[2] = 0.0f;

	res.m[3] = -s * scale.y;
	res.m[4] = c * scale.y;
	res.m[5] = 0.0f;

	res.m[6] = pos.x;
	res.m[7] = pos.y;
	res.m[8] = 1.0f;

	return res;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& rhs) const {
	Matrix3x3 res;
	for (int c = 0; c < 3; ++c) {
		for (int r = 0; r < 3; ++r) {
			res.m[c * 3 + r] =
				m[0 * 3 + r] * rhs.m[c * 3 + 0] +
				m[1 * 3 + r] * rhs.m[c * 3 + 1] +
				m[2 * 3 + r] * rhs.m[c * 3 + 2];
		}
	}
	return res;
}

Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& rhs) {
	*this = *this * rhs;
	return *this;
}

bool Matrix3x3::operator==(const Matrix3x3& rhs) const {
	for (int i = 0; i < 9; ++i) {
		if (Math::Approximately(m[i], rhs.m[i]) == false) {
			return false;
		}
	}
	return true;
}

bool Matrix3x3::operator!=(const Matrix3x3& rhs) const {
	return !(*this == rhs);
}
