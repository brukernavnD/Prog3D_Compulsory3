#include "NPC.h"
#include <ostream>

#include "GameplayStatics.h"
#include "Macros.h"

NPC_::NPC_(const glm::vec3 InPos, const glm::vec3 InSize, BezierCurve* InPath) : WorldObject(InPos, InSize, CREATE_NAME), Path(InPath)
{
	//set the texture paths
	TexturePaths = {"Textures/NPC.png", "Textures/NPC.png", "Textures/NPC.png", "Textures/NPC.png", "Textures/NPC.png", "Textures/NPC.png"};
}

void NPC_::Tick(const float DeltaTime)
{
	//get the next point on the path
	glm::vec3 NextPoint = Path->GetPointOnCurve(PathIndex).Position;

	//adjust the y position of the next point
	NextPoint.y += 0.5f * Size.y;

	//if the distance between the next point and the current position is less than the speed
	if (distance(NextPoint, Position) < Speed * DeltaTime)
	{
		//increment/decrement the path index
		PathIndex += PathDirection;

		//check if the path index is greater than the number of points on the path
		if (PathIndex >= Path->Vertices.size() - 1)
		{
			//reverse the path direction
			PathDirection = -1;
		}
		//check if the path index is less than 0
		else if (PathIndex <= 0)
		{
			//reverse the path direction
			PathDirection = 1;
		}
	}
	else
	{
		//move towards the next point
		Position += normalize(NextPoint - Position) * Speed * DeltaTime;
	}
}