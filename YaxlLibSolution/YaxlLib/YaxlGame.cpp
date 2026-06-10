#include "YaxlGame.h"

#include <GLFW/glfw3.h>
#include "Core/Time/YaxlTimeInternal.h"
#include "Graphics/DebugGui/YaxlDebugGui.h"
#include "Graphics/YaxlGraphicsInternal.h"

using namespace Yaxl;
using namespace Internal;

Game::Game(int width, int height, const char* title, int target_fps, int tick_rate) {
    // グラフィックデバイスの生成と初期化
    graphics_device_ = new GraphicsDevice();
    bool is_success = graphics_device_->Init(width, height, title);

	// 失敗したらグラフィックデバイスを解放
    if (is_success == false) {
		ClearGraphicsDevice();
		return;
    }

	// 初期設定の保存
	SetTargetFps(target_fps);
	SetTickRate(tick_rate);
}

Game::~Game() {
	ClearGraphicsDevice();
}

int Game::run() {
	if (graphics_device_ == nullptr) {
		return -1;
	}

	// 実行中にする
	is_running_ = true;

	// グラフィックの初期化
	InitGraphics();

	// ImGuiの初期化
	GLFWwindow* window = graphics_device_->GetWindowHandle();
	DebugGui::Init(window);

	// 時間管理の初期化
	double prev_time = glfwGetTime();
	double tick_accumulator = 0.0f;
	double fps_time_accumulator = 0.0;
	int frame_counter = 0;
	// 1tickあたりに必要な時間（秒）を計算する
	const double tick_interval = 1.0f / GetTickRate();

	// 開始処理を呼び出す
	start();

	// メインループ
	while (is_running_ == true) {
		// グラフィックデバイスを更新
		graphics_device_->Update();

		// ウィンドウを閉じる必要があれば抜ける
		if (graphics_device_->IsWindowClosed()) {
			break;
		}

		// 経過時間を取得
		const double current_time = glfwGetTime();
		const double frame_time = current_time - prev_time;
		// FPSを制限する
		const int target_fps = GetTargetFps();
		if (target_fps > 0) {
			const double target_frame_time = 1.0 / target_fps;
			// 目標時間に達していない
			if (frame_time < target_frame_time) {
				continue;
			}
		}

		// 入力の更新
		Input::Update(graphics_device_);

		// ImGuiを開始
		DebugGui::Begin();

		// 時間の更新
		prev_time = current_time;
		SetDeltaTime(static_cast<float>(frame_time));
		// FPSの計算
		frame_counter++;
		fps_time_accumulator += frame_time;
		if (fps_time_accumulator >= 1.0) {
			SetCurrentFps(static_cast<float>(frame_counter) / static_cast<float>(fps_time_accumulator));
			frame_counter = 0;
			fps_time_accumulator -= 1.0; // 端数は残す
		}

		// tick処理を呼び出す
		tick_accumulator += frame_time;
		while (tick_accumulator >= tick_interval) {
			tick();
			IncrementTickCount();
			tick_accumulator -= tick_interval;
		}

		// 更新処理を呼び出す
		update();
		// 描画処理を呼び出す
		draw();

		// ImGuiを終了
		DebugGui::End();

		// ウィンドウに描画結果を表示
		graphics_device_->SwapBuffers();

		// ゲームの実行が終了したら抜ける
		if (is_running() == false) {
			break;
		}
	}

	// 終了処理を呼び出す
	end();

	// 実行終了
	is_running_ = false;

	// ImGuiを解放
	DebugGui::Clear();
	// グラフィックを解放
	ClearGraphics();
	// グラフィックデバイスを解放
	ClearGraphicsDevice();

	return 0;
}

void Game::ClearGraphicsDevice() {
	if (graphics_device_ != nullptr) {
		delete graphics_device_;
		graphics_device_ = nullptr;
	}
}
