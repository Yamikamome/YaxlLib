// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : トランスフォーム 関数のみUnityのTransform互換（2026/06/15時点）
//					https://docs.unity3d.com/ja/2020.2/ScriptReference/Transform.html
// -----------------------------------------------------------------------------------------

#ifndef YAXL_TRANSFORM_H_
#define YAXL_TRANSFORM_H_

#include "YaxlLibLink.h"
#include "Math/YaxlMatrix4x4.h"
#include "Math/YaxlQuaternion.h"
#include "Math/YaxlVector3.h"
#include <vector>

namespace Yaxl {

class Transform {
public:
	Transform() = default;

	~Transform();

public:
	// 座標系の指定
	enum class Space {
		Self,   // ローカル座標系
		World   // ワールド座標系
	};

public:

#pragma region [Direction]

	/// <summary>
	/// ワールド座標系のトランスフォームの青軸を取得
	/// </summary>
	/// <returns>青軸</returns>
	Vector3 Forward() const;

	/// <summary>
	/// ワールド座標系のトランスフォームの青軸を設定
	/// </summary>
	/// <param name="value"> = 青軸</param>
	void Forward(const Vector3& value);

	/// <summary>
	/// ワールド座標系のトランスフォームの赤軸を取得
	/// </summary>
	/// <returns>赤軸</returns>
	Vector3 Right() const;

	/// <summary>
	/// ワールド座標系のトランスフォームの赤軸を設定
	/// </summary>
	/// <param name="value">= 赤軸</param>
	void Right(const Vector3& value);

	/// <summary>
	/// ワールド座標系のトランスフォームの緑軸を取得
	/// </summary>
	/// <returns>緑軸</returns>
	Vector3 Up() const;

	/// <summary>
	/// ワールド座標系のトランスフォームの緑軸を設定
	/// </summary>
	/// <param name="value">= 緑軸</param>
	void Up(const Vector3& value);

#pragma endregion

#pragma region [Scale]

	/// <summary>
	/// ワールド座標系のスケールを取得
	/// </summary>
	/// <returns>スケール</returns>
	Vector3 LossyScale() const;

	/// <summary>
	/// 親のトランスフォームから見た相対的なスケールを取得
	/// </summary>
	/// <returns>スケール</returns>
	Vector3 LocalScale() const;

	/// <summary>
	/// 親のトランスフォームから見た相対的なスケールを設定
	/// </summary>
	/// <param name="value">= スケール</param>
	void LocalScale(const Vector3& value);

#pragma endregion

#pragma region [Position]

	/// <summary>
	/// ワールド座標系のトランスフォームの位置を取得
	/// </summary>
	/// <returns>位置</returns>
	Vector3 Position() const;

	/// <summary>
	/// ワールド座標系のトランスフォームの位置を設定
	/// </summary>
	/// <param name="value">= 位置</param>
	void Position(const Vector3& value);

	/// <summary>
	/// 親のトランスフォームから見た相対的な位置を取得
	/// </summary>
	/// <returns>位置</returns>
	Vector3 LocalPosition() const;

	/// <summary>
	/// 親のトランスフォームから見た相対的な位置を設定
	/// </summary>
	/// <param name="value">= 位置</param>
	void LocalPosition(const Vector3& value);

#pragma endregion

#pragma region [Rotation]

	/// <summary>
	/// クオータニオンとして保存されるワールド座標系でのトランスフォームの回転を取得
	/// </summary>
	/// <returns>回転</returns>
	Quaternion Rotation() const;

	/// <summary>
	/// クオータニオンとして保存されるワールド座標系でのトランスフォームの回転を設定
	/// </summary>
	/// <param name="value">= 回転</param>
	void Rotation(const Quaternion& value);

	/// <summary>
	/// 親のトランスフォームから見た相対的な回転を取得
	/// </summary>
	/// <returns>回転</returns>
	Quaternion LocalRotation() const;

	/// <summary>
	/// 親のトランスフォームから見た相対的な回転を設定
	/// </summary>
	/// <param name="value">= 回転</param>
	void LocalRotation(const Quaternion& value);

	/// <summary>
	/// 指定したトランスフォームに向く
	/// </summary>
	/// <param name="target">= トランスフォーム</param>
	/// <param name="world_up">= 緑軸</param>
	void LookAt(const Transform& target, const Vector3& world_up = Vector3::Up());

	/// <summary>
	/// 指定したワールド座標系の位置に向く
	/// </summary>
	/// <param name="target">= 位置</param>
	/// <param name="world_up">= 緑軸</param>
	void LookAt(const Vector3& target, const Vector3& world_up = Vector3::Up());

	/// <summary>
	/// Z X Yの順番で指定した角度分回転させる
	/// </summary>
	/// <param name="eulers">= オイラー角</param>
	/// <param name="relative_to">= 座標系</param>
	void Rotate(const Vector3& eulers, Space relative_to = Space::Self);

	/// <summary>
	/// ロール、ピッチ、ヨーの順番で指定した角度分回転させる
	/// </summary>
	/// <param name="pitch">= ピッチ</param>
	/// <param name="yaw">= ヨー</param>
	/// <param name="roll">= ロール</param>
	/// <param name="relative_to">= 座標系</param>
	void Rotate(float pitch, float yaw, float roll, Space relative_to = Space::Self);

	/// <summary>
	/// 指定した軸を起点に指定した角度分回転させる
	/// </summary>
	/// <param name="axis">= 軸</param>
	/// <param name="angle">= 角度</param>
	/// <param name="relative_to">= 座標系</param>
	void Rotate(const Vector3& axis, float angle, Space relative_to = Space::Self);

	/// <summary>
	/// 指定したクオータニオン分回転させる
	/// </summary>
	/// <param name="rotate">= クオータニオン</param>
	/// <param name="relative_to">= 座標系</param>
	void Rotate(const Quaternion& rotate, Space relative_to = Space::Self);

	/// <summary>
	/// ワールド座標系の位置を中心とした軸で指定した角度分回転させる
	/// </summary>
	/// <param name="point">= 位置</param>
	/// <param name="axis">= 軸</param>
	/// <param name="angle">= 角度</param>
	void RotateAround(const Vector3& point, const Vector3& axis, float angle);

#pragma endregion
	
#pragma region [Euler]

	/// <summary>
	/// オイラー角としての角度を取得
	/// </summary>
	/// <returns>角度</returns>
	Vector3 EulerAngles() const;

	/// <summary>
	/// オイラー角としての角度を設定
	/// </summary>
	/// <param name="value">= 角度</param>
	void EulerAngles(const Vector3& value);

	/// <summary>
	/// オイラー角としての角度を設定
	/// </summary>
	/// <param name="pitch">= ピッチ</param>
	/// <param name="yaw">= ヨー</param>
	/// <param name="roll">= ロール</param>
	void EulerAngles(float pitch, float yaw, float roll);

	/// <summary>
	/// 親のトランスフォームから見た相対的なオイラー角としての回転を取得
	/// </summary>
	/// <returns>角度</returns>
	Vector3 LocalEulerAngles() const;

	/// <summary>
	/// 親のトランスフォームから見た相対的なオイラー角としての回転を設定
	/// </summary>
	/// <param name="value">= 角度</param>
	void LocalEulerAngles(const Vector3& value);

#pragma endregion

#pragma region [Translate]

	/// <summary>
	/// 指定した方向に移動させる
	/// </summary>
	/// <param name="x">= 青軸の移動量</param>
	/// <param name="y">= 緑軸の移動量</param>
	/// <param name="z">= 赤軸の移動量</param>
	/// <param name="relative_to">= 座標系</param>
	void Translate(float x, float y, float z, Space relative_to = Space::Self);

	/// <summary>
	/// 指定した方向に移動させる
	/// </summary>
	/// <param name="translation">= 移動量</param>
	/// <param name="relative_to">= 座標系</param>
	void Translate(const Vector3& translation, Space relative_to = Space::Self);

	/// <summary>
	/// 指定した方向に移動させる
	/// </summary>
	/// <param name="x">= 青軸の移動量</param>
	/// <param name="y">= 緑軸の移動量</param>
	/// <param name="z">= 赤軸の移動量</param>
	/// <param name="relative_to">= 起点となるトランスフォーム</param>
	void Translate(float x, float y, float z, const Transform& relative_to);

	/// <summary>
	/// 指定した方向に移動させる
	/// </summary>
	/// <param name="translation">= 移動量</param>
	/// <param name="relative_to">= 起点となるトランスフォーム</param>
	void Translate(const Vector3& translation, const Transform& relative_to);

#pragma endregion

#pragma region [Matrix]

	/// <summary>
	/// ローカル座標からワールド座標へ変換した行列
	/// </summary>
	/// <returns>行列</returns>
	Matrix4x4 LocalToWorldMatrix() const;

	/// <summary>
	/// ワールド座標からローカル座標へ変換した行列
	/// </summary>
	/// <returns>行列</returns>
	Matrix4x4 WorldToLocalMatrix() const;

#pragma endregion

#pragma region [Transform]

	/// <summary>
	/// ローカル空間からワールド空間へ位置を変換（スケール・回転・平行移動）
	/// </summary>
	/// <param name="position">= 位置</param>
	/// <returns>位置</returns>
	Vector3 TransformPoint(const Vector3& position) const;

	/// <summary>
	/// ローカル空間からワールド空間へベクトルを変換（スケール・回転）
	/// </summary>
	/// <param name="vector">= ベクトル</param>
	/// <returns>ベクトル</returns>
	Vector3 TransformVector(const Vector3& vector) const;

	/// <summary>
	/// ローカル空間からワールド空間へ方向を変換（回転）
	/// </summary>
	/// <param name="direction">= 方向</param>
	/// <returns>方向</returns>
	Vector3 TransformDirection(const Vector3& direction) const;

	/// <summary>
	/// ワールド空間からローカル空間へ位置を変換
	/// </summary>
	/// <param name="position">= 位置</param>
	/// <returns>位置</returns>
	Vector3 InverseTransformPoint(const Vector3& position) const;

	/// <summary>
	/// ワールド空間からローカル空間へベクトルを変換
	/// </summary>
	/// <param name="vector">= ベクトル</param>
	/// <returns>ベクトル</returns>
	Vector3 InverseTransformVector(const Vector3& vector) const;

	/// <summary>
	/// ワールド空間からローカル空間へ方向を変換
	/// </summary>
	/// <param name="direction">= 方向</param>
	/// <returns>方向</returns>
	Vector3 InverseTransformDirection(const Vector3& direction) const;

#pragma endregion

#pragma region [Hierarchy]

	/// <summary>
	/// 親を設定
	/// </summary>
	/// <param name="parent">= 親のトランスフォーム</param>
	void SetParent(Transform* parent);

	/// <summary>
	/// 親を設定
	/// </summary>
	/// <param name="parent">= 親のトランスフォーム</param>
	/// <param name="world_position_stays">= 現在のワールド座標系の位置を維持するかどうか</param>
	void SetParent(Transform* parent, bool world_position_stays);

	/// <summary>
	/// 親を取得
	/// </summary>
	/// <returns>親が存在すれば親のトランスフォームを、親が存在しなければnullptrを返す</returns>
	Transform* GetParent() const;

	/// <summary>
	/// 親から切り離す
	/// </summary>
	void DetachParent();

	/// <summary>
	/// 全ての子を親から切り離す
	/// </summary>
	void DetachChildren();

#pragma endregion

private:
	/// <summary>
	/// トランスフォームの更新を設定
	/// </summary>
	void SetChanged();

	/// <summary>
	/// トランスフォームのキャッシュを更新
	/// </summary>
	void UpdateCache() const;

private:
	// ローカル座標系の位置
	Vector3 local_position_ = Vector3::Zero();
	// ローカル座標系の回転
	Quaternion local_rotation_ = Quaternion::Identity();
	// ローカル座標系のスケール
	Vector3 local_scale_ = Vector3::One();

	// 親
	Transform* parent_ = nullptr;
	// 子
	std::vector<Transform*> children_;

	// キャッシュ（強制上書きを通すためmutable）
private:
	// ワールド座標系の位置
	mutable Vector3 position_ = Vector3::Zero();
	// ワールド座標系の回転
	mutable Quaternion rotation_ = Quaternion::Identity();
	// ワールド座標系のスケール
	mutable Vector3 scale_ = Vector3::One();

	// ワールド変換行列キャッシュ
	mutable Matrix4x4 local_to_world_matrix_ = Matrix4x4::Identity();
	// ローカル変換行列キャッシュ
	mutable Matrix4x4 world_to_local_matrix_ = Matrix4x4::Identity();

	// フラグが偽になってからトランスフォームに更新があったかどうか
	mutable bool has_changed_ = true;
};

}	// namespace Yaxl end

#endif
