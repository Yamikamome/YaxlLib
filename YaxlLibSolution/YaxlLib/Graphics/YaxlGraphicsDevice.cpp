#include "YaxlGraphicsDevice.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Yaxl::GraphicsDevice::GraphicsDevice() {
    window_handle_ = nullptr;
    window_width_ = 0;
    window_height_ = 0;
    is_initialized_ = false;
}

Yaxl::GraphicsDevice::~GraphicsDevice() {
    if (is_initialized_ == true) {
        Clear();
    }
}

bool Yaxl::GraphicsDevice::Init(int width, int height, const char* title) {
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

    // GLADの初期化を行い、失敗したら終了
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
        glfwDestroyWindow(window_handle_);
        glfwTerminate();
        return false;
    }

    // 初期化に成功したら情報を保存
    window_width_ = width;
    window_height_ = height;
    is_initialized_ = true;

    return true;
}

void Yaxl::GraphicsDevice::Clear() {
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

void Yaxl::GraphicsDevice::Update() {
	if (is_initialized_ == false) {
		return;
	}

	// OSイベントの取得
	glfwPollEvents();

	// 背景をクリア
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Yaxl::GraphicsDevice::SwapBuffers() {
    if (is_initialized_ == false) {
        return;
    }

    // 描画したバッファにスワップ
    glfwSwapBuffers(window_handle_);
}

bool Yaxl::GraphicsDevice::IsWindowClosed() const {
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

GLFWwindow* Yaxl::GraphicsDevice::GetWindowHandle() const {
    return window_handle_;
}
