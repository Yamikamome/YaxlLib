// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 2Dコライダー
// -----------------------------------------------------------------------------------------

#ifndef YAXL_COLLIDER_2D_H_
#define YAXL_COLLIDER_2D_H_

#include "Math/YaxlVector2.h"

namespace Yaxl {

class BoxCollider2D;
class CircleCollider2D;
class Color;

class Collider2D {
public:
	virtual ~Collider2D() = default;

public:
	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="other">= 相手のコライダー</param>
	/// <param name="push_out">= 衝突時の押し出し量</param>
	/// <returns>衝突していたら真を、衝突していなければ偽を返す</returns>
	virtual bool IsCollide(const Collider2D& other, Vector2* push_out = nullptr) const = 0;

	// ダブルディスパッチ用インターフェース
public:
	virtual bool IsCollide(const BoxCollider2D& other, Vector2* push_out = nullptr) const = 0;
	virtual bool IsCollide(const CircleCollider2D& other, Vector2* push_out = nullptr) const = 0;

public:
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="color">= カラー</param>
	virtual void Draw(Color* color = nullptr) const = 0;

	/// <summary>
	/// 中心位置
	/// </summary>
	virtual Vector2 Center() const = 0;
};

}	// namespace Yaxl end

#endif
