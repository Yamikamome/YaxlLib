#include "YaxlTexture.h"

#include <glad/glad.h>
#include <iostream>

// stb_imageはここでのみ展開する
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace Yaxl;

Texture::Texture() :
	gl_texture_id_(0),
	width_(0),
	height_(0),
	channels_(0) {
}

Texture::~Texture() {
	Delete();
}

bool Texture::Load(const char* file_path) {
	std::string path_str(file_path);

	// DDSファイルは専用処理で読み込む
	if (path_str.substr(path_str.find_last_of(".") + 1) == "dds") {
		return LoadDDS(file_path);
	}

	return LoadStandardImage(file_path);
}

void Texture::Bind(unsigned int slot) const {
	if (gl_texture_id_ != 0) {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, gl_texture_id_);
	}
}

void Texture::Delete() {
	if (gl_texture_id_ != 0) {
		glDeleteTextures(1, &gl_texture_id_);
		gl_texture_id_ = 0;
	}
}

int Yaxl::Texture::GetWidth() const {
	return width_;
}

int Yaxl::Texture::GetHeight() const {
	return height_;
}

unsigned int Yaxl::Texture::GetTextureId() {
	return gl_texture_id_;
}

bool Yaxl::Texture::LoadStandardImage(const char* file_path) {
	// 座標系の反転設定
	stbi_set_flip_vertically_on_load(false);

	unsigned char* data = stbi_load(file_path, &width_, &height_, &channels_, 0);
	if (data == nullptr) {
		std::cerr << "ERROR::TEXTURE::FAILED_TO_LOAD_IMAGE\nDetail: " << file_path << std::endl;
		return false;
	}

	// チャンネル数からカラーフォーマットを判定
	GLenum format = GL_RGB;
	if (channels_ == 1) format = GL_RED;
	else if (channels_ == 3) format = GL_RGB;
	else if (channels_ == 4) format = GL_RGBA;

	glGenTextures(1, &gl_texture_id_);
	glBindTexture(GL_TEXTURE_2D, gl_texture_id_);

	// テクスチャのラッピング設定（端のピクセルを繰り返す）
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// テクスチャのフィルタリング設定（ピクセルアートなどのために綺麗に補間する）
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// GPUに画像データを転送し、ミップマップを自動生成
	glTexImage2D(GL_TEXTURE_2D, 0, format, width_, height_, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// メモリ上の画像データは使い終わったので解放
	stbi_image_free(data);
	// バインド解除
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

bool Yaxl::Texture::LoadDDS(const char* file_path) {
	return false;
}
