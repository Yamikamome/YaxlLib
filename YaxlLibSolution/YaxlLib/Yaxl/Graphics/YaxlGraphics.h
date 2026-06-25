// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : グラフィック関連API
// -----------------------------------------------------------------------------------------

#ifndef YAXL_GRAPHICS_H_
#define YAXL_GRAPHICS_H_

#include "YaxlLibLink.h"

namespace Yaxl {
	class Shader;
	class Texture;

	class Color;
	class Matrix3x3;
	class Matrix4x4;
	class Rect;
	class Vector2;
	class Vector3;
	class Vector4;

#pragma region [Screen]

	/// <summary>
	/// ビュー行列を設定
	/// </summary>
	/// <param name="view_matrix">ビュー行列</param>
	void SetViewMatrix(const Matrix4x4* view_matrix);
	
	/// <summary>
	/// プロジェクション行列を設定
	/// </summary>
	/// <param name="proj_matrix">プロジェクション行列</param>
	void SetProjectionMatrix(const Matrix4x4* proj_matrix);

	/// <summary>
	/// 現在のビュー行列を取得
	/// </summary>
	/// <returns>ビュー行列</returns>
	Matrix4x4 GetViewMatrix();

	/// <summary>
	/// 現在のプロジェクション行列を取得
	/// </summary>
	/// <returns>プロジェクション行列</returns>
	Matrix4x4 GetProjectionMatrix();

	/// <summary>
	/// 論理解像度の取得
	/// </summary>
	/// <returns>幅</returns>
	float GetLogicalWindowWidth();

	/// <summary>
	/// 論理解像度の取得
	/// </summary>
	/// <returns>高さ</returns>
	float GetLogicalWindowHeight();

	/// <summary>
	/// アスペクト比を取得
	/// </summary>
	/// <returns>比率</returns>
	float GetAspect();

#pragma endregion

#pragma region [Shader]

	/// <summary>
	/// シェーダーの読み込み
	/// </summary>
	/// <param name="id">= シェーダーID</param>
	/// <param name="vert_path">= 頂点シェーダーパス</param>
	/// <param name="frag_path">= フラグメントシェーダーパス</param>
	/// <returns>読み込みに成功したら真を、読み込みに失敗したら偽を返す</returns>
	bool LoadShader(unsigned int id, const char* vert_path, const char* frag_path);

	/// <summary>
	/// テキストからのシェーダーの読み込み
	/// </summary>
	/// <param name="id">= シェーダーID</param>
	/// <param name="vert_code">= 頂点シェーダーのテキスト</param>
	/// <param name="frag_code">= フラグメントシェーダーのテキスト</param>
	/// <returns>読み込みに成功したら真を、読み込みに失敗したら偽を返す</returns>
	bool LoadShaderString(unsigned int id, const char* vert_code, const char* frag_code);

	/// <summary>
	/// シェーダーの破棄
	/// </summary>
	/// <param name="id">= シェーダーID</param>
	void DeleteShader(unsigned int id);

	/// <summary>
	/// シェーダーの開始
	/// </summary>
	/// <param name="id">= シェーダーID</param>
	void BeginShader(unsigned int id);

	/// <summary>
	/// シェーダーの終了
	/// </summary>
	void EndShader();

	/// <summary>
	/// シェーダーの取得
	/// </summary>
	/// <param name="id">= シェーダーID</param>
	/// <returns>見つかればシェーダーを、見つからなければnullptrを返す</returns>
	Shader* GetShader(unsigned int id);

	/// <summary>
	/// 現在のシェーダーのUniform位置を取得
	/// </summary>
	/// <param name="name">= パラメータ名</param>
	/// <returns>見つかれば位置を、見つからなければ-1を返す</returns>
	int GetShaderUniform(const char* name);

	/// <summary>
	/// シェーダーにパラメータを設定
	/// </summary>
	/// <param name="name">= パラメータ名</param>
	/// <param name="param">= パラメータ</param>
	void SetShaderParamInt(const char* name, int param);

	/// <summary>
	/// シェーダーにパラメータを設定
	/// </summary>
	/// <param name="name">= パラメータ名</param>
	/// <param name="param">= パラメータ</param>
	void SetShaderParamFloat(const char* name, float param);

	/// <summary>
	/// シェーダーにパラメータを設定
	/// </summary>
	/// <param name="name">= パラメータ名</param>
	/// <param name="param">= パラメータ</param>
	void SetShaderParamVector2(const char* name, Vector2* param);

	/// <summary>
	/// シェーダーにパラメータを設定
	/// </summary>
	/// <param name="name">=パラメータ名</param>
	/// <param name="param">= パラメータ</param>
	void SetShaderParamVector3(const char* name, Vector3* param);

	/// <summary>
	/// シェーダーにパラメータを設定
	/// </summary>
	/// <param name="name">=パラメータ名</param>
	/// <param name="param">= パラメータ</param>
	void SetShaderParamVector4(const char* name, Vector4* param);

	/// <summary>
	/// シェーダーにパラメータを設定
	/// </summary>
	/// <param name="name">= パラメータ名</param>
	/// <param name="param">= パラメータ</param>
	void SetShaderParamMatrix3x3(const char* name, Matrix3x3* param);

	/// <summary>
	/// シェーダーにパラメータを設定
	/// </summary>
	/// <param name="name">= パラメータ名</param>
	/// <param name="param">= パラメータ</param>
	void SetShaderParamMatrix4x4(const char* name, Matrix4x4* param);

	/// <summary>
	/// デフォルトの2Dスプライト用シェーダーをバインドする
	/// </summary>
	/// <param name="id">= シェーダーID</param>
	void BindDefault2DSpriteShader(unsigned int id);

	/// <summary>
	/// バインドされているデフォルトの2Dスプライト用シェーダーIDを取得する
	/// </summary>
	/// <returns>= シェーダーID</returns>
	unsigned int GetBindDefault2DSpriteShader();

	/// <summary>
	/// デフォルトの3Dスプライト用シェーダーをバインドする
	/// </summary>
	/// <param name="id">= シェーダーID</param>
	void BindDefault3DSpriteShader(unsigned int id);

	/// <summary>
	/// バインドされているデフォルトの3Dスプライト用シェーダーIDを取得する
	/// </summary>
	/// <returns>= シェーダーID</returns>
	unsigned int GetBindDefault3DSpriteShader();

#pragma endregion

#pragma region [2DSimple]

	/// <summary>
	/// 2D矩形を描画
	/// </summary>
	/// <param name="position">= 位置</param>
	/// <param name="scale">= スケール</param>
	/// <param name="color">= カラー</param>
	/// <param name="angle">= 角度</param>
	void DrawRect2D(Vector2* position, Vector2* scale, Color* color = nullptr, float angle = 0.0f);

	/// <summary>
	/// 2D矩形を描画
	/// </summary>
	/// <param name="rect">= 描画範囲</param>
	/// <param name="color">= カラー</param>
	/// <param name="angle">= 角度</param>
	void DrawRect2D(Rect* rect, Color* color = nullptr, float angle = 0.0f);

	/// <summary>
	/// 2D円を描画
	/// </summary>
	/// <param name="position">= 位置</param>
	/// <param name="radius">= 半径</param>
	/// <param name="color">= カラー</param>
	void DrawCircle2D(Vector2* position, float radius, Color* color = nullptr);

#pragma endregion

#pragma region [Texture]

	/// <summary>
	/// テクスチャの読み込み
	/// </summary>
	/// <param name="id">= テクスチャID</param>
	/// <param name="file_path">= 画像ファイルパス</param>
	/// <returns>読み込みに成功したら真を、読み込みに失敗したら偽を返す</returns>
	bool LoadTexture(unsigned int id, const char* file_path);

	/// <summary>
	/// テクスチャの破棄
	/// </summary>
	/// <param name="id">= テクスチャID</param>
	void DeleteTexture(unsigned int id);

	/// <summary>
	/// テクスチャの取得
	/// </summary>
	/// <param name="id">= テクスチャID</param>
	/// <returns>見つかればテクスチャを、見つからなければnullptrを返す</returns>
	Texture* GetTexture(unsigned int id);

#pragma endregion

#pragma region [Sprite]

	/// <summary>
	/// 2Dスプライトを描画
	/// </summary>
	/// <param name="id">= テクスチャID</param>
	/// <param name="position">= 位置</param>
	/// <param name="rect">= 描画範囲</param>
	/// <param name="scale">= スケール</param>
	/// <param name="center">= 中心</param>
	/// <param name="color">= カラー</param>
	/// <param name="angle">= 角度</param>
	void DrawSprite2D(unsigned int id, Vector2* position, Rect* rect = nullptr, Vector2* scale = nullptr, Vector2* center = nullptr, Color* color = nullptr, float angle = 0.0f);

	/// <summary>
	/// 3Dスプライトを描画
	/// </summary>
	/// <param name="id">= テクスチャID</param>
	/// <param name="position">= 位置</param>
	/// <param name="rect">= 描画範囲</param>
	/// <param name="scale">= スケール</param>
	/// <param name="center">= 中心</param>
	/// <param name="color">= カラー</param>
	/// <param name="angle">= 角度</param>
	void DrawSprite3D(unsigned int id, Vector3* position, Rect* rect = nullptr, Vector2* scale = nullptr, Vector2* center = nullptr, Color* color = nullptr, float angle = 0.0f);

#pragma endregion

}	// namespace Yaxl end

#endif
