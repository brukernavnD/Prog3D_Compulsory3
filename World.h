#pragma once
#include <vector>

#include "Camera.h"
#include "WorldObject.h"


class PlayerCharacter_;
class PlayerController_;


class World
{
public:

	//constructor(s)
	World();

	//array to store all world objects (houses, npcs, pickups, player character, etc.)
	std::vector<WorldObject*> WorldObjects = std::vector<WorldObject*>();

	//pointer to the current terrain object
	WorldObject* Terrain = nullptr;

	//the player controller
	PlayerController_* PlayerController = nullptr;

	//the player character
	PlayerCharacter_* PlayerCharacter = nullptr;

	//the camera
	Camera PlayerCamera = Camera(glm::vec3(0, 1, 3));

	//the current lowest valid id for any new world object
	int CurrentValidID = 0;

	//list of all currently taken object names
	std::vector<std::string> ObjectNames = {};

	//function to initialize the world
	void InitializeWorld();

	//function to called when beginning play
	void BeginPlay() const;

	//function to tick the world
	void TickWorld(float DeltaTime);

	//function to render the world
	void RenderWorld() const;

	//function to update the world (tick and render)
	void UpdateWorld(float InDeltaTime);

	/** getters and setters */

	//function to get the vertices of the world
	std::vector<Vertex> GetWorldVertices() const;

	//function to get all the world objects
	std::vector<WorldObject*>& GetWorldObjects();

	//function to get the number of vertices in the world
	int GetNumVertices() const;

	//function to get a pointer to the current player camera
	Camera* GetPlayerCamera();

	//function to get the current player controller
	PlayerController_* GetPlayerController();

	//function to get the current player character
	PlayerCharacter_* GetPlayerCharacter();
};
