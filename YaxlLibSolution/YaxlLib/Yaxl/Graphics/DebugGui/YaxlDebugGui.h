#ifndef YAXL_IMGUI_H_
#define YAXL_IMGUI_H_

struct GLFWwindow;

namespace Yaxl {

class DebugGui {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="window">= 描画先のグラフィックデバイス</param>
	static void Init(GLFWwindow* window);

	/// <summary>
	/// ImGuiの解放
	/// </summary>
	static void Clear();

	/// <summary>
	/// ImGuiフレームの開始
	/// </summary>
	static void Begin();

	/// <summary>
	/// ImGuiフレームの終了
	/// </summary>
	static void End();

private:
	// 初期化済みかどうか
	static bool is_initialized_;

private:
	// インスタンス生成禁止
	DebugGui() = delete;
};

} // namespace Yaxl end

#endif