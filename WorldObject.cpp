#include "WorldObject.h"

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <fstream> 
#include <iostream>

#include "Debugging.h"
#include "GameplayStatics.h"
#include "stb_image.h"
#include "glm/gtx/transform.hpp"

//function to convert a world position to a barycentric coordinate
glm::vec3 WorldToBarycentric(glm::vec3 InWorldPos, glm::vec3 PointA, glm::vec3 PointB, glm::vec3 PointC)
{
	//PointA.z = 0;
	//PointB.z = 0;
	//PointC.z = 0;
	//InWorldPos.z = 0;

	glm::vec3 p12 = PointB-PointA;
	glm::vec3 p13 = PointC-PointA;
	glm::vec3 n = cross(p12,p13);
	float areal_123 = length(n); // dobbelt areal
	glm::vec3 baryc; // til retur. Husk
	// u
	glm::vec3 p = PointB - InWorldPos;
	glm::vec3 q = PointC - InWorldPos;
	n = glm::cross(p,q);
	baryc.x = n.z/areal_123;
	// v
	p = PointC - InWorldPos;
	q = PointA - InWorldPos;
	n = glm::cross(p,q);
	baryc.y = n.z/areal_123;
	// w
	p = PointA - InWorldPos;
	q = PointB - InWorldPos;
	n = glm::cross(p,q);
	baryc.z = n.z/areal_123;
	return baryc;
}

//function to convert a barycentric coordinate to a world position
glm::vec3 BarycentricToWorld(const glm::vec3 InBarycentric, const glm::vec3 PointA, const glm::vec3 PointB, const glm::vec3 PointC)
{
	return PointA * InBarycentric.x + PointB * InBarycentric.y + PointC * InBarycentric.z;
}

//function to check if a point is within a triangle
bool IsPointInTriangle(const glm::vec3 PointA, const glm::vec3 PointB, const glm::vec3 PointC, const glm::vec3 PointP)
{
	//get the barycentric coordinates
	const glm::vec3 Barycentric = WorldToBarycentric(PointP, PointA, PointB, PointC);

	//check if the point is within the triangle
	return Barycentric.x >= 0 && Barycentric.y >= 0 && Barycentric.z >= 0 && Barycentric.x <= 1 && Barycentric.y <= 1 && Barycentric.z <= 1;
}

WorldObject::~WorldObject()
{
	//do nothing

}

bool WorldObject::operator==(const WorldObject* Other) const
{
	return this->Position == Other->Position && this->RGB == Other->RGB && this->Size == Other->Size && this->Name == Other->Name;
}

WorldObject::WorldObject()
{
	//do nothing
}

void WorldObject::SetVertexIndex(const std::vector<std::vector<Vertex>>& InVertices)
{
	//get the start index for our vertices
	int LocVertexIndex = 0;

	//loop through the vertices and add the size of each to the vertex index
	for (const auto & InVertice : InVertices)
	{
		//check if this invertice is the same as ours
		if (InVertice == MyVertices)
		{
			break;
		}

		LocVertexIndex += InVertice.size();
	}

	VertexIndex = LocVertexIndex;
}

int WorldObject::GetVertexIndex() const
{
	return VertexIndex;	
}

std::vector<Vertex> WorldObject::CreateVertices() const
{
	return Statics::GetCubeVertices();
}

std::vector<Vertex> WorldObject::GetWorldVertices() const
{
	//create an identity matrix
    glm::mat4 model = glm::mat4(1.0f);

	//do the translation
	model = translate(model, Position);

	////do the rotation
	//model = rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	//model = rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	//model = rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	//do the scaling
	model = scale(model, Size);

	//create a vector to store the world vertices
	std::vector<Vertex> WorldVertices;

	//loop through the vertices and add the world position to the world vertices
	for (int i = 0; i < MyVertices.size(); i += 1)
	{
		//get the vertex
		const Vertex MyVertex = MyVertices[i];

		//get the world position
		const glm::vec4 WorldPosition = model * glm::vec4(MyVertex.Position, 1.0f);

		//add the world position to the world vertices
		WorldVertices.emplace_back(glm::vec3(WorldPosition), MyVertex.Normal, MyVertex.TextureCoordinates);
	}

	return WorldVertices;
}

bool WorldObject::CheckCollisionSimple(const WorldObject* InOtherObject) const
{
	//check if the other object is colliding with us
	if (Position.x + Size.x * 2 > InOtherObject->Position.x &&
		Position.x < InOtherObject->Position.x + InOtherObject->Size.x * 2 &&
		Position.y + Size.y * 2 > InOtherObject->Position.y &&
		Position.y < InOtherObject->Position.y + InOtherObject->Size.y * 2 &&
		Position.z + Size.z * 2 > InOtherObject->Position.z &&
		Position.z < InOtherObject->Position.z + InOtherObject->Size.z * 2)
	{
		return true;
	}

	return false;
}

bool WorldObject::CheckCollisionDetailed(const WorldObject* InOtherObject) const
{
	//get the world vertices of both objects
	const std::vector<Vertex> MyWorldVertices = this->GetWorldVertices();
	const std::vector<Vertex> OtherWorldVertices = InOtherObject->GetWorldVertices();

	//loop through our vertices as triangles
	for (int i = 0; i < MyWorldVertices.size(); i += 3)
	{
		////get the vertices of the triangle
		//const glm::vec3 MyPointA = glm::vec3(MyWorldVertices[i], MyWorldVertices[i + 1], MyWorldVertices[i + 2]);
		//const glm::vec3 MyPointB = glm::vec3(MyWorldVertices[i + VertexStride], MyWorldVertices[i + VertexStride + 1], MyWorldVertices[i + VertexStride + 2]);
		//const glm::vec3 MyPointC = glm::vec3(MyWorldVertices[i + VertexStride * 2], MyWorldVertices[i + VertexStride * 2 + 1], MyWorldVertices[i + VertexStride * 2 + 2]);

		const glm::vec3 MyPointA = MyWorldVertices[i].Position;
		const glm::vec3 MyPointB = MyWorldVertices[i + 1].Position;
		const glm::vec3 MyPointC = MyWorldVertices[i + 2].Position;

		//loop through the other objects vertices as points
		for (int j = 0; j < OtherWorldVertices.size(); j += 1)
		{
			//get the point
			const glm::vec3 OtherPointA = OtherWorldVertices[j].Position;

			//check if the point is within the triangle
			if (IsPointInTriangle(MyPointA, MyPointB, MyPointC, OtherPointA))
			{
				//get the position of j in the vertices array
				int Remainder = j % 3;

				////get the other 2 points of the triangle j is in (using the remainder to account for j being either the first, second or third point of the triangle)
				//const glm::vec3 OtherPointB = glm::vec3(OtherWorldVertices[j + VertexStride - Remainder], OtherWorldVertices[j + VertexStride + 1 - Remainder], OtherWorldVertices[j + VertexStride + 2 - Remainder]);
				//const glm::vec3 OtherPointC = glm::vec3(OtherWorldVertices[j + VertexStride * 2 - Remainder], OtherWorldVertices[j + VertexStride * 2 + 1 - Remainder], OtherWorldVertices[j + VertexStride * 2 + 2 - Remainder]);

				const glm::vec3 OtherPointB = OtherWorldVertices[j + 1 - Remainder].Position;
				const glm::vec3 OtherPointC = OtherWorldVertices[j + 2 - Remainder].Position;

				//check if the other 2 points are within the triangle
				if (
					IsPointInTriangle(OtherPointA, OtherPointB, OtherPointC, MyPointA) &&
					IsPointInTriangle(OtherPointA, OtherPointB, OtherPointC, MyPointB) ||
					IsPointInTriangle(OtherPointA, OtherPointB, OtherPointC, MyPointC))
				{
					//get the names of both objects
					const std::string MyName = Name;
					const std::string OtherName = InOtherObject->Name;

					return true;
				}

				
			}
		}
	}

	//return false if no collision was found
	return false;
}

void WorldObject::Initialize(std::vector<std::vector<Vertex>>& InVertices, const unsigned int& InShaderProgram)
{
	//create the vertices
	MyVertices = CreateVertices();

	//check if we have any vertices
	if (MyVertices.empty())
	{
		return;
	}

	//set the vertex index
	SetVertexIndex(InVertices);

	//add my vertices to the vertices array
	InVertices.push_back(MyVertices);

	//initialize the textures
	InitializeTextures(TexturePaths, InShaderProgram);
}

//code taken from https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/4.2.textures_combined/textures_combined.cpp
void WorldObject::InitializeTextures(std::vector<std::string>& InTexturePaths, const unsigned int& InShaderProgram)
{
	for (int i = 0; i < InTexturePaths.size(); i++)
	{
		//storage for the texture
		unsigned int Texture;

		glGenTextures(1, &Texture);
		glBindTexture(GL_TEXTURE_2D, Texture); 
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		unsigned char *data = stbi_load(InTexturePaths[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

		// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
		glUniform1i(glGetUniformLocation(InShaderProgram, ("texture" + std::to_string(i)).c_str()), i);

		//add the texture id to the list
		this->TextureIDs.push_back(Texture);
	}

	//update the shader program
	glUseProgram(InShaderProgram);

	//error check to prevent future errors from this function call potentially pointing to the next error check
	glWCheckError();
}

void WorldObject::BeginPlay(const std::vector<WorldObject*>& InWorldObjects)
{
	//storage for line trace hit
	Vertex Hit;

	//loop through all the world objects
	for (const auto& InWorldObject : InWorldObjects)
	{
		//check if it is the wave surface
		if (InWorldObject->Name == "WaveSurface")
		{
			//get the vertices of the object
			const std::vector<Vertex> WorldVertices = InWorldObject->GetWorldVertices();

			//loop through the vertices in sets of 3 (every triangle of the model)
			for (int i = 0; i < WorldVertices.size(); i += 3)
			{
				//get the vertices of the triangle
				const Vertex A = WorldVertices[i];
				const Vertex B = WorldVertices[i + 1];
				const Vertex C = WorldVertices[i + 2];

				//do a collision check downwards and assign the new position to be the collision point
				const bool IsBelow = Statics::testRayThruTriangle(A, B, C, Vertex(Position), Vertex(Position + glm::vec3(0, -100000, 0)), Hit);

				if (IsBelow)
				{
					//set the new position to be the collision point
					this->Position = Hit.Position + glm::vec3(0, 0.5 * Size.y, 0);
				}
			}
		}
	}
}

void WorldObject::Render(const unsigned int& InShaderProgram, const std::string& ModelKey)
{
	//create an identity matrix
    glm::mat4 model = glm::mat4(1.0f);

	//do the translation
	model = translate(model, this->Position);

	//do the rotation
	model = rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	//do the scaling
	model = scale(model, Size);

	//set the ModelMatrix property
	ModelMatrix = model;

	//get the vertex index
	const int VertexIndex = GetVertexIndex();

	//set the model matrix
	glUniformMatrix4fv(glGetUniformLocation(InShaderProgram, ModelKey.c_str()), 1, GL_FALSE, &model[0][0]);

	//check if we have textures
	if (TextureIDs.empty())
	{
		//prevent opengl from using the last texture
		glBindTexture(GL_TEXTURE_2D, 0);

		//draw our vertices
		glDrawArrays(GL_TRIANGLES, VertexIndex, MyVertices.size());
	}
	else
	{
		//loop through the verticies in sets of 6 (every face of the model)
		for (int i = 0; i < MyVertices.size(); i += 6)
		{
			//get the texture id
			const unsigned int TextureID = TextureIDs[i / 6];

			//bind the texture
			glBindTexture(GL_TEXTURE_2D, TextureID);

			//draw our vertices
			glDrawArrays(GL_TRIANGLES, VertexIndex + i, 6);
		}
	}

	
}

void WorldObject::Tick(float DeltaTime)
{
	//do nothing
}