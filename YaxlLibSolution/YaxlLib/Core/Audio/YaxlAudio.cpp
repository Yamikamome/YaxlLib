#include "YaxlAudio.h"
#include "YaxlAudioInternal.h"

#define MINIAUDIO_IMPLEMENTATION	// 展開
#include <miniaudio/miniaudio.h>
#include <unordered_map>
#include <vector>
#include "Math/YaxlVector3.h"

namespace {
	struct SEPool {
		std::vector<ma_sound*> sounds;
		int index = 0;
	};

	struct SoundSystem {
		ma_engine engine{};
		ma_sound_group bgm_group{};
		ma_sound_group se_group{};

		std::unordered_map<unsigned int, SEPool> se_map;
		std::unordered_map<unsigned int, ma_sound*> bgm_map;

		// 現在再生中のBGM
		ma_sound* current_bgm = nullptr;
		// BGMの一時停止フラグ
		bool is_bgm_paused = false;      

		// サウンドリスナーの減衰値が0になる距離
		float max_distance = 25.0f;
		// サウンドリスナーの減衰値が1になる距離
		float min_distance = 5.0f;

		/// <summary>
		/// BGM停止
		/// </summary>
		void stop_current_bgm() {
			if (current_bgm && ma_sound_is_playing(current_bgm)) {
				ma_sound_stop(current_bgm);
				// 巻き戻しておく
				ma_sound_seek_to_pcm_frame(current_bgm, 0);
			}

			is_bgm_paused = false;
		}
	};

	SoundSystem* sound_system = nullptr;
}

bool Yaxl::Internal::InitAudio() {
	if (sound_system != nullptr) {
		return true;
	}

	sound_system = new SoundSystem();

	if (ma_engine_init(NULL, &sound_system->engine) != MA_SUCCESS) {
		delete sound_system;
		sound_system = nullptr;
		return false;
	}

	ma_sound_group_init(&sound_system->engine, 0, NULL, &sound_system->bgm_group);
	ma_sound_group_init(&sound_system->engine, 0, NULL, &sound_system->se_group);

	return true;
}

void Yaxl::Internal::ClearAudio() {
	if (sound_system == nullptr) {
		return;
	}

	DeleteAllBGM();
	DeleteAllSE();

	ma_sound_group_uninit(&sound_system->bgm_group);
	ma_sound_group_uninit(&sound_system->se_group);
	ma_engine_uninit(&sound_system->engine);

	delete sound_system;
	sound_system = nullptr;
}

bool Yaxl::LoadBGM(unsigned int id, const char* file_name, bool loop) {
	if (sound_system == nullptr) {
		return false;
	}

	// ロード済みか？
	if (sound_system->bgm_map.count(id) > 0) {
		return true;
	}

	// ストリーミング再生を指定して読み込み
	ma_sound* sound = new ma_sound();
	if (ma_sound_init_from_file(&sound_system->engine, file_name, MA_SOUND_FLAG_STREAM, &sound_system->bgm_group, NULL, sound) != MA_SUCCESS) {
		delete sound;
		return false;
	}

	// ループ指定
	ma_sound_set_looping(sound, loop ? MA_TRUE : MA_FALSE);
	sound_system->bgm_map[id] = sound;

	return true;
}

void Yaxl::DeleteBGM(unsigned int id) {
	if (sound_system == nullptr) {
		return;
	}

	// 読み込まれているか？
	auto it = sound_system->bgm_map.find(id);
	if (it == sound_system->bgm_map.end()) {
		return;
	}

	// もし再生中なら停止
	if (sound_system->current_bgm == it->second) {
		sound_system->stop_current_bgm();
		sound_system->current_bgm = nullptr;
	}

	ma_sound_uninit(it->second);
	delete it->second;
	sound_system->bgm_map.erase(it);
}

void Yaxl::DeleteAllBGM() {
	if (sound_system == nullptr) {
		return;
	}

	for (auto& pair : sound_system->bgm_map) {
		ma_sound_uninit(pair.second);
		delete pair.second;
	}

	sound_system->bgm_map.clear();
	sound_system->current_bgm = nullptr;
	sound_system->is_bgm_paused = false;
}

void Yaxl::PlayBGM(unsigned int id) {
	if (sound_system == nullptr) {
		return;
	}

	// 読み込まれているか？
	auto it = sound_system->bgm_map.find(id);
	if (it == sound_system->bgm_map.end()) {
		return;
	}

	// 別のBGMが再生中なら止める
	if (sound_system->current_bgm != it->second) {
		sound_system->stop_current_bgm();
	}

	sound_system->current_bgm = it->second;
	sound_system->is_bgm_paused = false;

	// BGMは2D空間で再生する
	ma_sound_set_spatialization_enabled(sound_system->current_bgm, MA_FALSE);
	// 再生
	if (!ma_sound_is_playing(sound_system->current_bgm)) {
		ma_sound_start(sound_system->current_bgm);
	}
}

void Yaxl::StopBGM() {
	if (sound_system != nullptr) {
		sound_system->stop_current_bgm();
	}
}

void Yaxl::PauseBGM() {
	if (sound_system == nullptr) {
		return;
	}

	if (sound_system->current_bgm != nullptr && ma_sound_is_playing(sound_system->current_bgm)) {
		ma_sound_stop(sound_system->current_bgm);
		sound_system->is_bgm_paused = true;
	}
}

void Yaxl::ReStartBGM() {
	if (sound_system == nullptr) {
		return;
	}

	if (sound_system->current_bgm != nullptr && sound_system->is_bgm_paused) {
		ma_sound_start(sound_system->current_bgm);
		sound_system->is_bgm_paused = false;
	}
}

bool Yaxl::IsPlayBGM() {
	if (sound_system == nullptr || sound_system->current_bgm == nullptr) {
		return false;
	}

	return ma_sound_is_playing(sound_system->current_bgm) == MA_TRUE;
}

bool Yaxl::IsPauseBGM() {
	if (sound_system == nullptr) {
		return false;
	}

	return sound_system->is_bgm_paused;
}

void Yaxl::SetVolumeBGM(float volume) {
	if (sound_system != nullptr) {
		ma_sound_group_set_volume(&sound_system->bgm_group, volume);
	}
}

float Yaxl::GetVolumeBGM() {
	if (sound_system == nullptr) {
		return -1.0f;

	}

	return ma_sound_group_get_volume(&sound_system->bgm_group);
}

bool Yaxl::LoadSE(unsigned int id, const char* file_name, int count) {
	if (sound_system == nullptr) {
		return false;
	}

	// ロード済みか？
	if (sound_system->se_map.count(id) > 0) {
		return true;
	}

	SEPool pool;
	for (int i = 0; i < count; ++i) {
		// メモリ展開を指定して読み込み
		ma_sound* sound = new ma_sound();
		if (ma_sound_init_from_file(&sound_system->engine, file_name, MA_SOUND_FLAG_DECODE, &sound_system->se_group, NULL, sound) != MA_SUCCESS) {
			delete sound;
			continue;
		}
		pool.sounds.push_back(sound);
	}

	// なにも読み込まなかった
	if (pool.sounds.empty()) {
		return false;
	}

	sound_system->se_map[id] = pool;

	return true;
}

void Yaxl::DeleteSE(unsigned int id) {
	if (sound_system == nullptr) {
		return;
	}

	// 読み込まれているか？
	auto it = sound_system->se_map.find(id);
	if (it == sound_system->se_map.end()) {
		return;
	}

	for (ma_sound* s : it->second.sounds) {
		ma_sound_uninit(s);
		delete s;
	}

	sound_system->se_map.erase(it);
}

void Yaxl::DeleteAllSE() {
	if (sound_system == nullptr) {
		return;
	}

	for (auto& pair : sound_system->se_map) {
		for (ma_sound* s : pair.second.sounds) {
			ma_sound_uninit(s);
			delete s;
		}
	}

	sound_system->se_map.clear();
}

void Yaxl::PlaySE(unsigned int id, float pitch) {
	if (sound_system == nullptr) {
		return;
	}

	// 読み込まれているか？
	auto it = sound_system->se_map.find(id);
	if (it == sound_system->se_map.end()) {
		return;
	}
	SEPool& pool = it->second;
	if (pool.sounds.empty()) {
		return;
	}

	// 再生対象
	ma_sound* s = pool.sounds[pool.index];
	// 2D指定で再生
	ma_sound_set_spatialization_enabled(s, MA_FALSE);
	ma_sound_set_pitch(s, pitch);
	ma_sound_seek_to_pcm_frame(s, 0);
	ma_sound_start(s);
	pool.index = (pool.index + 1) % pool.sounds.size();
}

void Yaxl::PlaySE(unsigned int id, const Vector3& position, float pitch) {
	if (sound_system == nullptr) {
		return;
	}

	// 読み込まれているか？
	auto it = sound_system->se_map.find(id);
	if (it == sound_system->se_map.end()) {
		return;
	}
	SEPool& pool = it->second;
	if (pool.sounds.empty()) {
		return;
	}

	// 再生対象
	ma_sound* s = pool.sounds[pool.index];
	// 3D指定
	ma_sound_set_spatialization_enabled(s, MA_TRUE);
	ma_sound_set_position(s, position.x, position.y, position.z);
	// 距離減衰設定
	ma_sound_set_attenuation_model(s, ma_attenuation_model_linear);
	ma_sound_set_min_distance(s, sound_system->min_distance);
	ma_sound_set_max_distance(s, sound_system->max_distance);
	// 再生
	ma_sound_set_pitch(s, pitch);
	ma_sound_seek_to_pcm_frame(s, 0);
	ma_sound_start(s);
	pool.index = (pool.index + 1) % pool.sounds.size();
}

void Yaxl::StopSE(unsigned int id) {
	if (sound_system == nullptr) {
		return;
	}

	// 読み込まれているか？
	auto it = sound_system->se_map.find(id);
	if (it == sound_system->se_map.end()) {
		return;
	}

	for (ma_sound* s : it->second.sounds) {
		if (ma_sound_is_playing(s)) {
			ma_sound_stop(s);
			ma_sound_seek_to_pcm_frame(s, 0);
		}
	}
}

bool Yaxl::IsPlaySE(unsigned int id) {
	if (sound_system == nullptr) {
		return false;
	}

	// 読み込まれているか？
	auto it = sound_system->se_map.find(id);
	if (it == sound_system->se_map.end()) {
		return false;
	}

	// どれか一つでも鳴っていれば再生中とする
	for (ma_sound* s : it->second.sounds) {
		if (ma_sound_is_playing(s)) {
			return true;
		}
	}

	return false;
}

void Yaxl::SetVolumeSE(unsigned int id, float volume) {
	if (sound_system == nullptr) {
		return;
	}

	// 読み込まれているか？
	auto it = sound_system->se_map.find(id);
	if (it == sound_system->se_map.end()) {
		return;
	}

	for (ma_sound* s : it->second.sounds) {
		ma_sound_set_volume(s, volume);
	}
}

void Yaxl::SetMasterVolumeSE(float volume) {
	if (sound_system != nullptr) {
		ma_sound_group_set_volume(&sound_system->se_group, volume);
	}
}

float Yaxl::GetVolumeSE(unsigned int id) {
	if (sound_system == nullptr) {
		return -1.0f;
	}

	// 読み込まれているか？
	auto it = sound_system->se_map.find(id);
	if (it == sound_system->se_map.end() || it->second.sounds.empty()) {
		return -1.0f;
	}

	return ma_sound_get_volume(it->second.sounds[0]);
}

float Yaxl::GetMasterVolumeSE() {
	if (sound_system == nullptr) {
		return -1.0f;
	}

	return ma_sound_group_get_volume(&sound_system->se_group);
}

void Yaxl::SetPrimaryVolume(float volume) {
	if (sound_system != nullptr) {
		ma_engine_set_volume(&sound_system->engine, volume);
	}
}

float Yaxl::GetPrimaryVolume() {
	if (sound_system == nullptr) {
		return -1.0f;
	}

	return ma_engine_get_volume(&sound_system->engine);
}

void Yaxl::SetAudioListener(const Vector3& position, const Vector3& forward) {
	if (sound_system == nullptr) {
		return;
	}

	ma_engine_listener_set_position(&sound_system->engine, 0, position.x, position.y, position.z);
	ma_engine_listener_set_direction(&sound_system->engine, 0, forward.x, forward.y, forward.z);
}

void Yaxl::SetAudioListnerMaxDistance(float distance) {
	if (sound_system != nullptr) {
		sound_system->max_distance = distance;
	}
}

void Yaxl::SetAudioListenerMinDistance(float distance) {
	if (sound_system != nullptr) {
		sound_system->min_distance = distance;
	}
}
