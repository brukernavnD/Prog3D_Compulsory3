#pragma once
#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "Vertex.h"

//struct to store information about the y value of the object right below us
struct YBelowInfo_
{
	float YValue = 0.0f;
	glm::vec3 Normal = glm::vec3(0.0f, 0.0f, 0.0f);
	std::vector<Vertex> Vertices = std::vector<Vertex>();
};

class WorldObject
{
public:

	//our position
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);

	//our rotation
	glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	//our size
	glm::vec3 Size = glm::vec3(1.0f, 1.0f, 1.0f);

	//the vertices of the object (in the form of floats)
	std::vector<Vertex> Vertices;

	//whether or not the object is collidable
	bool bIsCollidable = true;

	//storage for texture paths
	std::vector<std::string> TexturePaths = std::vector<std::string>();

	//storage for the texture ids
	std::vector<unsigned int> TextureIDs = std::vector<unsigned int>();

	//the id of this object (defined with a preprocessor macro)
	int ID = -1;

	//our name
	std::string Name = "UnNamed";


	//destructor
	virtual ~WorldObject();

	//operator overloads
	bool operator==(const WorldObject* Other) const;

	//constructor(s)
	WorldObject();
	explicit WorldObject(glm::vec3 InPosition, glm::vec3 InSize, std::string InName);

	//function to get the the y value of of the object right below us (if there is one), using barycentric coordinates
	static float GetYBelow(glm::vec3 InPosition);
	float GetYBelow() const;

	//function to get the the y value of of the object right below us (if there is one), using barycentric coordinates and the normal of the triangle we are on
	static YBelowInfo_ GetYBelowInfo(glm::vec3 InPosition);
	YBelowInfo_ GetYBelowInfo() const;

	//function to get the identity matrix of the object
	glm::mat4 GetModelMatrix() const;

	//function to get the vertices of the object in world space
	std::vector<Vertex> GetWorldVertices() const;

	//function to translate a position from this object's local space to world space
	Vertex TranslateToWorldSpace(Vertex InVertex) const;

	//function to check if another hitbox is colliding with this one
	bool CheckCollisionSimple(const WorldObject* InOtherObject) const;

	//function to create the vertices of the object
	virtual std::vector<Vertex> CreateVertices() const;

	//function to initialize the textures of the object
	virtual void InitializeTextures(std::vector<std::string>& InTexturePaths);

	//function called when beginning play
	virtual void BeginPlay();

	//function to render the object
	virtual void Render();

	//tick function
	virtual void Tick(float DeltaTime);
};