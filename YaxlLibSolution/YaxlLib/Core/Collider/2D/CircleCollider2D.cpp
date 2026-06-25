#include "CircleCollider2D.h"
#include "BoxCollider2D.h"
#include "RectCollider2D.h"

#include "Graphics/YaxlGraphics.h"
#include "Math/YaxlMath.h"

using namespace Yaxl;

Yaxl::CircleCollider2D::CircleCollider2D() :
	center{ 0.0f, 0.0f },
	radius{ 1.0f } {
}

Yaxl::CircleCollider2D::CircleCollider2D(const Vector2& center, float radius) :
	center{ center },
	radius{ radius } {
}

bool Yaxl::CircleCollider2D::IsCollide(const Collider2D& other, Vector2* push_out) const {
	Vector2 push;
	const bool is_hit = other.IsCollide(*this, push_out ? &push : nullptr);
	if (is_hit && push_out) {
		push_out->x = -push.x;
		push_out->y = -push.y;
	}

	return is_hit;
}

bool Yaxl::CircleCollider2D::IsCollide(const BoxCollider2D& other, Vector2* push_out) const {
	Vector2 push;

	// 結果を反転
	const bool is_hit = other.IsCollide(*this, push_out ? &push : nullptr);
	if (is_hit && push_out) {
		push_out->x = -push.x;
		push_out->y = -push.y;
	}

	return is_hit;
}

bool Yaxl::CircleCollider2D::IsCollide(const CircleCollider2D& other, Vector2* push_out) const {
	const float diff_x = other.center.x - center.x;
	const float diff_y = other.center.y - center.y;
	const float sqr_dist = (diff_x * diff_x) + (diff_y * diff_y);

	const float sum_radius = radius + other.radius;

	if (sqr_dist > sum_radius * sum_radius) {
		return false;
	}

	if (push_out != nullptr) {
		// 座標が完全に一致している場合はランダムに押し出す
		if (sqr_dist == 0.0f) {
			push_out->x = sum_radius;
			push_out->y = 0.0f;
		}
		else {
			float dist = Math::Sqrt(sqr_dist);
			float overlap = sum_radius - dist;
			push_out->x = (diff_x / dist) * overlap;
			push_out->y = (diff_y / dist) * overlap;
		}
	}

	return true;
}

bool Yaxl::CircleCollider2D::IsCollide(const RectCollider2D& other, Vector2* push_out) const {
	return other.IsCollide(*this, push_out);
}

void Yaxl::CircleCollider2D::Draw(float scale, Color* color) const {
	Vector2 position = center;
	DrawCircle2D(&position, radius * scale, color);
}

Vector2 Yaxl::CircleCollider2D::Position() const {
	return center;
}

Vector2 Yaxl::CircleCollider2D::Center() const {
	return center;
}

CircleCollider2D Yaxl::CircleCollider2D::Translate(const Vector2& pos) const {
	return CircleCollider2D{ center + pos, radius };
}

float Yaxl::CircleCollider2D::Radius() const {
	return radius;
}
