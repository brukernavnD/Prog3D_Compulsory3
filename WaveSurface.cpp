#include "WaveSurface.h"

WaveSurface::WaveSurface(const glm::vec3 InPos, const glm::vec3 InSize)
{
	//set the position
	Position = InPos;

	//set the size
	Size = InSize;

	//set the name
	Name = "WaveSurface";
}

std::vector<Vertex> WaveSurface::CreateVertices() const
{
	//create the vertices
	std::vector<Vertex> Vertices;

	//loop through the length of the floor via the z axis
    for (int X = 0; X < Size.x; X++)
    {
        //get our x position
        const float XPos = float(X) - float(Size.x) / 2 + Position.x;

	    //loop through the width of the floor via the x axis
		for (int Z = 0; Z < Size.z; Z++)
		{
            //get our z position
            const float ZPos = float(Z) - float(Size.z) / 2 + Position.z;

			//create the first triangle
			Vertices.emplace_back(float(XPos), Size.y * sin(float(XPos)), float(ZPos), 1.0, 0.0, 0.0, 0.0, 0.0);
			Vertices.emplace_back(float(XPos) + 1, Size.y * sin(float(XPos) + 1), float(ZPos), 1.0, 0.0, 0.0, 0.0, 0.0);
			Vertices.emplace_back(float(XPos), Size.y * sin(float(XPos)), float(ZPos) + 1, 1.0, 0.0, 0.0, 0.0, 0.0);

			//create the second triangle
			Vertices.emplace_back(float(XPos) + 1, Size.y * sin(float(XPos) + 1), float(ZPos), 1.0, 0.0, 0.0, 0.0, 0.0);
			Vertices.emplace_back(float(XPos), Size.y * sin(float(XPos)), float(ZPos) + 1, 1.0, 0.0, 0.0, 0.0, 0.0);
			Vertices.emplace_back(float(XPos) + 1, Size.y * sin(float(XPos) + 1), float(ZPos) + 1, 1.0, 0.0, 0.0, 0.0, 0.0);
		}
	}

	//return the vertices
	return Vertices;
}

void WaveSurface::BeginPlay(const std::vector<WorldObject*>& InWorldObjects)
{
	//do nothing
}
