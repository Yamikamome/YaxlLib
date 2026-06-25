// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 音を管理する
//					ユーザーに見せたくない処理を分けている
// -----------------------------------------------------------------------------------------

#ifndef YAXL_AUDIO_INTERNAL_H_
#define YAXL_AUDIO_INTERNAL_H_

namespace Yaxl::Internal {
	/// <summary>
	/// サウンドの初期化
	/// </summary>
	/// <returns>初期化に成功すれば真、失敗すれば偽を返す</returns>
	bool InitAudio();

	/// <summary>
	/// サウンドの終了
	/// </summary>
	void ClearAudio();

}	// namespace Yaxl end

#endif