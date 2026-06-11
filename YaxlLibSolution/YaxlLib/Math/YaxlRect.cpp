#include "YaxlRect.h"

using namespace Yaxl;

Rect::Rect() :
	Vector4() {
}

Rect::Rect(float left, float top, float right, float bottom) {
	Vector4(left, top, right, bottom);
}

Rect::Rect(const Vector4& v) :
	Vector4(v.x, v.y, v.z, v.w) {
}
