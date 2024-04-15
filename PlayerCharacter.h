#pragma once

#include "WorldObject.h"

class PlayerCharacter_ : public WorldObject
{
	public:
	//constructor(s)
	explicit PlayerCharacter_(glm::vec3 InPos);
	void CheckForPickups() const;

	//the distance the camera should be from the player character
	float CameraDistance = 5.0f;

	//whether or not we should constrain the pitch of the camera
	bool ConstrainPitch = true;

	//whether or not to use the third person camera
	bool UseThirdPerson = true;

	//the movement speed of the player character
	float Speed = 2.5f;

	//function to queue up movement for the player character using barycentric coordinates to move along the surface of the terrain
	void MoveAlongSurface(glm::vec3 MoveDirection, float DeltaTime);
};