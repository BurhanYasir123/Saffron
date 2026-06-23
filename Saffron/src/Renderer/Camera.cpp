#include "Camera.h"
#include "Log.h"

namespace Saffron
{
	Camera::Camera()
	{
		FOV = 0.0;
		isConfigDone = false;
		pos = { 0, 0, 0 };
	}

	Camera::~Camera()
	{
		SF_CORE_INFO_("Camera Destroyed!", "Camera");
	}

	void Camera::CalculateVP()
	{
		glm::mat4 projection = glm::perspective(
            glm::radians(FOV),
            (float)win_w / win_h, 
            0.1f, 
            100.0f
        );

        glm::mat4 view = glm::lookAt(
            glm::vec3(pos), 
            glm::vec3({ 0.0f, 0.0f, 0.0f } ), 
            glm::vec3({ 0.0f, 1.0f, 0.0f } )
        );

        VP = projection * view;
	}

	void Camera::OverrideCameraPos(glm::vec3 _pos)
	{
		pos = _pos;
		CalculateVP();
	}

	void Camera::ConfigCamera(CameraConfigInfo info)
	{
		FOV = info.FOV;
		pos = info.pos;
		win_w = info.window_width;
		win_h = info.window_height;

		SF_CORE_INFO("FOV: " << FOV << " pos: " << pos.x << " " << pos.y << " " << pos.z);

		CalculateVP();

		isConfigDone = true;
	}

	glm::mat4 Camera::GetVP()
	{
		return VP;
	}

	bool Camera::IsConfigured()
	{
		return isConfigDone;
	}
}