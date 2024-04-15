#include "World.h"

#include "PlayerController.h"

class PlayerController_;
class PlayerCharacter_;

World::World()
{
}

void World::InitializeWorld()
{
	//iterate through all world objects
	for (WorldObject* Object : WorldObjects)
	{
		//initialize the vertices of the object
		Object->Vertices = Object->CreateVertices();

		//initialize the object's textures
		Object->InitializeTextures(Object->TexturePaths);

		//check if the object's name is "WaveSurface"
		if (Object->Name == "WaveSurface")
		{
			//set the wave surface object
			Terrain = Object;
		}
	}

	//iterate through all world objects (again, again)
	for (WorldObject* Object : WorldObjects)
	{
		//call the begin play function for the object
		Object->BeginPlay();
	}

	//create the player controller
	PlayerController = new PlayerController_();

	//call the begin play function for the player controller
	PlayerController->BeginPlay();
}

void World::BeginPlay() const
{
	//iterate through all world objects
	for (WorldObject* Object : WorldObjects)
	{
		//begin play for the object
		Object->BeginPlay();
	}
}

void World::TickWorld(const float DeltaTime)
{
	//tick the player controller first
	PlayerController->Tick(DeltaTime);

	//iterate through all world objects
	for (WorldObject* Object : GetWorldObjects())
	{
		//tick the object
		Object->Tick(DeltaTime);
	}
}

void World::RenderWorld() const
{
	//iterate through all world objects
	for (WorldObject* Object : WorldObjects)
	{
		//skip rendering the terrain if the flag is set
		if (Object == Terrain && !bRenderTerrain)
		{
			continue;
		}

		//render the object
		Object->Render();
	}
}

void World::UpdateWorld(const float InDeltaTime)
{
	//tick the world
	TickWorld(InDeltaTime);

	//render the world
	RenderWorld();
}

std::vector<Vertex> World::GetWorldVertices() const
{
	//return variable
	std::vector<Vertex> AllVertices = std::vector<Vertex>();

	//iterate through all world objects
	for (WorldObject* Object : WorldObjects)
	{
		//add the vertices of the object to the world vertices
		AllVertices.insert(AllVertices.end(), Object->Vertices.begin(), Object->Vertices.end());
	}

	//return the world vertices
	return AllVertices;
}

std::vector<WorldObject*>& World::GetWorldObjects()
{
	//return the world objects
	return WorldObjects;
}

int World::GetNumVertices() const
{
	//return variable
	int NumVertices = 0;

	//iterate through all world objects
	for (const WorldObject* Object : WorldObjects)
	{
		//add the number of vertices of the object to the total number of vertices
		NumVertices += Object->Vertices.size();
	}

	//return the number of vertices
	return NumVertices;
}

Camera* World::GetPlayerCamera()
{
	//return a pointer to the player camera
	return &PlayerCamera;
}

PlayerController_* World::GetPlayerController()
{
	//return the player controller
	return PlayerController;
}

PlayerCharacter_* World::GetPlayerCharacter()
{
	//return the player character
	return PlayerCharacter;
}
