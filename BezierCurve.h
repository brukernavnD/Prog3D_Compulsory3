#pragma once
#include "GameplayStatics.h"
#include "WorldObject.h"

//class for generating, storing, and rendering a curve
class BezierCurve : public WorldObject
{
public:

	//the control points of the curve
	std::vector<Vertex> ControlPoints = std::vector<Vertex>();

	//the curve's level of detail
	int LevelOfDetail = 500;

	//the curve's colour
	glm::vec3 Colour = WhiteColour;

	//constructor(s)
	BezierCurve(std::vector<Vertex> InControlPoints, /*std::vector<float> InControlVector,*/ glm::vec3 InPosition, glm::vec3 InSize);

	//function to generate our vertices
	std::vector<Vertex> CreateVertices() const override;

	//function called when beginning play
	void BeginPlay() override;

	//function to render the curve
	void Render() override;

	//function to get the start point of the curve
	Vertex GetPointOnCurve(int Index) const;
};

