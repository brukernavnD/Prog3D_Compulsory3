#include "Pickup.h"

#include <ostream>
#include <string>
#include <glm/glm.hpp>

#include "GameplayStatics.h"
#include "glm/gtx/transform.hpp"

static int NumPickups = 0;

Pickup::Pickup(const glm::vec3 InPos, const glm::vec3 InSize, std::string InTexturePath)
{
	//set the position
	Position = InPos;

	//set the size
	Size = InSize;

	//set the name
	Name = std::string("Pickup (worldindex: ").append(std::to_string(int(NumPickups))).append(")");

	//increment the number of pickups
	NumPickups++;

	//set the texture paths
	TexturePaths = {InTexturePath,InTexturePath,InTexturePath,InTexturePath,InTexturePath,InTexturePath};
}

void Pickup::Render(const unsigned int& InShaderProgram, const std::string& ModelKey)
{
	//check if the pickup isn't active
	if (!IsActive)
	{
		return;
	}

	//call the parent implementation
	WorldObject::Render(InShaderProgram, ModelKey);

}
