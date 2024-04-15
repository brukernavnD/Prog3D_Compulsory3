#pragma once
#include <string>
#include "Vertex.h"

#include "glm/detail/func_geometric.inl"

class WorldObject;

//storage variables for inputs to the shaders
const std::string ProjectionKey = "projection";
const std::string ViewKey = "view";
const std::string ModelKey = "model";

//the default texture to use for objects that don't have a texture
static std::string DefaultTexture = "Textures/DefaultTexture.png";

//the colour value to use to indicate that the object should be rendered with a texture
static glm::vec3 TextureColour = glm::vec3(-1);

//white colour value
static glm::vec3 WhiteColour = glm::vec3(1.0f, 1.0f, 1.0f);

//the culling distance used when rendering objects
static float CullingDistance = 10000000.0f;

//scale variable for the pickup placement in the world
static glm::vec3 PickupsScale = glm::vec3(5.5, 1, 5.5);

//the window's width and height
static float WindowWidth = 800;
static float WindowHeight = 800;

