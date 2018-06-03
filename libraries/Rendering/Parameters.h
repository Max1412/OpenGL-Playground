#pragma once

#include <vector>
#include <glm/glm.hpp>

struct ParameterFog
{
	glm::vec3 albedo;
	float anisotropy;
	float scattering;
	float absorption;
	float density;
};

struct PrarameterLight
{
	glm::vec3 color;        // all
	glm::vec3 position;     // spot, point
	glm::vec3 direction;    // dir, spot
	int pcfKernelSize = 1;
	float constant;         // spot, point
	float linear;           // spot, point
	float quadratic;        // spot, point
	float cutOff;           // spot
	float outerCutOff;      // spot
};

struct ParamterNoise
{
	float densityFactor;
	float densityHeight;
	float scale;
	float speed;
};

struct Parameters
{
	std::vector<PrarameterLight> lights;
	ParamterNoise noise;
	ParameterFog fog;
	float gamma;
	float exposure;
	float maxRange; //range of voxel grid

};

/* E X A M P L E
Parameters Scene{
  LIGHTS
	{
		{color, position, direction, pcfKernelSize, constant, linear, quadratic, cutOff, outerCutoff},
		...
	},
  NOISE
	{densityFactor, densityHeigt, scale, speed},
  FOG
	{albedo, anisotropy, scattering, absorption, density},
  HDR AND VOXEL SETTINGS
	gamma, exposure, maxRange
}*/

Parameters sponza{
	{
		//global directional light
		{glm::vec3(100.0f), glm::vec3(0.0f, 2000.0f, 0.0f), glm::vec3(0.0f, -1.0f, -0.2f)},
		//spotlight 1
		{glm::vec3(0.0f, 100.0f, 100.0f), glm::vec3(80.0f, 300.0f, 100.0f), glm::normalize(glm::vec3(0.0f) - glm::vec3(80.0f, 300.0f, 100.0f)), 1,
			0.05f, 0.002f, 0.0f, glm::cos(glm::radians(30.0f)), glm::cos(glm::radians(35.0f))}
	},
	//noise
	{0.015f, 0.85f, 0.003f, 0.15f},
	//fog
	{glm::vec3(1.0f), 0.2f, 0.6f, 0.25f, 0.125f },
	//hdr
	2.2f, 0.1f,
	3000.0f
};