#pragma once
#include <string>
#include "WorldObject.h"

class Pickup_ : public WorldObject
{
public:
	//constructor(s)
	Pickup_(glm::vec3 InPos);
	
	//whether or not the pickup is active
	bool IsActive = true;

	//function called when beginning play
	void BeginPlay() override;

	//function to render the pickup
	void Render() override;
};

