#include "YaxlGame.h"

#include <GLFW/glfw3.h>
#include "Core/Time/YaxlTimeInternal.h"

using namespace Yaxl;

Yaxl::Game::Game(int width, int height, const char* title, int target_fps, int tick_rate) {
    // グラフィックデバイスの生成と初期化
    graphics_device_ = new GraphicsDevice();
    bool is_success = graphics_device_->Init(width, height, title);

	// 失敗したらグラフィックデバイスを解放
    if (is_success == false) {
		ClearGraphicsDevice();
		return;
    }

	// 初期設定の保存
	Yaxl::SetTargetFps(target_fps);
	Yaxl::Internal::SetTickRate(tick_rate);
}

Yaxl::Game::~Game() {
	ClearGraphicsDevice();
}

int Yaxl::Game::run() {
	if (graphics_device_ == nullptr) {
		return -1;
	}

	// 実行中にする
	is_running_ = true;

	// 開始処理を呼び出す
	start();

	// 時間管理の初期化
	double prev_time = glfwGetTime();
	double tick_accumulator = 0.0f;

	// 1tickあたりに必要な時間（秒）を計算する
	const double tick_interval = 1.0f / Yaxl::GetTickRate();

	// メインループ
	while (is_running_ == true) {
		// ウィンドウを閉じる必要があれば抜ける
		if (graphics_device_->IsWindowClosed()) {
			break;
		}
		// ゲームの実行が終了したら抜ける
		if (is_running() == false) {
			break;
		}

		// 経過時間を取得
		const double current_time = glfwGetTime();
		const double frame_time = current_time - prev_time;

		// FPSを制限する
		const int target_fps = Yaxl::GetTargetFps();
		if (target_fps > 0) {
			const double target_frame_time = 1.0 / target_fps;
			// 目標時間に達していない
			if (frame_time < target_frame_time) {
				continue;
			}
		}

		// 入力の更新
		Yaxl::Input::Update(graphics_device_);

		// 時間の更新
		prev_time = current_time;
		Yaxl::Internal::SetDeltaTime(static_cast<float>(frame_time));

		// tick処理を呼び出す
		tick_accumulator += frame_time;
		while (tick_accumulator >= tick_interval) {
			tick();
			Yaxl::Internal::IncrementTickCount();
			tick_accumulator -= tick_interval;
		}


		// 更新処理を呼び出す
		update();
		// 描画処理を呼び出す
		draw();

		// ウィンドウに描画結果を表示
		graphics_device_->SwapBuffers();
	}

	// 終了処理を呼び出す
	end();

	// 実行終了
	is_running_ = false;
	// グラフィックデバイスを解放
	ClearGraphicsDevice();

	return 0;
}

void Yaxl::Game::ClearGraphicsDevice() {
	if (graphics_device_ != nullptr) {
		delete graphics_device_;
		graphics_device_ = nullptr;
	}
}
