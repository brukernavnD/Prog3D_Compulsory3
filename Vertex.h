#pragma once
#include <glm/vec3.hpp>

#include "glm/vec2.hpp"

struct Vertex
{
	//our position
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);

	//our colour
	glm::vec3 Normal = glm::vec3(0.0f, 0.0f, 0.0f);

	//our texture coordinates
	glm::vec2 TextureCoordinates = glm::vec2(0.0f, 0.0f);

	//constructor(s)
	Vertex();
	explicit Vertex(glm::vec3 InPos);
	Vertex(glm::vec3 Vec, glm::vec3 Vec3);
	Vertex(glm::vec3 InPos, glm::vec3 InNormal, glm::vec2 InTextureCoordinates);
	Vertex(float InX, float InY, float InZ, float InU, float InV);
	Vertex(float InX, float InY, float InZ, float InR, float InG, float InB, float InU, float InV);

	//operator overloads
	bool operator==(const Vertex& InVertex) const;
};

