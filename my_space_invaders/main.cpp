//GlFloats[] = {x,y,z,r,g,b,...}; V0:{P0,C0};

/*
"Hello Triangle". Just the basics + shaders + 2 buffers
Dependencies:
GLEW and GLFW3 to start GL.
Based on OpenGL 4 Example Code.
*/
#include <iostream>

#include "gl_utils.h"		// utility stuff discussed in previous tutorials is here
#include <GL/glew.h>		// include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h>		// GLFW helper library
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GL_LOG_FILE "gl.log"

using namespace std;
// keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 640;
int g_gl_height = 480;
int shot = 3;
int nave_pos = 10; // 0-20, inicia em 10
int monstro_move = 0;

int pontuação = 0;

int monstro_pos = 1;// 1-19
int monstro_dir = 1; //-1 ou 1
int distancia_do_jogador = 0; //
bool descer = false;
int inimigo_vel = 60;




GLFWwindow *g_window = NULL;
glm::mat4 trans(1.0);
glm::mat4 trans2(1.0);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		if (nave_pos > 1)
		{
			trans = glm::translate(trans, glm::vec3(-0.1f, 0.0f, 0.0f));
			nave_pos--;
			cout << nave_pos << endl;

		}

	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		if (nave_pos < 19)
		{
			trans = glm::translate(trans, glm::vec3(0.1f, 0.0f, 0.0f));
			nave_pos++;
			cout << nave_pos << endl;
		}
	}

	if ((key == GLFW_KEY_SPACE || key == GLFW_KEY_W) && action == GLFW_PRESS)
	{
		cout << "Tiro" << endl;
		shot = 9;
		if (nave_pos == monstro_pos)
		{
			glm::mat4 aux(1.0f);
			//trans2 = glm::translate(aux, glm::vec3(-0.1f*monstro_pos + 0.1, 0.9f, 0.0f));
			trans2 = glm::translate(aux, glm::vec3(-0.9f, 0.9f, 0.0f));
			monstro_pos = 1;
			monstro_dir = 1;
			distancia_do_jogador = 0;
			descer = false;

			if(inimigo_vel>10)
				inimigo_vel -= 5;
			else 
			{
				inimigo_vel = 1;
			}
			pontuação += 1;
			cout <<"Pontos: "<< pontuação << endl;
		}
	}
	else { shot = 3; }

	if ((key == GLFW_KEY_ESCAPE && action == GLFW_PRESS))
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

}
int main() {
	restart_gl_log();
	// all the start-up code for GLFW and GLEW is called here
	start_gl();

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS);		 // depth-testing interprets a smaller value as "closer"

								 /* OTHER STUFF GOES HERE NEXT */

	GLfloat vertices[] = {
		0.0f,  0.1f, 0.0f, 1.0f, 0.0f, 1.0f, // 0
		0.05f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 1
		-0.05f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 2

											  //Tiro
											  -0.025f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 3
											  0.025f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 4
											  -0.025f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 5
											  0.025f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f };// 6

	unsigned int indices[] = { 0,1,2,
		//Tiro
		3,5,6,
		3,6,4
	};

	GLfloat inimigos[]{ 
		0.0f,  -0.1f, 0.0f, 1.0f, 0.0f, 0.0f, // 0
		0.05f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 1
		-0.05f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 2
	};
	unsigned int indices_inimigos[] = { 0,2,1 };


	GLuint points_vbo;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* create a second VBO, containing the array of colours.
	note that we could also put them both into a single vertex buffer. in this
	case we would use the pointer and stride parameters of glVertexAttribPointer()
	to describe the different data layouts */

	GLuint colours_vbo;
	glGenBuffers(1, &colours_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);

	/* create the VAO.
	we bind each VBO in turn, and call glVertexAttribPointer() to indicate where
	the memory should be fetched for vertex shader input variables 0, and 1,
	respectively. we also have to explicitly enable both 'attribute' variables.
	'attribute' is the older name for vertex shader 'in' variables. */
	////////////////////////////////////////////////////////INIMIGOS///////////////////////////////////////////////////////////

	GLuint points_vbo_enemy;
	glGenBuffers(1, &points_vbo_enemy);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo_enemy);
	glBufferData(GL_ARRAY_BUFFER, sizeof(inimigos), inimigos, GL_STATIC_DRAW);

	GLuint colours_vbo_enemy;
	glGenBuffers(1, &colours_vbo_enemy);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_enemy);


	/////////////////////////////////////////////////FIM INIMIGOS//////////////////////////////////////////////////////////////////



	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(0);


	////////////////////////////////////////////////////////INIMIGOS///////////////////////////////////////////////////////////
	GLuint vao_enemy;
	glGenVertexArrays(1, &vao_enemy);
	glBindVertexArray(vao_enemy);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo_enemy);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_enemy);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	GLuint EBO_enemy;
	glGenBuffers(1, &EBO_enemy);

	glBufferData(GL_ARRAY_BUFFER, sizeof(inimigos), inimigos, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_enemy);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_inimigos), indices_inimigos, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(0);
	/////////////////////////////////////////////////FIM INIMIGOS//////////////////////////////////////////////////////////////////

	char vertex_shader[1024 * 256];
	char fragment_shader[1024 * 256];
	parse_file_into_str("test_vs.glsl", vertex_shader, 1024 * 256);
	parse_file_into_str("test_fs.glsl", fragment_shader, 1024 * 256);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
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

	GLuint shader_programme = glCreateProgram();
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

	glEnable(GL_CULL_FACE); // cull face
	glCullFace(GL_BACK);		// cull back face
	glFrontFace(GL_CW);			// GL_CCW for counter clock-wise



	trans = glm::translate(trans, glm::vec3(0.0f, -0.9f, 0.0f));

	trans2 = glm::translate(trans2, glm::vec3(-0.9f, 0.9f, 0.0f));

	while (!glfwWindowShouldClose(g_window)) {
		_update_fps_counter(g_window);
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, g_gl_width, g_gl_height);


		glfwSetKeyCallback(g_window, key_callback);

		monstro_move++;
		//cout << monstro_move << endl;
		if (monstro_move >= inimigo_vel) {
			if (descer == false)
			trans2 = glm::translate(trans2, glm::vec3(0.1f*monstro_dir, 0.0f, 0.0f));
			else {
				trans2 = glm::translate(trans2, glm::vec3(0.0f, -0.1f, 0.0f));
				distancia_do_jogador++;
				cout << "Distância: " << distancia_do_jogador << endl;
				descer = false;
				//17 morre
			}
			monstro_pos += monstro_dir;
			if ((monstro_pos == 19 || monstro_pos == 0) && descer == false) {
				monstro_dir = -monstro_dir;
				descer = true;
			}

			monstro_move = 0;
		}




		unsigned int transformLoc = glGetUniformLocation(shader_programme, "m");
		glUseProgram(shader_programme);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));



		glBindVertexArray(vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawElements(GL_TRIANGLES, shot, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		

		transformLoc = glGetUniformLocation(shader_programme, "m");
		glUseProgram(shader_programme);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans2));

		glBindVertexArray(vao_enemy);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);



		// update other events like input handling
		glfwPollEvents();
		if (distancia_do_jogador == 17) {
		glfwSetWindowShouldClose(g_window, 1);
		}
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(g_window);

	}

	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}
