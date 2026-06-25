#include "YaxlGame.h"

#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>

#include "Yaxl/Core/Audio/YaxlAudioInternal.h"
#include "Yaxl/Core/Time/YaxlTimeInternal.h"
#include "Yaxl/Graphics/YaxlGraphicsDevice.h"
#include "Yaxl/Graphics/YaxlGraphicsInternal.h"
#include "Yaxl/Graphics/DebugGui/YaxlDebugGui.h"

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
	// サウンドの初期化
	InitAudio();

	// ImGuiの初期化
	GLFWwindow* window = graphics_device_->GetWindowHandle();
	DebugGui::Init(window);

	// 時間管理の初期化
	double prev_time = glfwGetTime();
	double tick_accumulator = 0.0f;
	double fps_time_accumulator = 0.0f;
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
		double current_time = glfwGetTime();
		double frame_time = current_time - prev_time;

		// FPSを制限
		const int target_fps = GetTargetFps();
		if (target_fps > 0) {
			const double target_frame_time = 1.0f / target_fps;

			// 目標時間に達していない場合は待機
			if (frame_time < target_frame_time) {
				// OSのsleepを使って待機（精度対策で少し早めに終わる）
				double sleep_time = target_frame_time - frame_time - 0.02f;
				if (sleep_time > 0.0f) {
					std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleep_time * 1000.0f)));
				}

				// sleepを抜けたら精度対策の時間が終わるまで普通に更新
				while ((glfwGetTime() - prev_time) < target_frame_time) {
					// 何もしない
				}

				// 待機が終了したら情報を更新
				current_time = glfwGetTime();
				frame_time = current_time - prev_time;
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
		if (fps_time_accumulator >= 1.0f) {
			SetCurrentFps(static_cast<float>(frame_counter) / static_cast<float>(fps_time_accumulator));
			frame_counter = 0;
			fps_time_accumulator -= 1.0f; // 端数は残す
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
	// サウンドを解放
	ClearAudio();

	// グラフィックデバイスを解放
	ClearGraphicsDevice();

	return 0;
}

void Yaxl::Game::SetFullScreen(bool is_fullscreen) {
	if (graphics_device_ != nullptr) {
		graphics_device_->SetFullScreen(is_fullscreen);
	}
}

void Yaxl::Game::SetBorderless(bool is_borderless) {
	if (graphics_device_ != nullptr) {
		graphics_device_->SetBorderless(is_borderless);
	}
}

void Yaxl::Game::ToggleFullScreen() {
	if (graphics_device_ != nullptr) {
		graphics_device_->ToggleFullScreen();
	}
}

void Yaxl::Game::ToggleBorderless() {
	if (graphics_device_ != nullptr) {
		graphics_device_->ToggleBorderless();
	}
}

void Game::ClearGraphicsDevice() {
	if (graphics_device_ != nullptr) {
		delete graphics_device_;
		graphics_device_ = nullptr;
	}
}
