#include "Camera.h"

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>

Camera::Camera(const glm::vec3& position, const glm::vec3& camera_up, const float _fov, const float _yaw, const float _pitch,
	const float sensitivity, const float cam_speed, const glm::vec3& camera_front, const glm::vec3& world_up)
	: camera_position(position)
	, camera_up_vec(camera_up)
	, fov(_fov)
	, yaw(_yaw)
	, pitch(_pitch)
	, mouse_sensitivity(sensitivity)
	, camera_speed(cam_speed)
	, camera_front_vec(camera_front)
	, world_up_vec(world_up)
{
	update_camera_vectors();
}

void Camera::update_camera_vectors() 
{
	glm::vec3 front_vec;
	front_vec.x = std::cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front_vec.y = std::sin(glm::radians(pitch));
	front_vec.z = std::sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	camera_front_vec = glm::normalize(front_vec);
	camera_right_vec = glm::normalize(glm::cross(camera_front_vec, world_up_vec));
	camera_up_vec = glm::normalize(glm::cross(camera_right_vec, camera_front_vec));
}

void Camera::move(const CameraDirections& direction, const float delta_time, const float speed_coeff)
{
	const float velocity = camera_speed * speed_coeff * delta_time;
	switch (direction) {
	case CameraDirections::FORWARD: {
		camera_position += velocity * camera_front_vec;
		break;
	}
	case CameraDirections::BACKWARD: {
		camera_position -= velocity * camera_front_vec;
		break;
	}
	case CameraDirections::RIGHT: {
		camera_position += velocity * camera_right_vec;
		break;
	}
	case CameraDirections::LEFT: {
		camera_position -= velocity * camera_right_vec;
		break;
	}
	default:
		throw std::runtime_error("INVALID DIRECTION");
	}
}

void Camera::rotate(const float x_offset, const float y_offset)
{
	yaw += x_offset * mouse_sensitivity;
	pitch += y_offset * mouse_sensitivity;

	pitch = std::max(-89.0f, pitch);
	pitch = std::min(89.0f, pitch);

	update_camera_vectors();
}

void Camera::scroll(const float y_offset)
{
	fov -= y_offset;
	fov = std::max(1.0f, fov);
	fov = std::min(179.0f, fov);
}

const glm::mat4 Camera::getViewMatrix()	const
{
	return glm::lookAt(camera_position, camera_position + camera_front_vec, camera_up_vec);
}

const float Camera::getFov()	const
{
	return fov;
}

const float Camera::getYaw()	const
{
	return yaw;
}

const float Camera::getPitch()	const
{
	return pitch;
}

const float Camera::getSpeed()	const
{
	return camera_speed;
}

const float Camera::getSensitivity()	const
{
	return mouse_sensitivity;
}

const glm::vec3 Camera::getPos()	const
{
	return camera_position;
}

const glm::vec3 Camera::getFront()	const
{
	return camera_front_vec;
}

const glm::vec3 Camera::getUp()	const
{
	return camera_up_vec;
}

const glm::vec3 Camera::getRight()	const
{
	return camera_right_vec;
}

const glm::vec3 Camera::getWorldUp()	const
{
	return world_up_vec;
}

void Camera::setFov(const float new_fov)
{
	fov = new_fov;
	fov = std::max(1.0f, fov);
	fov = std::min(179.0f, fov);
}

void Camera::setYaw(const float new_yaw)
{
	yaw = new_yaw;
}

void Camera::setPitch(const float new_pitch)
{
	pitch = new_pitch;
	pitch = std::max(-89.0f, pitch);
	pitch = std::min(89.0f, pitch);
}

void Camera::setSpeed(const float new_speed)
{
	camera_speed = new_speed;
}

void Camera::setSensitivity(const float new_sensitivity)
{
	mouse_sensitivity = new_sensitivity;
}

void Camera::setPos(const glm::vec3& new_pos)
{
	camera_position = new_pos;
}

void Camera::setFront(const glm::vec3& new_front)
{
	camera_front_vec = new_front;
}

void Camera::setUp(const glm::vec3& new_up)
{
	camera_up_vec = new_up;
}

void Camera::setRight(const glm::vec3& new_right)
{
	camera_right_vec = new_right;
}

void Camera::setWorldUp(const glm::vec3& new_world_up)
{
	world_up_vec = new_world_up;
}

void Camera::confirm_settings()
{
	update_camera_vectors();
}

void Camera::reset()
{
	*this = Camera();
}
