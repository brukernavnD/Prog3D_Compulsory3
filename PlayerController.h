#pragma once
#include "PlayerCharacter.h"
#include "GLFW/glfw3.h"

//enum for the input value for a specific key
enum class EInputState
{
	NotPressed,
	Pressed,
	Released,
};

//Struct to store the player's input
struct PlayerInput_
{
	//vector to store the keys we care about and whether or not they've been updated this frame (to check for key release)
	std::vector<std::pair<int, EInputState>> KeysToCheck;

	//Constructor(s)
	PlayerInput_();

	//function to get get a pointer to the input state of a key based on the key code (adding the key to keys to check if it is not already there)
	EInputState GetKeyState(int Key);

	//function to get whether or not a key is pressed based on the key code
	bool IsPressed(int Key);

	//function to get whether or not a key was just released based on the key code
	bool WasReleased(int Key);

	//function to set all keys to check to false
	void ResetKeysData();
};

class PlayerController_ final
{
public:

	//the player character we are controlling
	PlayerCharacter_* PlayerCharacter = nullptr;

	//the input from the player
	PlayerInput_ PlayerInput;

	//storage for the pending movement input
	std::vector<glm::vec3> PendingMovementInput;

	//constructor(s)
	PlayerController_();

protected:

	//function to handle deligating movement to either the player or the camera based on whether or not the player character is in first person mode
	virtual void HandleMovement(glm::vec3 MoveDirection, float DeltaTime) const;

public:

	//function to process keyboard input
	virtual void ProcessKeyboardInput(GLFWwindow* Window, int Key, int ScanCode, int Action, int Mods);

	//function to process mouse movement for the camera (third person)
	virtual void ProcessMouseInput(float XPos, float YPos) const;

	//function to process mouse scroll wheel input
	virtual void ProcessMouseScroll(float yoffset) const;

	//function called at when beginning play
	virtual void BeginPlay();

	//tick function to update the player controller
	virtual void Tick(float DeltaTime);
};

