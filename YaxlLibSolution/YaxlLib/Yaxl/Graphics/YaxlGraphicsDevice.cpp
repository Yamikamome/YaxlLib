#include "YaxlGraphicsDevice.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "YaxlGraphics.h"
#include "YaxlGraphicsInternal.h"

using namespace Yaxl;

GraphicsDevice::GraphicsDevice() {
    window_handle_ = nullptr;
    window_width_ = 0;
    window_height_ = 0;
    is_initialized_ = false;
}

GraphicsDevice::~GraphicsDevice() {
    if (is_initialized_ == true) {
        Clear();
    }
}

bool GraphicsDevice::Init(int width, int height, const char* title) {
    if (is_initialized_ == true) {
        return false;
    }

    // GLFWの初期化を行い、失敗したら終了
    if (glfwInit() == GLFW_FALSE) {
        return false;
    }

    // OpenGL 4.5 Core Profile を要求する
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ウィンドウの生成
    window_handle_ = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (window_handle_ == nullptr) {
        glfwTerminate();
        return false;
    }

    // 描画対象として設定
    glfwMakeContextCurrent(window_handle_);

	// コールバック内でこのクラスのメンバ変数にアクセスできるようにポインタを登録
	glfwSetWindowUserPointer(window_handle_, this);
	// リサイズ時のコールバックを登録
	glfwSetFramebufferSizeCallback(window_handle_, FramebufferSizeCallback);

	// 初期論理解像度を初期化時のウィンドウサイズに合わせる
	Internal::SetLogicalWindowSize(static_cast<float>(width), static_cast<float>(height));

    // GLADの初期化を行い、失敗したら終了
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
        glfwDestroyWindow(window_handle_);
        glfwTerminate();
        return false;
    }

	// 垂直同期は使わない
	glfwSwapInterval(0);

    // 初期化に成功したら情報を保存
    window_width_ = width;
    window_height_ = height;
    is_initialized_ = true;

    return true;
}

void GraphicsDevice::Clear() {
    if (is_initialized_ == false) {
        return;
    }

    if (window_handle_ != nullptr) {
        glfwDestroyWindow(window_handle_);
        window_handle_ = nullptr;
    }

    // GLFWを終了
    glfwTerminate();
    is_initialized_ = false;
}

void GraphicsDevice::Update() {
	if (is_initialized_ == false) {
		return;
	}

	// OSイベントの取得
	glfwPollEvents();

	// 背景をクリア
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsDevice::SwapBuffers() {
    if (is_initialized_ == false) {
        return;
    }

    // 描画したバッファにスワップ
    glfwSwapBuffers(window_handle_);
}

bool GraphicsDevice::IsWindowClosed() const {
    if (window_handle_ == nullptr) {
        return true;
    }

    if (glfwWindowShouldClose(window_handle_) == 0) {
        return false;
    }
    else {
        return true;
    }
}

GLFWwindow* GraphicsDevice::GetWindowHandle() const {
    return window_handle_;
}

void Yaxl::GraphicsDevice::SetFullScreen(bool is_fullscreen) {
	if (is_fullscreen_ == is_fullscreen) return;

	if (is_fullscreen) {
		// フルスクリーン化する前の状態を保存
		glfwGetWindowPos(window_handle_, &saved_window_pos_x_, &saved_window_pos_y_);
		glfwGetWindowSize(window_handle_, &saved_window_width_, &saved_window_height_);

		// メインモニターを取得
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		// フルスクリーン化
		glfwSetWindowMonitor(window_handle_, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else {
		// ウィンドウモードに復元
		glfwSetWindowMonitor(window_handle_, nullptr, saved_window_pos_x_, saved_window_pos_y_, saved_window_width_, saved_window_height_, 0);
	}

	is_fullscreen_ = is_fullscreen;
}

void Yaxl::GraphicsDevice::SetBorderless(bool is_borderless) {
	if (is_borderless_ == is_borderless) return;

	// フルスクリーン中はボーダーレス設定を無視する
	if (!is_fullscreen_) {
		// GLFW_DECORATEDをfalseにすると枠なし
		glfwSetWindowAttrib(window_handle_, GLFW_DECORATED, is_borderless ? GLFW_FALSE : GLFW_TRUE);
	}

	is_borderless_ = is_borderless;
}

void Yaxl::GraphicsDevice::ToggleFullScreen() {
	SetFullScreen(!is_fullscreen_);
}

void Yaxl::GraphicsDevice::ToggleBorderless() {
	SetBorderless(!is_borderless_);
}

void Yaxl::GraphicsDevice::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	GraphicsDevice* device = static_cast<GraphicsDevice*>(glfwGetWindowUserPointer(window));
	if (device == nullptr || width == 0 || height == 0) return;

	// 目的のアスペクト比
	const float target_aspect = GetLogicalWindowWidth() / GetLogicalWindowHeight();
	// 現在のウィンドウのアスペクト比
	const float window_aspect = static_cast<float>(width) / static_cast<float>(height);

	int view_width = width;
	int view_height = height;
	int view_x = 0;
	int view_y = 0;

	if (window_aspect > target_aspect) {
		// ウィンドウが横に長すぎる場合は左右にピラーボックスを生成する
		view_width = static_cast<int>(height * target_aspect);
		view_x = (width - view_width) / 2;
	}
	else {
		// ウィンドウが縦に長すぎる場合は上下にレターボックスを生成する
		view_height = static_cast<int>(width / target_aspect);
		view_y = (height - view_height) / 2;
	}

	// 描画領域を再設定）
	glViewport(view_x, view_y, view_width, view_height);
}
