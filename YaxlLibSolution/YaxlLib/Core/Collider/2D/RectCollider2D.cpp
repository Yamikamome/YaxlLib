#include "RectCollider2D.h"
#include "BoxCollider2D.h"
#include "CircleCollider2D.h"

#include "Graphics/YaxlGraphics.h"
#include "Math/YaxlMath.h"

using namespace Yaxl;

Yaxl::RectCollider2D::RectCollider2D() :
	position{ 0.0f, 0.0f },
	size{ 0.0f, 0.0f } {
}

Yaxl::RectCollider2D::RectCollider2D(const Vector2& position, const Vector2& size) :
	position{ position },
	size{ size } {
}

bool Yaxl::RectCollider2D::IsCollide(const Collider2D& other, Vector2* push_out) const {
	Vector2 push;
	const bool is_hit = other.IsCollide(*this, push_out ? &push : nullptr);
	if (is_hit && push_out) {
		push_out->x = -push.x;
		push_out->y = -push.y;
	}

	return is_hit;
}

bool Yaxl::RectCollider2D::IsCollide(const BoxCollider2D& other, Vector2* push_out) const {
	return ToBoxCollider2D().IsCollide(other, push_out);
}

bool Yaxl::RectCollider2D::IsCollide(const CircleCollider2D& other, Vector2* push_out) const {
	return ToBoxCollider2D().IsCollide(other, push_out);
}

bool Yaxl::RectCollider2D::IsCollide(const RectCollider2D& other, Vector2* push_out) const {
	return ToBoxCollider2D().IsCollide(other.ToBoxCollider2D(), push_out);
}

void Yaxl::RectCollider2D::Draw(float scale, Color* color) const {
	Vector2 s = size * scale;
	Vector2 p = position;
	DrawRect2D(&p, &s, color);
}

Vector2 Yaxl::RectCollider2D::Position() const {
	return position;
}

Vector2 Yaxl::RectCollider2D::Center() const {
	return position + size * 0.5f;
}

RectCollider2D Yaxl::RectCollider2D::Translate(const Vector2& pos) const {
	return RectCollider2D{ position + pos, size };
}

Vector2 Yaxl::RectCollider2D::Size() const {
	return size;
}

BoxCollider2D Yaxl::RectCollider2D::ToBoxCollider2D() const {
	return BoxCollider2D{ position + size * 0.5f, size };
}
