#include <iostream>
#include <vector>

#include "World.h"
#include "Camera.h"
#include "House.h"
#include "NPC.h"
#include "Pickup.h"
#include "PlayerCharacter.h"
#include "Shaders.h"
#include "GameplayStatics.h"
#include "Skybox.h"
#include "WaveSurface.h"
#include "BezierCurve.h"
#include "PlayerController.h"
#include "Macros.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glm/ext/matrix_clip_space.hpp"


// callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double XPos, double YPos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

////camera (from https://learnopengl.com/Getting-started/Camera)
//Camera camera(glm::vec3(0, 1, 3));
//
////create the player controller
//PlayerController_ OurPlayerController;
//
////array to store all world objects (houses, npcs, pickups, player character, etc.)
//std::vector<WorldObject*> WorldObjects;
//
//int CurrentValidID = 0;
//std::vector<std::string> ObjectNames;
//
////vector to store the vertices (with the first element being an array of unorganized vertices to store objects that don't need to be organized)
//std::vector<std::vector<Vertex>> OrganizedVertices = {};
//
////vector to store the vertices of our models without any organisation (to make it easier to work with opengl)
//std::vector<Vertex> AllVertices = {};

//the game world
World GameWorld;

//function to create a glfw window
GLFWwindow* CreateWindow()
{
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create the window
	GLFWwindow* Window = glfwCreateWindow(WindowWidth, WindowHeight, "Compulsory 3", nullptr, nullptr);

    //set the window to the current context
	glfwMakeContextCurrent(Window);

    //set callback functions
	glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
    glfwSetKeyCallback(Window, key_callback);
	glfwSetCursorPosCallback(Window, mouse_callback);
    glfwSetScrollCallback(Window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //glad: load all OpenGL function pointers
	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));

    //create the shader program
    const unsigned int ShaderProgram = Shaders::CreateShader();

    //use the shader program
    glUseProgram(ShaderProgram);

    return Window;
}

//the window our game will be displayed in
GLFWwindow* GameWindow = CreateWindow();

int main()
{

	// timing (from https://learnopengl.com/Getting-started/Camera)
	// time between current frame and last frame
	double lastFrame = 0;

    //create the player character
	PlayerCharacter_ PlayerCharacter = PlayerCharacter_(glm::vec3(0,0.5,0));

	//set the game worlds player controllers player character
    GameWorld.PlayerCharacter = &PlayerCharacter;

    //create the wave surface
    WaveSurface Surface = WaveSurface(glm::vec3(-12, 0, -12), glm::vec3(25, 1, 25), 500, 60);

	//create the house
	House_ House1 = House_(glm::vec3(0, -2, -10), glm::vec3(2));

    //create the control points for the bezier curve
    std::vector<Vertex> ControlPoints = std::vector<Vertex>{
        Vertex(glm::vec3(-10, 0, -10)),
        Vertex(glm::vec3(-10, 0, 10)),
        Vertex(glm::vec3(10, 0, 10)),
        Vertex(glm::vec3(10, 0, -10))
    };

    //create the bezier curve
    BezierCurve Curve = BezierCurve(ControlPoints, glm::vec3(0, 5, 0), glm::vec3(1));

	//create the npc
	NPC_ Npc = NPC_(glm::vec3(-8, 0.5, 0), glm::vec3(1), &Curve);

	//creating the 10 pickups
	Pickup_ Pickup1 = Pickup_(glm::vec3(1.1, 0, -10));
	Pickup_ Pickup2 = Pickup_(glm::vec3(2.2, 0, -10));
	Pickup_ Pickup3 = Pickup_(glm::vec3(3.3, 0, -10));
	Pickup_ Pickup4 = Pickup_(glm::vec3(4.4, 0, -10));
	Pickup_ Pickup5 = Pickup_(glm::vec3(5.5, 0, -10));
	Pickup_ Pickup6 = Pickup_(glm::vec3(6.6, 0, -10));
	Pickup_ Pickup7 = Pickup_(glm::vec3(7.7, 0, -10));
	Pickup_ Pickup8 = Pickup_(glm::vec3(8.8, 0, -10));
    Pickup_ Pickup9 = Pickup_(glm::vec3(9.9, 0, -10));
    Pickup_ Pickup10 = Pickup_(glm::vec3(10, 0, -10));

	//create the skybox
	Skybox Sky = Skybox();

    //initialize the world
	GetWorld()->InitializeWorld();

    //print the total number of verticies
    std::cout << "Number Of Vertices: " << GetWorld()->GetNumVertices() << std::endl;

    //enable depth testing
    glEnable(GL_DEPTH_TEST);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, GetWorld()->GetNumVertices() * sizeof(Vertex), GetWorld()->GetWorldVertices().data(), GL_STATIC_DRAW);

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Position)));

    // normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Normal)));

    // texture attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, TextureCoordinates)));

    //unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // render loop
    while (!glfwWindowShouldClose(GameWindow))
    {
        // per-frame time logic (from https://learnopengl.com/Getting-started/Camera)
        // --------------------
        const double currentFrame = glfwGetTime();
        const double DeltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ////process keyboard input
        //GameWorld.GetPlayerController()->ProcessKeyboardInput(Window, DeltaTime);

        //draw the background
        glClearColor(0.2f, 0.3f, 0.3f, 1);

        //clear the colour buffer
		glClear(GL_COLOR_BUFFER_BIT);

        //clear the depth buffer
        glClear(GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);

        //(modified)from https://learnopengl.com/Getting-started/Camera
        glm::mat4 projection = glm::perspective(glm::radians(GameWorld.GetPlayerCamera()->Zoom), WindowWidth / WindowHeight, 0.1f, CullingDistance);
        glUniformMatrix4fv(glGetUniformLocation(SHADER_REF, PROJECTION_KEY_REF), 1, false, &projection[0][0]);

        // camera/view transformation
        glm::mat4 View = GameWorld.GetPlayerCamera()->GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(SHADER_REF,VIEW_KEY_REF), 1, false, &View[0][0]);

    	//model matrix
        glm::mat4 model = glm::mat4(1);

        //set the model matrix uniform
        glUniformMatrix4fv(glGetUniformLocation(SHADER_REF, MODEL_KEY_REF), 1, false, &model[0][0]);

        //do the tick and rendering for this frame
        GameWorld.UpdateWorld(static_cast<float>(DeltaTime));

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(GameWindow);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(SHADER_REF);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
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
void mouse_callback(GLFWwindow* window, const double XPos, const double YPos)
{
	GetWorld()->GetPlayerController()->ProcessMouseInput(float(XPos), float(YPos));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GetWorld()->GetPlayerController()->ProcessKeyboardInput(window, key, scancode, action, mods);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called (from https://learnopengl.com/Getting-started/Camera)
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, const double yoffset)
{
    GetWorld()->GetPlayerController()->ProcessMouseScroll(float(yoffset));
}