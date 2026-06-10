#include <YaxlGame.h>
#include <imgui/imgui.h>

class MyGame : public Yaxl::Game {
public:
	MyGame() : Yaxl::Game(1920, 1080, "YaxlLib", 60, 20) {}

protected:
	void start() override {
		// スクリーンの設定
		SetFullScreen(true);
	}

	void tick() override {

	}

	void update() override {
		// フルスクリーンの切り替え
		if (Yaxl::Input::IsKeyDown(Yaxl::KeyCode::F11)) {
			ToggleFullScreen();
		}

		ImGui::Begin("YaxlLibDebugWindow");
		ImGui::Text("FPS: %.1f", Yaxl::GetCurrentFps());
		ImGui::End();
	}

	void draw() const override {

	}

	void end() override {

	}

	bool is_running() const override {
		// パッドのBackとStartが両方押されていたら終了する
		if (Yaxl::Input::IsPadButton(Yaxl::PadButton::Back) && Yaxl::Input::IsPadButton(Yaxl::PadButton::Start)) {
			return false;
		}
		// キーボードのEscapeが押されていたら終了する
		if (Yaxl::Input::IsKey(Yaxl::KeyCode::Escape)) {
			return false;
		}

		// 上記に該当しなければ、ゲーム続行
		return true;
	}
};

int main() {
    return MyGame().run();
}
