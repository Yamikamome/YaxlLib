// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 2D用トランスフォーム
// -----------------------------------------------------------------------------------------

#ifndef YAXL_TRANSFORM_2D_H_
#define YAXL_TRANSFORM_2D_H_

#include "YaxlLibLink.h"
#include "Math/YaxlMatrix3x3.h"
#include "Math/YaxlVector2.h"
#include <vector>

namespace Yaxl {

	class Transform2D {
	public:
		Transform2D() = default;

		~Transform2D();

	public:
		// 座標系の指定
		enum class Space {
			Self,   // ローカル座標系
			World   // ワールド座標系
		};

	public:

#pragma region [Direction]

		/// <summary>
		/// ワールド座標系のトランスフォームの赤軸を取得
		/// </summary>
		/// <returns>赤軸</returns>
		Vector2 Right() const;

		/// <summary>
		/// ワールド座標系のトランスフォームの赤軸を設定
		/// </summary>
		/// <param name="value">= 赤軸</param>
		void Right(const Vector2& value);

		/// <summary>
		/// ワールド座標系のトランスフォームの緑軸を取得
		/// </summary>
		/// <returns>緑軸</returns>
		Vector2 Up() const;

		/// <summary>
		/// ワールド座標系のトランスフォームの緑軸を設定
		/// </summary>
		/// <param name="value">= 緑軸</param>
		void Up(const Vector2& value);

#pragma endregion

#pragma region [Scale]

		/// <summary>
		/// ワールド座標系のスケールを取得
		/// </summary>
		/// <returns>スケール</returns>
		Vector2 LossyScale() const;

		/// <summary>
		/// 親のトランスフォームから見た相対的なスケールを取得
		/// </summary>
		/// <returns>スケール</returns>
		Vector2 LocalScale() const;

		/// <summary>
		/// 親のトランスフォームから見た相対的なスケールを設定
		/// </summary>
		/// <param name="value">= スケール</param>
		void LocalScale(const Vector2& value);

#pragma endregion

#pragma region [Position]

		/// <summary>
		/// ワールド座標系のトランスフォームの位置を取得
		/// </summary>
		/// <returns>位置</returns>
		Vector2 Position() const;

		/// <summary>
		/// ワールド座標系のトランスフォームの位置を設定
		/// </summary>
		/// <param name="value">= 位置</param>
		void Position(const Vector2& value);

		/// <summary>
		/// 親のトランスフォームから見た相対的な位置を取得
		/// </summary>
		/// <returns>位置</returns>
		Vector2 LocalPosition() const;

		/// <summary>
		/// 親のトランスフォームから見た相対的な位置を設定
		/// </summary>
		/// <param name="value">= 位置</param>
		void LocalPosition(const Vector2& value);

#pragma endregion

#pragma region [Rotation]

		/// <summary>
		/// ワールド座標系でのトランスフォームの回転を取得
		/// </summary>
		/// <returns>回転</returns>
		float Rotation() const;

		/// <summary>
		/// ワールド座標系でのトランスフォームの回転を設定
		/// </summary>
		/// <param name="value">= 回転</param>
		void Rotation(float value);

		/// <summary>
		/// 親のトランスフォームから見た相対的な回転を取得
		/// </summary>
		/// <returns>回転</returns>
		float LocalRotation() const;

		/// <summary>
		/// 親のトランスフォームから見た相対的な回転を設定
		/// </summary>
		/// <param name="value">= 回転</param>
		void LocalRotation(float value);

		/// <summary>
		/// 指定したトランスフォームに向く
		/// </summary>
		/// <param name="target">= トランスフォーム</param>
		void LookAt(const Transform2D& target);

		/// <summary>
		/// 指定したワールド座標系の位置に向く
		/// </summary>
		/// <param name="target">= 位置</param>
		void LookAt(const Vector2& target);

		/// <summary>
		/// 指定した角度分回転させる
		/// </summary>
		/// <param name="angle">= 角度</param>
		void Rotate(float angle);

		/// <summary>
		/// ワールド座標系の位置を中心に指定した角度分回転させる
		/// </summary>
		/// <param name="point">= 位置</param>
		/// <param name="angle">= 角度</param>
		void RotateAround(const Vector2& point, float angle);

#pragma endregion

#pragma region [Translate]

		/// <summary>
		/// 指定した方向に移動させる
		/// </summary>
		/// <param name="x">= 青軸の移動量</param>
		/// <param name="y">= 緑軸の移動量</param>
		/// <param name="relative_to">= 座標系</param>
		void Translate(float x, float y, Space relative_to = Space::Self);

		/// <summary>
		/// 指定した方向に移動させる
		/// </summary>
		/// <param name="translation">= 移動量</param>
		/// <param name="relative_to">= 座標系</param>
		void Translate(const Vector2& translation, Space relative_to = Space::Self);

		/// <summary>
		/// 指定した方向に移動させる
		/// </summary>
		/// <param name="x">= 青軸の移動量</param>
		/// <param name="y">= 緑軸の移動量</param>
		/// <param name="relative_to">= 起点となるトランスフォーム</param>
		void Translate(float x, float y, const Transform2D& relative_to);

		/// <summary>
		/// 指定した方向に移動させる
		/// </summary>
		/// <param name="translation">= 移動量</param>
		/// <param name="relative_to">= 起点となるトランスフォーム</param>
		void Translate(const Vector2& translation, const Transform2D& relative_to);

#pragma endregion

#pragma region [Matrix]

		/// <summary>
		/// ローカル座標からワールド座標へ変換した行列
		/// </summary>
		/// <returns>行列</returns>
		Matrix3x3 LocalToWorldMatrix() const;

		/// <summary>
		/// ワールド座標からローカル座標へ変換した行列
		/// </summary>
		/// <returns>行列</returns>
		Matrix3x3 WorldToLocalMatrix() const;

#pragma endregion

#pragma region [Transform]

		/// <summary>
		/// ローカル空間からワールド空間へ位置を変換（スケール・回転・平行移動）
		/// </summary>
		/// <param name="position">= 位置</param>
		/// <returns>位置</returns>
		Vector2 TransformPoint(const Vector2& position) const;

		/// <summary>
		/// ローカル空間からワールド空間へベクトルを変換（スケール・回転）
		/// </summary>
		/// <param name="vector">= ベクトル</param>
		/// <returns>ベクトル</returns>
		Vector2 TransformVector(const Vector2& vector) const;

		/// <summary>
		/// ローカル空間からワールド空間へ方向を変換（回転）
		/// </summary>
		/// <param name="direction">= 方向</param>
		/// <returns>方向</returns>
		Vector2 TransformDirection(const Vector2& direction) const;

		/// <summary>
		/// ワールド空間からローカル空間へ位置を変換
		/// </summary>
		/// <param name="position">= 位置</param>
		/// <returns>位置</returns>
		Vector2 InverseTransformPoint(const Vector2& position) const;

		/// <summary>
		/// ワールド空間からローカル空間へベクトルを変換
		/// </summary>
		/// <param name="vector">= ベクトル</param>
		/// <returns>ベクトル</returns>
		Vector2 InverseTransformVector(const Vector2& vector) const;

		/// <summary>
		/// ワールド空間からローカル空間へ方向を変換
		/// </summary>
		/// <param name="direction">= 方向</param>
		/// <returns>方向</returns>
		Vector2 InverseTransformDirection(const Vector2& direction) const;

#pragma endregion

#pragma region [Hierarchy]

		/// <summary>
		/// 親を設定
		/// </summary>
		/// <param name="parent">= 親のトランスフォーム</param>
		void SetParent(Transform2D* parent);

		/// <summary>
		/// 親を設定
		/// </summary>
		/// <param name="parent">= 親のトランスフォーム</param>
		/// <param name="world_position_stays">= 現在のワールド座標系の位置を維持するかどうか</param>
		void SetParent(Transform2D* parent, bool world_position_stays);

		/// <summary>
		/// 親を取得
		/// </summary>
		/// <returns>親が存在すれば親のトランスフォームを、親が存在しなければnullptrを返す</returns>
		Transform2D* GetParent() const;

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
		Vector2 local_position_ = Vector2::Zero();
		// ローカル座標系の回転（度数法）
		float local_rotation_ = 0.0f;
		// ローカル座標系のスケール
		Vector2 local_scale_ = Vector2::One();

		// 親
		Transform2D* parent_ = nullptr;
		// 子
		std::vector<Transform2D*> children_;

		// キャッシュ（強制上書きを通すためmutable）
	private:
		// ワールド座標系の位置
		mutable Vector2 position_ = Vector2::Zero();
		// ワールド座標系の回転（度数法）
		mutable float rotation_ = 0.0f;
		// ワールド座標系のスケール
		mutable Vector2 scale_ = Vector2::One();

		// ワールド変換行列キャッシュ
		mutable Matrix3x3 local_to_world_matrix_ = Matrix3x3::Identity();
		// ローカル変換行列キャッシュ
		mutable Matrix3x3 world_to_local_matrix_ = Matrix3x3::Identity();

		// フラグが偽になってからトランスフォームに更新があったかどうか
		mutable bool has_changed_ = true;
	};

}	// namespace Yaxl end

#endif
