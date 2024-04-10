#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "glm/gtx/transform.hpp"
#include "Vertex.h"

class WorldObject
{
public:

	//our name
	std::string Name = "UnNamed";

	virtual ~WorldObject();
	bool operator==(const WorldObject* Other) const;


	//constructor(s)
	WorldObject();

	//our position
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);

	//our rotation
	glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	//our colour
	glm::vec3 RGB = glm::vec3(0.0f, 0.0f, 0.0f);

	//our size
	glm::vec3 Size = glm::vec3(1.0f, 1.0f, 1.0f);

	//the vertices of the object (in the form of floats)
	std::vector<Vertex> MyVertices;

	//whether or not the object is collidable
	bool bIsCollidable = true;

	//storage for the model matrix
	glm::mat4 ModelMatrix = glm::mat4(1.0f);

	//storage for texture paths
	std::vector<std::string> TexturePaths = std::vector<std::string>();

	//storage for the texture ids
	std::vector<unsigned int> TextureIDs = std::vector<unsigned int>();

	//storage for the vertex index
	int VertexIndex = -1;

private:
	//function to set the vertex index
	void SetVertexIndex(const std::vector<std::vector<Vertex>>& InVertices);

	//function to get the vertex index
	int GetVertexIndex() const;

	virtual std::vector<Vertex> CreateVertices() const;

public:

	//function to get the vertices of the object in world space
	std::vector<Vertex> GetWorldVertices() const;

	//function to check if another hitbox is colliding with this one
	bool CheckCollisionSimple(const WorldObject* InOtherObject) const;

	//detailed barycentric collision check for every triangle of both objects
	bool CheckCollisionDetailed(const WorldObject* InOtherObject) const;

	//function to add my vertices to the vertices array and set the vertex index
	virtual void Initialize(std::vector<std::vector<Vertex>>& InVertices, const unsigned int& InShaderProgram);

	//function to initialize the textures of the object
	virtual void InitializeTextures(std::vector<std::string>& InTexturePaths, const unsigned int& InShaderProgram);

	//function to render the object
	virtual void Render(const unsigned int& InShaderProgram, const std::string& ModelKey);

	//tick function
	virtual void Tick(float DeltaTime);
};