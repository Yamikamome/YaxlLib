// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : ウィンドウ、OpenGL、バッファの管理を行う
// -----------------------------------------------------------------------------------------

#ifndef YAXL_GRAPHICS_DEVICE_H_
#define YAXL_GRAPHICS_DEVICE_H_

struct GLFWwindow;

namespace Yaxl {
class GraphicsDevice {
public:
    GraphicsDevice();

    ~GraphicsDevice();

public:
    /// <summary>
    /// ウィンドウの初期化
    /// </summary>
    /// <param name="width">= ウィンドウの幅</param>
    /// <param name="height">= ウィンドウの高さ</param>
    /// <param name="title">= ウィンドウのタイトル</param>
    /// <returns>初期化に成功したら真を、失敗したら偽を返す</returns>
    bool Init(int width, int height, const char* title);

    /// <summary>
    /// ウィンドウの解放
    /// </summary>
    void Clear();

public:
	/// <summary>
	/// グラフィックデバイスの更新
	/// </summary>
	void Update();

    /// <summary>
    /// フロントバッファとバックバッファをスワップする
    /// </summary>
    void SwapBuffers();

public:
    /// <summary>
    /// ウィンドウを閉じる必要があるかどうか
    /// </summary>
    /// <returns>閉じる必要があるなら真を、閉じる必要がなければ偽を返す</returns>
    bool IsWindowClosed() const;

    /// <summary>
    /// GLFWのウィンドウハンドルを取得する
    /// </summary>
    /// <returns>ウィンドウハンドル</returns>
    GLFWwindow* GetWindowHandle() const;

private:
    // ウィンドウハンドル
    GLFWwindow* window_handle_{ nullptr };
    // ウィンドウの幅
    int window_width_{ 0 };
    // ウィンドウの高さ
    int window_height_{ 0 };
    // 初期化済みかどうか
    bool is_initialized_{ false };

public:
    // コピー禁止
    GraphicsDevice(const GraphicsDevice& other) = delete;
    GraphicsDevice& operator = (const GraphicsDevice& other) = delete;
};
}	// namespace Yaxl end

#endif