#include "YaxlColor.h"

#include "YaxlMath.h"

using namespace Yaxl;

Color::Color() :
	Vector4() {
}

Color::Color(float r, float g, float b, float a) :
	Vector4(r, g, b, a) {
}

Color::Color(const Vector4& v) :
	Vector4(v.x, v.y, v.z, v.w) {
}

float Color::Grayscale() const {
	// Unity準拠
	return 0.2126f * r + 0.7152f * g + 0.0722f * b;
}

float Color::MaxColorComponent() const {
	return Math::Max(Math::Max(r, g), b);
}

Color Color::Gamma() const {
	// 近似
	return Color(
		Math::Pow(r, 1.0f / 2.2f),
		Math::Pow(g, 1.0f / 2.2f),
		Math::Pow(b, 1.0f / 2.2f),
		a
	);
}

Color Color::Linear() const {
	return Color(
		Math::Pow(r, 2.2f),
		Math::Pow(g, 2.2f),
		Math::Pow(b, 2.2f),
		a
	);
}

Color Color::HSVToRGB(float H, float S, float V, bool hdr) {
	Color white = Color::White();
	if (S == 0.0f) {
		white.r = V;
		white.g = V;
		white.b = V;
		return white;
	}

	if (V == 0.0f) {
		return Color::Black();
	}

	white.r = 0.0f;
	white.g = 0.0f;
	white.b = 0.0f;

	float h = H * 6.0f;
	int i = Math::FloorToInt(h);
	float f = h - static_cast<float>(i);
	float p = V * (1.0f - S);
	float q = V * (1.0f - S * f);
	float t = V * (1.0f - S * (1.0f - f));

	switch (i) {
	case 0: white.r = V; white.g = t; white.b = p; break;
	case 1: white.r = q; white.g = V; white.b = p; break;
	case 2: white.r = p; white.g = V; white.b = t; break;
	case 3: white.r = p; white.g = q; white.b = V; break;
	case 4: white.r = t; white.g = p; white.b = V; break;
	case 5: white.r = V; white.g = p; white.b = q; break;
	case 6: white.r = V; white.g = t; white.b = p; break;
	case -1: white.r = V; white.g = p; white.b = q; break;
	default: break;
	}

	if (hdr == false) {
		white.r = Math::Clamp01(white.r);
		white.g = Math::Clamp01(white.g);
		white.b = Math::Clamp01(white.b);
	}

	return white;
}

void Color::RGBToHSV(const Color& rgbColor, float& H, float& S, float& V) {
	float cmax = Math::Max(Math::Max(rgbColor.r, rgbColor.g), rgbColor.b);
	float cmin = Math::Min(Math::Min(rgbColor.r, rgbColor.g), rgbColor.b);
	float diff = cmax - cmin;

	V = cmax;

	if (cmax == 0.0f) {
		S = 0.0f;
		H = 0.0f;
		return;
	}

	S = diff / cmax;

	if (diff == 0.0f) {
		H = 0.0f;
		return;
	}

	if (cmax == rgbColor.r) {
		H = 60.0f * ((rgbColor.g - rgbColor.b) / diff);
	}
	else if (cmax == rgbColor.g) {
		H = 60.0f * ((rgbColor.b - rgbColor.r) / diff) + 120.0f;
	}
	else if (cmax == rgbColor.b) {
		H = 60.0f * ((rgbColor.r - rgbColor.g) / diff) + 240.0f;
	}

	if (H < 0.0f) {
		H += 360.0f;
	}

	// Unityの仕様に合わせてHは0.0〜1.0で返す
	H /= 360.0f;
}

Color Color::Clear() {
    return Color(0.0f, 0.0f, 0.0f, 0.0f);
}

Color Color::Black() {
	return Color(0.0f, 0.0f, 0.0f, 1.0f);
}

Color Color::White() {
	return Color(1.0f, 1.0f, 1.0f, 1.0f);
}

Color Color::Red() {
	return Color(1.0f, 0.0f, 0.0f, 1.0f);
}

Color Color::Blue() {
	return Color(0.0f, 0.0f, 1.0f, 1.0f);
}

Color Color::Green() {
	return Color(0.0f, 1.0f, 0.0f, 1.0f);
}

Color Color::Yellow() {
	return Color(1.0f, 0.92f, 0.016f, 1.0f);
}

Color Color::Cyan() {
	return Color(0.0f, 1.0f, 1.0f, 1.0f);
}

Color Color::Gray() {
	return Color(0.5f, 0.5f, 0.5f, 1.0f);
}

Color Color::Grey() {
	return Color(0.5f, 0.5f, 0.5f, 1.0f);
}

Color Color::Magenta() {
	return Color(1.0f, 0.0f, 1.0f, 1.0f);
}
