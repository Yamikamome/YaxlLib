// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 4Dベクトル UnityのVector4互換（2026/06/08時点）
//					https://docs.unity3d.com/ja/2021.2/ScriptReference/Vector4.html
//					Color値（RGBA）としても使える
// -----------------------------------------------------------------------------------------

#ifndef YAXL_VECTOR4_H_
#define YAXL_VECTOR4_H_

#include "YaxlLibLink.h"

namespace Yaxl {

// 前方宣言
class Vector2;
class Vector3;

class Vector4 {
public:
#pragma warning(push)
#pragma warning(disable : 4201) // 無名構造体警告を無視
	union {
		// ベクトル
		struct {
			// ベクトルのx成分
			float x;
			// ベクトルのy成分
			float y;
			// ベクトルのz成分
			float z;
			// ベクトルのw成分
			float w;
		};
		// カラー
		struct {
			// カラーのr成分
			float r;
			// カラーのg成分
			float g;
			// カラーのb成分
			float b;
			// カラーのa成分
			float a;
		};
		// 矩形
		struct {
			// 矩形のleft成分
			float left;
			// 矩形のtop成分
			float top;
			// 矩形のright成分
			float right;
			// 矩形のbottom成分
			float bottom;
		};
	};
#pragma warning(pop)

public:
	// デフォルトコンストラクタ（0.0, 0.0, 0.0, 0.0）
	Vector4();
	// コンストラクタ
	Vector4(float x, float y, float z, float w);
	// 3Dベクトルからのコンストラクタ（wは0.0）
	Vector4(float x, float y, float z);
	// 3Dベクトルからのコンストラクタ（wは0.0）
	Vector4(const Vector3& v);

public:
	// 既存のベクトルに値を設定
	void Set(float x, float y, float z, float w);
	// ベクトルの長さを返す
	float Magnitude() const;
	// ベクトルの二乗の長さを返す
	float SqrMagnitude() const;
	// 正規化したベクトルを返す
	Vector4 Normalized() const;
	// 正規化
	void Normalize();

public:
	// Vector4(0.0, 0.0, 0.0, 0.0)
	static Vector4 Zero();
	// Vector4(1.0, 1.0, 1.0, 1.0)
	static Vector4 One();
	// 無限大
	static Vector4 PositiveInfinity();
	// 負の無限大
	static Vector4 NegativeInfinity();

public:
	// 内積を求める
	static float Dot(const Vector4& lhs, const Vector4& rhs);
	// 距離を求める
	static float Distance(const Vector4& a, const Vector4& b);
	// 大きさを制限したベクトルのコピーを返す
	static Vector4 ClampMagnitude(const Vector4& vector, float maxLength);
	// 線形補間
	static Vector4 Lerp(const Vector4& a, const Vector4& b, float t);
	// 線形補間（tに上限はなし）
	static Vector4 LerpUnclamped(const Vector4& a, const Vector4& b, float t);
	// 最大値を求める
	static Vector4 Max(const Vector4& lhs, const Vector4& rhs);
	// 最小値を求める
	static Vector4 Min(const Vector4& lhs, const Vector4& rhs);
	// 指定したスピードで移動
	static Vector4 MoveTowards(const Vector4& current, const Vector4& target, float maxDistanceDelta);
	// 別のベクトルに投影
	static Vector4 Project(const Vector4& vector, const Vector4& onNormal);
	// 乗算したベクトルを返す
	static Vector4 Scale(const Vector4& a, const Vector4& b);

	// 演算子オーバーロード
public:
	Vector4 operator+(const Vector4& rhs) const;
	Vector4 operator-(const Vector4& rhs) const;
	Vector4 operator*(float d) const;
	Vector4 operator/(float d) const;
	Vector4& operator+=(const Vector4& rhs);
	Vector4& operator-=(const Vector4& rhs);
	Vector4& operator*=(float d);
	Vector4& operator/=(float d);
	bool operator==(const Vector4& rhs) const;
	bool operator!=(const Vector4& rhs) const;
};

// 左辺からのスカラー乗算
Vector4 operator*(float d, const Vector4& rhs);

} // namespace Yaxl end

#endif