// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 4Dベクトルを矩形として扱っている
// -----------------------------------------------------------------------------------------

#ifndef YAXL_RECT_H_
#define YAXL_RECT_H_

#include "YaxlLibLink.h"
#include "YaxlVector4.h"

namespace Yaxl {

class Rect : public Vector4 {
public:
	// デフォルトコンストラクタ（0.0, 0.0, 0.0, 0.0f）
	Rect();
	// コンストラクタ
	Rect(float left, float top, float right, float bottom);
	// 暗黙変換
	Rect(const Vector4& v);
};

}// namespace Yaxl end

#endif
