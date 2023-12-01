#pragma once
#include "Objet3D.hpp"
class Plan :
	public Objet3D
{
private:
	glm::vec3 pt;
	glm::vec3 norm;

public:
	Plan( glm::vec3 pt, glm::vec3 norm, Material *mat);
	~Plan();
	bool calculIntersection(const Rayon *r, std::vector<Intersection> *I);
	bool calculAABB(const Rayon *r){return true;};
};

