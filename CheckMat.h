#pragma once
#include "Material.h"
#include "Intersection.hpp"
#include "Light.h"
#include "math.h"
#include "glm\glm.hpp"
#include "Scene.hpp"
#include"rayon.hpp"
class CheckMat :
	public Material
{
	float ka;
	float kd;
	
	int case_size;
	glm::vec3 color2;

public:
	CheckMat(glm::vec3 col, glm::vec3 col2, int Csize,float ka, float kd, float t, float m, float r);
	glm::vec3 getColor(Intersection *I, Scene *S, const Rayon *R, int current);
	glm::vec3 shadows(glm::vec3 color, glm::vec3 pt, glm::vec3 norm, Scene *s);

};

//julien.gerhardt@ETU