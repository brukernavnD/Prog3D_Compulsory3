#pragma once
#include <string>
#include <vector>
#include "Vertex.h"

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
}

