// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : シェーダーを管理する
// -----------------------------------------------------------------------------------------

#ifndef YAXL_SHADER_H_
#define YAXL_SHADER_H_

#include "YaxlLibLink.h"

namespace Yaxl {

class Shader {
public:
	Shader();

	~Shader();

public:
	/// <summary>
	/// シェーダーの読み込み
	/// </summary>
	/// <param name="vert_path">= ファイルパス</param>
	/// <param name="frag_path">= ファイルパス</param>
	/// <returns>読み込みに成功したら真を、読み込みに失敗したら偽を返す</returns>
	bool Load(const char* vert_path, const char* frag_path);

	/// <summary>
	/// テキストからのシェーダーの読み込み
	/// </summary>
	/// <param name="vert_code">= テキスト</param>
	/// <param name="frag_code">= テキスト</param>
	/// <returns>読み込みに成功したら真を、読み込みに失敗したら偽を返す</returns>
	bool LoadString(const char* vert_code, const char* frag_code);

	/// <summary>
	/// シェーダーを適用
	/// </summary>
	void Use() const;

	/// <summary>
	/// シェーダーを破棄
	/// </summary>
	void Delete();

	/// <summary>
	/// 生IDの取得
	/// </summary>
	/// <returns>ID</returns>
	unsigned int GetProgramID() const;

private:
	unsigned int gl_program_id_;

public:
	// コピー禁止
	Shader(const Shader& other) = delete;
	Shader& operator = (const Shader& other) = delete;
};
}	// namespace Yaxl end

#endif
