// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : グラフィック関連API
//					ユーザーに見せたくない処理を分けている
// -----------------------------------------------------------------------------------------

#ifndef YAXL_GRAPHICS_INTERNAL_H_
#define YAXL_GRAPHICS_INTERNAL_H_

namespace Yaxl::Internal {
/// <summary>
/// 論理解像度の設定
/// </summary>
/// <param name="width">= 幅</param>
/// <param name="height">= 高さ</param>
void SetLogicalWindowSize(float width, float height);

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
/// 初期化
/// </summary>
void InitGraphics();

/// <summary>
/// 解放
/// </summary>
void ClearGraphics();

/// <summary>
/// シェーダーの適用
/// </summary>
/// <param name="id">= シェーダーID</param>
void ApplyShader(unsigned int id);

/// <summary>
/// テクスチャをバインド
/// </summary>
/// <param name="id">= テクスチャID</param>
/// <param name="slot">= バインド先のスロット番号</param>
void BindTexture(unsigned int id, unsigned int slot = 0);

}	// namespace Yaxl end

#endif
