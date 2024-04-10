#include "Vertex.h"

Vertex::Vertex()
{
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Normal = glm::vec3(1.0f, 1.0f, 1.0f);
}

Vertex::Vertex(glm::vec3 InPos)
{
	Position = InPos;
	Normal = glm::vec3(1.0f, 1.0f, 1.0f);
	TextureCoordinates = glm::vec2(0.0f, 0.0f);
}

Vertex::Vertex(const glm::vec3 InPos, const glm::vec3 InNormal, const glm::vec2 InTextureCoordinates)
{
	Position = InPos;
	Normal = InNormal;
	TextureCoordinates = InTextureCoordinates;
}

Vertex::Vertex(float InX, float InY, float InZ, float InU, float InV)
{
	Position = glm::vec3(InX, InY, InZ);
	Normal = glm::vec3(1.0f, 1.0f, 1.0f);
	TextureCoordinates = glm::vec2(InU, InV);
}

Vertex::Vertex(const float InX, const float InY, const float InZ, const float InR, const float InG, const float InB, const float InU, const float InV)
{
	Position = glm::vec3(InX, InY, InZ);
	Normal = glm::vec3(InR, InG, InB);
	TextureCoordinates = glm::vec2(InU, InV);
}

bool Vertex::operator==(const Vertex& InVertex) const
{
	return Position == InVertex.Position && Normal == InVertex.Normal && TextureCoordinates == InVertex.TextureCoordinates;
}
