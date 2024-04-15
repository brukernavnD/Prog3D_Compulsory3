#include "Terrain.h"

#include "Macros.h"

Terrain_::Terrain_(glm::vec3 InPosition, glm::vec3 InSize, std::string InName) : WorldObject(InPosition, InSize, InName)
{

}

void Terrain_::Render()
{
	//check if we're not the terrain of the current level
	if (GetWorld()->Terrain != this)
	{
		//if we're not, then we don't render
		return;
	}

	//render the terrain
	WorldObject::Render();
}
