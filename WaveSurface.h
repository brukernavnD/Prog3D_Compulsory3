#pragma once
#include "WorldObject.h"

class WaveSurface : public WorldObject
{
	public:

	//constructor(s)
	WaveSurface(glm::vec3 InPos, glm::vec3 InSize);

	//generate the vertices of the uneven surface
	std::vector<Vertex> CreateVertices() const override;

	//begin play function
	void BeginPlay(const std::vector<WorldObject*>& InWorldObjects) override;
};

