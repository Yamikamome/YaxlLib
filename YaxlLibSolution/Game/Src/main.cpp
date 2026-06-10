#include <YaxlGame.h>
#include <imgui/imgui.h>

class MyGame : public Yaxl::Game {
public:
	MyGame() : Yaxl::Game(1280, 720, "YaxlLib", 60, 20) {}

protected:
	void start() override {

	}

	void tick() override {

	}

	void update() override {
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
