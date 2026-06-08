// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 2Dベクトル UnityのVector2互換（2026/06/08時点）
//					https://docs.unity3d.com/ja/2021.2/ScriptReference/Vector2.html
// -----------------------------------------------------------------------------------------

#ifndef YAXL_VECTOR2_H_
#define YAXL_VECTOR2_H_

#include "YaxlLibLink.h"

namespace Yaxl {

class Vector2 {
public:
	// ベクトルのx成分
	float x;
	// ベクトルのy成分
	float y;

public:
	// デフォルトコンストラクタ（0.0, 0.0）
	Vector2();
	// コンストラクタ
	Vector2(float x, float y);

public:
	// 既存のベクトルに値を設定
	void Set(float x, float y);
	// ベクトルの長さを返す
	float Magnitude() const;
	// ベクトルの二乗の長さを返す
	float SqrMagnitude() const;
	// 正規化したベクトルを返す
	Vector2 Normalized() const;
	// 正規化
	void Normalize();

public:
	// Vector2(0.0, 0.0)
	static Vector2 Zero();
	// Vector2(1.0, 1.0)
	static Vector2 One();
	// Vector2(0.0, 1.0)
	static Vector2 Up();
	// Vector2(0.0, -1.0)
	static Vector2 Down();
	// Vector2(-1.0, 0.0)
	static Vector2 Left();
	// Vector2(1.0, 0.0)
	static Vector2 Right();
	// 無限大
	static Vector2 PositiveInfinity();
	// 負の無限大
	static Vector2 NegativeInfinity();

public:
	// 内積を求める
	static float Dot(const Vector2& lhs, const Vector2& rhs);
	// 距離を求める
	static float Distance(const Vector2& a, const Vector2& b);
	// 間の角度を求める（符号なし）
	static float Angle(const Vector2& from, const Vector2& to);
	// 間の角度を求める（符号あり）
	static float SignedAngle(const Vector2& from, const Vector2& to);
	// 大きさを制限したベクトルのコピーを返す
	static Vector2 ClampMagnitude(const Vector2& vector, float maxLength);
	// 線形補間
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
	// 線形補間（tに上限はなし）
	static Vector2 LerpUnclamped(const Vector2& a, const Vector2& b, float t);
	// 最大値を求める
	static Vector2 Max(const Vector2& lhs, const Vector2& rhs);
	// 最小値を求める
	static Vector2 Min(const Vector2& lhs, const Vector2& rhs);
	// 指定したスピードで移動
	static Vector2 MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta);
	// ベクトルに対して垂直なベクトルを返す
	static Vector2 Perpendicular(const Vector2& inDirection);
	// 法線を基準にした反射したベクトルを返す
	static Vector2 Reflect(const Vector2& inDirection, const Vector2& inNormal);
	// 乗算したベクトルを返す
	static Vector2 Scale(const Vector2& a, const Vector2& b);

	// 演算子オーバーロード
public:
	Vector2 operator+(const Vector2& rhs) const;
	Vector2 operator-(const Vector2& rhs) const;
	Vector2 operator*(float d) const;
	Vector2 operator/(float d) const;
	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	Vector2& operator*=(float d);
	Vector2& operator/=(float d);
	bool operator==(const Vector2& rhs) const;
	bool operator!=(const Vector2& rhs) const;
};

// 左辺からのスカラー乗算
Vector2 operator*(float d, const Vector2& rhs);

} // namespace Yaxl end

#endif