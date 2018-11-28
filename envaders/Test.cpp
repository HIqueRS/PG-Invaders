#include "Test.h"



Test::Test()
{
	enemyX = -1.f;
	enemyY = 1.f;
}


Test::~Test()
{
}

void Test::movimentacao(float & enemyX, float & enemyY)
{
	if (enemy_dir) {
		if (enemyX < 2.9) {
			enemyX += 0.0015f;
		}
		else {
			enemyY -= 0.1f;
			enemy_dir = false;
		}
	}
	else {
		if (enemyX > -1) {
			enemyX -= 0.0015f;
		}
		else {
			enemyY -= 0.1f;
			enemy_dir = true;
		}
	}
}

void Test::inicializar()
{
	
	glGenBuffers(1, &points_vbo_enemy);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo_enemy);
	glBufferData(GL_ARRAY_BUFFER, sizeof(inimigos), inimigos, GL_STATIC_DRAW);

	glGenBuffers(1, &colours_vbo_enemy);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_enemy);

	glGenVertexArrays(1, &vao_enemy);
	glBindVertexArray(vao_enemy);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo_enemy);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_enemy);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

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

	//shadersssss

	char enemy_vertex_shader[1024 * 256];
	parse_file_into_str("enemy_vs.glsl", enemy_vertex_shader, 1024 * 256);

	GLuint evs = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *pe = (const GLchar *)enemy_vertex_shader;
	glShaderSource(evs, 1, &pe, NULL);
	glCompileShader(evs);

	int param = -1;
	glGetShaderiv(evs, GL_COMPILE_STATUS, &param);
	if (GL_TRUE != param) {
		fprintf(stderr, "o shader do inimigo deu ruim\n", evs);
		print_shader_info_log(evs);
		//return 1;
	}

	enemy_shader_programme = glCreateProgram();//é ne
	//glAttachShader(shader_programme, fs);
	glAttachShader(enemy_shader_programme, evs);
	glLinkProgram(enemy_shader_programme);
}

void Test::atualizar()
{
	glUseProgram(enemy_shader_programme);
	glBindVertexArray(vao_enemy);
	// draw points 0-3 from the currently bound VAO with current in-use shader
	posuniform = glGetUniformLocation(enemy_shader_programme, "posplus");
	movimentacao(enemyX, enemyY);
	glUniform4f(posuniform, enemyX, enemyY, 0.0f, 1.0f);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
