#include "PlayerCharacter.h"

#include <iostream>

#include "Camera.h"
#include "GameplayStatics.h"
#include "Pickup.h"

PlayerCharacter::PlayerCharacter(const glm::vec3 InPos, const glm::vec3 InSize, std::string InTexturePath) : OriginalPosition(InPos)
{
	//set the position
	Position = InPos;

	//set the size
	Size = InSize;

	//set the name
	Name = "Player Character";

	//set the texture paths
	TexturePaths = {InTexturePath,InTexturePath,InTexturePath,InTexturePath,InTexturePath,InTexturePath};
}

void PlayerCharacter::ProcessInput(Camera& InCamera, Camera_Movement CameraDirection, float DeltaTime, std::vector<WorldObject*>& InWorldObjects)
{
	//calculate the velocity
    const float Velocity = InCamera.MovementSpeed * DeltaTime;

	//check if we're moving forward, backward, left, or right
	switch (CameraDirection)
	{
		case FORWARD:
			MoveAlongSurface(InCamera.Front, Velocity, InWorldObjects);
			break;
		case BACKWARD:
			MoveAlongSurface(-InCamera.Front, Velocity, InWorldObjects);
			break;
		case RIGHT:
			MoveAlongSurface(InCamera.Right, Velocity, InWorldObjects);
			break;
		case LEFT:
			MoveAlongSurface(-InCamera.Right, Velocity, InWorldObjects);
			break;
	}

	//update the camera's position
	UpdateCameraPosition(InCamera);
}

void PlayerCharacter::ProcessMouseMovement(Camera& InCamera, float xoffset, float yoffset, GLboolean constrainPitch) const
{
	//process the mouse movement
	InCamera.ProcessMouseMovement(xoffset, yoffset, constrainPitch);

	//update the camera's position
	UpdateCameraPosition(InCamera);
}

void PlayerCharacter::BeginPlay(const std::vector<WorldObject*>& InWorldObjects)
{
	//do nothing
}

void PlayerCharacter::MoveAlongSurface(glm::vec3 MoveDirection, float DesiredDistanceLeft, const std::vector<WorldObject*>& InWorldObjects)
{
	const std::vector<Vertex>& Verticies = InWorldObjects[0]->GetWorldVertices();

	//move with no consideration for the surface
	Position += MoveDirection * DesiredDistanceLeft;

	//iterate through all the vertices float data in sets of 18 to get the three vertices of each triangle
	for (size_t i = 0; i < Verticies.size(); i += 3)
	{
		Vertex A = Verticies[i];
		Vertex B = Verticies[i + 1];
		Vertex C = Verticies[i + 2];

		//vec3 to store the collision point
		Vertex CollisionPoint;

		//do a collision check downwards and assign the new position to be the collision point
		const bool IsBelow = Statics::testRayThruTriangle(A, B, C, Vertex(Position), Vertex(Position + glm::vec3(0,-100000,0)), CollisionPoint);

		if (IsBelow)
		{
			//set the new position to be the collision point
			Position = CollisionPoint.Position + glm::vec3(0, 0.5 * Size.y, 0);
		}
		//check if we're below the triangle
		else if (Statics::testRayThruTriangle(A, B, C, Vertex(Position), Vertex(Position + glm::vec3(0,100000,0)), CollisionPoint))
		{
			//set the new position to be the collision point
			Position = CollisionPoint.Position + glm::vec3(0, 0.5 * Size.y, 0);
		}

		////check if our current postion is within the triangle (using a point in the triangle for our y value)
		//if (IsPointInTriangle(A, B, C, Position))
		//{
		//	//set the in triangle flag to true
		//	InTriangle = true;

		//	//get the barycentric coordinates of the player character's position
		//	const glm::vec3 Barycentric = WorldToBarycentric(Position, A, B, C);

		//	//calculate the desired movement in barycentric coordinates
		//	glm::vec3 DesiredMoveBarycentric = WorldToBarycentric(MoveDirection * DesiredDistanceLeft, A, B, C);

		//	//get the new position in world coordinates
		//	const glm::vec3 NewPosition = BarycentricToWorld(Barycentric + DesiredMoveBarycentric, A, B, C);

		//	//update the position
		//	Position = NewPosition;

		//	return;
		//}
	}

	////check if we're not in a triangle
	//if (!InTriangle)
	//{
	//	//move with no consideration for the surface
	//	Position += MoveDirection * DesiredDistanceLeft;
	//}

	//iterate over all the world objects
	for (WorldObject* Object : InWorldObjects)
	{
		//skip ourselves
		if(Object == this)
		{
			continue;
		}

		//skip non-collidable objects
		if (!Object->bIsCollidable)
		{
			continue;
		}

		//check if we're colliding with the object
		if (Object->CheckCollisionSimple(this))
		{
			//cast the object to a pickup
			auto* PickUp = dynamic_cast<Pickup*>(Object);

			//check if the object is a pickup
			if (PickUp != nullptr)
			{
				//check if the pickup is active
				if (PickUp->IsActive)
				{
					//set the pickup to be inactive
					PickUp->IsActive = false;

					//print a message
					std::cout << "Collision detected! Colliding objects are " << Name << " and "<< Object->Name << std::endl;
				}
			}
		}
	}
}

//glm::vec3 PlayerCharacter::WorldToBarycentric(glm::vec3 Point, glm::vec3 A, glm::vec3 B, glm::vec3 C)
//{
//	//calculate the vectors
//	glm::vec3 V0 = B - A;
//	glm::vec3 V1 = C - A;
//	glm::vec3 V2 = Point - A;
//
//	//calculate the dot products
//	float Dot00 = glm::dot(V0, V0);
//	float Dot01 = glm::dot(V0, V1);
//	float Dot02 = glm::dot(V0, V2);
//	float Dot11 = glm::dot(V1, V1);
//	float Dot12 = glm::dot(V1, V2);
//
//	//calculate the inverse denominator
//	float InverseDenominator = 1 / (Dot00 * Dot11 - Dot01 * Dot01);
//
//	//calculate the barycentric coordinates
//	float U = (Dot11 * Dot02 - Dot01 * Dot12) * InverseDenominator;
//	float V = (Dot00 * Dot12 - Dot01 * Dot02) * InverseDenominator;
//	float W = 1 - U - V;
//
//	//return the barycentric coordinates
//	return {U, V, W};
//}
//
//glm::vec3 PlayerCharacter::BarycentricToWorld(glm::vec3 Barycentric, glm::vec3 A, glm::vec3 B, glm::vec3 C)
//{
//	//return the world space coordinates
//	return Barycentric.x * A + Barycentric.y * B + Barycentric.z * C;
//}
//
//bool PlayerCharacter::IsPointInTriangle(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 P)
//{
//	//get the point P as a barycentric coordinate of the triangle ABC
//	const glm::vec3 Barycentric = WorldToBarycentric(P, A, B, C);
//
//	//check if the x coordinate is greater than 1 or less than 0
//	if (Barycentric.x > 1 || Barycentric.x < 0)
//	{
//		//return false
//		return false;
//	}
//
//	//check if the z coordinate is greater than 1 or less than 0
//	if (Barycentric.z > 1 || Barycentric.z < 0)
//	{
//		//return false
//		return false;
//	}
//
//	//check if the y coordinate is greater than 1
//	if (Barycentric.y > 1 || Barycentric.y < 0)
//	{
//		//return false
//		return false;
//	}
//
//	return true;
//}

void PlayerCharacter::UpdateCameraPosition(Camera& InCamera) const
{
	//get the forward vector of the camera multiplied by the camera distance
	const glm::vec3 Forward = InCamera.Front * CameraDistance;

	//set the camera's position to the player character's position minus the forward vector multiplied by the camera distance
	InCamera.Position = Position - Forward;

	//process 0 mouse movement to update the camera
	InCamera.ProcessMouseMovement(0, 0);
}