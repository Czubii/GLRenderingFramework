#include "cameraOperator.h"
#include <iostream>
CameraOperator::CameraOperator(Camera *_camera) : m_camera(_camera) {}

void CameraOperator::handleInputs(GLFWwindow *window, const float timeDelta)
{
	
	Camera &camera = *m_camera;

	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.transform.pos += timeDelta * speed * camera.orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.transform.pos += timeDelta * speed * -glm::normalize(glm::cross(camera.orientation, camera.up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.transform.pos += timeDelta * speed * -camera.orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.transform.pos += timeDelta * speed * glm::normalize(glm::cross(camera.orientation, camera.up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.transform.pos += timeDelta * speed * camera.up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		camera.transform.pos += timeDelta * speed * -camera.up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = OPERATOR_SPEED_SHIFT_KEY;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = OPERATOR_SPEED;
	}

		// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//TODO: make this use
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (m_firstClick)
		{
			glfwSetCursorPos(window, (camera.width / 2), (camera.height / 2));
			m_firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (camera.height / 2)) / camera.height;
		float rotY = sensitivity * (float)(mouseX - (camera.width / 2)) / camera.width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(camera.orientation, glm::radians(-rotX), glm::normalize(glm::cross(camera.orientation, camera.up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, camera.up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			camera.orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		camera.orientation = glm::rotate(camera.orientation, glm::radians(-rotY), camera.up);

		camera.transform.rot = glm::rotation(glm::vec3(0.0f, 0.0f, 1.0f), camera.orientation);//FIXME: wrong rotation when camera moves horizontally - left <-> Right

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (camera.width / 2), (camera.height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		m_firstClick = true;
	}
}

void CameraOperator::setCamera(Camera *_camera)
{
	m_camera = _camera;
}

Camera &CameraOperator::getCamera()
{
	return *m_camera;
}
