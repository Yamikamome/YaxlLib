// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : YaxlLibを使ったゲーム制作を行うためのクラス
// -----------------------------------------------------------------------------------------

#ifndef YAXL_GAME_H_
#define YAXL_GAME_H_

#include "YaxlLib.h"

class GraphicsDevice;

namespace Yaxl {
class Game {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="width">= ウィンドウの幅</param>
    /// <param name="height">= ウィンドウの高さ</param>
    /// <param name="title">= ウィンドウのタイトル</param>
    /// <param name="target_fps">= FPSの制限値</param>
    /// <param name="tick_rate">= 1秒間にTickを実行する目標回数</param>
    Game(int width = 640, int height = 480, const char* title = "YaxlGame", int target_fps = 0, int tick_rate = 20);

    virtual ~Game();

public:
    /// <summary>
    /// 実行
    /// </summary>
    /// <returns>状態を返す</returns>
    int run();

	/// <summary>
	/// フルスクリーンの設定
	/// </summary>
	/// <param name="is_fullscreen">= フルスクリーンにするかどうか</param>
	void SetFullScreen(bool is_fullscreen);

	/// <summary>
	/// ボーダーレスウィンドウの設定
	/// </summary>
	/// <param name="is_borderless">= ボーダーレスウィンドウにするかどうか</param>
	void SetBorderless(bool is_borderless);

	/// <summary>
	/// フルスクリーンの切り替え
	/// </summary>
	void ToggleFullScreen();

	/// <summary>
	/// ボーダーレスウィンドウの切り替え
	/// </summary>
	void ToggleBorderless();

public:
    /// <summary>
    /// ゲームの開始
    /// </summary>
    virtual void start() {};

    /// <summary>
    /// Tickの更新
    /// </summary>
    virtual void tick() {};

    /// <summary>
    /// ゲームの更新
    /// </summary>
    virtual void update() {};

    /// <summary>
    /// ゲームの描画
    /// </summary>
    virtual void draw() const {};

    /// <summary>
    /// ゲームの終了
    /// </summary>
    virtual void end() {};

    /// <summary>
    /// ゲームが実行中かどうか
    /// </summary>
    /// <returns>実行中なら真を、終了するなら偽を返す</returns>
    virtual bool is_running() const { return true; }

private:
	/// <summary>
	/// 管理中のグラフィックデバイスを解放
	/// </summary>
	void ClearGraphicsDevice();

private:
    // グラフィックデバイス
    GraphicsDevice* graphics_device_{ nullptr };
    // ゲームループが実行中かどうか
    bool is_running_{ false };

public:
    // コピー禁止
    Game(const Game& other) = delete;
    Game& operator = (const Game& other) = delete;
};
}	// namespace Yaxl end

#endif