#pragma once
#include "WorldObject.h"

class House : public WorldObject
{
public:

	//general wall variables
	float WallHeight = 2.f;
	glm::vec3 WallColour = glm::vec3(1.0f, 1.0f, 1.0f);

	//wall proportions
	float FrontBackWallWidth = 3;
	float SideWallWidth = 3;

	//roof variables
	float RoofAngle = 45.f;
	glm::vec3 RoofColour = glm::vec3(0.5f, 0.5f, 0.5f);

	//door variables
	float DoorWidth = 1.f;
	glm::vec3 DoorColour = glm::vec3(0.5f, 0.5f, 0.5f);

	//whether or not the door is open
	bool CheckDoorCollision = true;

	std::vector<Vertex> DoorVertices =
	{
     //door (first triangle)
     Vertex(glm::vec3(-DoorWidth / 2.0f, 0, SideWallWidth / 2.0f), DoorColour, glm::vec2(0)),
     Vertex(glm::vec3(DoorWidth / 2.0f, 0, SideWallWidth / 2.0f), DoorColour, glm::vec2(0)),
     Vertex(glm::vec3(-DoorWidth / 2.0f, WallHeight, SideWallWidth / 2.0f), DoorColour, glm::vec2(0)),

     //door (second triangle)
     Vertex(glm::vec3(DoorWidth / 2.0f, 0, SideWallWidth / 2.0f), DoorColour, glm::vec2(0)),
     Vertex(glm::vec3(-DoorWidth / 2.0f, WallHeight, SideWallWidth / 2.0f), DoorColour, glm::vec2(0)),
     Vertex(glm::vec3(DoorWidth / 2.0f, WallHeight, SideWallWidth / 2.0f), DoorColour, glm::vec2(0)),
	};

	//constructor(s)
	House(glm::vec3 InPos, glm::vec3 InSize);

	//create the vertices of the house
	std::vector<Vertex> CreateVertices() const override;

	//initialize the house
	void Initialize(std::vector<std::vector<Vertex>>& InVertices, const unsigned& InShaderProgram) override;

	//function to render the house
	void Render(const unsigned int& InShaderProgram, const std::string& ModelKey) override;
};

