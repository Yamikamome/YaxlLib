// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : リンカー設定を自動で行う
// -----------------------------------------------------------------------------------------

#ifndef YAXL_LIB_LINK_H_
#define YAXL_LIB_LINK_H_

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "YaxlLib.lib")

#ifdef _DEBUG
#pragma comment(linker, "/NODEFAULTLIB:msvcrt.lib")
#endif

#endif