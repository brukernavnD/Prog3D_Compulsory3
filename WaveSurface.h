#pragma once
#include "Terrain.h"

class WaveSurface : public Terrain_
{
public:

	//the level of detail of the wave surface
	int LOD = 100;

	//the waviness of the wave surface
	float Waviness = 2.0f;

	//constructor(s)
	WaveSurface(glm::vec3 InPos, glm::vec3 InSize, int InLOD, float InWaviness);

	//generate the vertices of the uneven surface
	std::vector<Vertex> CreateVertices() const override;
};

