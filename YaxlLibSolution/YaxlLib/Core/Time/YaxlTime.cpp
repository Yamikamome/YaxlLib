#include "YaxlTime.h"
#include "YaxlTimeInternal.h"

// FPS制限値
static int target_fps_ = 0;
// 経過時間（秒）
static float delta_time_ = 0.0f;
// 1秒間にTickを実行する目標回数
static int tick_rate_ = 20;
// Tickの実行回数
static unsigned long long tick_count_ = 0;

void Yaxl::SetTargetFps(int fps) {
	target_fps_ = fps;
}

int Yaxl::GetTargetFps() {
	return target_fps_;
}

int Yaxl::GetTickRate() {
	return tick_rate_;
}

float Yaxl::GetDeltaTime() {
	return delta_time_;
}

unsigned long long Yaxl::GetTickCount() {
	return tick_count_;
}

void Yaxl::Internal::SetDeltaTime(float delta_time) {
	delta_time_ = delta_time;
}

void Yaxl::Internal::SetTickRate(int tick_rate) {
	tick_rate_ = tick_rate;
}

void Yaxl::Internal::IncrementTickCount() {
	tick_count_++;
}