
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define GL_LOG_FILE "gl.log"
#include <iostream>
#include "gl_utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Nave.h"
#include "Test.h"

int g_gl_width = 640;
int g_gl_height = 480;
GLFWwindow *g_window = NULL;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
float posplusx = 0.f, posplusy = 0.f, posplusz = 0.f;


Nave nave;

//// Movimentação inimigo ////

Test test, test2;

//bool enemy_dir = true; // if true == dir false == esq
//float enemyX= -1.f, enemyY =1.f;
//void enemy_move(float &enemyX, float &enemyY) {
//	if (enemy_dir){
//		if (enemyX < 2.9) {
//			enemyX += 0.0015f;
//		}
//		else{
//			enemyY -= 0.1f;
//			enemy_dir = false;
//		}
//	}
//	else{
//		if (enemyX > -1){
//			enemyX -= 0.0015f;
//		}
//		else {
//			enemyY -= 0.1f;
//			enemy_dir = true;
//		}
//	}
//}
//// movimentação inimigo ////

int main() {
	restart_gl_log();
	// all the GLFW and GLEW start-up code is moved to here in gl_utils.cpp
	start_gl("Space Invaders");
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	//glEnable( GL_DEPTH_TEST ); // enable depth-testing
	//glDepthFunc( GL_LESS );		 // depth-testing interprets a smaller value as "closer"


	glfwSetKeyCallback(g_window, key_callback);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
	//};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	//float *n = nave.GetVertices();
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, nave.getSizeVec(), nave.GetVertices(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////INIMIGO/////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	test.inicializar();
	//test2.inicializar();

	//GLfloat inimigos[]{
	//	-0.95f,  0.9f, 0.0f, 1.0f, 0.0f, 0.0f, // 0 ponta
	//	-0.90f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 1 dir
	//	-1.00f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 2 esq
	//};
	//unsigned int indices_inimigos[] = { 0,2,1 };

	//GLuint points_vbo_enemy;
	//glGenBuffers(1, &points_vbo_enemy);
	//glBindBuffer(GL_ARRAY_BUFFER, points_vbo_enemy);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(inimigos), inimigos, GL_STATIC_DRAW);

	//GLuint colours_vbo_enemy;
	//glGenBuffers(1, &colours_vbo_enemy);
	//glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_enemy);

	//GLuint vao_enemy;
	//glGenVertexArrays(1, &vao_enemy);
	//glBindVertexArray(vao_enemy);
	//glBindBuffer(GL_ARRAY_BUFFER, points_vbo_enemy);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_enemy);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);

	//GLuint EBO_enemy;
	//glGenBuffers(1, &EBO_enemy);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(inimigos), inimigos, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_enemy);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_inimigos), indices_inimigos, GL_STATIC_DRAW);

	//// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(0);

	////shadersssss

	//char enemy_vertex_shader[1024 * 256];
	//parse_file_into_str("enemy_vs.glsl", enemy_vertex_shader, 1024 * 256);

	//GLuint evs = glCreateShader(GL_VERTEX_SHADER);
	//const GLchar *pe = (const GLchar *)enemy_vertex_shader;
	//glShaderSource(evs, 1, &pe, NULL);
	//glCompileShader(evs);

	//int param = -1;
	//glGetShaderiv(evs, GL_COMPILE_STATUS, &param);
	//if (GL_TRUE != param) {
	//	fprintf(stderr, "o shader do inimigo deu ruim\n",evs);
	//	print_shader_info_log(evs);
	//	return 1;
	//}

	//GLuint enemy_shader_programme = glCreateProgram();//é ne
	////glAttachShader(shader_programme, fs);
	//glAttachShader(enemy_shader_programme, evs);
	//glLinkProgram(enemy_shader_programme);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////INIMIGO/////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	char vertex_shader[1024 * 256];
	char fragment_shader[1024 * 256];
	
	parse_file_into_str("test_vs.glsl", vertex_shader, 1024 * 256);
	parse_file_into_str("test_fs.glsl", fragment_shader, 1024 * 256);
	
	//aqui tu bota

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);//cirar
	const GLchar *p = (const GLchar *)vertex_shader;
	glShaderSource(vs, 1, &p, NULL);
	glCompileShader(vs);

	// check for compile errors
	int params = -1;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf(stderr, "ERROR: GL shader index %i did not compile\n", vs);
		print_shader_info_log(vs);
		return 1; // or exit or something
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	p = (const GLchar *)fragment_shader;
	glShaderSource(fs, 1, &p, NULL);
	glCompileShader(fs);

	// check for compile errors
	glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf(stderr, "ERROR: GL shader index %i did not compile\n", fs);
		print_shader_info_log(fs);
		return 1; // or exit or something
	}

	GLuint shader_programme = glCreateProgram();//é ne
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	glGetProgramiv(shader_programme, GL_LINK_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf(stderr, "ERROR: could not link shader programme GL index %i\n",
			shader_programme);
		print_programme_info_log(shader_programme);
		return false;
	}

	// load and create a texture
	// -------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	//stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("spaceshuttle.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glEnable(GL_CULL_FACE); // cull face
	glCullFace(GL_BACK);		// cull back face
	glFrontFace(GL_CW);			// GL_CCW for counter clock-wise


	int posuniform;

	while (!glfwWindowShouldClose(g_window)) {

		// wipe the drawing surface clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glViewport(0, 0, g_gl_width, g_gl_height);

		// bind Texture
		glBindTexture(GL_TEXTURE_2D, texture);

		//
		// Note: this call is not necessary, but I like to do it anyway before any
		// time that I call glDrawArrays() so I never use the wrong shader programme
		glUseProgram(shader_programme);

		posuniform = glGetUniformLocation(shader_programme, "posplus");
		glUniform4f(posuniform, posplusx, posplusy, posplusz, 1.0f);

		// Note: this call is not necessary, but I like to do it anyway before any
		// time that I call glDrawArrays() so I never use the wrong vertex data
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////INIMIGO/////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//glUseProgram(enemy_shader_programme);
		//glBindVertexArray(vao_enemy);
		//// draw points 0-3 from the currently bound VAO with current in-use shader
		//posuniform = glGetUniformLocation(enemy_shader_programme, "posplus");
		//enemy_move(enemyX, enemyY);
		//glUniform4f(posuniform, enemyX, enemyY, 0.0f, 1.0f);

		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

		test.atualizar();

		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////INIMIGO/////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		// update other events like input handling
		glfwPollEvents();
		if (GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(g_window, 1);
		}
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(g_window);
	}



	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	static bool gWireframe = 0;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	/*if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
	gWireframe = !gWireframe;
	if (gWireframe)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}*/

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);



	if (key == GLFW_KEY_A && action != GLFW_RELEASE)
		if (posplusx > -1.8f)
			 posplusx-=0.1f;


	if (key == GLFW_KEY_D && action != GLFW_RELEASE)
		if(posplusx < 1.8f)
			posplusx+=0.1f;



	//if (key == GLFW_KEY_W && action != GLFW_RELEASE)
	//{
	//	posplusy += 0.1f;
	//}

	//if (key == GLFW_KEY_S && action != GLFW_RELEASE)
	//{
	//	posplusy -= 0.1f;
	//}

	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		std::cout <<"x ="<< posplusx <<"\n y =" <<posplusy<<	 "X de X-homens\n";
	}
}


