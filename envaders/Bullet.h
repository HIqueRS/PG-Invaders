#pragma once
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <time.h>
//#define GL_LOG_FILE "gl.log"
#include <iostream>
#include "gl_utils.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

class Bullet
{
public:
	Bullet();
	~Bullet();
	void movimentacao(float &nvX, float &nvY,bool & atirou);
	void inicializar();
	void atualizar(float &nvX,float &nvY,bool &atirou);

protected:
	float bulletX, bulletY;
	bool atirado;

	GLfloat bullet[18]{
		0.05f,  -0.7f, 0.0f,   1.0f, 0.0f, 0.0f, // 0 ponta
		0.1f, -0.9f, 0.0f,   0.0f, 1.0f, 0.0f, // 1 dir
		-0.1f, -0.9f, 0.0f,   0.0f, 0.0f, 1.0f // 2 esq
	};

	unsigned int indices_bullet[3] = { 0,2,1 };

	int posuniform;

	GLuint points_vbo_bullet;

	GLuint colours_vbo_bullet;

	GLuint vao_bullet;

	GLuint ebo_bullet;

	GLuint bullet_shader_programme;
};

