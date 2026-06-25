// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 乱数管理
// -----------------------------------------------------------------------------------------

#ifndef YAXL_RANDOM_H_
#define YAXL_RANDOM_H_

#include "YaxlLibLink.h"

namespace Yaxl {

class Vector2;
class Vector3;

class Random {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="seed">= シード値</param>
	static void Init(unsigned int seed);

public:
	/// <summary>
	/// 現在のシード値を取得する
	/// </summary>
	/// <returns>現在のシード値</returns>
	static unsigned int GetSeed();

public:
	/// <summary>
	/// 0.0~1.0の間のランダムな値を取得する
	/// </summary>
	/// <returns>ランダムな値</returns>
	static float Value();

	/// <summary>
	/// intのランダムな値を取得する
	/// </summary>
	/// <param name="min">= 最小値</param>
	/// <param name="max">= 最大値</param>
	/// <returns>ランダムな値</returns>
	static int Range(int min, int max);

	/// <summary>
	/// floatのランダムな値を取得する
	/// </summary>
	/// <param name="min">= 最小値</param>
	/// <param name="max">= 最大値</param>
	/// <returns>ランダムな値</returns>
	static float Range(float min, float max);

	/// <summary>
	/// Vector2のランダムな値を取得する
	/// </summary>
	/// <param name="min">= 最小値</param>
	/// <param name="max">= 最大値</param>
	/// <returns>ランダムな値</returns>
	static Vector2 Range(const Vector2& min, const Vector2& max);

	/// <summary>
	/// Vector3のランダムな値を取得する
	/// </summary>
	/// <param name="min">= 最小値</param>
	/// <param name="max">= 最大値</param>
	/// <returns>ランダムな値</returns>
	static Vector3 Range(const Vector3& min, const Vector3& max);

	/// <summary>
	/// 半径1の球体内部のランダムな座標を取得する
	/// </summary>
	/// <returns>ランダムな値</returns>
	static Vector3 InsideUnitSphere();
};

} // namespace Yaxl end

#endif