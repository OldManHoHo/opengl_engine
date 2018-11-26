#include "TGLMeshVertices.h"



TGLMeshVertices::TGLMeshVertices(std::vector<GLfloat> const &vertices)
{
	GLuint VAO;
	
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}

	glGenBuffers(1, &vertex_VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	count = vertices.size() / 3;
	
	calculate_normals(vertices);
}

TGLMeshVertices::~TGLMeshVertices()
{
}

void TGLMeshVertices::calculate_normals(std::vector<GLfloat> const &vertices)
{
	int length = vertices.size();
	std::vector <GLfloat> out_normals;
	//out_normals.resize(length);
	out_normals = vertices;
	
	glm::vec3 center(0, 0, 0);
	
	for (int i = 0; i < length; i += 3)
	{
		center += glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
	}
	center = center * (1.0f / (length / 3));
	for (int i = 0; i < length; i = i + 9)
	{
		glm::vec3 vert1 = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
		glm::vec3 vert2 = glm::vec3(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
		glm::vec3 vert3 = glm::vec3(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
		glm::vec3 v1 = vert2 - vert1;
		glm::vec3 v2 = vert3 - vert1;
		glm::vec3 face_center = (vert1 + vert2 + vert3)*(1.0f / 3);
		glm::vec3 out_vec = glm::cross(v1, v2);
		out_vec = glm::normalize(out_vec);
		if (glm::dot(out_vec, face_center - center) < 0)
		{
			out_vec = out_vec*-1.0f;
		}
		out_normals[i] = out_vec[0]; out_normals[i + 1] = out_vec[1]; out_normals[i + 2] = out_vec[2];
		out_normals[i + 3] = out_vec[0]; out_normals[i + 4] = out_vec[1]; out_normals[i + 5] = out_vec[2];
		out_normals[i + 6] = out_vec[0]; out_normals[i + 7] = out_vec[1]; out_normals[i + 8] = out_vec[2];
	}
	for (int i = 0; i < length; i += 3)
	{
		//out_normals[i] = 0.0;
		//out_normals[i+1] = 1.0;
		//out_normals[i + 2] = 0.0;

	}

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}

	glGenBuffers(1, &normal_VBO);

	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}

	glBindBuffer(GL_ARRAY_BUFFER, normal_VBO);

	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}

	glBufferData(GL_ARRAY_BUFFER, length * sizeof(GLfloat), &out_normals[0], GL_STATIC_DRAW);

	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}
}