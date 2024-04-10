#pragma once
#include "WorldObject.h"

class Skybox : public WorldObject
{
public:
	//constructor(s)
	explicit Skybox(std::vector<std::string> InTexturePaths);
};

