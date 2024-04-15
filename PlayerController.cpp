#include "PlayerController.h"

#include <map>

#include "Camera.h"
#include "Macros.h"
#include "PlayerCharacter.h"

PlayerInput_::PlayerInput_() = default;

EInputState PlayerInput_::GetKeyState(const int Key)
{
	//get the current key state
	const EInputState CurrentKeyState = glfwGetKey(GameWindow, Key) == GLFW_PRESS ? EInputState::Pressed : EInputState::NotPressed;

	//check if the key is not in the keys to check vector
	if (std::count(KeysToCheck.begin(), KeysToCheck.end(), std::pair<int, EInputState>(Key, EInputState::Pressed)) == 0)
	{
		//check if the key is currently pressed
		if (CurrentKeyState == EInputState::Pressed)
		{
			//add the key to the keys to check vector
			KeysToCheck.emplace_back(Key, EInputState::Pressed);
		}

		//return the current key state
		return CurrentKeyState;
	}

	//get the index of the key in the keys to check vector
	const int KeyIndex = std::distance(KeysToCheck.begin(), std::find(KeysToCheck.begin(), KeysToCheck.end(), std::pair<int, EInputState>(Key, EInputState::Pressed)));

	//check if the key was pressed last frame and isn't currently pressed
	if (KeysToCheck.at(KeyIndex).second == EInputState::Pressed && CurrentKeyState == EInputState::NotPressed)
	{
		//set the key state to released
		KeysToCheck.at(KeyIndex) = std::pair<int, EInputState>(Key, EInputState::Released);

		//return the released key state
		return EInputState::Released;
	}

	//return the current key state
	return CurrentKeyState;
}

bool PlayerInput_::IsPressed(const int Key)
{
	//return the key state
	return GetKeyState(Key) == EInputState::Pressed;
}

bool PlayerInput_::WasReleased(const int Key)
{
	//return the key state
	return GetKeyState(Key) == EInputState::Released;
}

void PlayerInput_::ResetKeysData()
{
	//iterate through the keys to check vector
	for (std::pair<int, EInputState>& Key : KeysToCheck)
	{
		//check if the key was released last frame
		if (Key.second == EInputState::Released)
		{
			//remove the key from the keys to check vector
			KeysToCheck.erase(std::remove(KeysToCheck.begin(), KeysToCheck.end(), Key), KeysToCheck.end());
		}
	}
}

PlayerController_::PlayerController_() = default;

void PlayerController_::HandleMovement(const glm::vec3 MoveDirection, const float DeltaTime) const
{
	//check if we're using the third person camera
	if (PlayerCharacter->UseThirdPerson)
	{
		//move the player
		PlayerCharacter->MoveAlongSurface(MoveDirection, DeltaTime);
	}
	else
	{
		//move the camera
		GetWorld()->GetPlayerCamera()->Position += MoveDirection * DeltaTime * PlayerCharacter->Speed;
	}
}

void PlayerController_::ProcessKeyboardInput(GLFWwindow* Window, int Key, int ScanCode, int Action, int Mods)
{
	//check if the escape key is pressed or held
    if (Key == GLFW_KEY_ESCAPE && (Action == GLFW_PRESS || Action == GLFW_REPEAT)) 
	{
		glfwSetWindowShouldClose(Window, true);
	}

	//check if the 1 key was just released
	if (PlayerInput.WasReleased(GLFW_KEY_1))
	{
		//get the gl_polygon_mode
		GLint PolygonModeArray[2];
		glGetIntegerv(GL_POLYGON_MODE, PolygonModeArray);
		const GLint PolygonMode = PolygonModeArray[0];

		//check if the polygon mode is GL_FILL
		if (PolygonMode == GL_FILL)
		{
			//set the polygon mode to GL_LINE
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			//set the polygon mode to GL_FILL
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	//check if the 2 key was just released
	if (PlayerInput.WasReleased(GLFW_KEY_2))
	{
		//toggle the third person camera
		PlayerCharacter->UseThirdPerson = !PlayerCharacter->UseThirdPerson;
	}
}

void PlayerController_::ProcessMouseInput(const float XPos, const float YPos) const
{
	//process the mouse movement
	GetWorld()->GetPlayerCamera()->ProcessMouseInput(XPos, YPos, PlayerCharacter->UseThirdPerson, PlayerCharacter->CameraDistance, true);
}

void PlayerController_::ProcessMouseScroll(const float yoffset) const
{
	GetWorld()->GetPlayerCamera()->ProcessMouseScroll(yoffset);
}

void PlayerController_::BeginPlay()
{
	//get the player character
	PlayerCharacter = GetWorld()->GetPlayerCharacter();
}

void PlayerController_::Tick(const float DeltaTime)
{
	//check if the w key is pressed
	if (PlayerInput.IsPressed(GLFW_KEY_W))
	{
		HandleMovement(GetWorld()->GetPlayerCamera()->Front, DeltaTime);
	}

	//check if the a key is pressed
	if (PlayerInput.IsPressed(GLFW_KEY_A))
	{
		HandleMovement(-GetWorld()->GetPlayerCamera()->Right, DeltaTime);
	}

	//check if the s key is pressed
	if (PlayerInput.IsPressed(GLFW_KEY_S))
	{
		HandleMovement(-GetWorld()->GetPlayerCamera()->Front, DeltaTime);
	}

	//check if the d key is pressed
	if (PlayerInput.IsPressed(GLFW_KEY_D))
	{
		HandleMovement(GetWorld()->GetPlayerCamera()->Right, DeltaTime);
	}

	//check if were using the third person camera
	if (PlayerCharacter->UseThirdPerson)
	{
		//process 0 mouse movement to update the camera
    	GetWorld()->GetPlayerCamera()->ProcessMouseMovementThirdPerson(0,0,PlayerCharacter->CameraDistance, true);
	}

	//reset the keys data
	PlayerInput.ResetKeysData();
}
