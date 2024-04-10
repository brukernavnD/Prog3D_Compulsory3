#pragma once
#include <string>
#include <vector>

#include "Vertex.h"
#include "WorldObject.h"
#include "glm/vec3.hpp"

class Pickup : public WorldObject
{
public:
	//constructor(s)
	Pickup(glm::vec3 InPos, glm::vec3 InSize, std::string InTexturePath);
	
	//whether or not the pickup is active
	bool IsActive = true;

	//function to render the pickup
	void Render(const unsigned int& InShaderProgram, const std::string& ModelKey) override;
};

