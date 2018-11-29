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
#include "Nave.h"

class Test
{
public:
	Test();
	~Test();
	Test(int i);
	void movimentacao(float &enemyX, float &enemyY);
	void inicializar();
	void atualizar();

protected:

	
	float enemyX, enemyY,pos;
	bool enemy_dir = true; // if true == dir false == esq

	GLfloat inimigos[18] {
		-0.95f,  0.9f, 0.0f, 1.0f, 0.0f, 0.0f, // 0 ponta
		-0.90f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 1 dir
		-1.00f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 2 esq
	};
	unsigned int indices_inimigos[3] = { 0,2,1 };

	int posuniform;

	GLuint points_vbo_enemy;

	GLuint colours_vbo_enemy;

	GLuint vao_enemy;

	GLuint EBO_enemy;

	GLuint enemy_shader_programme;

};

