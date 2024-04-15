#include "WaveSurface.h"

#include "Macros.h"

WaveSurface::WaveSurface(const glm::vec3 InPos, const glm::vec3 InSize, const int InLOD, const float InWaviness) : Terrain_(InPos, InSize, CREATE_NAME), LOD(InLOD), Waviness(InWaviness)
{

}

std::vector<Vertex> WaveSurface::CreateVertices() const
{
	//create the vertices
	std::vector<Vertex> Vertices;

	//the colour of the bezier curve
	constexpr glm::vec3 Colour = glm::vec3(1, 0, 0);

	//constant z value 1
	const float ZValue1 = 0;

	//constant z value 2
	const float ZValue2 = 1;

	//loop through the x axis
	for (int x = 0; x < LOD; x += 1)
	{
		//get the x position
		const float XPos = float(x) / float(LOD);

		//get the y position
		const float YPos = sin(XPos * Waviness);

		//get the next x position
		const float NextXPos = float(x + 1) / float(LOD);

		//get the nexy y position
		const float NextYPos = sin(NextXPos * Waviness);

		////amount of z values for every x value
		//constexpr int ZValues = 2;
		//
		////loop through the z axis
		//for (int z = 0; z < ZValues; z++)
		//{
		//	//set the z values
		//	const float ZValue1 = float(z) / float(ZValues);
		//	const float ZValue2 = float(z + 1) / float(ZValues);

			//create our triangles
			Vertices.insert(Vertices.end(), 
			{
				//create the first triangle
				Vertex(glm::vec3(XPos, YPos, ZValue1), Colour),
				Vertex(glm::vec3(NextXPos, NextYPos, ZValue1), Colour),
				Vertex(glm::vec3(XPos, YPos, ZValue2), Colour),

				//create the second triangle
				Vertex(glm::vec3(NextXPos, NextYPos, ZValue1), Colour),
				Vertex(glm::vec3(XPos, YPos, ZValue2), Colour),
				Vertex(glm::vec3(NextXPos, NextYPos, ZValue2), Colour)
			});

			//////create the first triangle
			//Vertices.emplace_back(glm::vec3(XPos, YPos, ZValue1), Colour);
			//Vertices.emplace_back(glm::vec3(NextXPos, NextYPos, ZValue1), Colour);
			//Vertices.emplace_back(glm::vec3(XPos, YPos, ZValue2), Colour);

			//////create the second triangle
			//Vertices.emplace_back(glm::vec3(NextXPos, NextYPos, ZValue1), Colour);
			//Vertices.emplace_back(glm::vec3(XPos, YPos, ZValue2), Colour);
			//Vertices.emplace_back(glm::vec3(NextXPos, NextYPos, ZValue2), Colour);
		//}
	}

	//return the vertices
	return Vertices;
}
