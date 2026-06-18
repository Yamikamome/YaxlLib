#include "YaxlMatrix4x4.h"

#include <cstring>
#include "YaxlVector3.h"
#include "YaxlVector4.h"
#include "YaxlQuaternion.h"
#include "YaxlMath.h"

using namespace Yaxl;

Matrix4x4::Matrix4x4() {
	std::memset(m, 0, sizeof(float) * 16);
	m[0] = 1.0f;
	m[5] = 1.0f;
	m[10] = 1.0f;
	m[15] = 1.0f;
}

float Matrix4x4::Determinant() const {
	float det =
		m[3] * m[6] * m[9] * m[12] - m[2] * m[7] * m[9] * m[12] -
		m[3] * m[5] * m[10] * m[12] + m[1] * m[7] * m[10] * m[12] +
		m[2] * m[5] * m[11] * m[12] - m[1] * m[6] * m[11] * m[12] -
		m[3] * m[6] * m[8] * m[13] + m[2] * m[7] * m[8] * m[13] +
		m[3] * m[4] * m[10] * m[13] - m[0] * m[7] * m[10] * m[13] -
		m[2] * m[4] * m[11] * m[13] + m[0] * m[6] * m[11] * m[13] +
		m[3] * m[5] * m[8] * m[14] - m[1] * m[7] * m[8] * m[14] -
		m[3] * m[4] * m[9] * m[14] + m[0] * m[7] * m[9] * m[14] +
		m[1] * m[4] * m[11] * m[14] - m[0] * m[5] * m[11] * m[14] -
		m[2] * m[5] * m[8] * m[15] + m[1] * m[6] * m[8] * m[15] +
		m[2] * m[4] * m[9] * m[15] - m[0] * m[6] * m[9] * m[15] -
		m[1] * m[4] * m[10] * m[15] + m[0] * m[5] * m[10] * m[15];
	return det;
}

Matrix4x4 Matrix4x4::Inverse() const {
	Matrix4x4 inv;

	inv.m[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
	inv.m[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
	inv.m[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
	inv.m[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
	inv.m[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
	inv.m[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
	inv.m[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
	inv.m[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
	inv.m[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
	inv.m[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
	inv.m[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
	inv.m[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
	inv.m[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
	inv.m[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
	inv.m[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
	inv.m[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

	float det = m[0] * inv.m[0] + m[1] * inv.m[4] + m[2] * inv.m[8] + m[3] * inv.m[12];

	if (Math::Abs(det) < Math::Epsilon) {
		return Matrix4x4::Zero();
	}

	float invDet = 1.0f / det;
	for (int i = 0; i < 16; ++i) {
		inv.m[i] *= invDet;
	}

	return inv;
}

Matrix4x4 Matrix4x4::Transpose() const {
	Matrix4x4 res;
	res.m[0] = m[0];   res.m[4] = m[1];   res.m[8] = m[2];   res.m[12] = m[3];
	res.m[1] = m[4];   res.m[5] = m[5];   res.m[9] = m[6];   res.m[13] = m[7];
	res.m[2] = m[8];   res.m[6] = m[9];   res.m[10] = m[10]; res.m[14] = m[11];
	res.m[3] = m[12];  res.m[7] = m[13];  res.m[11] = m[14]; res.m[15] = m[15];
	return res;
}

Vector4 Matrix4x4::GetColumn(int index) const {
	int i = index * 4;
	return Vector4(m[i], m[i + 1], m[i + 2], m[i + 3]);
}

Vector4 Matrix4x4::GetRow(int index) const {
	return Vector4(m[index], m[index + 4], m[index + 8], m[index + 12]);
}

void Matrix4x4::SetColumn(int index, const Vector4& column) {
	int i = index * 4;
	m[i] = column.x;
	m[i + 1] = column.y;
	m[i + 2] = column.z;
	m[i + 3] = column.w;
}

void Matrix4x4::SetRow(int index, const Vector4& row) {
	m[index] = row.x;
	m[index + 4] = row.y;
	m[index + 8] = row.z;
	m[index + 12] = row.w;
}

Vector3 Matrix4x4::MultiplyPoint(const Vector3& point) const {
	Vector3 res;
	float w = m[3] * point.x + m[7] * point.y + m[11] * point.z + m[15];

	res.x = (m[0] * point.x + m[4] * point.y + m[8] * point.z + m[12]) / w;
	res.y = (m[1] * point.x + m[5] * point.y + m[9] * point.z + m[13]) / w;
	res.z = (m[2] * point.x + m[6] * point.y + m[10] * point.z + m[14]) / w;

	return res;
}

Vector3 Matrix4x4::MultiplyPoint3x4(const Vector3& point) const {
	Vector3 res;
	res.x = m[0] * point.x + m[4] * point.y + m[8] * point.z + m[12];
	res.y = m[1] * point.x + m[5] * point.y + m[9] * point.z + m[13];
	res.z = m[2] * point.x + m[6] * point.y + m[10] * point.z + m[14];
	return res;
}

Vector3 Matrix4x4::MultiplyVector(const Vector3& vector) const {
	Vector3 res;
	res.x = m[0] * vector.x + m[4] * vector.y + m[8] * vector.z;
	res.y = m[1] * vector.x + m[5] * vector.y + m[9] * vector.z;
	res.z = m[2] * vector.x + m[6] * vector.y + m[10] * vector.z;
	return res;
}

void Yaxl::Matrix4x4::SetPosition(const Vector3& value) {
	m[12] = value.x;
	m[13] = value.y;
	m[14] = value.z;
}

Vector3 Yaxl::Matrix4x4::GetPosition() const {
	return Vector3(m[12], m[13], m[14]);
}

void Yaxl::Matrix4x4::SetRotation(const Quaternion& value) {
	SetTRS(GetPosition(), value, GetLossyScale());
}

Quaternion Yaxl::Matrix4x4::GetRotation() const {
	const Vector3 scale = GetLossyScale();

	// スケール0対策
	if (Math::Approximately(scale.x, 0.0f) || Math::Approximately(scale.y, 0.0f) || Math::Approximately(scale.z, 0.0f)) {
		return Quaternion::Identity();
	}

	float r00 = m[0] / scale.x;
	float r01 = m[4] / scale.y;
	float r02 = m[8] / scale.z;

	float r10 = m[1] / scale.x;
	float r11 = m[5] / scale.y;
	float r12 = m[9] / scale.z;

	float r20 = m[2] / scale.x;
	float r21 = m[6] / scale.y;
	float r22 = m[10] / scale.z;

	float trace = r00 + r11 + r22;

	Quaternion q;

	if (trace > 0.0f) {
		float s = Math::Sqrt(trace + 1.0f) * 2.0f;

		q.w = 0.25f * s;
		q.x = (r21 - r12) / s;
		q.y = (r02 - r20) / s;
		q.z = (r10 - r01) / s;
	}
	else if (r00 > r11 && r00 > r22) {
		float s = Math::Sqrt(1.0f + r00 - r11 - r22) * 2.0f;

		q.w = (r21 - r12) / s;
		q.x = 0.25f * s;
		q.y = (r01 + r10) / s;
		q.z = (r02 + r20) / s;
	}
	else if (r11 > r22) {
		float s = Math::Sqrt(1.0f + r11 - r00 - r22) * 2.0f;

		q.w = (r02 - r20) / s;
		q.x = (r01 + r10) / s;
		q.y = 0.25f * s;
		q.z = (r12 + r21) / s;
	}
	else {
		float s = Math::Sqrt(1.0f + r22 - r00 - r11) * 2.0f;

		q.w = (r10 - r01) / s;
		q.x = (r02 + r20) / s;
		q.y = (r12 + r21) / s;
		q.z = 0.25f * s;
	}

	q.Normalize();
	return q;
}

void Yaxl::Matrix4x4::SetScale(const Vector3& value) {
	SetTRS(GetPosition(), GetRotation(), value);
}

Vector3 Yaxl::Matrix4x4::GetLossyScale() const {
	return Vector3(
		Vector3(m[0], m[1], m[2]).Magnitude(),
		Vector3(m[4], m[5], m[6]).Magnitude(),
		Vector3(m[8], m[9], m[10]).Magnitude()
	);
}

void Yaxl::Matrix4x4::SetTRS(const Vector3& pos, const Vector3& euler, const Vector3& scale) {
	SetTRS(pos, Quaternion::Euler(euler), scale);
}

void Yaxl::Matrix4x4::SetTRS(const Vector3& pos, const Quaternion& q, const Vector3& scale) {
	*this = Matrix4x4::TRS(pos, q, scale);
}

Matrix4x4 Matrix4x4::Identity() {
	return Matrix4x4();
}

Matrix4x4 Matrix4x4::Zero() {
	Matrix4x4 res;
	std::memset(res.m, 0, sizeof(float) * 16);
	return res;
}

Matrix4x4 Matrix4x4::Translate(const Vector3& vector) {
	Matrix4x4 res;
	res.m[12] = vector.x;
	res.m[13] = vector.y;
	res.m[14] = vector.z;
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

	res.m[0] = 1.0f - 2.0f * (yy + zz);
	res.m[1] = 2.0f * (xy + zw);
	res.m[2] = 2.0f * (xz - yw);
	res.m[3] = 0.0f;

	res.m[4] = 2.0f * (xy - zw);
	res.m[5] = 1.0f - 2.0f * (xx + zz);
	res.m[6] = 2.0f * (yz + xw);
	res.m[7] = 0.0f;

	res.m[8] = 2.0f * (xz + yw);
	res.m[9] = 2.0f * (yz - xw);
	res.m[10] = 1.0f - 2.0f * (xx + yy);
	res.m[11] = 0.0f;

	res.m[12] = 0.0f;
	res.m[13] = 0.0f;
	res.m[14] = 0.0f;
	res.m[15] = 1.0f;

	return res;
}

Matrix4x4 Matrix4x4::Scale(const Vector3& vector) {
	Matrix4x4 res;
	res.m[0] = vector.x;
	res.m[5] = vector.y;
	res.m[10] = vector.z;
	return res;
}

Matrix4x4 Matrix4x4::TRS(const Vector3& pos, const Vector3& euler, const Vector3& scale) {
	return TRS(pos, Quaternion::Euler(euler), scale);
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

	res.m[0] = (1.0f - 2.0f * (yy + zz)) * scale.x;
	res.m[1] = (2.0f * (xy + zw)) * scale.x;
	res.m[2] = (2.0f * (xz - yw)) * scale.x;
	res.m[3] = 0.0f;

	res.m[4] = (2.0f * (xy - zw)) * scale.y;
	res.m[5] = (1.0f - 2.0f * (xx + zz)) * scale.y;
	res.m[6] = (2.0f * (yz + xw)) * scale.y;
	res.m[7] = 0.0f;

	res.m[8] = (2.0f * (xz + yw)) * scale.z;
	res.m[9] = (2.0f * (yz - xw)) * scale.z;
	res.m[10] = (1.0f - 2.0f * (xx + yy)) * scale.z;
	res.m[11] = 0.0f;

	res.m[12] = pos.x;
	res.m[13] = pos.y;
	res.m[14] = pos.z;
	res.m[15] = 1.0f;

	return res;
}

Matrix4x4 Matrix4x4::Ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
	Matrix4x4 res = Matrix4x4::Zero();

	res.m[0] = 2.0f / (right - left);
	res.m[5] = 2.0f / (top - bottom);
	res.m[10] = -2.0f / (zFar - zNear);
	res.m[15] = 1.0f;

	res.m[12] = -(right + left) / (right - left);
	res.m[13] = -(top + bottom) / (top - bottom);
	res.m[14] = -(zFar + zNear) / (zFar - zNear);

	return res;
}

Matrix4x4 Matrix4x4::Perspective(float fov, float aspect, float zNear, float zFar) {
	Matrix4x4 res = Matrix4x4::Zero();

	float tanHalfFov = Math::Tan(fov * 0.5f * Math::Deg2Rad);

	res.m[0] = 1.0f / (aspect * tanHalfFov);
	res.m[5] = 1.0f / (tanHalfFov);
	res.m[10] = -(zFar + zNear) / (zFar - zNear);
	res.m[11] = -1.0f;
	res.m[14] = -(2.0f * zFar * zNear) / (zFar - zNear);

	return res;
}

Matrix4x4 Matrix4x4::LookAt(const Vector3& eye, const Vector3& target, const Vector3& up) {
	Vector3 zAxis = (eye - target).Normalized();
	Vector3 xAxis = Vector3::Cross(up, zAxis).Normalized();
	Vector3 yAxis = Vector3::Cross(zAxis, xAxis);

	Matrix4x4 res;
	res.m[0] = xAxis.x;
	res.m[4] = xAxis.y;
	res.m[8] = xAxis.z;
	res.m[12] = -Vector3::Dot(xAxis, eye);

	res.m[1] = yAxis.x;
	res.m[5] = yAxis.y;
	res.m[9] = yAxis.z;
	res.m[13] = -Vector3::Dot(yAxis, eye);

	res.m[2] = zAxis.x;
	res.m[6] = zAxis.y;
	res.m[10] = zAxis.z;
	res.m[14] = -Vector3::Dot(zAxis, eye);

	res.m[3] = 0.0f;
	res.m[7] = 0.0f;
	res.m[11] = 0.0f;
	res.m[15] = 1.0f;

	return res;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const {
	Matrix4x4 res;
	for (int c = 0; c < 4; ++c) {
		for (int r = 0; r < 4; ++r) {
			res.m[c * 4 + r] =
				m[0 * 4 + r] * rhs.m[c * 4 + 0] +
				m[1 * 4 + r] * rhs.m[c * 4 + 1] +
				m[2 * 4 + r] * rhs.m[c * 4 + 2] +
				m[3 * 4 + r] * rhs.m[c * 4 + 3];
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
		if (Math::Approximately(m[i], rhs.m[i]) == false) {
			return false;
		}
	}
	return true;
}

bool Matrix4x4::operator!=(const Matrix4x4& rhs) const {
	return !(*this == rhs);
}
