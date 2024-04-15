#include "PlayerCharacter.h"

#include <iostream>

#include "Camera.h"
#include "GameplayStatics.h"
#include "Macros.h"
#include "Pickup.h"

PlayerCharacter_::PlayerCharacter_(const glm::vec3 InPos) : WorldObject(InPos, glm::vec3(0.5), CREATE_NAME)
{
	//set the texture paths (just repeating the same texture 6 times for the 6 faces of the cube)
	TexturePaths = {
		"Textures/PlayerCharacter/PlayerCharacter.png",
		"Textures/PlayerCharacter/PlayerCharacter.png",
		"Textures/PlayerCharacter/PlayerCharacter.png",
		"Textures/PlayerCharacter/PlayerCharacter.png",
		"Textures/PlayerCharacter/PlayerCharacter.png",
		"Textures/PlayerCharacter/PlayerCharacter.png",
	};
}

void PlayerCharacter_::CheckForPickups() const
{
	//iterate over all the world objects
	for (WorldObject* Object : OBJECTS_REF)
	{
		//check if the object doesn't contain the word "Pickup"
		if (Object->Name.find("Pickup") == std::string::npos)
		{
			//skip the object
			continue;
		
		}

		//check if we're not colliding with the object
		if (!Object->CheckCollisionSimple(this))
		{
			//skip the object
			continue;
		
		}

		//cast the object to a pickup
		auto* PickUp = dynamic_cast<Pickup_*>(Object);

		//check if the pickup is inactive
		if (!PickUp->IsActive)
		{
			//skip the object
			continue;
		}

		//set the pickup to be inactive
		PickUp->IsActive = false;

		//print a message
		std::cout << "Collision detected! Colliding objects are " << Name << " and "<< Object->Name << std::endl;
	}
}

void PlayerCharacter_::MoveAlongSurface(const glm::vec3 MoveDirection, const float DeltaTime)
{
	//do the move
	Position += MoveDirection * Speed * DeltaTime;

	//check for pickups
	CheckForPickups();

	//get the y below info
	const YBelowInfo_ YBelowInfo = GetYBelowInfo();

	//get the y below
	const float YBelow = YBelowInfo.YValue;

	//check if the y below is the default value
	if (YBelow != 0.0000000001f)
	{
		//correct the position
		Position.y = YBelow + 0.5f * Size.y;

	}

	//get the current terrain's vertices
	const std::vector<Vertex>& WorldVertices = GetWorld()->Terrain->GetWorldVertices();

	//iterate over the current terrain's vertices
	for (int Index = 0; Index < WorldVertices.size(); Index += 3)
	{
		//do a ray trace to correct the position in case the barycentric calculation failed due to the player being on the edge of the triangle
		Vertex HitLocation;

		//check if the ray trace hit something
		if (testRayThruTriangle(WorldVertices[Index], WorldVertices[Index + 1], WorldVertices[Index + 2], Vertex(Position + glm::vec3(0, 100, 0)), Vertex(Position + glm::vec3(0, -100, 0)), HitLocation))
		{
			//correct the position
			Position.y = HitLocation.Position.y + 0.5f * Size.y;

			return;
		}
	}
}

