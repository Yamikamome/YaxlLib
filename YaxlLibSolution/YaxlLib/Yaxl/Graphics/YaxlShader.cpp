#include "YaxlShader.h"

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace Yaxl;

static constexpr unsigned int EMPTY_SHADER_ID{ 0 };

Shader::Shader() :
	gl_program_id_(EMPTY_SHADER_ID) {
}

Shader::~Shader() {
	Delete();
}

bool Shader::Load(const char* vert_path, const char* frag_path) {
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream v_shader_file;
	std::ifstream f_shader_file;

	v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		v_shader_file.open(vert_path);
		f_shader_file.open(frag_path);
		std::stringstream v_shader_stream, f_shader_stream;
		v_shader_stream << v_shader_file.rdbuf();
		f_shader_stream << f_shader_file.rdbuf();
		v_shader_file.close();
		f_shader_file.close();
		vertex_code = v_shader_stream.str();
		fragment_code = f_shader_stream.str();
	}
	catch (const std::ifstream::failure& e) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << "Detail: " << e.what() << std::endl;
		return false;
	}

	const char* v_shader_code = vertex_code.c_str();
	const char* f_shader_code = fragment_code.c_str();
	unsigned int vertex, fragment;
	int success;
	char info_log[512];

	// 頂点シェーダー
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &v_shader_code, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, info_log);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	// フラグメントシェーダー
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &f_shader_code, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, info_log);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	// リンク
	gl_program_id_ = glCreateProgram();
	glAttachShader(gl_program_id_, vertex);
	glAttachShader(gl_program_id_, fragment);
	glLinkProgram(gl_program_id_);
	glGetProgramiv(gl_program_id_, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(gl_program_id_, 512, NULL, info_log);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return true;
}

bool Yaxl::Shader::LoadString(const char* vert_code, const char* frag_code) {
	unsigned int vertex, fragment;
	int success;
	char info_log[512];

	// 頂点シェーダーのコンパイル
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vert_code, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, info_log);
		return false;
	}

	// フラグメントシェーダーのコンパイル
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &frag_code, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, info_log);
		return false;
	}

	// プログラムのリンク
	gl_program_id_ = glCreateProgram();
	glAttachShader(gl_program_id_, vertex);
	glAttachShader(gl_program_id_, fragment);
	glLinkProgram(gl_program_id_);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return true;
}

void Shader::Use() const {
	if (gl_program_id_ != EMPTY_SHADER_ID) {
		glUseProgram(gl_program_id_);
	}
}

void Shader::Delete() {
	if (gl_program_id_ != EMPTY_SHADER_ID) {
		glDeleteProgram(gl_program_id_);
		gl_program_id_ = EMPTY_SHADER_ID;
	}
}

unsigned int Shader::GetProgramID() const {
	return gl_program_id_;
}
