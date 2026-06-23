#pragma once

#include "Core.h"

namespace Saffron
{

	struct CameraConfigInfo
	{
		CameraConfigInfo() {}
		int window_width;
		int window_height;
		float FOV;
		glm::vec3 pos;
	};

	class Camera
	{
	private:
		glm::mat4 VP;
		glm::vec3 pos;
		float FOV;
		int win_w; int win_h;

		bool isConfigDone;

	public:
		Camera();
		~Camera();

		void ConfigCamera(CameraConfigInfo info);
		void OverrideCameraPos(glm::vec3 _pos);
		void CalculateVP();
		glm::mat4 GetVP();
		bool IsConfigured();
	};
}