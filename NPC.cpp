#include "NPC.h"
#include <ostream>

#include "GameplayStatics.h"

Path::Path(const float InMovementSpeed, float(* InMathFunction)(float), const float InLength, const glm::vec3 InDirection): MovementSpeed(InMovementSpeed), MathFunction(InMathFunction), Length(InLength), Direction(InDirection)
{
		
}

NPC::NPC(const glm::vec3 InPos, const glm::vec3 InSize, std::string InTexturePath) : OriginalPosition(InPos)
{
	//set the position
	Position = InPos;

	//set the size
	Size = InSize;

	//set the name
	Name = "NPC";

	//set the texture paths
	TexturePaths = {InTexturePath,InTexturePath,InTexturePath,InTexturePath,InTexturePath,InTexturePath};
}

float NPC::MathFunction1(const float Param)
{
	//get the value
	const float Value = 24.5210653286f * Param * Param -2.0635480065f * Param - 0.4835875541f;
	return Value;
}

float NPC::MathFunction2(const float Param)
{
    //get the value
	const float Value = 0.5f * Param * Param - 0.5f * Param;
	return Value;
}

void NPC::BeginPlay(const std::vector<WorldObject*>& InWorldObjects)
{
	//call the parent implementation
	WorldObject::BeginPlay(InWorldObjects);

	//update our original position
	OriginalPosition = Position;
}

void NPC::Tick(const float DeltaTime)
{
	//check if we've reached the end of the path
    CheckForPathEnd();

	//move the npc towards the goal
	MoveTowardsGoal(DeltaTime);
}

void NPC::MoveTowardsGoal(const float DeltaTime)
{
	//get the direction to the goal
	const glm::vec3 Direction = GetEndOfPath() - Position;

	//normalize the direction
	const glm::vec3 NormalizedDirection = normalize(Direction);

	//move the npc towards the goal
	Position += NormalizedDirection * DeltaTime * GetCurrentMovementSpeed();
}

void NPC::SwitchPath(Path* NewPathPtr)
{
    //check if the path is the same as the one we are switching to
    if (CurrentPathPtr == NewPathPtr)
    {
	    //if it is, return
		return;
	}

	//switch the path
	CurrentPathPtr = NewPathPtr;

    //reset the path progress direction
    PathProgressDirection = 1;
}

void NPC::CheckForPathEnd()
{
    //the minimum distance away from the end of the path before we switch paths
    constexpr float MinDistance = 0.1f;

	//get the distance between the npc and the end of the path
	const float Distance = distance(Position, GetEndOfPath());

	//check if either distance is less than the minimum distance
	if (Distance < MinDistance)
	{
		//reverse the direction of the path progress
		PathProgressDirection *= -1;
	}
}

glm::vec3 NPC::GetEndOfPath() const
{
	//check if the path progress direction is positive
	if (PathProgressDirection > 0)
	{
		//return the end of the current path
		return {OriginalPosition.x + CurrentPathPtr->Direction.x * CurrentPathPtr->MathFunction(CurrentPathPtr->Length), OriginalPosition.y + CurrentPathPtr->Direction.y * CurrentPathPtr->MathFunction(CurrentPathPtr->Length), OriginalPosition.z + CurrentPathPtr->Direction.z * CurrentPathPtr->MathFunction(CurrentPathPtr->Length)};
	}
	if (PathProgressDirection < 0)
	{
		//return the beginning of the current path
		return {OriginalPosition.x + CurrentPathPtr->Direction.x * CurrentPathPtr->MathFunction(0), OriginalPosition.y + CurrentPathPtr->Direction.y * CurrentPathPtr->MathFunction(0), OriginalPosition.z + CurrentPathPtr->Direction.z * CurrentPathPtr->MathFunction(0)};
	}

	//return zero vector
	return {0.0f, 0.0f, 0.0f};
}

float NPC::GetCurrentMovementSpeed() const
{
	return CurrentPathPtr->MovementSpeed;
}
