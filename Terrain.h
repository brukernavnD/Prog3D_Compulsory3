#pragma once
#include "WorldObject.h"

class Terrain_ : public WorldObject
{
public:

	//constructor
	Terrain_(glm::vec3 InPosition, glm::vec3 InSize, std::string InName);

	//rendering
	void Render() override;
};

