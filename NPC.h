#pragma once
#include "BezierCurve.h"
#include "WorldObject.h"

class NPC_ : public WorldObject
{
public:
	//constructor(s)
	NPC_(glm::vec3 InPos, glm::vec3 InSize, BezierCurve* InPath);

	//the movement speed of the npc
	float Speed = 5;

	//pointer to the vector of vertices that make up the path
	BezierCurve* Path = nullptr;

	//path progress direction
	int PathDirection = 1.0f;

	//the current index of the path
	int PathIndex = 0;

	//function to update the npc
	void Tick(float DeltaTime) override;
};
