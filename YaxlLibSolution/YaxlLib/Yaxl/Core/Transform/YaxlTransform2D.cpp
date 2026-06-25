#include "YaxlTransform2D.h"
#include <algorithm>
#include "Yaxl/Math/YaxlMath.h"

using namespace Yaxl;

Yaxl::Transform2D::~Transform2D() {
	DetachChildren();
	DetachParent();
}

Vector2 Yaxl::Transform2D::Right() const {
	const float rad = Rotation() * Math::Deg2Rad;
	return Vector2(Math::Cos(rad),Math::Sin(rad));
}

void Yaxl::Transform2D::Right(const Vector2& value) {
	Rotation(Math::Atan2(value.y, value.x) * Math::Rad2Deg);
}

Vector2 Yaxl::Transform2D::Up() const {
	const float rad = Rotation() * Math::Deg2Rad;
	return Vector2(-Math::Sin(rad), Math::Cos(rad));
}

void Yaxl::Transform2D::Up(const Vector2& value) {
	Rotation(Math::Atan2(-value.x, value.y) * Math::Rad2Deg);
}

Vector2 Yaxl::Transform2D::LossyScale() const {
	UpdateCache();
	return scale_;
}

Vector2 Yaxl::Transform2D::LocalScale() const {
	return local_scale_;
}

void Yaxl::Transform2D::LocalScale(const Vector2& value) {
	local_scale_ = value;
	SetChanged();
}

Vector2 Yaxl::Transform2D::Position() const {
	UpdateCache();
	return position_;
}

void Yaxl::Transform2D::Position(const Vector2& value) {
	if (parent_ != nullptr) {
		LocalPosition(parent_->InverseTransformPoint(value));
	}
	else {
		LocalPosition(value);
	}
}

Vector2 Yaxl::Transform2D::LocalPosition() const {
	return local_position_;
}

void Yaxl::Transform2D::LocalPosition(const Vector2& value) {
	local_position_ = value;
	SetChanged();
}

float Yaxl::Transform2D::Rotation() const {
	UpdateCache();
	return rotation_;
}

void Yaxl::Transform2D::Rotation(float value) {
	if (parent_ != nullptr) {
		LocalRotation(value - parent_->Rotation());
	}
	else {
		LocalRotation(value);
	}
}

float Yaxl::Transform2D::LocalRotation() const {
	return local_rotation_;
}

void Yaxl::Transform2D::LocalRotation(float value) {
	local_rotation_ = value;
	SetChanged();
}

void Yaxl::Transform2D::LookAt(const Transform2D& target) {
	LookAt(target.Position());
}

void Yaxl::Transform2D::LookAt(const Vector2& target) {
	const Vector2 dir = target - Position();

	Rotation(Math::Atan2(dir.y, dir.x) * Math::Rad2Deg);
}

void Yaxl::Transform2D::Rotate(float angle) {
	Rotation(Rotation() + angle);
}

void Yaxl::Transform2D::RotateAround(const Vector2& point, float angle) {
	const float rad = angle * Math::Deg2Rad;

	const float c = Math::Cos(rad);
	const float s = Math::Sin(rad);

	const Vector2 offset = Position() - point;
	const Vector2 rotated(offset.x * c - offset.y * s, offset.x * s + offset.y * c);

	Position(point + rotated);
	Rotate(angle);
}

void Yaxl::Transform2D::Translate(float x, float y, Space relative_to) {
	Translate(Vector2(x, y), relative_to);
}

void Yaxl::Transform2D::Translate(const Vector2& translation, Space relative_to) {
	if (relative_to == Space::Self) {
		Position(Position() + TransformDirection(translation));
	}
	else {
		Position(Position() + translation);
	}
}

void Yaxl::Transform2D::Translate(float x, float y, const Transform2D& relative_to) {
	Translate(Vector2(x, y), relative_to);
}

void Yaxl::Transform2D::Translate(const Vector2& translation, const Transform2D& relative_to) {
	Position(Position() + relative_to.TransformDirection(translation));
}

Matrix3x3 Yaxl::Transform2D::LocalToWorldMatrix() const {
	UpdateCache();
	return local_to_world_matrix_;
}

Matrix3x3 Yaxl::Transform2D::WorldToLocalMatrix() const {
	UpdateCache();
	return world_to_local_matrix_;
}

Vector2 Yaxl::Transform2D::TransformPoint(const Vector2& position) const {
	return LocalToWorldMatrix().MultiplyPoint2D(position);
}

Vector2 Yaxl::Transform2D::TransformVector(const Vector2& vector) const {
	return LocalToWorldMatrix().MultiplyVector2D(vector);
}

Vector2 Yaxl::Transform2D::TransformDirection(const Vector2& direction) const {
	const Vector2 right = Right();
	const Vector2 up = Up();

	return right * direction.x + up * direction.y;
}

Vector2 Yaxl::Transform2D::InverseTransformPoint(const Vector2& position) const {
	return WorldToLocalMatrix().MultiplyPoint2D(position);
}

Vector2 Yaxl::Transform2D::InverseTransformVector(const Vector2& vector) const {
	return WorldToLocalMatrix().MultiplyVector2D(vector);
}

Vector2 Yaxl::Transform2D::InverseTransformDirection(const Vector2& direction) const {
	const float rad = -Rotation() * Math::Deg2Rad;
	const float c = Math::Cos(rad);
	const float s = Math::Sin(rad);

	return Vector2(direction.x * c - direction.y * s, direction.x * s + direction.y * c);
}

void Yaxl::Transform2D::SetParent(Transform2D* parent) {
	SetParent(parent, true);
}

void Yaxl::Transform2D::SetParent(Transform2D* parent, bool world_position_stays) {
	if (parent_ == parent) return;

	const Vector2 current_world_pos = Position();
	const float current_world_rot = Rotation();
	const Vector2 current_world_scale = LossyScale();

	DetachParent();
	parent_ = parent;

	if (parent_ != nullptr) {
		if (world_position_stays){
			// 親が切り替わってもワールド空間での見え方を維持する
			Vector2 parent_scale = parent_->LossyScale();
			local_scale_.x = Math::SafeDivide(current_world_scale.x, parent_scale.x);
			local_scale_.y = Math::SafeDivide(current_world_scale.y, parent_scale.y);

			local_position_ = parent_->InverseTransformPoint(current_world_pos);
			local_rotation_ =current_world_rot - parent_->Rotation();
		}
		parent_->children_.push_back(this);
	}
	else {
		// 親が外れた場合は、現在のワールド情報をそのままにする
		local_rotation_ = current_world_rot;
		local_position_ = current_world_pos;
		local_scale_ = current_world_scale;
	}

	// 親が変わったのでキャッシュを再計算させる
	SetChanged();
}

Transform2D* Yaxl::Transform2D::GetParent() const {
	return parent_;
}

void Yaxl::Transform2D::DetachParent() {
	if (parent_ != nullptr) {
		auto& children = parent_->children_;

		children.erase(
			std::remove(children.begin(), children.end(), this),
			children.end()
		);

		parent_ = nullptr;
	}
}

void Yaxl::Transform2D::DetachChildren() {
	while (!children_.empty()) {
		Transform2D* child = children_.front();
		// 子の親を自分の親に引き継ぐ
		child->SetParent(parent_);
	}
}

void Yaxl::Transform2D::SetChanged() {
	if (has_changed_) {
		return;
	}

	has_changed_ = true;

	// 子にも動いたことを通知する
	for (Transform2D* child : children_) {
		child->SetChanged();
	}
}

void Yaxl::Transform2D::UpdateCache() const {
	if (!has_changed_) {
		return;
	}

	// ローカル行列生成
	const Matrix3x3 local_matrix = Matrix3x3::TRS(local_position_, local_rotation_, local_scale_);

	if (parent_ != nullptr) {
		// 親を先に更新
		parent_->UpdateCache();

		local_to_world_matrix_ = parent_->local_to_world_matrix_ * local_matrix;
		position_ = local_to_world_matrix_.GetPosition();

		// 情報が復元できるよう直接階層計算を行う
		rotation_ = parent_->rotation_ + local_rotation_;
		scale_ = Vector2(parent_->scale_.x * local_scale_.x, parent_->scale_.y * local_scale_.y);
	}
	else {
		local_to_world_matrix_ = local_matrix;
		position_ = local_position_;
		rotation_ = local_rotation_;
		scale_ = local_scale_;
	}

	// 逆行列
	world_to_local_matrix_ = local_to_world_matrix_.Inverse();

	has_changed_ = false;
}
