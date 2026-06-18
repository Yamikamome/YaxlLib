#include "YaxlTransform.h"
#include <algorithm>
#include "Math/YaxlMath.h"

using namespace Yaxl;

Yaxl::Transform::~Transform() {
	DetachChildren();
	DetachParent();
}

Vector3 Yaxl::Transform::Forward() const {
	return Rotation() * Vector3::Forward();
}

void Yaxl::Transform::Forward(const Vector3& value) {
	Rotation(Quaternion::LookRotation(value.Normalized(), Vector3::Up()));
}

Vector3 Yaxl::Transform::Right() const {
	return Rotation() * Vector3::Right();
}

void Yaxl::Transform::Right(const Vector3& value) {
	Rotation(Quaternion::FromToRotation(Right(), value.Normalized()) * Rotation());
}

Vector3 Yaxl::Transform::Up() const {
	return Rotation() * Vector3::Up();
}

void Yaxl::Transform::Up(const Vector3& value) {
	Rotation(Quaternion::FromToRotation(Up(), value.Normalized()) * Rotation());
}

Vector3 Yaxl::Transform::LossyScale() const {
	UpdateCache();
	return scale_;
}

Vector3 Yaxl::Transform::LocalScale() const {
	return local_scale_;
}

void Yaxl::Transform::LocalScale(const Vector3& value) {
	local_scale_ = value;
	SetChanged();
}

Vector3 Yaxl::Transform::Position() const {
	UpdateCache();
	return position_;
}

void Yaxl::Transform::Position(const Vector3& value) {
	if (parent_ != nullptr) {
		LocalPosition(parent_->InverseTransformPoint(value));
	}
	else {
		LocalPosition(value);
	}
}

Vector3 Yaxl::Transform::LocalPosition() const {
	return local_position_;
}

void Yaxl::Transform::LocalPosition(const Vector3& value) {
	local_position_ = value;
	SetChanged();
}

Quaternion Yaxl::Transform::Rotation() const {
	UpdateCache();
	return rotation_;
}

void Yaxl::Transform::Rotation(const Quaternion& value) {
	if (parent_ != nullptr) {
		LocalRotation(Quaternion::Inverse(parent_->Rotation()) * value);
	}
	else {
		LocalRotation(value);
	}
}

Quaternion Yaxl::Transform::LocalRotation() const {
	return local_rotation_;
}

void Yaxl::Transform::LocalRotation(const Quaternion& value) {
	local_rotation_ = value;
	local_rotation_.Normalize();
	SetChanged();
}

void Yaxl::Transform::LookAt(const Transform& target, const Vector3& world_up) {
	LookAt(target.Position(), world_up);
}

void Yaxl::Transform::LookAt(const Vector3& target, const Vector3& world_up) {
	Rotation(Quaternion::LookRotation(target - Position(), world_up));
}

void Yaxl::Transform::Rotate(const Vector3& eulers, Space relative_to) {
	Rotate(Quaternion::Euler(eulers.x, eulers.y, eulers.z), relative_to);
}

void Yaxl::Transform::Rotate(float pitch, float yaw, float roll, Space relative_to) {
	Rotate(Vector3(pitch, yaw, roll), relative_to);
}

void Yaxl::Transform::Rotate(const Vector3& axis, float angle, Space relative_to) {
	Rotate(Quaternion::AngleAxis(angle, axis), relative_to);
}

void Yaxl::Transform::Rotate(const Quaternion& rotate, Space relative_to) {
	if (relative_to == Space::Self) {
		LocalRotation(local_rotation_ * rotate);
	}
	else {
		Rotation(rotate * Rotation());
	}
}

void Yaxl::Transform::RotateAround(const Vector3& point, const Vector3& axis, float angle) {
	Quaternion q = Quaternion::AngleAxis(angle, axis);
	Position(point + q * (Position() - point));
	Rotation(q * Rotation());
}

Vector3 Yaxl::Transform::EulerAngles() const {
	return Rotation().EulerAngles();
}

void Yaxl::Transform::EulerAngles(const Vector3& value) {
	Rotation(Quaternion::Euler(value));
}

void Yaxl::Transform::EulerAngles(float pitch, float yaw, float roll) {
	EulerAngles(Vector3(pitch, yaw, roll));
}

Vector3 Yaxl::Transform::LocalEulerAngles() const {
	return local_rotation_.EulerAngles();
}

void Yaxl::Transform::LocalEulerAngles(const Vector3& value) {
	LocalRotation(Quaternion::Euler(value));
}

void Yaxl::Transform::Translate(float x, float y, float z, Space relative_to) {
	Translate(Vector3(x, y, z), relative_to);
}

void Yaxl::Transform::Translate(const Vector3& translation, Space relative_to) {
	if (relative_to == Space::Self) {
		Position(Position() + TransformDirection(translation));
	}
	else {
		Position(Position() + translation);
	}
}

void Yaxl::Transform::Translate(float x, float y, float z, const Transform& relative_to) {
	Translate(Vector3(x, y, z), relative_to);
}

void Yaxl::Transform::Translate(const Vector3& translation, const Transform& relative_to) {
	Position(Position() + relative_to.TransformDirection(translation));
}

Matrix4x4 Yaxl::Transform::LocalToWorldMatrix() const {
	UpdateCache();
	return local_to_world_matrix_;
}

Matrix4x4 Yaxl::Transform::WorldToLocalMatrix() const {
	UpdateCache();
	return world_to_local_matrix_;
}

Vector3 Yaxl::Transform::TransformPoint(const Vector3& position) const {
	return LocalToWorldMatrix().MultiplyPoint(position);
}

Vector3 Yaxl::Transform::TransformVector(const Vector3& vector) const {
	return LocalToWorldMatrix().MultiplyVector(vector);
}

Vector3 Yaxl::Transform::TransformDirection(const Vector3& direction) const {
	return Rotation() * direction;
}

Vector3 Yaxl::Transform::InverseTransformPoint(const Vector3& position) const {
	return WorldToLocalMatrix().MultiplyPoint(position);
}

Vector3 Yaxl::Transform::InverseTransformVector(const Vector3& vector) const {
	return WorldToLocalMatrix().MultiplyVector(vector);
}

Vector3 Yaxl::Transform::InverseTransformDirection(const Vector3& direction) const {
	return Quaternion::Inverse(Rotation()) * direction;
}

void Yaxl::Transform::SetParent(Transform* parent) {
	SetParent(parent, true);
}

void Yaxl::Transform::SetParent(Transform* parent, bool world_position_stays) {
	if (parent_ == parent) return;

	const Vector3 current_world_pos = Position();
	const Quaternion current_world_rot = Rotation();
	const Vector3 current_world_scale = LossyScale();

	DetachParent();
	parent_ = parent;

	if (parent_ != nullptr) {
		if (world_position_stays) {
			// 親が切り替わってもワールド空間での見え方を維持する
			Vector3 parent_scale = parent_->LossyScale();
			local_scale_.x = Math::SafeDivide(current_world_scale.x, parent_scale.x);
			local_scale_.y = Math::SafeDivide(current_world_scale.y, parent_scale.y);
			local_scale_.z = Math::SafeDivide(current_world_scale.z, parent_scale.z);

			local_rotation_ = Quaternion::Inverse(parent_->Rotation()) * current_world_rot;
			local_rotation_.Normalize();

			local_position_ = parent_->InverseTransformPoint(current_world_pos);
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

Transform* Yaxl::Transform::GetParent() const {
	return parent_;
}

void Yaxl::Transform::DetachParent() {
	if (parent_ != nullptr) {
		auto& children = parent_->children_;

		children.erase(
			std::remove(children.begin(), children.end(), this),
			children.end()
		);

		parent_ = nullptr;
	}
}

void Yaxl::Transform::DetachChildren() {
	while (!children_.empty()) {
		Transform* child = children_.front();
		// 子の親を自分の親に引き継ぐ
		child->SetParent(parent_);
	}
}

void Yaxl::Transform::SetChanged() {
	if (has_changed_) {
		return;
	}

	has_changed_ = true;

	// 子にも動いたことを通知する
	for (Transform* child : children_) {
		child->SetChanged();
	}
}

void Yaxl::Transform::UpdateCache() const {
	if (!has_changed_) {
		return;
	}

	// ローカル行列生成
	const Matrix4x4 local_matrix = Matrix4x4::TRS(local_position_, local_rotation_, local_scale_);

	if (parent_ != nullptr) {
		// 親を先に更新
		parent_->UpdateCache();

		local_to_world_matrix_ = parent_->local_to_world_matrix_ * local_matrix;
		position_ = local_to_world_matrix_.GetPosition();

		// 情報が復元できるよう直接階層計算を行う
		rotation_ = parent_->rotation_ * local_rotation_;
		rotation_.Normalize();
		scale_ = Vector3::Scale(parent_->scale_, local_scale_);
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
