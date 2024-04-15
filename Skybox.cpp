#include "Skybox.h"

#include "GameplayStatics.h"
#include "Macros.h"

Skybox::Skybox() : WorldObject(glm::vec3(0.0f), glm::vec3(10000), CREATE_NAME)
{
	//set is collidable to false
	bIsCollidable = false;

	//set the texture paths
	TexturePaths = {
	    "Textures/Skybox/Front.png",
		"Textures/Skybox/Back.png",
		"Textures/Skybox/Left.png",
		"Textures/Skybox/Right.png",
		"Textures/Skybox/Top.png",
		"Textures/Skybox/Bottom.png"
	};
}
