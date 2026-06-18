// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 4*4行列 UnityのMatrix4x4互換（2026/06/08時点）
//					https://docs.unity3d.com/ja/2021.2/ScriptReference/Matrix4x4.html
// -----------------------------------------------------------------------------------------

#ifndef YAXL_MATRIX4X4_H_
#define YAXL_MATRIX4X4_H_

#include "YaxlLibLink.h"

namespace Yaxl {

class Vector3;
class Vector4;
class Quaternion;

class Matrix4x4 {
public:
	// 4*4行列成分
	// m[0]		m[4]	m[8]	m[12]
	// m[1]		m[5]	m[9]	m[13]
	// m[2]		m[6]	m[10]	m[14]
	// m[3]		m[7]	m[11]	m[15]
	float m[16];

public:
	// コンストラクタ
	Matrix4x4();

public:
	// 行列式を返す
	float Determinant() const;
	// 逆行列を返す
	Matrix4x4 Inverse() const;
	// 転置行列を返す
	Matrix4x4 Transpose() const;
	// 行列の列を返す
	Vector4 GetColumn(int index) const;
	// 行列の行を返す
	Vector4 GetRow(int index) const;
	// 行列の列を設定
	void SetColumn(int index, const Vector4& column);
	// 行列の行を設定
	void SetRow(int index, const Vector4& row);
	// 3Dの線形変換（回転・拡縮）
	Vector3 MultiplyPoint(const Vector3& point) const;
	// 座標変換（移動・回転・拡縮）
	Vector3 MultiplyPoint3x4(const Vector3& point) const;
	// 方向変換（回転・拡縮のみ）
	Vector3 MultiplyVector(const Vector3& vector) const;
	// 位置を設定
	void SetPosition(const Vector3& value);
	// 位置を返す
	Vector3 GetPosition() const;
	// 回転を設定
	void SetRotation(const Quaternion& value);
	// 回転を返す
	Quaternion GetRotation() const;
	// スケールを設定
	void SetScale(const Vector3& value);
	// スケールを返す（負の値は保持されない）
	Vector3 GetLossyScale() const;
	// TRSを設定
	void SetTRS(const Vector3& pos, const Vector3& euler, const Vector3& scale);
	// TRSを設定
	void SetTRS(const Vector3& pos, const Quaternion& q, const Vector3& scale);

public:
	// 恒等行列
	static Matrix4x4 Identity();
	// ゼロ行列
	static Matrix4x4 Zero();
	// TRS（平行移動、回転、拡縮）行列を作成
	static Matrix4x4 TRS(const Vector3& pos, const Vector3& euler, const Vector3& scale);
	// TRS（平行移動、回転、拡縮）行列を作成
	static Matrix4x4 TRS(const Vector3& pos, const Quaternion& q, const Vector3& scale);
	// 平行移動行列を作成
	static Matrix4x4 Translate(const Vector3& vector);
	// 回転行列を作成
	static Matrix4x4 Rotate(const Quaternion& q);
	// 拡縮行列を作成
	static Matrix4x4 Scale(const Vector3& vector);
	// 平行投影行列を作成
	static Matrix4x4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
	// 透視投影を作成
	static Matrix4x4 Perspective(float fov, float aspect, float zNear, float zFar);
	// 視野変換行列を作成
	static Matrix4x4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

	// 演算子オーバーロード
	Matrix4x4 operator*(const Matrix4x4& rhs) const;
	Matrix4x4& operator*=(const Matrix4x4& rhs);
	bool operator==(const Matrix4x4& rhs) const;
	bool operator!=(const Matrix4x4& rhs) const;
};

} // namespace Yaxl end

#endif
