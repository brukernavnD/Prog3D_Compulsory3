#include "WorldObject.h"

#include <iostream>
#include <string>
#include <glm/glm.hpp>

#include <fstream> 
#include <iostream>

#include "Macros.h"
#include "GameplayStatics.h"
#include "stb_image.h"
#include "glm/gtx/transform.hpp"

WorldObject::~WorldObject()
{
	//do nothing

}

bool WorldObject::operator==(const WorldObject* Other) const
{
	return ID == Other->ID;
}

WorldObject::WorldObject()
{
	//do nothing
}

WorldObject::WorldObject(const glm::vec3 InPosition, const glm::vec3 InSize, std::string InName) : Position(InPosition), Size(InSize), Name(std::move(InName))
{
	//get our id
	ID = ID_COUNTER_REF;

	//add ourselves to the world object vector
	OBJECTS_REF.emplace_back(this);
}

std::vector<Vertex> WorldObject::CreateVertices() const
{
	return GetCubeVertices();
}

float WorldObject::GetYBelow(glm::vec3 InPosition)
{
	//get the vertices of the object
	const std::vector<Vertex> TerrainVerices = GetWorld()->Terrain->GetWorldVertices();

	//iterate through all the vertices float data in sets of 18 to get the three vertices of each triangle
	for (int i = 0; i < TerrainVerices.size(); i += 3)
	{
		//get the vertices of the triangle
		Vertex A = TerrainVerices[i];
		Vertex B = TerrainVerices[i + 1];
		Vertex C = TerrainVerices[i + 2];

		//get the barycentric coordinates of the positions
		glm::vec3 Barycentric = GetBaryCentricCoord(InPosition, A, B, C);

		//check if the barycentric coordinates are valid
		if(Barycentric.x < 0 || Barycentric.y < 0 || Barycentric.z < 0)
		{
			continue;
		}

		//get the height right below us
		float Height = Barycentric.x * TerrainVerices[i].Position.y + Barycentric.y * TerrainVerices[i].Position.y + Barycentric.z * TerrainVerices[i+2].Position.y;

		//return the height
		return Height;
	}

	//return the y value
	return 0.0000000001f;
}

float WorldObject::GetYBelow() const
{
	return GetYBelow(Position);
}

YBelowInfo_ WorldObject::GetYBelowInfo(glm::vec3 InPosition)
{
	//get the vertices of the object
	const std::vector<Vertex> TerrainVerices = GetWorld()->Terrain->GetWorldVertices();

	//iterate through all the vertices float data in sets of 18 to get the three vertices of each triangle
	for (int i = 0; i < TerrainVerices.size(); i += 3)
	{
		//get the vertices of the triangle
		Vertex A = TerrainVerices[i];
		Vertex B = TerrainVerices[i + 1];
		Vertex C = TerrainVerices[i + 2];

		//get the barycentric coordinates of the positions
		glm::vec3 Barycentric = GetBaryCentricCoord(InPosition, A, B, C);

		//check if the barycentric coordinates are valid
		if(Barycentric.x < 0 || Barycentric.y < 0 || Barycentric.z < 0)
		{
			continue;
		}

		//get the height right below us
		float Height = Barycentric.x * TerrainVerices[i].Position.y + Barycentric.y * TerrainVerices[i].Position.y + Barycentric.z * TerrainVerices[i+2].Position.y;

		//get the normal of the triangle
		glm::vec3 Normal = normalize(cross(B.Position - A.Position, C.Position - A.Position));

		//check if the y value of the normal is negative
		if (Normal.y < 0)
		{
			Normal = -Normal;
		}

		//return the height
		return {Height, Normal, std::vector<Vertex>{A, B, C}};
	}

	//return the y value
	return {0.0000000001f, glm::vec3(0.0f)};

}

YBelowInfo_ WorldObject::GetYBelowInfo() const
{
	return GetYBelowInfo(Position);

}

glm::mat4 WorldObject::GetModelMatrix() const
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

	return model;
}

std::vector<Vertex> WorldObject::GetWorldVertices() const
{
	//get the model matrix
	const glm::mat4 model = GetModelMatrix();

	//create a vector to store the world vertices
	std::vector<Vertex> WorldVertices;

	//loop through the vertices and add the world position to the world vertices
	for (int i = 0; i < Vertices.size(); i += 1)
	{
		//get the vertex
		const Vertex MyVertex = Vertices[i];

		//get the world position
		const glm::vec4 WorldPosition = model * glm::vec4(MyVertex.Position, 1.0f);

		//add the world position to the world vertices
		WorldVertices.emplace_back(glm::vec3(WorldPosition), MyVertex.Normal, MyVertex.TextureCoordinates);
	}

	return WorldVertices;
}

Vertex WorldObject::TranslateToWorldSpace(Vertex InVertex) const
{
	//get the model matrix
	const glm::mat4 model = GetModelMatrix();

	//get the world position
	const glm::vec4 WorldPosition = model * glm::vec4(InVertex.Position, 1.0f);

	//return the world vertex
	return {glm::vec3(WorldPosition), InVertex.Normal, InVertex.TextureCoordinates};
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

//code taken from https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/4.2.textures_combined/textures_combined.cpp
void WorldObject::InitializeTextures(std::vector<std::string>& InTexturePaths)
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
		glUniform1i(glGetUniformLocation(SHADER_REF, ("texture" + std::to_string(i)).c_str()), i);

		//add the texture id to the list
		TextureIDs.push_back(Texture);
	}

	glWCheckError();

	//update the shader program
	glUseProgram(SHADER_REF);
}

void WorldObject::BeginPlay()
{
	
}

void WorldObject::Render()
{
	//get the model matrix
	glm::mat4 model = GetModelMatrix();

	//get our VertexIndex
	const int VertexIndex = VERTEX_INDEX_REF;

	//set the model matrix
	glUniformMatrix4fv(glGetUniformLocation(SHADER_REF, MODEL_KEY_REF), 1, GL_FALSE, &model[0][0]);

	//check if we have textures
	if (TextureIDs.empty())
	{
		//draw our vertices
		glDrawArrays(GL_TRIANGLES, VertexIndex, Vertices.size());
	}
	else
	{
		//loop through the verticies in sets of 6 (every face of the model)
		for (int i = 0; i < Vertices.size(); i += 6)
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