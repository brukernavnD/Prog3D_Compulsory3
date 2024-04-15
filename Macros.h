#pragma once
#include <iostream>
#include <ostream>

#include "GameplayStatics.h"
#include "World.h"

//the current game world
extern World GameWorld;

//the window the game is running in
extern struct GLFWwindow* GameWindow;

//function to get a pointer to the game world
inline World* GetWorld()
{
	return &GameWorld;
}

//opengl error checking code from https://learnopengl.com/In-Practice/Debugging (modified)
inline GLenum glCheckError_(const WorldObject* InWorldObject, const char* function, const int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
			case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
			case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
			case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
			case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
			//0x0500 is the value of GL_INVALID_FRAMEBUFFER_OPERATION
			case 0x0506: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}

		//check if the world object is valid
		if (InWorldObject != nullptr)
		{
			std::cout << InWorldObject->Name << " | " << error << " | " << function << " (" << line << ")" << std::endl;
		}
		else
		{
			std::cout << error << " | " << function << " (" << line << ")" << std::endl;
		}
	}
	return errorCode;
}

//function to get the active shader program
inline unsigned int GetActiveShaderProgram_()
{
	int currentProgram;
	//0x8B8D is the value of GL_CURRENT_PROGRAM
	glGetIntegerv(0x8B8D, &currentProgram);
	return currentProgram;
}

//function to get a valid vertex index for a world object
inline int GetObjectVertexIndex_(const WorldObject* InWorldObject)
{
	int VertexIndex = 0;

	//loop through the world objects
	for (WorldObject* const& Object : GameWorld.WorldObjects)
	{
		//check if the object is the same
		if (Object == InWorldObject)
		{
			//return the vertex index
			return VertexIndex;
		}

		//increment the vertex index
		VertexIndex += Object->Vertices.size();
	}

	//return -1 if the object wasn't found
	return -1;
}

//function to get the next valid id for a world object
inline int IDCounter_()
{
	return GameWorld.CurrentValidID++;
}

//function to get the name of the file the macro is in without the path or extension
inline std::string GetFileName_(const char* file)
{
	std::string FileName = file;
	const size_t LastSlash = FileName.find_last_of("\\/");
	FileName = FileName.substr(LastSlash + 1);
	const size_t LastDot = FileName.find_last_of('.');
	FileName = FileName.substr(0, LastDot);
	return FileName;
}

//function to create a name for a world object using the file name and the number of such objects that have already been created
inline std::string CreateName_(const char* file)
{
	std::string FileName = file;
	const size_t LastSlash = FileName.find_last_of("\\/");
	FileName = FileName.substr(LastSlash + 1);
	const size_t LastDot = FileName.find_last_of('.');
	FileName = FileName.substr(0, LastDot);

	//check how many objects have been created with this file name
	int NumObjects = 0;

	//loop through the names
	for (const std::string& Name : GetWorld()->ObjectNames)
	{
		//check if the name contains the file name
		if (Name.find(FileName) != std::string::npos)
		{
			//increment the number of objects
			NumObjects++;
		}
	}
	
	//check if there are no objects with this file name
	if (NumObjects == 0)
	{
		//use the file name as the name
		GetWorld()->ObjectNames.push_back(FileName);
		return FileName;
	}
	
	std::string Name = FileName + " (" + std::to_string(GetWorld()->ObjectNames.size()) + ")";
	GetWorld()->ObjectNames.push_back(Name);
	return Name;
}

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

//bernstein function (from https://stackoverflow.com/questions/17556985/bezier-curve-using-c-opengl) (modified)
static float Bernstein(const int n, const int i, const float t)
{
	//get the binomial coefficient
	const float BinomialCoefficient = tgammaf(n + 1) / (tgammaf(i + 1) * tgammaf(n - i + 1));

	//return the value
	return BinomialCoefficient * pow(t, i) * pow(1 - t, n - i);
}

//recursive bezier function
static Vertex Bezier(const float Param, const std::vector<Vertex>& InControlPoints)
{
	//check if we're at the end of the curve
	if (InControlPoints.size() == 1)
	{
		//return the point
		return InControlPoints[0];
	}
	//get the new control points
	std::vector<Vertex> NewControlPoints;
	for (size_t i = 0; i < InControlPoints.size() - 1; i++)
	{
		//get the points
		const Vertex P0 = InControlPoints[i];
		const Vertex P1 = InControlPoints[i + 1];

		//get the value
		const float ValueX = (1 - Param) * P0.Position.x + Param * P1.Position.x;
		const float ValueY = (1 - Param) * P0.Position.y + Param * P1.Position.y;
		const float ValueZ = (1 - Param) * P0.Position.z + Param * P1.Position.z;

		//add the new point
		NewControlPoints.emplace_back(glm::vec3(ValueX, ValueY, ValueZ));
	}
	//return the recursive call
	return Bezier(Param, NewControlPoints);
}

//get the barycentric coordinates of a point in a triangle (from https://https://johnshatterly.wordpress.com/2017/08/09/graphics-programming-simple-terrain-collision-using-barycentric-coordinates/) (modified)
static glm::vec3 GetBaryCentricCoord(const glm::vec3& Position, Vertex A, Vertex B, Vertex C)
{
	//get the determinant
	float det = (B.Position.z - C.Position.z) * (A.Position.x - C.Position.x) + (C.Position.x - B.Position.x) * (A.Position.z - C.Position.z);

	//avoid division by zero
	if(det == 0)
	{
		det=0.0001f;
	}

	//get the first barycentric coordinate
	float b1 = (B.Position.z - C.Position.z) * (Position.x - C.Position.x) + (C.Position.x - B.Position.x) * (Position.z - C.Position.z) / det;

	//get the second barycentric coordinate
	float b2 = (C.Position.z - A.Position.z) * (Position.x - C.Position.x) + (A.Position.x - C.Position.x) * (Position.z - C.Position.z) / det;

	//get the last barycentric coordinate by subtracting the first two from 1
	float b3 = 1 - b1 - b2;

	return {b1, b2, b3};
}

//define for the error checking outside of world objects
#define glCheckError() glCheckError_(nullptr, __FUNCTION__, __LINE__)

//define for the error checking inside of world objects
#define glWCheckError() glCheckError_(this, __FUNCTION__, __LINE__)

//create a valid id for a world object and increment the current id, then return the id
#define ID_COUNTER_REF (IDCounter_())

//get reference to the world objects vector
#define OBJECTS_REF (GameWorld.GetWorldObjects())

//get reference to the active shader program
#define SHADER_REF (GetActiveShaderProgram_())

//get reference to projection key
#define PROJECTION_KEY_REF (ProjectionKey.c_str())

//get reference to view key
#define VIEW_KEY_REF (ViewKey.c_str())

//get reference to model key
#define MODEL_KEY_REF (ModelKey.c_str())

//get the vertex index for this world object
#define VERTEX_INDEX_REF (GetObjectVertexIndex_(this))

//create a name for a world object
#define CREATE_NAME (CreateName_(__FILE__))