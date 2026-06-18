// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 演算処理 UnityのMath互換（2026/06/08時点）
//					https://docs.unity3d.com/ja/2021.2/ScriptReference/Mathf.html
// -----------------------------------------------------------------------------------------

#ifndef YAXL_MATH_H_
#define YAXL_MATH_H_

#include "YaxlLibLink.h"
#include <limits>

namespace Yaxl {

class Math {
public:
	// 円周率
	static constexpr float PI = 3.14159265358979323846f;
	// 無限大
	static constexpr float Infinity = std::numeric_limits<float>::infinity();
	// 負の無限大
	static constexpr float NegativeInfinity = -std::numeric_limits<float>::infinity();
	// 度からラジアンに変換
	static constexpr float Deg2Rad = PI * 2.0f / 360.0f;
	// ラジアンから度に変換
	static constexpr float Rad2Deg = 1.0f / Deg2Rad;
	// ごくわずかな浮動小数点の値
	static constexpr float Epsilon = std::numeric_limits<float>::epsilon();

public:
	// 絶対値を求める（float）
	static float Abs(float f);
	// 絶対値を求める（int）
	static int Abs(int value);
	// 符号を求める
	static float Sign(float f);
	// 最大値を求める（float）
	static float Max(float a, float b);
	// 最大値を求める（int）
	static int Max(int a, int b);
	// 最小値を求める（float）
	static float Min(float a, float b);
	// 最小値を求める（int）
	static int Min(int a, int b);

public:
	// 切り上げ
	static float Ceil(float f);
	// 切り上げ（intに変換）
	static int CeilToInt(float f);
	// 切り捨て
	static float Floor(float f);
	// 切り捨て（intに変換）
	static int FloorToInt(float f);
	// 四捨五入
	static float Round(float f);
	// 四捨五入（intに変換）
	static int RoundToInt(float f);

public:
	// 値を範囲内に収める（float）
	static float Clamp(float value, float min, float max);
	// 値を範囲内に収める（int）
	static int Clamp(int value, int min, int max);
	// 値を0.0~1.0の範囲内に収める
	static float Clamp01(float value);

public:
	// 線形補間
	static float Lerp(float a, float b, float t);
	// 線形補間
	static float LerpAngle(float a, float b, float t);
	// 線形補間（tに上限はなし）
	static float LerpUnclamped(float a, float b, float t);
	// 値が2つの値のどこに位置するかを判定
	static float InverseLerp(float a, float b, float value);
	// スムージング補間
	static float SmoothStep(float from, float to, float t);
	// 指定したスピードで移動
	static float MoveTowards(float current, float target, float maxDelta);
	// 指定したスピードで移動
	static float MoveTowardsAngle(float current, float target, float maxDelta);

public:
	// 0からlengthの間でループ
	static float Repeat(float t, float length);
	// 0からlengthの間で増減する値を返す
	static float PingPong(float t, float length);
	// 与えられた角度の最小の差を返す
	static float DeltaAngle(float current, float target);

public:
	// サイン（ラジアン）
	static float Sin(float f);
	// コサイン（ラジアン）
	static float Cos(float f);
	// タンジェント（ラジアン）
	static float Tan(float f);
	// アークサイン（ラジアン）
	static float Asin(float f);
	// アークコサイン（ラジアン）
	static float Acos(float f);
	// アークタンジェント（ラジアン）
	static float Atan(float f);
	// y/xになる角度（ラジアン）を返す
	static float Atan2(float y, float x);

public:
	// べき乗
	static float Pow(float f, float p);
	// ネイピア数を指定した乗数を返す
	static float Exp(float power);
	// 対数
	static float Log(float f);
	// 底が10の対数
	static float Log10(float f);
	// 平方根
	static float Sqrt(float f);

public:
	// 浮動小数点の誤差を考慮した等価判定
	static bool Approximately(float a, float b);
	// 2の累乗かどうか
	static bool IsPowerOfTwo(int value);
	// 最も近い2の累乗の値を返す
	static int ClosestPowerOfTwo(int value);
	// 次の2の累乗の値を返す
	static int NextPowerOfTwo(int value);
	// ごくわずかな浮動小数点による0除算対策
	static float SafeDivide(float value, float divisor);

private:
	// インスタンス生成禁止
	Math() = delete;
};

} // namespace Yaxl end

#endif
