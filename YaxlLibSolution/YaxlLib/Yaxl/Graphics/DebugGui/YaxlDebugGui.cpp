#include "YaxlDebugGui.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace Yaxl;

bool DebugGui::is_initialized_ = false;

void DebugGui::Init(GLFWwindow* window) {
	if (is_initialized_ == true) {
		return;
	}
	if (window == nullptr) {
		return;
	}

	// ImGuiのコンテキストを作成
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	// スタイルを設定
	ImGui::StyleColorsDark();

	// キーボード操作有効にする
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	// ゲームパッド操作を有効にする
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	// バックエンドの初期化
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	// OpenGLのバージョンに合わせて初期化
	ImGui_ImplOpenGL3_Init("#version 330");

	is_initialized_ = true;
}

void DebugGui::Clear() {
	if (is_initialized_ == false) {
		return;
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	is_initialized_ = false;
}

void DebugGui::Begin() {
	if (is_initialized_ == false) {
		return;
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void DebugGui::End() {
	if (is_initialized_ == false) {
		return;
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
