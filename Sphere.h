#pragma once
#include "Objet3D.hpp"

class Sphere :
	public Objet3D
{
private :
	float R;
	glm::vec3 center;

public:
	Sphere(float r, glm::vec3 c, Material *mat);
	~Sphere();
	bool calculIntersection(const Rayon *r, std::vector<Intersection> *I);
	bool calculAABB(const Rayon *r);

};