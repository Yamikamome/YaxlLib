// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : クオータニオン UnityのQuaternion互換（2026/06/08時点）
//					https://docs.unity3d.com/ja/2021.2/ScriptReference/Quaternion.html
// -----------------------------------------------------------------------------------------

#ifndef YAXL_QUATERNION_H_
#define YAXL_QUATERNION_H_

#include "YaxlLibLink.h"

namespace Yaxl {

class Vector3;

class Quaternion {
public:
	// クオータニオンのx成分
	float x;
	// クオータニオンのy成分
	float y;
	// クオータニオンのz成分
	float z;
	// クオータニオンのw成分
	float w;

public:
	// デフォルトコンストラクタ（0.0, 0.0, 0.0, 0.0）
	Quaternion();
	// コンストラクタ
	Quaternion(float x, float y, float z, float w);

public:
	// 既存のクオータニオンに値を設定
	void Set(float x, float y, float z, float w);
	// クオータニオンの長さを返す
	float Magnitude() const;
	// クオータニオンの二乗の長さを返す
	float SqrMagnitude() const;
	// 正規化したクオータニオンを返す
	Quaternion Normalized() const;
	// 正規化
	void Normalize();
	// オイラー角の回転を取得する
	Vector3 EulerAngles() const;
	// 軸と角度へ変換する
	void ToAngleAxis(float& angle, Vector3& axis) const;

public:
	// 無回転（単位四元数）
	static Quaternion Identity();
	// 2つのQuaternionのなす角を返す
	static float Angle(const Quaternion& a, const Quaternion& b);
	// 特定の軸の周りをangle度回転させるQuaternionを作成する
	static Quaternion AngleAxis(float angle, const Vector3& axis);
	// 内積
	static float Dot(const Quaternion& a, const Quaternion& b);
	// オイラー角からQuaternionを作成する
	static Quaternion Euler(float x, float y, float z);
	// オイラー角からQuaternionを作成する
	static Quaternion Euler(const Vector3& euler);
	// fromDirectionからtoDirectionへ向ける回転を作成する
	static Quaternion FromToRotation(const Vector3& fromDirection, const Vector3& toDirection);
	// 回転の逆を返す
	static Quaternion Inverse(const Quaternion& rotation);
	// 線形補間
	static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float t);
	// 線形補間（tに上限はなし）
	static Quaternion LerpUnclamped(const Quaternion& a, const Quaternion& b, float t);
	// 指定されたforwardとupwards方向に回転したクオータニオンを返す
	static Quaternion LookRotation(const Vector3& forward, const Vector3& upwards);
	// 球状補間
	static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);
	// 球状補間（tに上限はなし）
	static Quaternion SlerpUnclamped(const Quaternion& a, const Quaternion& b, float t);
	// 指定したスピードで回転
	static Quaternion RotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta);

public:
	// 演算子オーバーロード
	Quaternion operator*(const Quaternion& rhs) const;
	Vector3 operator*(const Vector3& point) const;
	Quaternion& operator*=(const Quaternion& rhs);
	bool operator==(const Quaternion& rhs) const;
	bool operator!=(const Quaternion& rhs) const;
};

} // namespace Yaxl end

#endif
