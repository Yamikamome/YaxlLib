// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 4Dベクトルをカラー（RGBA）として扱っている
//					Unityのカラー互換（2026/06/08時点）
//					https://docs.unity3d.com/ja/2021.2/ScriptReference/Color.html
// -----------------------------------------------------------------------------------------

#ifndef YAXL_COLOR_H_
#define YAXL_COLOR_H_

#include "YaxlLibLink.h"
#include "YaxlVector4.h"

namespace Yaxl {

class Color : public Vector4 {
public:
	// デフォルトコンストラクタ（0.0, 0.0, 0.0）
	Color();
	// コンストラクタ
	Color(float r, float g, float b, float a = 1.0f);
	// 暗黙変換
	Color(const Vector4& v);

public:
	// グレースケール（輝度）を返す
	float Grayscale() const;
	// RGBの中で最も大きい値を返す
	float MaxColorComponent() const;
	// ガンマ空間
	Color Gamma() const;
	// リニア空間
	Color Linear() const;
	// HSV（色相、彩度、明度）からRGBカラーを作成
	static Color HSVToRGB(float H, float S, float V, bool hdr = true);
	// RGBカラーからHSV（色相、彩度、明度）を抽出
	static void RGBToHSV(const Color& rgbColor, float& H, float& S, float& V);

public:
	// 透明
	static Color Clear();
	// 黒
	static Color Black();
	// 白
	static Color White();
	// 赤
	static Color Red();
	// 青
	static Color Blue();
	// 緑
	static Color Green();
	// 黄
	static Color Yellow();
	// シアン
	static Color Cyan();
	// グレー
	static Color Gray();
	// グレー
	static Color Grey();
	// マゼンタ
	static Color Magenta();
};

}// namespace Yaxl end

#endif
