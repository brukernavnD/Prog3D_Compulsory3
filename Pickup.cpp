#include "Pickup.h"

#include <ostream>
#include <glm/glm.hpp>

#include "GameplayStatics.h"
#include "Macros.h"
#include "glm/gtx/transform.hpp"

Pickup_::Pickup_(const glm::vec3 InPos) : WorldObject(InPos, glm::vec3(1), CREATE_NAME)
{
	//set the texture paths
	TexturePaths = {"Textures/Pickup.png", "Textures/Pickup.png", "Textures/Pickup.png", "Textures/Pickup.png", "Textures/Pickup.png", "Textures/Pickup.png"};
}

void Pickup_::BeginPlay()
{
	//get the y below
	const float YBelow = GetYBelow();

	//check if the y below is not 0.0000000001f
	if (YBelow != 0.0000000001f)
	{
		//set our y position
		this->Position.y = YBelow + 0.5f * Size.y;
	}
}

void Pickup_::Render()
{
	//check if the pickup isn't active
	if (!IsActive)
	{
		return;
	}

	//call the parent implementation
	WorldObject::Render();

}
