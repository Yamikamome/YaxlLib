// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 2D用矩形コライダー
//					位置を左上で管理する、描画向け
// -----------------------------------------------------------------------------------------

#ifndef YAXL_RECT_COLLIDER_2D_H_
#define YAXL_RECT_COLLIDER_2D_H_

#include "Collider2D.h"

namespace Yaxl {

class RectCollider2D : public Collider2D {
public:
	RectCollider2D();

	RectCollider2D(const Vector2& position, const Vector2& size);

public:
	bool IsCollide(const Collider2D& other, Vector2* push_out = nullptr) const override;
	bool IsCollide(const BoxCollider2D& other, Vector2* push_out = nullptr) const override;
	bool IsCollide(const CircleCollider2D& other, Vector2* push_out = nullptr) const override;
	bool IsCollide(const RectCollider2D& other, Vector2* push_out = nullptr) const override;

	void Draw(float scale = 1.0f, Color* color = nullptr) const override;

	Vector2 Position() const override;

	Vector2 Center() const override;

public:
	/// <summary>
	/// 平行移動
	/// </summary>
	RectCollider2D Translate(const Vector2& pos) const;

	/// <summary>
	/// 大きさ
	/// </summary>
	Vector2 Size() const;

	/// <summary>
	/// BoxColliderに変換
	/// </summary>
	BoxCollider2D ToBoxCollider2D() const;

public:
	// 位置（左上）
	Vector2 position;
	// 大きさ
	Vector2 size;
};

}	// namespace Yaxl end

#endif
