#include "Skybox.h"

#include "GameplayStatics.h"

Skybox::Skybox(std::vector<std::string> InTexturePaths)
{
	//set the position
	Position = glm::vec3(0);

	//set the size
	Size = glm::vec3(10000);

	//set the name
	Name = "Skybox";

	//set is collidable to false
	bIsCollidable = false;

	//set the texture paths
	TexturePaths = InTexturePaths;
}
