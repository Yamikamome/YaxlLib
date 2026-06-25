// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 3Dベクトル UnityのVector3互換（2026/06/08時点）
//					https://docs.unity3d.com/ja/2021.2/ScriptReference/Vector3.html
// -----------------------------------------------------------------------------------------

#ifndef YAXL_VECTOR3_H_
#define YAXL_VECTOR3_H_

#include "YaxlLibLink.h"


namespace Yaxl {

// 前方宣言
class Vector2;

class Vector3 {
public:
	// ベクトルのx成分
	float x;
	// ベクトルのy成分
	float y;
	// ベクトルのz成分
	float z;

public:
	// デフォルトコンストラクタ（0.0, 0.0, 0.0）
	Vector3();
	// コンストラクタ
	Vector3(float x, float y, float z);
	// 2Dベクトルからのコンストラクタ（zは0.0）
	Vector3(float x, float y);
	// 2Dベクトルからのコンストラクタ（zは0.0）
	Vector3(const Vector2& v);

public:
	// 既存のベクトルに値を設定
	void Set(float x, float y, float z);
	// ベクトルの長さを返す
	float Magnitude() const;
	// ベクトルの二乗の長さを返す
	float SqrMagnitude() const;
	// 正規化したベクトルを返す
	Vector3 Normalized() const;
	// 正規化
	void Normalize();

public:
	// Vector3(0.0, 0.0, 0.0)
	static Vector3 Zero();
	// Vector3(1.0, 1.0, 1.0)
	static Vector3 One();
	// Vector3(0.0, 1.0, 0.0)
	static Vector3 Up();
	// Vector3(0.0, -1.0, 0.0)
	static Vector3 Down();
	// Vector3(-1.0, 0.0, 0.0)
	static Vector3 Left();
	// Vector3(1.0, 0.0, 0.0)
	static Vector3 Right();
	// Vector3(0.0, 0.0, 1.0)
	static Vector3 Forward();
	// Vector3(0.0, 0.0, -1.0)
	static Vector3 Back();
	// 無限大
	static Vector3 PositiveInfinity();
	// 負の無限大
	static Vector3 NegativeInfinity();

public:
	// 内積を求める
	static float Dot(const Vector3& lhs, const Vector3& rhs);
	// 外積を求める
	static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
	// 距離を求める
	static float Distance(const Vector3& a, const Vector3& b);
	// 間の角度を求める（符号なし）
	static float Angle(const Vector3& from, const Vector3& to);
	// 間の角度を求める（符号あり）
	static float SignedAngle(const Vector3& from, const Vector3& to, const Vector3& axis);
	// 大きさを制限したベクトルのコピーを返す
	static Vector3 ClampMagnitude(const Vector3& vector, float maxLength);
	// 線形補間
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
	// 線形補間（tに上限はなし）
	static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);
	// 球状補間
	static Vector3 Slerp(const Vector3& a, const Vector3& b, float t);
	// 球状補間（tに上限はなし）
	static Vector3 SlerpUnclamped(const Vector3& a, const Vector3& b, float t);
	// 最大値を求める
	static Vector3 Max(const Vector3& lhs, const Vector3& rhs);
	// 最小値を求める
	static Vector3 Min(const Vector3& lhs, const Vector3& rhs);
	// 指定したスピードで移動
	static Vector3 MoveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta);
	// 別のベクトルに投影
	static Vector3 Project(const Vector3& vector, const Vector3& onNormal);
	// 平面に垂直な法線ベクトルによって定義される平面上にベクトルを射影
	static Vector3 ProjectOnPlane(const Vector3& vector, const Vector3& planeNormal);
	// 法線で定義された平面で反射したベクトルを返す
	static Vector3 Reflect(const Vector3& inDirection, const Vector3& inNormal);
	// 乗算したベクトルを返す
	static Vector3 Scale(const Vector3& a, const Vector3& b);
	// 直交化
	static void OrthoNormalize(Vector3& normal, Vector3& tangent);

	// 演算子オーバーロード
public:
	Vector3 operator+(const Vector3& rhs) const;
	Vector3 operator-(const Vector3& rhs) const;
	Vector3 operator*(float d) const;
	Vector3 operator/(float d) const;
	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	Vector3& operator*=(float d);
	Vector3& operator/=(float d);
	bool operator==(const Vector3& rhs) const;
	bool operator!=(const Vector3& rhs) const;
};

// 左辺からのスカラー乗算
Vector3 operator*(float d, const Vector3& rhs);

} // namespace Yaxl end

#endif