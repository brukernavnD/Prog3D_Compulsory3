#include "Camera.h"

#include "GameplayStatics.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch): Position(position), Front(glm::vec3(0.0f, 0.0f, -1.0f)), WorldUp(up), Yaw(yaw), Pitch(pitch), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	// mouse movement (from https://learnopengl.com/Getting-started/Camera)
	LastX = Statics::WindowWidth / 2.0f;
	LastY = Statics::WindowHeight / 2.0f;
	IsFirstMouse = true;

	updateCameraVectors();
};

glm::mat4 Camera::GetViewMatrix() const
{
	return lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(const Camera_Movement direction, const float deltaTime)
{
	const float Velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
	{
		Position += Front * Velocity;
	}
	if (direction == BACKWARD)
	{
		Position -= Front * Velocity;
	}
	if (direction == LEFT)
	{
		Position -= Right * Velocity;
	}
	if (direction == RIGHT)
	{
		Position += Right * Velocity;
	}
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, const GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw   += xoffset;
	Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(const float yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = normalize(front);
	// also re-calculate the Right and Up vector
	Right = normalize(cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up    = normalize(cross(Right, Front));
}
