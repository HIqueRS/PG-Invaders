#include "Bullet.h"



Bullet::Bullet()
{
	bulletX = 0;
	bulletY = 0;
}


Bullet::~Bullet()
{
}

void Bullet::movimentacao(float & nvX, float & nvY, bool & atirou)
{
	if (!atirou)
	{
		std::cout << "sla to com sono";
		bulletX = nvX;
		bulletY = nvY;
	}
	else {
		bulletY += 0.0020f;
	}
}

void Bullet::inicializar()
{
	glGenBuffers(1, &points_vbo_bullet);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo_bullet);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bullet), bullet, GL_STATIC_DRAW);

	glGenBuffers(1, &colours_vbo_bullet);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_bullet);

	glGenVertexArrays(1, &vao_bullet);
	glBindVertexArray(vao_bullet);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo_bullet);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo_bullet);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo_bullet);

	glBufferData(GL_ARRAY_BUFFER, sizeof(bullet), bullet, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_bullet);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_bullet), indices_bullet, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(0);

	//shadersssss

	char bullet_vertex_shader[1024 * 256];
	parse_file_into_str("bullet_vs.glsl", bullet_vertex_shader, 1024 * 256);

	GLuint evs = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *pe = (const GLchar *)bullet_vertex_shader;
	glShaderSource(evs, 1, &pe, NULL);
	glCompileShader(evs);

	int param = -1;
	glGetShaderiv(evs, GL_COMPILE_STATUS, &param);
	if (GL_TRUE != param) {
		fprintf(stderr, "o shader do inimigo deu ruim\n", evs);
		print_shader_info_log(evs);
		//return 1;
	}

	bullet_shader_programme = glCreateProgram();//é ne
	//glAttachShader(shader_programme, fs);
	glAttachShader(bullet_shader_programme, evs);
	glLinkProgram(bullet_shader_programme);
}

void Bullet::atualizar(float & nvX, float & nvY, bool & atirou)
{
	glUseProgram(bullet_shader_programme);
	glBindVertexArray(vao_bullet);
	// draw points 0-3 from the currently bound VAO with current in-use shader
	posuniform = glGetUniformLocation(bullet_shader_programme, "posplus");
	//movimentacao(nvX, nvY,atirou);
	//glUniform4f(posuniform, bulletX, bulletY, 0.0f, 1.0f);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

