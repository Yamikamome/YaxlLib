#include "YaxlMatrix3x3.h"

#include <cstring>
#include "YaxlMath.h"
#include "YaxlVector2.h"
#include "YaxlVector3.h"

using namespace Yaxl;

Matrix3x3::Matrix3x3() {
	std::memset(m_, 0, sizeof(float) * 9);
	m_[0] = 1.0f;
	m_[4] = 1.0f;
	m_[8] = 1.0f;
}

float Matrix3x3::Determinant() const {
	float det = m_[0] * (m_[4] * m_[8] - m_[7] * m_[5])
		- m_[3] * (m_[1] * m_[8] - m_[7] * m_[2])
		+ m_[6] * (m_[1] * m_[5] - m_[4] * m_[2]);
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
	res.m_[0] = (m_[4] * m_[8] - m_[5] * m_[7]) * invDet;
	res.m_[1] = -(m_[1] * m_[8] - m_[2] * m_[7]) * invDet;
	res.m_[2] = (m_[1] * m_[5] - m_[2] * m_[4]) * invDet;
	res.m_[3] = -(m_[3] * m_[8] - m_[5] * m_[6]) * invDet;
	res.m_[4] = (m_[0] * m_[8] - m_[2] * m_[6]) * invDet;
	res.m_[5] = -(m_[0] * m_[5] - m_[2] * m_[3]) * invDet;
	res.m_[6] = (m_[3] * m_[7] - m_[4] * m_[6]) * invDet;
	res.m_[7] = -(m_[0] * m_[7] - m_[1] * m_[6]) * invDet;
	res.m_[8] = (m_[0] * m_[4] - m_[1] * m_[3]) * invDet;

	return res;
}

Matrix3x3 Matrix3x3::Transpose() const {
	Matrix3x3 res;
	res.m_[0] = m_[0];
	res.m_[1] = m_[3];
	res.m_[2] = m_[6];
	res.m_[3] = m_[1];
	res.m_[4] = m_[4];
	res.m_[5] = m_[7];
	res.m_[6] = m_[2];
	res.m_[7] = m_[5];
	res.m_[8] = m_[8];
	return res;
}

Vector3 Matrix3x3::GetColumn(int index) const {
	int i = index * 3;
	return Vector3(m_[i], m_[i + 1], m_[i + 2]);
}

Vector3 Matrix3x3::GetRow(int index) const {
	return Vector3(m_[index], m_[index + 3], m_[index + 6]);
}

void Matrix3x3::SetColumn(int index, const Vector3& column) {
	int i = index * 3;
	m_[i] = column.x;
	m_[i + 1] = column.y;
	m_[i + 2] = column.z;
}

void Matrix3x3::SetRow(int index, const Vector3& row) {
	m_[index] = row.x;
	m_[index + 3] = row.y;
	m_[index + 6] = row.z;
}

Vector3 Matrix3x3::MultiplyVector(const Vector3& vector) const {
	Vector3 res;
	res.x = m_[0] * vector.x + m_[3] * vector.y + m_[6] * vector.z;
	res.y = m_[1] * vector.x + m_[4] * vector.y + m_[7] * vector.z;
	res.z = m_[2] * vector.x + m_[5] * vector.y + m_[8] * vector.z;
	return res;
}

Vector2 Matrix3x3::MultiplyPoint2D(const Vector2& point) const {
	Vector2 res;
	res.x = m_[0] * point.x + m_[3] * point.y + m_[6] * 1.0f;
	res.y = m_[1] * point.x + m_[4] * point.y + m_[7] * 1.0f;
	return res;
}

Vector2 Matrix3x3::MultiplyVector2D(const Vector2& vector) const {
	Vector2 res;
	res.x = m_[0] * vector.x + m_[3] * vector.y;
	res.y = m_[1] * vector.x + m_[4] * vector.y;
	return res;
}

Matrix3x3 Matrix3x3::Identity() {
	return Matrix3x3();
}

Matrix3x3 Matrix3x3::Zero() {
	Matrix3x3 res;
	std::memset(res.m_, 0, sizeof(float) * 9);
	return res;
}

Matrix3x3 Matrix3x3::TRS(const Vector2& pos, float rotation_degrees, const Vector2& scale) {
	Matrix3x3 res;
	float rad = rotation_degrees * Math::Deg2Rad;
	float s = Math::Sin(rad);
	float c = Math::Cos(rad);

	res.m_[0] = c * scale.x;
	res.m_[1] = s * scale.x;
	res.m_[2] = 0.0f;

	res.m_[3] = -s * scale.y;
	res.m_[4] = c * scale.y;
	res.m_[5] = 0.0f;

	res.m_[6] = pos.x;
	res.m_[7] = pos.y;
	res.m_[8] = 1.0f;

	return res;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& rhs) const {
	Matrix3x3 res;
	for (int c = 0; c < 3; ++c) {
		for (int r = 0; r < 3; ++r) {
			res.m_[c * 3 + r] =
				m_[0 * 3 + r] * rhs.m_[c * 3 + 0] +
				m_[1 * 3 + r] * rhs.m_[c * 3 + 1] +
				m_[2 * 3 + r] * rhs.m_[c * 3 + 2];
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
		if (Math::Approximately(m_[i], rhs.m_[i]) == false) {
			return false;
		}
	}
	return true;
}

bool Matrix3x3::operator!=(const Matrix3x3& rhs) const {
	return !(*this == rhs);
}
