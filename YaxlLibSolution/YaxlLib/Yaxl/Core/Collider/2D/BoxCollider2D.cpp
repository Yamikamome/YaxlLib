#include "BoxCollider2D.h"
#include "CircleCollider2D.h"
#include "RectCollider2D.h"

#include "Yaxl/Graphics/YaxlGraphics.h"
#include "Yaxl/Math/YaxlMath.h"

using namespace Yaxl;

Yaxl::BoxCollider2D::BoxCollider2D() :
	center{ 0.0f, 0.0f },
	size{ 0.0f, 0.0f } {
}

Yaxl::BoxCollider2D::BoxCollider2D(const Vector2& center, const Vector2& size) :
	center{ center },
	size{ size } {
}

bool Yaxl::BoxCollider2D::IsCollide(const Collider2D& other, Vector2* push_out) const {
	Vector2 push;
	const bool is_hit = other.IsCollide(*this, push_out ? &push : nullptr);
	if (is_hit && push_out) {
		push_out->x = -push.x;
		push_out->y = -push.y;
	}

	return is_hit;
}

bool Yaxl::BoxCollider2D::IsCollide(const BoxCollider2D& other, Vector2* push_out) const {
	// 距離の差分
	const float diff_x = other.center.x - center.x;
	const float diff_y = other.center.y - center.y;
	// 中心から端までの距離の合計
	const float sum_half_w = (size.x + other.size.x) * 0.5f;
	const float sum_half_h = (size.y + other.size.y) * 0.5f;

	// 重なり具合
	const float overlap_x = sum_half_w - Math::Abs(diff_x);
	const float overlap_y = sum_half_h - Math::Abs(diff_y);

	if (overlap_x > 0.0f && overlap_y > 0.0f) {
		if (push_out != nullptr) {
			// XとYのうち、浅くめり込んでいる方向に押し出す
			if (overlap_x < overlap_y) {
				push_out->x = (diff_x > 0.0f) ? overlap_x : -overlap_x;
				push_out->y = 0.0f;
			}
			else {
				push_out->x = 0.0f;
				push_out->y = (diff_y > 0.0f) ? overlap_y : -overlap_y;
			}
		}

		return true;
	}

	return false;
}

bool Yaxl::BoxCollider2D::IsCollide(const CircleCollider2D& other, Vector2* push_out) const {
	const float half_w = size.x * 0.5f;
	const float half_h = size.y * 0.5f;

	const float min_x = center.x - half_w;
	const float max_x = center.x + half_w;
	const float min_y = center.y - half_h;
	const float max_y = center.y + half_h;

	// 矩形上で、円の中心に最も近い点を求める
	Vector2 closest;
	closest.x = Math::Clamp(other.center.x, min_x, max_x);
	closest.y = Math::Clamp(other.center.y, min_y, max_y);

	// 最近接点から円の中心へのベクトル
	const float diff_x = other.center.x - closest.x;
	const float diff_y = other.center.y - closest.y;
	const float sqr_dist = (diff_x * diff_x) + (diff_y * diff_y);

	// 衝突していない
	if (sqr_dist > other.radius * other.radius) {
		return false;
	}

	if (push_out != nullptr) {
		// 円の中心が矩形の完全に内側に入り込んでいる場合
		if (sqr_dist == 0.0f) {
			float dist_left = other.center.x - min_x;
			float dist_right = max_x - other.center.x;
			float dist_bottom = other.center.y - min_y;
			float dist_top = max_y - other.center.y;

			float min_dist = dist_left;
			Vector2 push_dir{ -1.0f, 0.0f };

			if (dist_right < min_dist) {
				min_dist = dist_right; push_dir = Vector2{ 1.0f, 0.0f };
			}
			if (dist_bottom < min_dist) {
				min_dist = dist_bottom; push_dir = Vector2{ 0.0f, -1.0f };
			}
			if (dist_top < min_dist) {
				min_dist = dist_top; push_dir = Vector2{ 0.0f, 1.0f };
			}

			push_out->x = push_dir.x * (min_dist + other.radius);
			push_out->y = push_dir.y * (min_dist + other.radius);
		}
		else {
			float dist = Math::Sqrt(sqr_dist);
			float overlap = other.radius - dist;
			push_out->x = (diff_x / dist) * overlap;
			push_out->y = (diff_y / dist) * overlap;
		}
	}

	return true;
}

bool Yaxl::BoxCollider2D::IsCollide(const RectCollider2D& other, Vector2* push_out) const {
	return IsCollide(other.ToBoxCollider2D(), push_out);
}

void Yaxl::BoxCollider2D::Draw(float scale, Color* color) const {
	const float half_w = size.x * 0.5f * scale;
	const float half_h = size.y * 0.5f * scale;
	Vector2 p{ center.x - half_w , center.y - half_h };
	Vector2 s = size * scale;
	DrawRect2D(&p, &s, color);
}

Vector2 Yaxl::BoxCollider2D::Position() const {
	return center - size * 0.5f;
}

Vector2 Yaxl::BoxCollider2D::Center() const {
	return center;
}

BoxCollider2D Yaxl::BoxCollider2D::Translate(const Vector2& pos) const {
	return BoxCollider2D{ center + pos, size };
}

Vector2 Yaxl::BoxCollider2D::Size() const {
	return size;
}

RectCollider2D Yaxl::BoxCollider2D::ToRectCollider2D() const {
	return RectCollider2D{ center - size * 0.5f, size };
}
