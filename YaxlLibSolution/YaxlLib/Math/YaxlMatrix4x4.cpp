#include "YaxlMatrix4x4.h"

#include <cstring>
#include "YaxlVector3.h"
#include "YaxlVector4.h"
#include "YaxlQuaternion.h"
#include "YaxlMath.h"

using namespace Yaxl;

Matrix4x4::Matrix4x4() {
	std::memset(m_, 0, sizeof(float) * 16);
	m_[0] = 1.0f;
	m_[5] = 1.0f;
	m_[10] = 1.0f;
	m_[15] = 1.0f;
}

float Matrix4x4::Determinant() const {
	float det =
		m_[3] * m_[6] * m_[9] * m_[12] - m_[2] * m_[7] * m_[9] * m_[12] -
		m_[3] * m_[5] * m_[10] * m_[12] + m_[1] * m_[7] * m_[10] * m_[12] +
		m_[2] * m_[5] * m_[11] * m_[12] - m_[1] * m_[6] * m_[11] * m_[12] -
		m_[3] * m_[6] * m_[8] * m_[13] + m_[2] * m_[7] * m_[8] * m_[13] +
		m_[3] * m_[4] * m_[10] * m_[13] - m_[0] * m_[7] * m_[10] * m_[13] -
		m_[2] * m_[4] * m_[11] * m_[13] + m_[0] * m_[6] * m_[11] * m_[13] +
		m_[3] * m_[5] * m_[8] * m_[14] - m_[1] * m_[7] * m_[8] * m_[14] -
		m_[3] * m_[4] * m_[9] * m_[14] + m_[0] * m_[7] * m_[9] * m_[14] +
		m_[1] * m_[4] * m_[11] * m_[14] - m_[0] * m_[5] * m_[11] * m_[14] -
		m_[2] * m_[5] * m_[8] * m_[15] + m_[1] * m_[6] * m_[8] * m_[15] +
		m_[2] * m_[4] * m_[9] * m_[15] - m_[0] * m_[6] * m_[9] * m_[15] -
		m_[1] * m_[4] * m_[10] * m_[15] + m_[0] * m_[5] * m_[10] * m_[15];
	return det;
}

Matrix4x4 Matrix4x4::Inverse() const {
	Matrix4x4 inv;

	inv.m_[0] = m_[5] * m_[10] * m_[15] - m_[5] * m_[11] * m_[14] - m_[9] * m_[6] * m_[15] + m_[9] * m_[7] * m_[14] + m_[13] * m_[6] * m_[11] - m_[13] * m_[7] * m_[10];
	inv.m_[4] = -m_[4] * m_[10] * m_[15] + m_[4] * m_[11] * m_[14] + m_[8] * m_[6] * m_[15] - m_[8] * m_[7] * m_[14] - m_[12] * m_[6] * m_[11] + m_[12] * m_[7] * m_[10];
	inv.m_[8] = m_[4] * m_[9] * m_[15] - m_[4] * m_[11] * m_[13] - m_[8] * m_[5] * m_[15] + m_[8] * m_[7] * m_[13] + m_[12] * m_[5] * m_[11] - m_[12] * m_[7] * m_[9];
	inv.m_[12] = -m_[4] * m_[9] * m_[14] + m_[4] * m_[10] * m_[13] + m_[8] * m_[5] * m_[14] - m_[8] * m_[6] * m_[13] - m_[12] * m_[5] * m_[10] + m_[12] * m_[6] * m_[9];
	inv.m_[1] = -m_[1] * m_[10] * m_[15] + m_[1] * m_[11] * m_[14] + m_[9] * m_[2] * m_[15] - m_[9] * m_[3] * m_[14] - m_[13] * m_[2] * m_[11] + m_[13] * m_[3] * m_[10];
	inv.m_[5] = m_[0] * m_[10] * m_[15] - m_[0] * m_[11] * m_[14] - m_[8] * m_[2] * m_[15] + m_[8] * m_[3] * m_[14] + m_[12] * m_[2] * m_[11] - m_[12] * m_[3] * m_[10];
	inv.m_[9] = -m_[0] * m_[9] * m_[15] + m_[0] * m_[11] * m_[13] + m_[8] * m_[1] * m_[15] - m_[8] * m_[3] * m_[13] - m_[12] * m_[1] * m_[11] + m_[12] * m_[3] * m_[9];
	inv.m_[13] = m_[0] * m_[9] * m_[14] - m_[0] * m_[10] * m_[13] - m_[8] * m_[1] * m_[14] + m_[8] * m_[2] * m_[13] + m_[12] * m_[1] * m_[10] - m_[12] * m_[2] * m_[9];
	inv.m_[2] = m_[1] * m_[6] * m_[15] - m_[1] * m_[7] * m_[14] - m_[5] * m_[2] * m_[15] + m_[5] * m_[3] * m_[14] + m_[13] * m_[2] * m_[7] - m_[13] * m_[3] * m_[6];
	inv.m_[6] = -m_[0] * m_[6] * m_[15] + m_[0] * m_[7] * m_[14] + m_[4] * m_[2] * m_[15] - m_[4] * m_[3] * m_[14] - m_[12] * m_[2] * m_[7] + m_[12] * m_[3] * m_[6];
	inv.m_[10] = m_[0] * m_[5] * m_[15] - m_[0] * m_[7] * m_[13] - m_[4] * m_[1] * m_[15] + m_[4] * m_[3] * m_[13] + m_[12] * m_[1] * m_[7] - m_[12] * m_[3] * m_[5];
	inv.m_[14] = -m_[0] * m_[5] * m_[14] + m_[0] * m_[6] * m_[13] + m_[4] * m_[1] * m_[14] - m_[4] * m_[2] * m_[13] - m_[12] * m_[1] * m_[6] + m_[12] * m_[2] * m_[5];
	inv.m_[3] = -m_[1] * m_[6] * m_[11] + m_[1] * m_[7] * m_[10] + m_[5] * m_[2] * m_[11] - m_[5] * m_[3] * m_[10] - m_[9] * m_[2] * m_[7] + m_[9] * m_[3] * m_[6];
	inv.m_[7] = m_[0] * m_[6] * m_[11] - m_[0] * m_[7] * m_[10] - m_[4] * m_[2] * m_[11] + m_[4] * m_[3] * m_[10] + m_[8] * m_[2] * m_[7] - m_[8] * m_[3] * m_[6];
	inv.m_[11] = -m_[0] * m_[5] * m_[11] + m_[0] * m_[7] * m_[9] + m_[4] * m_[1] * m_[11] - m_[4] * m_[3] * m_[9] - m_[8] * m_[1] * m_[7] + m_[8] * m_[3] * m_[5];
	inv.m_[15] = m_[0] * m_[5] * m_[10] - m_[0] * m_[6] * m_[9] - m_[4] * m_[1] * m_[10] + m_[4] * m_[2] * m_[9] + m_[8] * m_[1] * m_[6] - m_[8] * m_[2] * m_[5];

	float det = m_[0] * inv.m_[0] + m_[1] * inv.m_[4] + m_[2] * inv.m_[8] + m_[3] * inv.m_[12];

	if (Math::Abs(det) < Math::Epsilon) {
		return Matrix4x4::Zero();
	}

	float invDet = 1.0f / det;
	for (int i = 0; i < 16; ++i) {
		inv.m_[i] *= invDet;
	}

	return inv;
}

Matrix4x4 Matrix4x4::Transpose() const {
	Matrix4x4 res;
	res.m_[0] = m_[0];   res.m_[4] = m_[1];   res.m_[8] = m_[2];   res.m_[12] = m_[3];
	res.m_[1] = m_[4];   res.m_[5] = m_[5];   res.m_[9] = m_[6];   res.m_[13] = m_[7];
	res.m_[2] = m_[8];   res.m_[6] = m_[9];   res.m_[10] = m_[10]; res.m_[14] = m_[11];
	res.m_[3] = m_[12];  res.m_[7] = m_[13];  res.m_[11] = m_[14]; res.m_[15] = m_[15];
	return res;
}

Vector4 Matrix4x4::GetColumn(int index) const {
	int i = index * 4;
	return Vector4(m_[i], m_[i + 1], m_[i + 2], m_[i + 3]);
}

Vector4 Matrix4x4::GetRow(int index) const {
	return Vector4(m_[index], m_[index + 4], m_[index + 8], m_[index + 12]);
}

void Matrix4x4::SetColumn(int index, const Vector4& column) {
	int i = index * 4;
	m_[i] = column.x;
	m_[i + 1] = column.y;
	m_[i + 2] = column.z;
	m_[i + 3] = column.w;
}

void Matrix4x4::SetRow(int index, const Vector4& row) {
	m_[index] = row.x;
	m_[index + 4] = row.y;
	m_[index + 8] = row.z;
	m_[index + 12] = row.w;
}

Vector3 Matrix4x4::MultiplyPoint(const Vector3& point) const {
	Vector3 res;
	float w = m_[3] * point.x + m_[7] * point.y + m_[11] * point.z + m_[15];

	res.x = (m_[0] * point.x + m_[4] * point.y + m_[8] * point.z + m_[12]) / w;
	res.y = (m_[1] * point.x + m_[5] * point.y + m_[9] * point.z + m_[13]) / w;
	res.z = (m_[2] * point.x + m_[6] * point.y + m_[10] * point.z + m_[14]) / w;

	return res;
}

Vector3 Matrix4x4::MultiplyPoint3x4(const Vector3& point) const {
	Vector3 res;
	res.x = m_[0] * point.x + m_[4] * point.y + m_[8] * point.z + m_[12];
	res.y = m_[1] * point.x + m_[5] * point.y + m_[9] * point.z + m_[13];
	res.z = m_[2] * point.x + m_[6] * point.y + m_[10] * point.z + m_[14];
	return res;
}

Vector3 Matrix4x4::MultiplyVector(const Vector3& vector) const {
	Vector3 res;
	res.x = m_[0] * vector.x + m_[4] * vector.y + m_[8] * vector.z;
	res.y = m_[1] * vector.x + m_[5] * vector.y + m_[9] * vector.z;
	res.z = m_[2] * vector.x + m_[6] * vector.y + m_[10] * vector.z;
	return res;
}

Matrix4x4 Matrix4x4::Identity() {
	return Matrix4x4();
}

Matrix4x4 Matrix4x4::Zero() {
	Matrix4x4 res;
	std::memset(res.m_, 0, sizeof(float) * 16);
	return res;
}

Matrix4x4 Matrix4x4::Translate(const Vector3& vector) {
	Matrix4x4 res;
	res.m_[12] = vector.x;
	res.m_[13] = vector.y;
	res.m_[14] = vector.z;
	return res;
}

Matrix4x4 Matrix4x4::Rotate(const Quaternion& q) {
	Matrix4x4 res;

	float xx = q.x * q.x;
	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float xw = q.x * q.w;

	float yy = q.y * q.y;
	float yz = q.y * q.z;
	float yw = q.y * q.w;

	float zz = q.z * q.z;
	float zw = q.z * q.w;

	res.m_[0] = 1.0f - 2.0f * (yy + zz);
	res.m_[1] = 2.0f * (xy + zw);
	res.m_[2] = 2.0f * (xz - yw);
	res.m_[3] = 0.0f;

	res.m_[4] = 2.0f * (xy - zw);
	res.m_[5] = 1.0f - 2.0f * (xx + zz);
	res.m_[6] = 2.0f * (yz + xw);
	res.m_[7] = 0.0f;

	res.m_[8] = 2.0f * (xz + yw);
	res.m_[9] = 2.0f * (yz - xw);
	res.m_[10] = 1.0f - 2.0f * (xx + yy);
	res.m_[11] = 0.0f;

	res.m_[12] = 0.0f;
	res.m_[13] = 0.0f;
	res.m_[14] = 0.0f;
	res.m_[15] = 1.0f;

	return res;
}

Matrix4x4 Matrix4x4::Scale(const Vector3& vector) {
	Matrix4x4 res;
	res.m_[0] = vector.x;
	res.m_[5] = vector.y;
	res.m_[10] = vector.z;
	return res;
}

Matrix4x4 Matrix4x4::TRS(const Vector3& pos, const Vector3& euler, const Vector3& scale) {
	return TRS(pos, Quaternion::Euler(euler), scale);;
}

Matrix4x4 Matrix4x4::TRS(const Vector3& pos, const Quaternion& q, const Vector3& scale) {
	Matrix4x4 res;

	float xx = q.x * q.x;
	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float xw = q.x * q.w;

	float yy = q.y * q.y;
	float yz = q.y * q.z;
	float yw = q.y * q.w;

	float zz = q.z * q.z;
	float zw = q.z * q.w;

	res.m_[0] = (1.0f - 2.0f * (yy + zz)) * scale.x;
	res.m_[1] = (2.0f * (xy + zw)) * scale.x;
	res.m_[2] = (2.0f * (xz - yw)) * scale.x;
	res.m_[3] = 0.0f;

	res.m_[4] = (2.0f * (xy - zw)) * scale.y;
	res.m_[5] = (1.0f - 2.0f * (xx + zz)) * scale.y;
	res.m_[6] = (2.0f * (yz + xw)) * scale.y;
	res.m_[7] = 0.0f;

	res.m_[8] = (2.0f * (xz + yw)) * scale.z;
	res.m_[9] = (2.0f * (yz - xw)) * scale.z;
	res.m_[10] = (1.0f - 2.0f * (xx + yy)) * scale.z;
	res.m_[11] = 0.0f;

	res.m_[12] = pos.x;
	res.m_[13] = pos.y;
	res.m_[14] = pos.z;
	res.m_[15] = 1.0f;

	return res;
}

Matrix4x4 Matrix4x4::Ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
	Matrix4x4 res = Matrix4x4::Zero();

	res.m_[0] = 2.0f / (right - left);
	res.m_[5] = 2.0f / (top - bottom);
	res.m_[10] = -2.0f / (zFar - zNear);
	res.m_[15] = 1.0f;

	res.m_[12] = -(right + left) / (right - left);
	res.m_[13] = -(top + bottom) / (top - bottom);
	res.m_[14] = -(zFar + zNear) / (zFar - zNear);

	return res;
}

Matrix4x4 Matrix4x4::Perspective(float fov, float aspect, float zNear, float zFar) {
	Matrix4x4 res = Matrix4x4::Zero();

	float tanHalfFov = Math::Tan(fov * 0.5f * Math::Deg2Rad);

	res.m_[0] = 1.0f / (aspect * tanHalfFov);
	res.m_[5] = 1.0f / (tanHalfFov);
	res.m_[10] = -(zFar + zNear) / (zFar - zNear);
	res.m_[11] = -1.0f;
	res.m_[14] = -(2.0f * zFar * zNear) / (zFar - zNear);

	return res;
}

Matrix4x4 Matrix4x4::LookAt(const Vector3& eye, const Vector3& target, const Vector3& up) {
	Vector3 zAxis = (eye - target).Normalized();
	Vector3 xAxis = Vector3::Cross(up, zAxis).Normalized();
	Vector3 yAxis = Vector3::Cross(zAxis, xAxis);

	Matrix4x4 res;
	res.m_[0] = xAxis.x;
	res.m_[4] = xAxis.y;
	res.m_[8] = xAxis.z;
	res.m_[12] = -Vector3::Dot(xAxis, eye);

	res.m_[1] = yAxis.x;
	res.m_[5] = yAxis.y;
	res.m_[9] = yAxis.z;
	res.m_[13] = -Vector3::Dot(yAxis, eye);

	res.m_[2] = zAxis.x;
	res.m_[6] = zAxis.y;
	res.m_[10] = zAxis.z;
	res.m_[14] = -Vector3::Dot(zAxis, eye);

	res.m_[3] = 0.0f;
	res.m_[7] = 0.0f;
	res.m_[11] = 0.0f;
	res.m_[15] = 1.0f;

	return res;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const {
	Matrix4x4 res;
	for (int c = 0; c < 4; ++c) {
		for (int r = 0; r < 4; ++r) {
			res.m_[c * 4 + r] =
				m_[0 * 4 + r] * rhs.m_[c * 4 + 0] +
				m_[1 * 4 + r] * rhs.m_[c * 4 + 1] +
				m_[2 * 4 + r] * rhs.m_[c * 4 + 2] +
				m_[3 * 4 + r] * rhs.m_[c * 4 + 3];
		}
	}
	return res;
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs) {
	*this = *this * rhs;
	return *this;
}

bool Matrix4x4::operator==(const Matrix4x4& rhs) const {
	for (int i = 0; i < 16; ++i) {
		if (Math::Approximately(m_[i], rhs.m_[i]) == false) {
			return false;
		}
	}
	return true;
}

bool Matrix4x4::operator!=(const Matrix4x4& rhs) const {
	return !(*this == rhs);
}
