#pragma once
#include "WorldObject.h"

//struct for the npc's path
struct Path
{
	//constructor(s)
	Path(float InMovementSpeed, float(*InMathFunction)(float), float InLength, glm::vec3 InDirection);

	//the npc's movement speed on this path
	float MovementSpeed = 1.f;

	//the function we use to move the npc
	float(*MathFunction)(float) = nullptr;

	//the path length
	float Length = 1.f;

	//the direction of the path
	glm::vec3 Direction = glm::vec3(0.0f, 0.0f, 1.0f);
};

class NPC : public WorldObject
{
public:
	//constructor(s)
	NPC(glm::vec3 InPos, glm::vec3 InSize, std::string InTexturePath);

	//our original position
	glm::vec3 OriginalPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	//vector of npc paths
	std::vector<Path> Paths = {
		Path(5, MathFunction1, 1, glm::vec3(0, 0, 1)),
		Path(5, MathFunction2, 5, glm::vec3(1, 0, 0)),
	};

	//pointer to the current path (default to the first path)
	Path* CurrentPathPtr = &Paths[0];

	//path progress direction
	float PathProgressDirection = 1.0f;

	//the math function we use to move the npc
	static float MathFunction1(float Param);

	//the math function we use to move the npc
	static float MathFunction2(float Param);

	//function to update the npc
	void Tick(float DeltaTime) override;

	//function to move the npc towards the current goal(start or end of the path)
	void MoveTowardsGoal(float DeltaTime);

	//function to switch the current path
	void SwitchPath(Path* NewPathPtr);

	//function to check whether the npc has reached the end of the current path
	void CheckForPathEnd();

	//function to get the end of the current path
	glm::vec3 GetEndOfPath() const;

	//function to get the current movement speed
	float GetCurrentMovementSpeed() const;
};
