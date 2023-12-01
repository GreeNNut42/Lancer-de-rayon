#pragma once
#include "Objet3D.hpp"

class Box:
	public Objet3D
{
private :
	float R;
	glm::vec3 center;
	glm::vec3 b;


public:
	Box(float r, glm::vec3 c, glm::vec3 b ,Material *mat);
	~Box();
	bool calculIntersection(const Rayon *r, std::vector<Intersection> *I);

	float h(glm::vec3 X);
	glm::vec3 computeNormal(glm::vec3 p);
	float min(float a, float b, float k);

};