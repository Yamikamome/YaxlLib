// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 2D用矩形コライダー
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
	bool IsCollide(Collider2D& other, Vector2* push_out = nullptr) override;
	bool IsCollide(BoxCollider2D& other, Vector2* push_out = nullptr) override;
	bool IsCollide(CircleCollider2D& other, Vector2* push_out = nullptr) override;

	void Draw(Color* color = nullptr) const override;

public:
	/// <summary>
	/// 平行移動
	/// </summary>
	BoxCollider2D Translate(const Vector2& pos) const;

public:
	// 中心
	Vector2 center;
	// 大きさ
	Vector2 size;
};

}	// namespace Yaxl end

#endif
