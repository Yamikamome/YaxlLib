// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 時間を管理する
//                  ユーザーに見せたくない処理を分けている
// -----------------------------------------------------------------------------------------

#ifndef YAXL_TIME_INTERNAL_H_
#define YAXL_TIME_INTERNAL_H_

namespace Yaxl::Internal {
    /// <summary>
    /// 前回のフレームからかかった時間（秒）を設定
    /// </summary>
    /// <param name="delta_time">経過時間（秒）</param>
    void SetDeltaTime(float delta_time);

    /// <summary>
    /// 1秒間にTickを実行する目標回数を設定
    /// </summary>
    /// <param name="tick_rate">目標回数</param>
    void SetTickRate(int tick_rate);

    /// <summary>
    /// Tickの実行回数を進める
    /// </summary>
    void IncrementTickCount();

}	// namespace Yaxl end

#endif