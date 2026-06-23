#pragma once

#include "Core.h"
#include <glm/ext/vector_float3.hpp>

namespace Saffron
{
	namespace Util
	{
		inline glm::vec3 NC_to_SC(int w, int h, glm::vec3 NC)
		{
			float aspect = (float)h / w;
			
			float NCX = NC.x * aspect;
	
			float SCX = NCX * (w/2.0f);
			float SCY = NC.y * (h/2.0f);
	
			return { SCX, SCY, NC.z };
		}

		inline glm::vec3 SC_to_NC(int w, int h, glm::vec3 SC)
		{
			float aspect = (float)h / w;
 
			float ANCX = SC.x / (w/2);
			float NCX = ANCX / aspect;
			float NCY = SC.y / (h/2);

			return { NCX, NCY, SC.z };
		}

		inline float Single_SC_to_NC(int h, float SC)
		{
			return SC / (h/2);
		}
	}
}
