// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 音を管理する
// -----------------------------------------------------------------------------------------

#ifndef YAXL_AUDIO_H_
#define YAXL_AUDIO_H_

namespace Yaxl {

class Vector3;

	/// <summary>
	/// BGMの読み込み
	/// </summary>
	/// <param name="id">= リソースID</param>
	/// <param name="file_name">= ファイル名</param>
	/// <param name="loop">= ループ指定フラグ</param>
	/// <returns>読み込みに成功すれば真、失敗すれば偽を返す</returns>
	bool LoadBGM(unsigned int id, const char* file_name, bool loop);
	
	/// <summary>
	/// BGMの解放
	/// </summary>
	/// <param name="id">= リソースID</param>
	void DeleteBGM(unsigned int id);
	
	/// <summary>
	/// 全てのBGMを解放
	/// </summary>
	void DeleteAllBGM();
	
	/// <summary>
	/// BGMの再生
	/// </summary>
	/// <param name="id">= リソースID</param>
	void PlayBGM(unsigned int id);
	
	/// <summary>
	/// BGMの停止
	/// </summary>
	void StopBGM();
	
	/// <summary>
	/// BGMの一時停止
	/// </summary>
	void PauseBGM();
	
	/// <summary>
	/// BGMの一時停止からの再開
	/// </summary>
	void ReStartBGM();
	
	/// <summary>
	/// BGMが再生中か調べる
	/// </summary>
	/// <returns>再生中なら真、再生していなければ偽を返す</returns>
	bool IsPlayBGM();
	
	/// <summary>
	/// BGMが一時停止中か調べる
	/// </summary>
	/// <returns>一時停止中なら真、一時停止していなければ偽を返す</returns>
	bool IsPauseBGM();
	
	/// <summary>
	/// BGMのボリュームを設定する
	/// </summary>
	/// <param name="volume">= 0.0（無音）～ 1.0（デフォルト）</param>
	void SetVolumeBGM(float volume);
	
	/// <summary>
	/// BGMのボリュームを取得する
	/// </summary>
	/// <returns>0.0（無音）～ 1.0（デフォルト）</returns>
	float GetVolumeBGM();
	
	/// <summary>
	/// SEの読み込み
	/// </summary>
	/// <param name="id">= リソースID</param>
	/// <param name="file_name">= ファイル名</param>
	/// <param name="count">= 同時再生可能数</param>
	/// <returns>読み込みに成功すれば真、失敗すれば偽を返す</returns>
	bool LoadSE(unsigned int id, const char* file_name, int count = 1);
	
	/// <summary>
	/// SEの解放
	/// </summary>
	/// <param name="id">= リソースID</param>
	void DeleteSE(unsigned int id);
	
	/// <summary>
	/// 全てのSEを解放
	/// </summary>
	void DeleteAllSE();
	
	/// <summary>
	/// SEの再生
	/// </summary>
	/// <param name="id">= リソースID</param>
	/// <param name="pitch">= ピッチ 1.0（デフォルト）</param>
	void PlaySE(unsigned int id, float pitch = 1.0f);
	
	/// <summary>
	/// SEの再生（3D）
	/// </summary>
	/// <param name="id">= リソースID</param>
	/// <param name="position">= 再生位置（ワールド座標系）</param>
	/// <param name="pitch">= ピッチ 1.0（デフォルト）</param>
	void PlaySE(unsigned int id, const Vector3& position, float pitch = 1.0f);
	
	/// <summary>
	/// SEの停止
	/// </summary>
	/// <param name="id">= リソースID</param>
	void StopSE(unsigned int id);
	
	/// <summary>
	/// SEが再生中か調べる
	/// </summary>
	/// <param name="id">= リソースID</param>
	/// <returns>再生中なら真、再生していなければ偽を返す</returns>
	bool IsPlaySE(unsigned int id);
	
	/// <summary>
	/// SEのボリュームを設定する
	/// </summary>
	/// <param name="id">= リソースID</param>
	/// <param name="volume">= 0.0（無音）～ 1.0（デフォルト）</param>
	void SetVolumeSE(unsigned int id, float volume);
	
	/// <summary>
	/// SEのマスターボリュームを設定する
	/// </summary>
	/// <param name="volume">= 0.0（無音）～ 1.0（デフォルト）</param>
	void SetMasterVolumeSE(float volume);
	
	/// <summary>
	/// SEのボリュームを取得する
	/// </summary>
	/// <param name="id">= リソースID</param>
	/// <returns>0.0（無音）～ 1.0（デフォルト）</returns>
	float GetVolumeSE(unsigned int id);
	
	/// <summary>
	/// SEのマスターボリュームを取得する
	/// </summary>
	/// <returns>0.0（無音）～ 1.0（デフォルト）</returns>
	float GetMasterVolumeSE();
	
	/// <summary>
	/// 全体のボリュームを設定する
	/// </summary>
	/// <param name="volume">= 0.0（無音）～ 1.0（デフォルト）</param>
	void SetPrimaryVolume(float volume);
	
	/// <summary>
	/// 全体のボリュームを取得する
	/// </summary>
	/// <returns>0.0（無音）～ 1.0（デフォルト）</returns>
	float GetPrimaryVolume();
	
	/// <summary>
	/// サウンドリスナーの位置を設定する
	/// </summary>
	/// <param name="position">= リスナーの位置（ワールド座標系）</param>
	/// <param name="forward">= リスナーの前方向ベクトル（ワールド座標系）</param>
	void SetAudioListener(const Vector3& position, const Vector3& forward);
	
	/// <summary>
	/// サウンドリスナー減衰値が０になる距離を設定する
	/// これより遠くのSEは再生されない
	/// </summary>
	/// <param name="distance">= 最大距離</param>
	void SetAudioListnerMaxDistance(float distance);
	
	/// <summary>
	/// ウンドリスナー減衰値が１になる距離を設定する
	/// これより近くのSEは減衰されずに再生される
	/// </summary>
	/// <param name="distance">= 最小距離</param>
	void SetAudioListenerMinDistance(float distance);

}	// namespace Yaxl end

#endif
