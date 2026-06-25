#include "YaxlInput.h"
#include "Yaxl/Graphics/YaxlGraphicsDevice.h"
#include <GLFW/glfw3.h>

using namespace Yaxl;

// 初期化
bool Input::current_mouse_buttons_[static_cast<int>(MouseButton::MAX)] = { false };
bool Input::prev_mouse_buttons_[static_cast<int>(MouseButton::MAX)] = { false };
float Input::mouse_x_ = 0.0f;
float Input::mouse_y_ = 0.0f;
float Input::delta_mouse_x_ = 0.0f;
float Input::delta_mouse_y_ = 0.0f;
bool Input::current_keys_[static_cast<int>(KeyCode::MAX)] = { false };
bool Input::prev_keys_[static_cast<int>(KeyCode::MAX)] = { false };
bool Input::is_pad_connected_ = false;
bool Input::current_pad_buttons_[static_cast<int>(PadButton::MAX)] = { false };
bool Input::prev_pad_buttons_[static_cast<int>(PadButton::MAX)] = { false };
float Input::left_stick_x_ = 0.0f;
float Input::left_stick_y_ = 0.0f;
float Input::right_stick_x_ = 0.0f;
float Input::right_stick_y_ = 0.0f;
float Input::left_trigger_ = 0.0f;
float Input::right_trigger_ = 0.0f;

// 対応マップ
static const int GLFW_MOUSE_MAP[static_cast<int>(MouseButton::MAX)] = {
        GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE,
        GLFW_MOUSE_BUTTON_4, GLFW_MOUSE_BUTTON_5
};
static const int GLFW_KEY_MAP[static_cast<int>(KeyCode::MAX)] = {
        GLFW_KEY_A, GLFW_KEY_B, GLFW_KEY_C, GLFW_KEY_D, GLFW_KEY_E, GLFW_KEY_F, GLFW_KEY_G,
        GLFW_KEY_H, GLFW_KEY_I, GLFW_KEY_J, GLFW_KEY_K, GLFW_KEY_L, GLFW_KEY_M, GLFW_KEY_N,
        GLFW_KEY_O, GLFW_KEY_P, GLFW_KEY_Q, GLFW_KEY_R, GLFW_KEY_S, GLFW_KEY_T, GLFW_KEY_U,
        GLFW_KEY_V, GLFW_KEY_W, GLFW_KEY_X, GLFW_KEY_Y, GLFW_KEY_Z,
        GLFW_KEY_0, GLFW_KEY_1, GLFW_KEY_2, GLFW_KEY_3, GLFW_KEY_4,
        GLFW_KEY_5, GLFW_KEY_6, GLFW_KEY_7, GLFW_KEY_8, GLFW_KEY_9,
        GLFW_KEY_ESCAPE, GLFW_KEY_ENTER, GLFW_KEY_SPACE,
        GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_LEFT, GLFW_KEY_RIGHT,
        GLFW_KEY_LEFT_SHIFT, GLFW_KEY_RIGHT_SHIFT, GLFW_KEY_LEFT_CONTROL, GLFW_KEY_RIGHT_CONTROL,
        GLFW_KEY_LEFT_ALT, GLFW_KEY_RIGHT_ALT, GLFW_KEY_TAB, GLFW_KEY_BACKSPACE,
        GLFW_KEY_F1, GLFW_KEY_F2, GLFW_KEY_F3, GLFW_KEY_F4, GLFW_KEY_F5, GLFW_KEY_F6,
        GLFW_KEY_F7, GLFW_KEY_F8, GLFW_KEY_F9, GLFW_KEY_F10, GLFW_KEY_F11, GLFW_KEY_F12
};

void Input::Update(GraphicsDevice* graphics_device) {
    if (graphics_device == nullptr) {
        return;
    }

    GLFWwindow* window = graphics_device->GetWindowHandle();
    if (window == nullptr) {
        return;
    }

    // マウスの更新
    for (int i = 0; i < static_cast<int>(MouseButton::MAX); ++i) {
        prev_mouse_buttons_[i] = current_mouse_buttons_[i];

        int glfw_button = GLFW_MOUSE_MAP[i];
        int state = glfwGetMouseButton(window, glfw_button);

        if (state == GLFW_PRESS) {
            current_mouse_buttons_[i] = true;
        }
        else {
            current_mouse_buttons_[i] = false;
        }
    }
    double mx, my;
    glfwGetCursorPos(window, &mx, &my);

    // 今回の座標から前回の座標を引いて、移動量を計算する
    delta_mouse_x_ = static_cast<float>(mx) - mouse_x_;
    delta_mouse_y_ = static_cast<float>(my) - mouse_y_;
    // 現在の座標を保存
    mouse_x_ = static_cast<float>(mx);
    mouse_y_ = static_cast<float>(my);

    // キーコードの更新
    for (int i = 0; i < static_cast<int>(KeyCode::MAX); ++i) {
        // 今の状態を過去の状態として保存する
        prev_keys_[i] = current_keys_[i];

        // 変換表を使ってGLFWに現在の状態を聞く
        int glfw_key = GLFW_KEY_MAP[i];
        int state = glfwGetKey(window, glfw_key);

        if (state == GLFW_PRESS) {
            current_keys_[i] = true;
        }
        else {
            current_keys_[i] = false;
        }
    }

    // ゲームパッドの更新
    GLFWgamepadstate pad_state;
    // プレイヤー1のパッド状態を取得できるかチェック
    if (glfwGetGamepadState(GLFW_JOYSTICK_1, &pad_state) == GLFW_TRUE) {
        is_pad_connected_ = true;

        // ボタンの更新
        for (int i = 0; i < static_cast<int>(PadButton::MAX); ++i) {
            prev_pad_buttons_[i] = current_pad_buttons_[i];

            if (pad_state.buttons[i] == GLFW_PRESS) {
                current_pad_buttons_[i] = true;
            }
            else {
                current_pad_buttons_[i] = false;
            }
        }

        // アナログスティックとトリガーの更新
        left_stick_x_ = pad_state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
        left_stick_y_ = pad_state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
        right_stick_x_ = pad_state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
        right_stick_y_ = pad_state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];
        // トリガーは-1.0が離している状態なので正規化
        left_trigger_ = (pad_state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] + 1.0f) * 0.5f;
        right_trigger_ = (pad_state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] + 1.0f) * 0.5f;
    }
    else {
        // ゲームパッドが切断されたら全てのボタンを解放する
        if (is_pad_connected_ == true) {
            for (int i = 0; i < static_cast<int>(PadButton::MAX); ++i) {
                current_pad_buttons_[i] = false;
                prev_pad_buttons_[i] = false;
            }
            left_stick_x_ = 0.0f;
            left_stick_y_ = 0.0f;
            right_stick_x_ = 0.0f;
            right_stick_y_ = 0.0f;
            left_trigger_ = 0.0f;
            right_trigger_ = 0.0f;

            is_pad_connected_ = false;
        }
    }

}

bool Input::IsMouseButtonDown(MouseButton button) {
    int index = static_cast<int>(button);
    if (current_mouse_buttons_[index] == true) {
        if (prev_mouse_buttons_[index] == false) {
            return true;
        }
    }
    return false;
}

bool Input::IsMouseButton(MouseButton button) {
    int index = static_cast<int>(button);
    return current_mouse_buttons_[index];
}

bool Input::IsMouseButtonUp(MouseButton button) {
    int index = static_cast<int>(button);
    if (current_mouse_buttons_[index] == false) {
        if (prev_mouse_buttons_[index] == true) {
            return true;
        }
    }
    return false;
}

float Input::GetMouseX() {
    return mouse_x_;
}

float Input::GetMouseY() {
    return mouse_y_;
}

float Input::GetMouseDeltaX() {
    return delta_mouse_x_;
}

float Input::GetMouseDeltaY() {
    return delta_mouse_y_;
}

bool Input::IsKeyDown(KeyCode key) {
    int index = static_cast<int>(key);
    if (current_keys_[index] == true) {
        if (prev_keys_[index] == false) {
            return true;
        }
    }
    return false;
}

bool Input::IsKey(KeyCode key) {
    int index = static_cast<int>(key);
    return current_keys_[index];
}

bool Input::IsKeyUp(KeyCode key) {
    int index = static_cast<int>(key);
    if (current_keys_[index] == false) {
        if (prev_keys_[index] == true) {
            return true;
        }
    }
    return false;
}

bool Input::IsPadConnected() {
    return is_pad_connected_;
}

bool Input::IsPadButtonDown(PadButton button) {
    int index = static_cast<int>(button);
    if (current_pad_buttons_[index] == true) {
        if (prev_pad_buttons_[index] == false) {
            return true;
        }
    }
    return false;
}

bool Input::IsPadButton(PadButton button) {
    int index = static_cast<int>(button);
    return current_pad_buttons_[index];
}

bool Input::IsPadButtonUp(PadButton button) {
    int index = static_cast<int>(button);
    if (current_pad_buttons_[index] == false) {
        if (prev_pad_buttons_[index] == true) {
            return true;
        }
    }
    return false;
}

float Input::GetLeftStickX() {
    return left_stick_x_;
}

float Input::GetLeftStickY() {
    return left_stick_y_;
}

float Input::GetRightStickX() {
    return right_stick_x_;
}

float Input::GetRightStickY() {
    return right_stick_y_;
}

float Input::GetLeftTrigger() {
    return left_trigger_;
}

float Input::GetRightTrigger() {
    return right_trigger_;
}
