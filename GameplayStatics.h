#pragma once
#include <string>
#include <vector>
#include "Vertex.h"
#include "glm/detail/func_geometric.inl"

namespace Statics
{
	//the default texture to use for objects that don't have a texture
	static std::string DefaultTexture = "Textures/DefaultTexture.png";

	//the colour value to use to indicate that the object should be rendered with a texture
	static glm::vec3 TextureColour = glm::vec3(-1);

	//the culling distance used when rendering objects
	static float CullingDistance = 10000000.0f;

	//scale variable for the pickup placement in the world
	static glm::vec3 PickupsScale = glm::vec3(5.5, 1, 5.5);

	//the window's width and height
	static float WindowWidth = 800;
	static float WindowHeight = 800;

	//function to get the verticies of a cube with a specific colour
	static std::vector<Vertex> GetCubeVertices()
	{
		//create a vector to store the vertices
		std::vector<Vertex> Vertices = {

			//front side (first triangle)
			Vertex(glm::vec3(-1, -1, 1), TextureColour, glm::vec2(0, 0)),
			Vertex(glm::vec3(1, -1, 1), TextureColour, glm::vec2(1, 0)),
			Vertex(glm::vec3(-1, 1, 1), TextureColour, glm::vec2(0, 1)),

			//front side (second triangle)
			Vertex(glm::vec3(1, -1, 1), TextureColour, glm::vec2(1, 0)),
			Vertex(glm::vec3(-1, 1, 1), TextureColour, glm::vec2(0, 1)),
			Vertex(glm::vec3(1, 1, 1), TextureColour, glm::vec2(1, 1)),

			//back side (first triangle)
			Vertex(glm::vec3(-1, -1, -1), TextureColour, glm::vec2(0, 0)),
			Vertex(glm::vec3(-1, 1, -1), TextureColour, glm::vec2(0, 1)),
			Vertex(glm::vec3(1, -1, -1), TextureColour, glm::vec2(1, 0)),

			//back side (second triangle)
			Vertex(glm::vec3(-1, 1, -1), TextureColour, glm::vec2(0, 1)),
			Vertex(glm::vec3(1, -1, -1), TextureColour, glm::vec2(1, 0)),
			Vertex(glm::vec3(1, 1, -1), TextureColour, glm::vec2(1, 1)),

			//left side (first triangle)
			Vertex(glm::vec3(-1, -1, -1), TextureColour, glm::vec2(0, 0)),
			Vertex(glm::vec3(-1, -1, 1), TextureColour, glm::vec2(1, 0)),
			Vertex(glm::vec3(-1, 1, -1), TextureColour, glm::vec2(0, 1)),

			//left side (second triangle)
			Vertex(glm::vec3(-1, -1, 1), TextureColour, glm::vec2(1, 0)),
			Vertex(glm::vec3(-1, 1, -1), TextureColour, glm::vec2(0, 1)),
			Vertex(glm::vec3(-1, 1, 1), TextureColour, glm::vec2(1, 1)),

			//right side (first triangle)
			Vertex(glm::vec3(1, -1, -1), TextureColour, glm::vec2(0, 0)),
			Vertex(glm::vec3(1, 1, -1), TextureColour, glm::vec2(0, 1)),
			Vertex(glm::vec3(1, -1, 1), TextureColour, glm::vec2(1, 0)),

			//right side (second triangle)
			Vertex(glm::vec3(1, 1, -1), TextureColour, glm::vec2(0, 1)),
			Vertex(glm::vec3(1, -1, 1), TextureColour, glm::vec2(1, 0)),
			Vertex(glm::vec3(1, 1, 1), TextureColour, glm::vec2(1, 1)),

			//top side (first triangle)
			Vertex(glm::vec3(-1, 1, -1), TextureColour, glm::vec2(0, 0)),
			Vertex(glm::vec3(1, 1, -1), TextureColour, glm::vec2(1, 0)),
			Vertex(glm::vec3(-1, 1, 1), TextureColour, glm::vec2(0, 1)),

			//top side (second triangle)
			Vertex(glm::vec3(1, 1, -1), TextureColour, glm::vec2(1, 0)),
			Vertex(glm::vec3(-1, 1, 1), TextureColour, glm::vec2(0, 1)),
			Vertex(glm::vec3(1, 1, 1), TextureColour, glm::vec2(1, 1)),

			//bottom side (first triangle)
			Vertex(glm::vec3(-1, -1, -1), TextureColour, glm::vec2(0, 0)),
			Vertex(glm::vec3(-1, -1, 1), TextureColour, glm::vec2(0, 1)),
			Vertex(glm::vec3(1, -1, -1), TextureColour, glm::vec2(1, 0)),

			//bottom side (second triangle)
			Vertex(glm::vec3(-1, -1, 1), TextureColour, glm::vec2(0, 1)),
			Vertex(glm::vec3(1, -1, -1), TextureColour, glm::vec2(1, 0)),
			Vertex(glm::vec3(1, -1, 1), TextureColour, glm::vec2(1, 1)),
	};

	return Vertices;
	}

	//code to test if a ray intersects with a triangle (from https://gamedev.stackexchange.com/questions/5585/line-triangle-intersection-last-bits) (modified)
	static bool testRayThruTriangle(Vertex P1, Vertex P2, Vertex P3, Vertex R1, Vertex R2, Vertex& PIP)
	{
		glm::vec3 Normal, IntersectPos;

		// Find Triangle Normal
		Normal = normalize(cross(P2.Position - P1.Position, P3.Position - P1.Position));

		// Find distance from LP1 and LP2 to the plane defined by the triangle
		float Dist1 = dot(R1.Position-P1.Position, Normal);
		float Dist2 = dot(R2.Position-P1.Position, Normal);

		if (Dist1 * Dist2 >= 0.0f)
		{
			return false;
		} // line doesn't cross the triangle.

		if ( Dist1 == Dist2)
		{
			return false;
		} // line and plane are parallel

		// Find point on the line that intersects with the plane
		IntersectPos = R1.Position + (R2.Position-R1.Position) * (-Dist1/(Dist2-Dist1));

		// Find if the interesection point lies inside the triangle by testing it against all edges
		glm::vec3 vTest;

		vTest = cross(Normal, P2.Position-P1.Position);
		if (dot(vTest, IntersectPos-P1.Position) < 0.0f)
		{
			return false;
		}

		vTest = cross(Normal, P3.Position-P2.Position);
		if (dot(vTest, IntersectPos-P2.Position) < 0.0f)
		{
			return false;
		}

		vTest = cross(Normal, P1.Position-P3.Position);
		if (dot(vTest, IntersectPos-P1.Position) < 0.0f)
		{
			return false;
		}

		PIP = Vertex(IntersectPos, Normal, glm::vec2(0, 0));
		return true;
	}
}

