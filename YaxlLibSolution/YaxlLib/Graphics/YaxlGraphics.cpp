#include "YaxlGraphics.h"
#include "YaxlGraphicsInternal.h"

#include <unordered_map>
#include <stack>
#include <glad/glad.h>

#include "YaxlShader.h"
#include "YaxlTexture.h"

#include "Math/YaxlMath.h"
#include "Math/YaxlColor.h"
#include "Math/YaxlMatrix3x3.h"
#include "Math/YaxlMatrix4x4.h"
#include "Math/YaxlVector2.h"
#include "Math/YaxlVector3.h"
#include "Math/YaxlVector4.h"

#include "DefaultShader/YaxlSprite2DShader.h"

using namespace Yaxl;

static constexpr unsigned int SHADER_EMPTY_ID{ 0xFFFFFFFF };
static constexpr unsigned int SHADER_DEFAULT_2D_SPRITE_ID{ 0xFFFFFFFF - 1 };

static constexpr unsigned int TEXTURE_EMPTY_ID{ 0xFFFFFFFF };

namespace {
	// 論理解像度の幅
	float logical_window_width_ = 1920.0f;
	// 論理解像度の高さ
	float logical_window_height_ = 1080.0f;

	// ビュー行列
	Matrix4x4 current_view_matrix_ = Matrix4x4::Identity();
	// プロジェクション行列
	Matrix4x4 current_projection_matrix_ = Matrix4x4::Identity();

	// シェーダーマップ
	std::unordered_map<unsigned int, Shader*> shaders_map_;
	// シェーダースタック
	std::stack<unsigned int> active_shader_stack_;

	// デフォルトスプライト2Dシェーダー
	unsigned int default_sprite_2d_shader_id_ = SHADER_EMPTY_ID;

	// テクスチャマップ
	std::unordered_map<unsigned int, Texture*> textures_map_;

	// スプライト用VAO
	unsigned int sprite_vao_ = 0;
	// スプライト用VBO
	unsigned int sprite_vbo_ = 0;
}

#pragma region [Internal]

void Yaxl::Internal::SetLogicalWindowSize(float width, float height) {
	logical_window_width_ = width;
	logical_window_height_ = height;
}

float Yaxl::Internal::GetLogicalWindowWidth() {
	return logical_window_width_;
}

float Yaxl::Internal::GetLogicalWindowHeight() {
	return logical_window_height_;
}

void Yaxl::Internal::InitGraphics() {
	// デフォルトシェーダーの読み込み
	if (LoadShaderString(SHADER_DEFAULT_2D_SPRITE_ID, YAXL_DEFAULT_SPRITE_2D_SHADER_VERT, YAXL_DEFAULT_SPRITE_2D_SHADER_FRAG)) {
		default_sprite_2d_shader_id_ = SHADER_DEFAULT_2D_SPRITE_ID;
	}

	// スプライトの生成
	{
		// 四角形ポリゴンデータの頂点データの作成（三角形二枚）
		float vertices[] = {
		0.0f, 1.0f, // 左下
		1.0f, 0.0f, // 右上
		0.0f, 0.0f, // 左上

		0.0f, 1.0f, // 左下
		1.0f, 1.0f, // 右下
		1.0f, 0.0f  // 右上
		};

		// バッファの作成
		glGenVertexArrays(1, &sprite_vao_);
		glGenBuffers(1, &sprite_vbo_);
		// バッファをバインド
		glBindVertexArray(sprite_vao_);
		// データをGPUに転送
		glBindBuffer(GL_ARRAY_BUFFER, sprite_vbo_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// データ構造をシェーダーに設定
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		// バインド解除
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}

void Yaxl::Internal::ClearGraphics() {
	// シェーダーの解放
	{
		for (auto& shader : shaders_map_) {
			delete shader.second;
		}
		shaders_map_.clear();
		glUseProgram(0);
	}
	
	// テクスチャの解放
	{
		for (auto& texture : textures_map_) {
			delete texture.second;
		}
		textures_map_.clear();
	}
}

void Yaxl::Internal::ApplyShader(unsigned int id) {
	// 空シェーダーIDが来たらシェーダーを解除する
	if (id == SHADER_EMPTY_ID) {
		glUseProgram(0);
		return;
	}

	if (auto shader = GetShader(id)) {
		shader->Use();
	}
	else {
		glUseProgram(0);
	}
}

void Yaxl::Internal::BindTexture(unsigned int id, unsigned int slot) {
	// 空テクスチャIDが来たら無効なテクスチャをバインド
	if (id == TEXTURE_EMPTY_ID) {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
		return;
	}

	auto it = textures_map_.find(id);
	if (it != textures_map_.end()) {
		it->second->Bind(slot);
	}
	else {
		// テクスチャが見つからない場合は無効なテクスチャをバインド
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

#pragma endregion

#pragma region [Screen]

void Yaxl::SetViewMatrix(const Matrix4x4* view_matrix) {
	if (view_matrix != nullptr) {
		current_view_matrix_ = *view_matrix;
	}
}

void Yaxl::SetProjectionMatrix(const Matrix4x4* proj_matrix) {
	if (proj_matrix != nullptr) {
		current_projection_matrix_ = *proj_matrix;
	}
}

Matrix4x4 Yaxl::GetViewMatrix() {
	return current_view_matrix_;
}

Matrix4x4 Yaxl::GetProjectionMatrix() {
	return current_projection_matrix_;
}

float Yaxl::GetAspect() {
	return logical_window_width_ / logical_window_height_;
}

#pragma endregion

#pragma region [Shader]

bool Yaxl::LoadShader(unsigned int id, const char* vert_path, const char* frag_path) {
	// 既に読み込まれていたら既存のを解放する
	if (shaders_map_.find(id) != shaders_map_.end()) {
		DeleteShader(id);
	}

	Shader* new_shader = new Shader();
	if (new_shader->Load(vert_path, frag_path)) {
		shaders_map_[id] = new_shader;
		return true;
	}

	delete new_shader;
	return false;
}

bool Yaxl::LoadShaderString(unsigned int id, const char* vert_code, const char* frag_code) {
	// 既に読み込まれていたら既存のを解放する
	if (shaders_map_.find(id) != shaders_map_.end()) {
		DeleteShader(id);
	}

	Shader* new_shader = new Shader();
	if (new_shader->LoadString(vert_code, frag_code)) {
		shaders_map_[id] = new_shader;
		return true;
	}

	delete new_shader;
	return false;
}

void Yaxl::DeleteShader(unsigned int id) {
	auto it = shaders_map_.find(id);
	if (it != shaders_map_.end()) {
		delete it->second;
		shaders_map_.erase(it);
	}
}

void Yaxl::BeginShader(unsigned int id) {
	active_shader_stack_.push(id);
	Internal::ApplyShader(id);
}

void Yaxl::EndShader() {
	if (!active_shader_stack_.empty()) {
		active_shader_stack_.pop();
	}

	// スタックにシェーダーが存在するなら有効にする
	if (!active_shader_stack_.empty()) {
		Internal::ApplyShader(active_shader_stack_.top());
	}
	// スタックが空ならシェーダーを解除する
	else {
		Internal::ApplyShader(SHADER_EMPTY_ID);
	}
}

Shader* Yaxl::GetShader(unsigned int id) {
	auto it = shaders_map_.find(id);
	if (it != shaders_map_.end()) {
		return it->second;
	}
	return nullptr;
}

int Yaxl::GetShaderUniform(const char* name) {
	if (active_shader_stack_.empty()) {
		return -1;
	}

	if (Shader* shader = GetShader(active_shader_stack_.top())) {
		return glGetUniformLocation(shader->GetProgramID(), name);
	}

	return -1;
}

void Yaxl::SetShaderParamInt(const char* name, int param) {
	if (int location = GetShaderUniform(name); location != -1) {
		glUniform1i(location, param);
	}
}

void Yaxl::SetShaderParamFloat(const char* name, float param) {
	if (int location = GetShaderUniform(name); location != -1) {
		glUniform1f(location, param);
	}
}

void Yaxl::SetShaderParamVector2(const char* name, Vector2* param) {
	if (int location = GetShaderUniform(name); location != -1 && param) {
		glUniform2f(location, param->x, param->y);
	}
}

void Yaxl::SetShaderParamVector3(const char* name, Vector3* param) {
	if (int location = GetShaderUniform(name); location != -1 && param) {
		glUniform3f(location, param->x, param->y, param->z);
	}
}

void Yaxl::SetShaderParamVector4(const char* name, Vector4* param) {
	if (int location = GetShaderUniform(name); location != -1 && param) {
		glUniform4f(location, param->x, param->y, param->z, param->w);
	}
}

void Yaxl::SetShaderParamMatrix3x3(const char* name, Matrix3x3* param) {
	if (int location = GetShaderUniform(name); location != -1 && param) {
		glUniformMatrix3fv(location, 1, GL_FALSE, param->m);
	}
}

void Yaxl::SetShaderParamMatrix4x4(const char* name, Matrix4x4* param) {
	if (int location = GetShaderUniform(name); location != -1 && param) {
		glUniformMatrix4fv(location, 1, GL_FALSE, param->m);
	}
}

void Yaxl::BindDefaultSprite2DShader(unsigned int id) {
	default_sprite_2d_shader_id_ = id;
}

unsigned int Yaxl::GetBindDefaultSprite2DShader() {
	return default_sprite_2d_shader_id_;
}

#pragma endregion

#pragma region [Texture]

bool Yaxl::LoadTexture(unsigned int id, const char* file_path) {
	// 既に読み込まれていたら既存のを解放する
	if (textures_map_.find(id) != textures_map_.end()) {
		DeleteTexture(id);
	}

	Texture* new_texture = new Texture();
	if (new_texture->Load(file_path)) {
		textures_map_[id] = new_texture;
		return true;
	}

	delete new_texture;
	return false;
}

void Yaxl::DeleteTexture(unsigned int id) {
	auto it = textures_map_.find(id);
	if (it != textures_map_.end()) {
		delete it->second;
		textures_map_.erase(it);
	}
}

Texture* Yaxl::GetTexture(unsigned int id) {
	auto it = textures_map_.find(id);
	if (it != textures_map_.end()) {
		return it->second;
	}
	return nullptr;
}

void Yaxl::DrawSprite2D(unsigned int id, Vector2* position, Vector4* rect, Vector2* scale, Vector2* center, Color* color, float angle) {
	// シェーダーがバインドされていなければデフォルトシェーダーをバインドする
	bool is_empty_shader = active_shader_stack_.empty();
	if (is_empty_shader) {
		BeginShader(SHADER_DEFAULT_2D_SPRITE_ID);
	}

	// ステート設定
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// テクスチャをバインド
	Internal::BindTexture(id, 0);

	// バインド中のテクスチャサイズを取得
	float tw = 1.0f;
	float th = 1.0f;
	if (Texture* tex = GetTexture(id)) {
		tw = (float)tex->GetWidth();
		th = (float)tex->GetHeight();
	}

	// 画像の切り出しサイズ
	float sprite_w = Math::Abs(rect->z - rect->x);
	float sprite_h = Math::Abs(rect->w - rect->y);
	Vector2 sprite_size{ sprite_w, sprite_h };

	// 画像の切り出し位置
	Vector2 tex_pos{ rect->x / tw, rect->y / th };
	// 画像の切り出しサイズ
	Vector2 tex_size{ sprite_w / tw, sprite_h / th };
	// 画像の回転角度
	float angle_rad = angle * (3.14159265f / 180.0f);
	// 画面サイズの取得
	Vector2 screen_size{ logical_window_width_, logical_window_height_ };

	// パラメータを設定
	SetShaderParamVector2("u_ScreenSize", &screen_size);
	SetShaderParamVector2("u_SpritePosition", position);
	SetShaderParamVector2("u_SpriteSize", &sprite_size);
	SetShaderParamVector2("u_SpriteScale", scale);
	SetShaderParamVector2("u_SpriteCenter", center);
	SetShaderParamFloat("u_SpriteAngle", angle_rad);
	SetShaderParamVector4("u_SpriteColor", color);
	SetShaderParamVector2("u_TexturePosition", &tex_pos);
	SetShaderParamVector2("u_TextureSize", &tex_size);

	// サンプラーにテクスチャユニット0を指定
	if (int location = GetShaderUniform("u_BaseMap"); location != -1) {
		glUniform1i(location, 0);
	}

	// 描画
	glBindVertexArray(sprite_vao_);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	// 空テクスチャをバインドして解除
	Internal::BindTexture(TEXTURE_EMPTY_ID, 0);

	// デフォルトシェーダーを使用したならバインドを解除する
	if (is_empty_shader) {
		EndShader();
	}
}

#pragma endregion
