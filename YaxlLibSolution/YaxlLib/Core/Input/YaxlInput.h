// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : 入力を管理する
// -----------------------------------------------------------------------------------------

#ifndef YAXL_CORE_INPUT_H_
#define YAXL_CORE_INPUT_H_

#include "YaxlLibLink.h"

namespace Yaxl {
// マウスボタン
enum class MouseButton {
    Left = 0, Right, Middle, Side1, Side2,
    MAX
};

// キーコード
enum class KeyCode {
    A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    Escape, Enter, Space, Up, Down, Left, Right,
    LeftShift, RightShift, LeftCtrl, RightCtrl, LeftAlt, RightAlt, Tab, Backspace,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    MAX
};

// ゲームパッドボタン
enum class PadButton {
    A = 0, B, X, Y,
    LeftShoulder, RightShoulder,
    Back, Start, Guide,
    LeftThumb, RightThumb,
    Up, Right, Down, Left,
    MAX
};

class GraphicsDevice;

class Input {
public:
    /// <summary>
    /// 入力状態の更新
    /// </summary>
    /// <param name="graphics_device">= 取得先のグラフィックデバイス</param>
    static void Update(GraphicsDevice* graphics_device);

public:
    /// <summary>
    /// マウスボタンを入力した瞬間かどうか
    /// </summary>
    /// <param name="button">= 判定するマウスボタン</param>
    /// <returns>入力した瞬間なら真を、入力した瞬間でなければ偽を返す</returns>
    static bool IsMouseButtonDown(MouseButton button);

    /// <summary>
    /// マウスボタンを入力しているかどうか
    /// </summary>
    /// <param name="button">= 判定するマウスボタン</param>
    /// <returns>入力しているなら真を、入力していなければ偽を返す</returns>
    static bool IsMouseButton(MouseButton button);

    /// <summary>
    /// マウスボタンを離した瞬間かどうか
    /// </summary>
    /// <param name="button">= 判定するマウスボタン</param>
    /// <returns>離した瞬間なら真を、離した瞬間でなければ偽を返す</returns>
    static bool IsMouseButtonUp(MouseButton button);

    /// <summary>
    /// マウスのウィンドウ左上を原点としたX座標を取得する
    /// </summary>
    /// <returns>座標</returns>
    static float GetMouseX();

    /// <summary>
    /// マウスのウィンドウ左上を原点としたY座標を取得する
    /// </summary>
    /// <returns>座標</returns>
    static float GetMouseY();

    /// <summary>
    /// マウスの1フレーム前からのX移動量を取得する
    /// </summary>
    /// <returns>移動量</returns>
    static float GetMouseDeltaX();

    /// <summary>
    /// マウスの1フレーム前からのY移動量を取得する
    /// </summary>
    /// <returns>移動量</returns>
    static float GetMouseDeltaY();

    /// <summary>
    /// キーを入力した瞬間かどうか
    /// </summary>
    /// <param name="key">= 判定するキー</param>
    /// <returns>入力した瞬間なら真を、入力した瞬間でなければ偽を返す</returns>
    static bool IsKeyDown(KeyCode key);

    /// <summary>
    /// キーを入力しているかどうか
    /// </summary>
    /// <param name="key">= 判定するキー</param>
    /// <returns>入力しているなら真を、入力していなければ偽を返す</returns>
    static bool IsKey(KeyCode key);

    /// <summary>
    /// キーを離した瞬間かどうか
    /// </summary>
    /// <param name="key">= 判定するキー</param>
    /// <returns>離した瞬間なら真を、離した瞬間でなければ偽を返す</returns>
    static bool IsKeyUp(KeyCode key);

    /// <summary>
    /// ゲームパッドが接続されているかどうか
    /// </summary>
    /// <returns>接続されていたら真を、されていなければ偽を返す</returns>
    static bool IsPadConnected();

    /// <summary>
    /// パッドボタンを入力した瞬間かどうか
    /// </summary>
    /// <param name="key">= 判定するパッドボタン</param>
    /// <returns>入力した瞬間なら真を、入力した瞬間でなければ偽を返す</returns>
    static bool IsPadButtonDown(PadButton button);

    /// <summary>
    /// パッドボタンを入力しているかどうか
    /// </summary>
    /// <param name="key">= 判定するパッドボタン</param>
    /// <returns>入力しているなら真を、入力していなければ偽を返す</returns>
    static bool IsPadButton(PadButton button);

    /// <summary>
    /// パッドボタンを離した瞬間かどうか
    /// </summary>
    /// <param name="key">= 判定するパッドボタン</param>
    /// <returns>離した瞬間なら真を、離した瞬間でなければ偽を返す</returns>
    static bool IsPadButtonUp(PadButton button);

    /// <summary>
    /// ゲームパッドの左スティックの水平方向の状態を取得する（-1.0 ~ 1.0）
    /// </summary>
    /// <returns>水平方向の状態</returns>
    static float GetLeftStickX();
    
    /// <summary>
    /// ゲームパッドの左スティックの垂直方向の状態を取得する（-1.0 ~ 1.0）
    /// </summary>
    /// <returns>垂直方向の状態</returns>
    static float GetLeftStickY();
    
    /// <summary>
    /// ゲームパッドの右スティックの水平方向の状態を取得する（-1.0 ~ 1.0）
    /// </summary>
    /// <returns>水平方向の状態</returns>
    static float GetRightStickX();

    /// <summary>
    /// ゲームパッドの右スティックの垂直方向の状態を取得する（-1.0 ~ 1.0）
    /// </summary>
    /// <returns>垂直方向の状態</returns>
    static float GetRightStickY();
    
    /// <summary>
    /// ゲームパッドの左トリガーの状態を取得する（0.0 ~ 1.0）
    /// </summary>
    /// <returns>左トリガーの状態</returns>
    static float GetLeftTrigger();
    
    /// <summary>
    /// ゲームパッドの右トリガーの状態を取得する（0.0 ~ 1.0）
    /// </summary>
    /// <returns>右トリガーの状態</returns>
    static float GetRightTrigger();

private:
    // マウスの絶対座標（ウィンドウの左上からのピクセル位置）
    static float mouse_x_;
    static float mouse_y_;
    // マウスの移動量
    static float delta_mouse_x_;
    static float delta_mouse_y_;

    // 現在入力されているマウスボタン
    static bool current_mouse_buttons_[static_cast<int>(MouseButton::MAX)];
    // 過去に入力されていたマウスボタン
    static bool prev_mouse_buttons_[static_cast<int>(MouseButton::MAX)];

    // 現在入力されているキー
    static bool current_keys_[static_cast<int>(KeyCode::MAX)];
    // 過去に入力されていたキー
    static bool prev_keys_[static_cast<int>(KeyCode::MAX)];

    // パッドが接続されているかどうか
    static bool is_pad_connected_;
    // 現在入力されているパッドボタン
    static bool current_pad_buttons_[static_cast<int>(PadButton::MAX)];
    // 過去に入力されていたパッドボタン
    static bool prev_pad_buttons_[static_cast<int>(PadButton::MAX)];
    // パッドのアナログ入力
    static float left_stick_x_;
    static float left_stick_y_;
    static float right_stick_x_;
    static float right_stick_y_;
    static float left_trigger_;
    static float right_trigger_;

private:
    // インスタンス生成禁止
    Input() = delete;
};
} // namespace Yaxl end

#endif