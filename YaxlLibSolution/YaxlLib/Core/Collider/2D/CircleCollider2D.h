// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 2D用円コライダー
// -----------------------------------------------------------------------------------------

#ifndef YAXL_CIRCLE_COLLIDER_2D_H_
#define YAXL_CIRCLE_COLLIDER_2D_H_

#include "Collider2D.h"

namespace Yaxl {
class CircleCollider2D : public Collider2D {
public:
	CircleCollider2D();

	CircleCollider2D(const Vector2& center, float radius);

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
	CircleCollider2D Translate(const Vector2& pos) const;

	/// <summary>
	/// 半径
	/// </summary>
	float Radius() const;

public:
	// 中心
	Vector2 center;
	// 半径
	float radius;
};

}	// namespace Yaxl end

#endif
