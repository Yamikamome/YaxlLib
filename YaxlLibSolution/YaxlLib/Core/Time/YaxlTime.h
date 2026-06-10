// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 時間を管理する
// -----------------------------------------------------------------------------------------

#ifndef YAXL_TIME_H_
#define YAXL_TIME_H_

namespace Yaxl {
    /// <summary>
    /// FPSの制限値を設定（0を指定すると可変FPSになる）
    /// </summary>
    /// <param name="fps">= FPS</param>
    void SetTargetFps(int fps = 0);

    /// <summary>
    /// 現在設定されているFPSの制限値を取得
    /// </summary>
    /// <returns>FPSの制限値</returns>
    int GetTargetFps();

	/// <summary>
	/// 現在のFPSを取得
	/// </summary>
	/// <returns>現在のFPS</returns>
	float GetCurrentFps();

    /// <summary>
    /// 1秒間にTickを実行する目標回数を取得
    /// </summary>
    /// <returns>目標回数</returns>
    int GetTickRate();

    /// <summary>
    /// 前回のフレームからかかった時間（秒）を取得
    /// </summary>
    /// <returns>経過時間（秒）</returns>
    float GetDeltaTime();

    /// <summary>
    /// ゲーム開始からTickが実行された累計回数を取得
    /// </summary>
    /// <returns>累計回数</returns>
    unsigned long long GetTickCount();

}	// namespace Yaxl end

#endif