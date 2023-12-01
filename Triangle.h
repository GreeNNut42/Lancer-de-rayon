#pragma once
#include "Objet3D.hpp"


class Triangle :
	public Objet3D
{
public:
	glm::vec3 p0, p1, p2, norm0, norm1, norm2;

public:
	Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 norm0, glm::vec3 norm1, glm::vec3 norm2, Material *mat);
	~Triangle();
	bool calculIntersection(const Rayon *r, std::vector<Intersection> *I);

};