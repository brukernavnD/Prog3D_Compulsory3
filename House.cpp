#include "House.h"

#include "GameplayStatics.h"
#include "Macros.h"

House_::House_(const glm::vec3 InPos, const glm::vec3 InSize) : WorldObject(InPos, InSize, CREATE_NAME)
{
	
}

std::vector<Vertex> House_::CreateVertices() const
{
	//create the vertices for the house
	std::vector<Vertex> LocVerticies = {
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

	//add the door vertices
	LocVerticies.insert(LocVerticies.end(), DoorVertices.begin(), DoorVertices.end());

	//return the vertices
	return LocVerticies;
}