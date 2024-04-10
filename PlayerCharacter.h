#pragma once
#include "Camera.h"
#include "WorldObject.h"
class PlayerCharacter : public WorldObject
{
	public:
	//constructor(s)
	PlayerCharacter(glm::vec3 InPos, glm::vec3 InSize, std::string InTexturePath);

	//the player character's original position
	glm::vec3 OriginalPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	//the movement speed of the player character
	float MovementSpeed = 2.5f;

	//the distance the camera should be from the player character
	float CameraDistance = 5.0f;

	//function to process input
	void ProcessInput(Camera& InCamera, Camera_Movement CameraDirection, float DeltaTime, std::vector<WorldObject*>& InWorldObjects);

	//function to process mouse movement for the camera (third person)
	void ProcessMouseMovement(Camera& InCamera, float xoffset, float yoffset, GLboolean constrainPitch = true) const;

	//begin play function
	void BeginPlay(const std::vector<WorldObject*>& InWorldObjects) override;

private:

	//function to move the player character using barysentric coordinates
	void MoveAlongSurface(glm::vec3 MoveDirection, float DesiredDistanceLeft, const std::vector<WorldObject*>& InWorldObjects);

	//function to update the player character's camera's position
	void UpdateCameraPosition(Camera& InCamera) const;
};