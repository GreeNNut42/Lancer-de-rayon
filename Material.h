#ifndef MATERIAL_H_
#define MATERIAL_H_
#include"glm\glm.hpp"
#include"Intersection.hpp"
#include<time.h>
class Rayon;
class Scene;
class Material
{
protected:

	glm::vec3 color;
	float transparent; // Indice of transparence (between 0(opaque) & 1(full transparent)
	float refraction; // Indice of refraction like the physical meaning
	float reflective; // Indice of reflection (between 0(non reflective) & 1(full mirror)


public:
	Material(){};

	virtual	glm::vec3 getColor(Intersection *I, Scene *S, const Rayon *R, int current){ return glm::vec3(0.0, 0.0, 0.0); };

	virtual glm::vec3 shadows(glm::vec3 color, glm::vec3 pt, Scene *s){ return glm::vec3(0.0, 0.0, 0.0); };
};

#endif