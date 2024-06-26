#pragma once
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/detail/func_geometric.inl>

#include "glm/ext/matrix_transform.hpp"

//original code from https://learnopengl.com/Getting-started/Camera but has been modified to work with the rest of the project and handle third person camera

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum EWasd_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
constexpr float YAW         = -90.0f;
constexpr float PITCH       =  0.0f;
constexpr float SPEED       =  2.5f;
constexpr float SENSITIVITY =  0.1f;
constexpr float ZOOM        =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MouseSensitivity;
    float Zoom;

    //mouse variables
    double LastX, LastY;
    bool IsFirstMouse;

    // constructor with vectors
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() const;

    //function to process mouse input so it can be used for first or third person camera
    void ProcessMouseInput(float XPos, float YPos, bool UseThirdPerson, float CameraDistance = 0, bool constrainPitch = true);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseInputFirstPerson(float xoffset, float yoffset, bool constrainPitch = true);

    //process mouse movement for third person camera
    void ProcessMouseMovementThirdPerson(float xoffset, float yoffset, float CameraDistance, bool constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};

