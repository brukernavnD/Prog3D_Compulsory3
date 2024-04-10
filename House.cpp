#include "House.h"

#include "GameplayStatics.h"
#include "glad/glad.h"

House::House(glm::vec3 InPos, glm::vec3 InSize)
{
	//set the position
	Position = InPos;

	//set the size
	Size = InSize;

	//set the name
	Name = "House";
}

std::vector<Vertex> House::CreateVertices() const
{
	//create the vertices
	return {
		//back wall (first triangle)
		Vertex(-FrontBackWallWidth / 2, 0, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 0.0f),
		Vertex(FrontBackWallWidth / 2, 0, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 0.0f),
		Vertex(-FrontBackWallWidth / 2, WallHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 1.0f),

		//back wall (second triangle)
		Vertex(FrontBackWallWidth / 2, 0, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 0.0f),
		Vertex(-FrontBackWallWidth / 2, WallHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 1.0f),
		Vertex(FrontBackWallWidth / 2, WallHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 1.0f),

		//left wall (first triangle)
		Vertex(-FrontBackWallWidth / 2, 0, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 0.0f),
		Vertex(-FrontBackWallWidth / 2, 0, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 0.0f),
		Vertex(-FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 1.0f),

		//left wall (second triangle)
		Vertex(-FrontBackWallWidth / 2, 0, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 0.0f),
		Vertex(-FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 1.0f),
		Vertex(-FrontBackWallWidth / 2, WallHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 1.0f),

		//right wall (first triangle)
		Vertex(FrontBackWallWidth / 2, 0, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 0.0f),
		Vertex(FrontBackWallWidth / 2, 0, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 0.0f),
		Vertex(FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 1.0f),

		//right wall (second triangle)
		Vertex(FrontBackWallWidth / 2, 0, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 0.0f),
		Vertex(FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 1.0f),
		Vertex(FrontBackWallWidth / 2, WallHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 1.0f),

		//front wall left of door (first triangle)
		Vertex(-FrontBackWallWidth / 2, 0, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 0.0f),
		Vertex(-DoorWidth / 2.0f, 0, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 0.0f),
		Vertex(-FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 1.0f),

		//front wall left of door (second triangle)
		Vertex(-DoorWidth / 2.0f, 0, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 0.0f),
		Vertex(-FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 1.0f),
		Vertex(-DoorWidth / 2.0f, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 1.0f),

		//front wall right of door (first triangle)
		Vertex(DoorWidth / 2.0f, 0, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 0.0f),
		Vertex(FrontBackWallWidth / 2, 0, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 0.0f),
		Vertex(DoorWidth / 2.0f, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 1.0f),

		//front wall right of door (second triangle)
		Vertex(FrontBackWallWidth / 2, 0, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 0.0f),
		Vertex(DoorWidth / 2.0f, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 0.0f, 1.0f),
		Vertex(FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b, 1.0f, 1.0f),

		//left square of roof (first triangle)
	    Vertex(-FrontBackWallWidth / 2, WallHeight, -SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b, 0.0f, 0.0f),
	    Vertex(-FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b, 1.0f, 0.0f),
	    Vertex(-0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b, 0.5f, 1.0f),

		//left square of roof (second triangle)
	    Vertex(-FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b, 1.0f, 0.0f),
	    Vertex(-0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b, 0.5f, 1.0f),
	    Vertex(-0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b, 0.5f, 1.0f),

		//right square of roof (first triangle)
		Vertex(FrontBackWallWidth / 2, WallHeight, -SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b, 0.0f, 0.0f),
		Vertex(FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b, 1.0f, 0.0f),
	    Vertex(-0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b, 0.5f, 1.0f),

		//right square of roof (second triangle)
		Vertex(FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b, 1.0f, 0.0f),
	    Vertex(-0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b, 0.5f, 1.0f),
	    Vertex(-0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b, 0.5f, 1.0f),

		//front triangle of roof (first triangle)
	    Vertex(-FrontBackWallWidth / 2, WallHeight, -SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b, 0.0f, 0.0f),
		Vertex(FrontBackWallWidth / 2, WallHeight, -SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b, 1.0f, 0.0f),
	    Vertex(-0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b, 0.5f, 1.0f),

		//front triangle of roof (second triangle)
		Vertex(FrontBackWallWidth / 2, WallHeight, -SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b, 1.0f, 0.0f),
	    Vertex(-0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b, 0.5f, 1.0f),
	    Vertex(-0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b, 0.5f, 1.0f),

		//back triangle of roof (first triangle)
	    Vertex(-FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b, 0.0f, 0.0f),
		Vertex(FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b, 1.0f, 0.0f),
	    Vertex(-0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b, 0.5f, 1.0f),

		//back triangle of roof (second triangle)
		Vertex(FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b, 1.0f, 0.0f),
	    Vertex(-0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b, 0.5f, 1.0f),
	    Vertex(-0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b, 0.5f, 1.0f),
	};
}

void House::Initialize(std::vector<std::vector<Vertex>>& InVertices, const unsigned& InShaderProgram)
{
	WorldObject::Initialize(InVertices, InShaderProgram);

	//check if our vertices are empty
	if (!MyVertices.empty())
	{
		InVertices.emplace_back(DoorVertices);
	}
}

void House::Render(const unsigned& InShaderProgram, const std::string& ModelKey)
{
	WorldObject::Render(InShaderProgram, ModelKey);

	//draw the door vertices
    if (CheckDoorCollision)
    {
		//set the model matrix
		glUniformMatrix4fv(glGetUniformLocation(InShaderProgram, ModelKey.c_str()), 1, GL_FALSE, &ModelMatrix[0][0]);

		//draw the door vertices
        glDrawArrays(GL_TRIANGLES, VertexIndex + MyVertices.size(), DoorVertices.size());
	}
}
