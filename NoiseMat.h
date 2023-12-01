#pragma once
#include "Material.h"
#include "Intersection.hpp"
#include "Light.h"
#include "math.h"
#include "glm\glm.hpp"
#include "Scene.hpp"
#include "rayon.hpp"
#include "glm\gtc\noise.hpp"
class NoiseMat :
	public Material
{
	float ka;
	float kd;
	float ks;
	float fresnel;

	glm::vec3 cSpec;

public:
	NoiseMat(glm::vec3 col, float ka, float kd, float ks, float t, float m, float r, float f);
	glm::vec3 getColor(Intersection *I, Scene *S, const Rayon *R, int current);
	glm::vec3 shadows(glm::vec3 color, glm::vec3 pt, Scene *s, Intersection *I);

};
