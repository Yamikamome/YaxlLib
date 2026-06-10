// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 3*3行列 Unityには3*3行列がなかったので互換なし
// -----------------------------------------------------------------------------------------

#ifndef YAXL_MATRIX3X3_H_
#define YAXL_MATRIX3X3_H_

#include "YaxlLibLink.h"

namespace Yaxl {

class Vector2;
class Vector3;

class Matrix3x3 {
public:
	// 3*3行列成分
	// m[0]		m[3]	m[6]
	// m[1]		m[4]	m[7]
	// m[2]		m[5]	m[8]
	float m[9];

public:
	// コンストラクタ
	Matrix3x3();

public:
	// 行列式を返す
	float Determinant() const;
	// 逆行列を返す
	Matrix3x3 Inverse() const;
	// 転置行列を返す
	Matrix3x3 Transpose() const;
	// 行列の列を返す
	Vector3 GetColumn(int index) const;
	// 行列の行を返す
	Vector3 GetRow(int index) const;
	// 行列の列を設定
	void SetColumn(int index, const Vector3& column);
	// 行列の行を設定
	void SetRow(int index, const Vector3& row);
	// 3Dの線形変換（回転・拡縮）
	Vector3 MultiplyVector(const Vector3& vector) const;
	// 2Dの座標変換（移動・回転・拡縮）
	Vector2 MultiplyPoint2D(const Vector2& point) const;
	// 2Dの方向変換（回転・拡縮のみ）
	Vector2 MultiplyVector2D(const Vector2& vector) const;

public:
	// 恒等行列
	static Matrix3x3 Identity();
	// ゼロ行列
	static Matrix3x3 Zero();

public:
	// 2D用のTRS（平行移動、回転、拡縮）行列を作成する
	static Matrix3x3 TRS(const Vector2& pos, float rotation_degrees, const Vector2& scale);

public:
	// 演算子オーバーロード
	Matrix3x3 operator*(const Matrix3x3& rhs) const;
	Matrix3x3& operator*=(const Matrix3x3& rhs);
	bool operator==(const Matrix3x3& rhs) const;
	bool operator!=(const Matrix3x3& rhs) const;
};

} // namespace Yaxl end

#endif