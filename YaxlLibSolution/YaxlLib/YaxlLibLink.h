// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : リンカー設定を自動で行う
// -----------------------------------------------------------------------------------------

#ifndef YAXL_LIB_LINK_H_
#define YAXL_LIB_LINK_H_

#ifdef _MSC_VER // Visual Studioでコンパイルされている場合のみ有効
#ifdef _DEBUG
	// デバッグモードの時は _d 付きのライブラリを探してリンクする
#pragma comment(lib, "YaxlLib_d.lib")
#else
	// リリースモードの時は通常のライブラリを探してリンクする
#pragma comment(lib, "YaxlLib.lib")
#endif
#endif

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "YaxlLib.lib")

#ifdef _DEBUG
#pragma comment(linker, "/NODEFAULTLIB:msvcrt.lib")
#endif

#endif