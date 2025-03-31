#pragma once

#include <glm/gtc/matrix_transform.hpp>

// DEFAULT SETTINGS
constexpr float YAW_DEFAULT			= -90.0f;
constexpr float PITCH_DEFAULT		= 0.0f;
constexpr float SENSITIVITY_DEFAULT = 0.05f;
constexpr float FOV_DEFAULT			= 45.0f;
constexpr float CAM_SPEED_DEFAULT	= 5.0f;

const glm::vec3 CAM_POS_DEFAULT		= glm::vec3(0.0f, 0.0f, 3.0f);
const glm::vec3 CAM_FRONT_DEFAULT	= glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 CAM_UP_DEFAULT		= glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 WORLD_UP_DEFAULT	= glm::vec3(0.0f, 1.0f, 0.0f);

// Camera move directions
enum class CameraDirections {
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT
};

// 
class Camera
{
private:

	// mouse horizontal offset
	float yaw;
	// mouse vertical offset
	float pitch;
	// speed of camera
	float camera_speed;
	// sensitive of mouse
	float mouse_sensitivity;
	// Field of View (degrees)
	float fov;

	// camera position vector
	glm::vec3 camera_position;
	// front camera direction
	glm::vec3 camera_front_vec;
	// up camera direction
	glm::vec3 camera_up_vec;
	// right camera direction
	glm::vec3 camera_right_vec;
	// world Y_plus axis
	glm::vec3 world_up_vec;

	// After changes we need to update camera's coordinate system
	void update_camera_vectors();

public:

	// Main constructor with all parameters
	Camera(const glm::vec3& position = CAM_POS_DEFAULT, const glm::vec3& camera_up = CAM_UP_DEFAULT, const float _fov = FOV_DEFAULT,
		const float _yaw = YAW_DEFAULT, const float _pitch = PITCH_DEFAULT, const float sensitivity = SENSITIVITY_DEFAULT, const float cam_speed = CAM_SPEED_DEFAULT, const glm::vec3& camera_front = CAM_FRONT_DEFAULT,
		const glm::vec3& world_up = WORLD_UP_DEFAULT);

	// move camera_function
	void move(const CameraDirections& direction, const float delta_time, const float speed_coeff = 1.0f);

	// rotate camera horizontal and vertical
	void rotate(const float x_offset, const float y_offset);
	
	// zoom camera
	void scroll(const float y_offset);

	// calculate view matrix and return it
	const glm::mat4 getViewMatrix()	const;

	// getters
	const float getFov()	const;
	const float getYaw()	const;
	const float getPitch()	const;
	const float getSpeed()	const;
	const float getSensitivity()	const;
	const glm::vec3 getPos()	const;
	const glm::vec3 getFront()	const;
	const glm::vec3 getUp()		const;
	const glm::vec3 getRight()	const;
	const glm::vec3 getWorldUp()	const;

	// setters
	void setFov(const float new_fov);
	void setYaw(const float new_yaw);
	void setPitch(const float new_pitch);
	void setSpeed(const float new_speed);
	void setSensitivity(const float new_sensitivity);
	void setPos(const glm::vec3& new_pos);
	void setFront(const glm::vec3& new_front);
	void setUp(const glm::vec3& new_up);
	void setRight(const glm::vec3& new_right);
	void setWorldUp(const glm::vec3& new_world_up);

	// update all vectors
	void confirm_settings();
	// reset to default
	void reset();

	// default destructor
	~Camera() = default;

};
