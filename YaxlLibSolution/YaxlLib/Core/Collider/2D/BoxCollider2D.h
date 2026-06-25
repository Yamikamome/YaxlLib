// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 2D用矩形コライダー
//					位置を中心で管理する、計算向け
// -----------------------------------------------------------------------------------------

#ifndef YAXL_BOX_COLLIDER_2D_H_
#define YAXL_BOX_COLLIDER_2D_H_

#include "Collider2D.h"

namespace Yaxl {

class BoxCollider2D : public Collider2D {
public:
	BoxCollider2D();

	BoxCollider2D(const Vector2& center, const Vector2& size);

public:
	bool IsCollide(const Collider2D& other, Vector2* push_out = nullptr) const override;
	bool IsCollide(const BoxCollider2D& other, Vector2* push_out = nullptr) const override;
	bool IsCollide(const CircleCollider2D& other, Vector2* push_out = nullptr) const override;

	void Draw(Color* color = nullptr) const override;

	Vector2 Center() const override;

public:
	/// <summary>
	/// 平行移動
	/// </summary>
	BoxCollider2D Translate(const Vector2& pos) const;

	/// <summary>
	/// 大きさ
	/// </summary>
	Vector2 Size() const;

public:
	// 中心
	Vector2 center;
	// 大きさ
	Vector2 size;
};

}	// namespace Yaxl end

#endif
