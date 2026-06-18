# YaxlLib
自作ライブラリ第一弾<br>
読み方はヤクセル（Yami * voxel） <br>
# How2Use
[ダウンロード]()<br>
<br>
VisualStudio2022を想定しています<br>
C++ 空のプロジェクトを作成します<br>
x64を指定し、プロパティからC++17以降を指定します(ライブラリはc++17で開発しています)<br>
C/C++ 全般 追加のインクルードディレクトリにincフォルダを、<br>
リンカー 全般 追加のライブラリディレクトリにlibフォルダを指定してください<br>
※VC++ ディレクトリでの指定でも問題ありません<br>
<br>
main.cppを作成し、以下のコードを入力します<br>
```
#include <YaxlGame.h>

class MyGame : public Yaxl::Game {
public:
	MyGame() : Yaxl::Game(1920, 1080, "App Name", 60) {}
};

int main() {
	return MyGame().run();
}
```
実行すると、画面を表示させることができます<Br>
<br>
他の機能については、[リファレンス]()を確認してください<br>
# 使用している外部ライブラリ
[GLFW](https://www.glfw.org/download) ウィンドウ管理<br>
[GLAD](https://glad.dav1d.de/) OpenGL関数のロード<br>
[ImGui](https://github.com/ocornut/imgui) デバッグ用GUI<br>
[stb_image](https://github.com/nothings/stb/tree/master) 画像読み込み<br>
[miniaudio](https://github.com/mackron/miniaudio) オーディオ管理<br>
使用しているライブラリは YaxlLib/ExternalLibrary 内で管理されています<br>
# 開発経緯
学校で使っていたゲーム開発用ライブラリの改造に限界を感じたため<br>
学校での経験を生かして使いやすいライブラリの実装を目指す<br>
<br>
更新 2026/06/18 15:12 Yamikamome