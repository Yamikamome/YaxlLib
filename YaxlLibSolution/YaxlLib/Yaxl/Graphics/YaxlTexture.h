// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : テクスチャ管理クラス
// -----------------------------------------------------------------------------------------

#ifndef YAXL_TEXTURE_H_
#define YAXL_TEXTURE_H_

namespace Yaxl {

class Texture {
public:
	Texture();

	Texture(unsigned int gl_id, int width, int height);

	~Texture();

	/// <summary>
	/// 画像ファイルの読み込み
	/// </summary>
	/// <param name="file_path">= 画像ファイルパス</param>
	/// <returns>読み込みに成功したら真を、読み込みに失敗したら偽を返す</returns>
	bool Load(const char* file_path);

	/// <summary>
	/// テクスチャをバインド
	/// </summary>
	/// <param name="slot">= バインド先のスロット番号</param>
	void Bind(unsigned int slot = 0) const;

	/// <summary>
	/// テクスチャを破棄
	/// </summary>
	void Delete();

	/// <summary>
	/// テクスチャの幅を取得
	/// </summary>
	/// <returns>幅（px）</returns>
	int GetWidth() const;

	/// <summary>
	/// テクスチャの高さを取得
	/// </summary>
	/// <returns>高さ（px）</returns>
	int GetHeight() const;

	/// <summary>
	/// 生IDの取得
	/// </summary>
	/// <returns>ID</returns>
	unsigned int GetTextureId();

private:
	/// <summary>
	/// 標準的な画像の読み込み
	/// </summary>
	/// <param name="file_path">= 画像ファイルパス</param>
	/// <returns>読み込みに成功したら真を、読み込みに失敗したら偽を返す</returns>
	bool LoadStandardImage(const char* file_path);

	/// <summary>
	/// DDSの読み込み
	/// </summary>
	/// <param name="file_path">= 画像ファイルパス</param>
	/// <returns>読み込みに成功したら真を、読み込みに失敗したら偽を返す</returns>
	bool LoadDDS(const char* file_path);

private:
	unsigned int gl_texture_id_;

	int width_;

	int height_;

	int channels_;

public:
	// コピー禁止
	Texture(const Texture& other) = delete;
	Texture& operator = (const Texture& other) = delete;
};

}	// namespace Yaxl end

#endif