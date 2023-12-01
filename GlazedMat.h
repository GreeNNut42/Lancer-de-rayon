#pragma once
#include "Material.h"
#include "Intersection.hpp"
#include "Light.h"
#include "math.h"
#include "glm\glm.hpp"
#include "Scene.hpp"
#include"rayon.hpp"
class GlazedMat :
	public Material
{
	float ka;
	float kd;

	glm::vec3 cSpec;

public:
	GlazedMat(glm::vec3 col, float ka, float kd, float t, float m, float r);
	glm::vec3 getColor(Intersection *I, Scene *S, const Rayon *R, int current);

	glm::vec3 shadows(glm::vec3 color, glm::vec3 pt, Scene *s);
	
};

//julien.gerhardt@ETU