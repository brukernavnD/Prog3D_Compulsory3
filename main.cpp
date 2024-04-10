#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtx/rotate_vector.inl"
#include "glm/gtx/string_cast.hpp"

#include "Camera.h"
#include "House.h"
#include "NPC.h"
#include "Pickup.h"
#include "PlayerCharacter.h"
#include "Shaders.h"
#include "GameplayStatics.h"
#include "Skybox.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Debugging.h"
#include "stb_image.h"
#include "WaveSurface.h"

// callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float InDeltaTime);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

// camera (from https://learnopengl.com/Getting-started/Camera)
Camera camera(glm::vec3(0, 1, 3));


//create the player character (position right behind the door)
PlayerCharacter Player = PlayerCharacter(glm::vec3(0,0.5,0), glm::vec3(0.5), "Textures/PlayerCharacter/PlayerCharacter.png");

//array to store all world objects (houses, npcs, pickups, player character, etc.)
std::vector<WorldObject*> WorldObjects;

//setup function
void GLFWSetup()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

//function to create a glfw window
GLFWwindow* CreateWindow()
{
    //create the window
	GLFWwindow* Window = glfwCreateWindow(Statics::WindowWidth, Statics::WindowHeight, "Compulsory 3", nullptr, nullptr);

    //set the window to the current context
	glfwMakeContextCurrent(Window);

    //set the on resize callback
	glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
    glfwSetCursorPosCallback(Window, mouse_callback);
    glfwSetScrollCallback(Window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return Window;
}

int main()
{
	// timing (from https://learnopengl.com/Getting-started/Camera)
	// time between current frame and last frame
	double lastFrame = 0;

    //setup glfw
    GLFWSetup();

    //glfw window creation
    GLFWwindow* Window = CreateWindow();

    //glad: load all OpenGL function pointers
	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));

    //create the shader program
    const unsigned int ShaderProgram = Shaders::CreateShader();

    //array to store the vertices of our models without any organisation (to make it easier to work with opengl)
	std::vector<Vertex> Vertices = {};

    //create the wave surface
    WaveSurface Surface = WaveSurface(glm::vec3(0), glm::vec3(5, 2, 5));
    glCheckError();

	//create the house
	House House1 = House(glm::vec3(0, -2, -10), glm::vec3(2));
    glCheckError();

	//create the npc
	NPC Npc = NPC(glm::vec3(-8, 0.5, 0), glm::vec3(1),"Textures/NPC.png");
    glCheckError();

	//creating the 9 pickups
	Pickup Pickup1 = Pickup(glm::vec3(0, 0, -10), glm::vec3(1), "Textures/Pickup.png");
	Pickup Pickup2 = Pickup(glm::vec3(0, 0, -10) + glm::vec3(2 * Statics::PickupsScale.x, 0.5 * Statics::PickupsScale.y, 2 * Statics::PickupsScale.z), glm::vec3(1), "Textures/Pickup.png");
	Pickup Pickup3 = Pickup(glm::vec3(0, 0, -10) + glm::vec3(-2 * Statics::PickupsScale.x, 0.5 * Statics::PickupsScale.y, 2 * Statics::PickupsScale.z), glm::vec3(1), "Textures/Pickup.png");
	Pickup Pickup4 = Pickup(glm::vec3(0, 0, -10) + glm::vec3(1 * Statics::PickupsScale.x, 0.5 * Statics::PickupsScale.y, 0 * Statics::PickupsScale.z), glm::vec3(1), "Textures/Pickup.png");
	Pickup Pickup5 = Pickup(glm::vec3(0, 0, -10) + glm::vec3(-1 * Statics::PickupsScale.x, 0.5 * Statics::PickupsScale.y, 0 * Statics::PickupsScale.z), glm::vec3(1), "Textures/Pickup.png");
	Pickup Pickup6 = Pickup(glm::vec3(0, 0, -10) + glm::vec3(1 * Statics::PickupsScale.x, 0.5 * Statics::PickupsScale.y, 1 * Statics::PickupsScale.z), glm::vec3(1), "Textures/Pickup.png");
	Pickup Pickup7 = Pickup(glm::vec3(0, 0, -10) + glm::vec3(-1 * Statics::PickupsScale.x, 0.5 * Statics::PickupsScale.y, -1 * Statics::PickupsScale.z), glm::vec3(1), "Textures/Pickup.png");
	Pickup Pickup8 = Pickup(glm::vec3(0, 0, -10) + glm::vec3(1 * Statics::PickupsScale.x, 0.5 * Statics::PickupsScale.y, -1 * Statics::PickupsScale.z), glm::vec3(1), "Textures/Pickup.png");
	Pickup Pickup9 = Pickup(glm::vec3(0, 0, -10) + glm::vec3(-1 * Statics::PickupsScale.x, 0.5 * Statics::PickupsScale.y, 1 * Statics::PickupsScale.z), glm::vec3(1), "Textures/Pickup.png");
    glCheckError();

	//create the skybox
	Skybox Sky = Skybox({
	    "Textures/Skybox/Front.png",
		"Textures/Skybox/Back.png",
		"Textures/Skybox/Left.png",
		"Textures/Skybox/Right.png",
		"Textures/Skybox/Top.png",
		"Textures/Skybox/Bottom.png"
	});
    glCheckError();

    //set the world objects array
    WorldObjects = {&Surface, &House1, &Npc, &Pickup1, &Pickup2, &Pickup3, &Pickup4, &Pickup5, &Pickup6, &Pickup7, &Pickup8, &Pickup9, &Sky, &Player};

	//vector to store the vertices (with the first element being an array of unorganized vertices to store objects that don't need to be organized)
	std::vector<std::vector<Vertex>> OrganizedVertices = {std::vector<Vertex>()};

	//initialize all the world objects
    for (WorldObject* Object : WorldObjects)
    {
    	Object->Initialize(OrganizedVertices, ShaderProgram);
    }

    //add all of the vertices to the vertices array
    for (std::vector<Vertex> OrganizedVertex : OrganizedVertices)
    {
	    Vertices.insert(Vertices.end(), OrganizedVertex.begin(), OrganizedVertex.end());
    }

    //enable depth testing
    glEnable(GL_DEPTH_TEST);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Position)));

    // normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));

    // texture attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(offsetof(Vertex, TextureCoordinates)));

    //unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //storage variables for the uniform names
    const std::string name1 = "projection";
    const std::string name2 = "view";
    const std::string name3 = "model";

    // render loop
    while (!glfwWindowShouldClose(Window))
    {
        // per-frame time logic (from https://learnopengl.com/Getting-started/Camera)
        // --------------------
        const double currentFrame = glfwGetTime();
        const double DeltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
		processInput(Window, DeltaTime);

        //draw the background
        glClearColor(0.2f, 0.3f, 0.3f, 1);

        //clear the colour buffer
		glClear(GL_COLOR_BUFFER_BIT);

        //clear the depth buffer
        glClear(GL_DEPTH_BUFFER_BIT);

        glUseProgram(ShaderProgram);
        glBindVertexArray(VAO);

        //(modified)from https://learnopengl.com/Getting-started/Camera
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), Statics::WindowWidth / Statics::WindowHeight, 0.1f, Statics::CullingDistance);
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name1.c_str()), 1, false, &projection[0][0]);

        // camera/view transformation
        glm::mat4 View = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram,name2.c_str()), 1, false, &View[0][0]);

    	//model matrix
        glm::mat4 model = glm::mat4(1);

        //set the model matrix uniform
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name3.c_str()), 1, false, &model[0][0]);

        //do the update for this frame
        for (WorldObject* Object : WorldObjects)
	    {
		    Object->Tick(DeltaTime);
	    }

        glCheckError();

        //do the rendering for this frame
	    for (WorldObject* Object : WorldObjects)
	    {
		    Object->Render(ShaderProgram, name3);
		}

        glCheckError();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(ShaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window, const float InDeltaTime)
{
    //check if the escape key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

    //process the input for the player
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Player.ProcessInput(camera, FORWARD, InDeltaTime, WorldObjects);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Player.ProcessInput(camera, BACKWARD, InDeltaTime, WorldObjects);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Player.ProcessInput(camera, LEFT, InDeltaTime, WorldObjects);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Player.ProcessInput(camera, RIGHT, InDeltaTime, WorldObjects);
	}

    //process the mouse movement to update the camera vectors
	camera.ProcessMouseMovement(0, 0);
}

//called whenever the window is resized
void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    std::cout << " windows resized with " << width << " Height " << height << std::endl;
}

// glfw: whenever the mouse moves, this callback is called (from https://learnopengl.com/Getting-started/Camera)
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, const double xposIn, const double yposIn)
{
	const double Xpos = xposIn;
    const double Ypos = yposIn;

    if (camera.IsFirstMouse)
    {
        camera.LastX = Xpos;
        camera.LastY = Ypos;
        camera.IsFirstMouse = false;
    }

    const double Xoffset = Xpos - camera.LastX;
    const double Yoffset = camera.LastY - Ypos; // reversed since y-coordinates go from bottom to top

    camera.LastX = Xpos;
    camera.LastY = Ypos;

    Player.ProcessMouseMovement(camera, Xoffset, Yoffset, false);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called (from https://learnopengl.com/Getting-started/Camera)
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, const double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}