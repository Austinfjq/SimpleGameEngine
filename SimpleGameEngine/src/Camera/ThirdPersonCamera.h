#pragma once

#ifndef THIRD_PERSON_CAMERA_H
#define THIRD_PERSON_CAMERA_H

#include "Camera.h"
#include "Model/Model.h"

class ThirdPersonCamera
{
public:
	Model& person;
	Camera camera;
	glm::vec3 center;		// The point this camera is always looking at.
	float distance;			// How far this camera is from the center.
	
	// these variables are equal to those in object 'Camera camera'
	// Stupid design for compatibility. Haven't figured out a better solution though.
	float Zoom;
	glm::vec3 Position;

	ThirdPersonCamera(Model& person, float distance = 6.0f, float yaw = 90.0f, float pitch = PITCH)
		: person(person), distance(distance),
		camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), yaw, pitch)
	{
		Init();
		Zoom = camera.Zoom;	

		if (this->distance < 1.0f) this->distance = 1.0f;
		else if (this->distance > 15.0f) this->distance = 15.0f;
	}
	~ThirdPersonCamera() {}
	void Init()
	{
		float x = (person.getCollider().xmin + person.getCollider().xmax) / 2;
		float y = (person.getCollider().ymin / 6 + person.getCollider().ymax * 5 / 6);
		float z = (person.getCollider().zmin + person.getCollider().zmax) / 2;
		center = glm::vec3(person.getModelMatrix() * glm::vec4(x, y, z, 1.0));
		camera.Position = -distance * glm::normalize(camera.Front) + center;
		Position = camera.Position;
	}

	glm::mat4 GetViewMatrix() { return camera.GetViewMatrix(); }

	void ProcessKeyboard(Camera::Camera_Movement direction, float deltaTime)
	{
		float velocity = camera.MovementSpeed * deltaTime;
		glm::vec3 shift;
		if (direction == Camera::FORWARD)
			shift = glm::normalize(glm::vec3(camera.Front.x, 0.0f, camera.Front.z)) * velocity;
		else if (direction == Camera::BACKWARD)
			shift = -glm::normalize(glm::vec3(camera.Front.x, 0.0f, camera.Front.z)) * velocity;
		else if (direction == Camera::LEFT)
			shift = -glm::normalize(glm::vec3(camera.Right.x, 0.0f, camera.Right.z)) * velocity;
		else if (direction == Camera::RIGHT)
			shift = glm::normalize(glm::vec3(camera.Right.x, 0.0f, camera.Right.z)) * velocity;
		camera.Position += shift;
		center += shift;
		Position = camera.Position;
		person.Translate(shift);
	}

	void ProcessMouseMovement(float xoffset, float yoffset)
	{
		// try to let our role to rotate with camera!
		// person.Rotate(-xoffset * camera.MouseSensitivity, glm::vec3(0, 1.0f, 0));
		float MAXPITCH = 60.0f, MINPITCH = -60.0f;
		if (camera.Pitch + yoffset * camera.MouseSensitivity > MAXPITCH)
			yoffset = (MAXPITCH - camera.Pitch) / camera.MouseSensitivity;
		else if (camera.Pitch + yoffset * camera.MouseSensitivity < MINPITCH)
			yoffset = (MINPITCH - camera.Pitch) / camera.MouseSensitivity;
		camera.ProcessMouseMovement(xoffset, yoffset);
		
		camera.Position = -distance * glm::normalize(camera.Front) + center;
		Position = camera.Position;
	}

	void ProcessMouseScroll(float yoffset)
	{
		distance -= yoffset;
		if (distance < 1.0f)distance = 1.0f;
		else if (distance > 15.0f)distance = 15.0f;
		camera.Position = -distance * glm::normalize(camera.Front) + center;
		Position = camera.Position;
	}

};

#endif
