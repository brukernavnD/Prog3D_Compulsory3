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

void PlayerCharacter::MoveAlongSurface(glm::vec3 MoveDirection, float DesiredDistanceLeft, const std::vector<WorldObject*>& InWorldObjects)
{
	const std::vector<Vertex>& Verticies = InWorldObjects[0]->GetWorldVertices();

	//bool InTriangle = false;

	//move with no consideration for the surface
	Position += MoveDirection * DesiredDistanceLeft;

	//iterate through all the vertices float data in sets of 18 to get the three vertices of each triangle
	for (size_t i = 0; i < Verticies.size(); i += 3)
	{
		////get the three vertices of the triangle
		//glm::vec3 A = {Verticies[i], Verticies[i + 1], Verticies[i + 2]};
		//glm::vec3 B = {Verticies[i + VertexStride], Verticies[i + VertexStride + 1], Verticies[i + VertexStride + 2]};
		//glm::vec3 C = {Verticies[i + VertexStride * 2], Verticies[i + VertexStride * 2 + 1], Verticies[i + VertexStride * 2 + 2]};
		glm::vec3 A = Verticies[i].Position;
		glm::vec3 B = Verticies[i + 1].Position;
		glm::vec3 C = Verticies[i + 2].Position;

		//vec3 to store the collision point
		glm::vec3 CollisionPoint;

		//do a collision check downwards and assign the new position to be the collision point
		const bool IsBelow = testRayThruTriangle(A, B, C, Position, Position + glm::vec3(0,-100000,0), CollisionPoint);

		if (IsBelow)
		{
			//set the new position to be the collision point
			Position = CollisionPoint + glm::vec3(0, 0.5 * Size.y, 0);
		}
		//check if we're below the triangle
		else if (testRayThruTriangle(A, B, C, Position, Position + glm::vec3(0,100000,0), CollisionPoint))
		{
			//set the new position to be the collision point
			Position = CollisionPoint + glm::vec3(0, 0.5 * Size.y, 0);
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

//PIP = Point In Plane (function taken from https://gamedev.stackexchange.com/questions/5585/line-triangle-intersection-last-bits)
bool PlayerCharacter::testRayThruTriangle( glm::vec3 P1, glm::vec3 P2, glm::vec3 P3, glm::vec3 R1, glm::vec3 R2, glm::vec3& PIP)
{  
    glm::vec3 Normal, IntersectPos;

    // Find Triangle Normal
    Normal = glm::normalize(glm::cross(P2 - P1, P3 - P1));

    // Find distance from LP1 and LP2 to the plane defined by the triangle
    float Dist1 = glm::dot(R1-P1, Normal);
    float Dist2 = glm::dot(R2-P1, Normal);

    if (Dist1 * Dist2 >= 0.0f)
    {
        return false; 
    } // line doesn't cross the triangle.

    if ( Dist1 == Dist2)
    {
        return false; 
    } // line and plane are parallel

    // Find point on the line that intersects with the plane
    IntersectPos = R1 + (R2-R1) * (-Dist1/(Dist2-Dist1));

    // Find if the interesection point lies inside the triangle by testing it against all edges
    glm::vec3 vTest;

    vTest = glm::cross(Normal, P2-P1);
    if (glm::dot(vTest, IntersectPos-P1) < 0.0f)
    { 
        //SFLog(@"no intersect P2-P1"); 
        return false; 
    }

    vTest = glm::cross(Normal, P3-P2);
    if (glm::dot(vTest, IntersectPos-P2) < 0.0f)
    { 
        //SFLog(@"no intersect P3-P2"); 
        return false; 
    }

    vTest = glm::cross(Normal, P1-P3);
    if (glm::dot(vTest, IntersectPos-P1) < 0.0f)
    { 
        //SFLog(@"no intersect P1-P3"); 
        return false; 
    }

    PIP = IntersectPos;

    return true;
}