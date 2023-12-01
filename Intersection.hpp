#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP
#include "glm/glm.hpp"
class Objet3D;
class Intersection
{
public:
	Intersection();
	~Intersection();
	float dist; // La distance à l'origine de l'intersection
	glm::vec3 normal;
	Objet3D *Objet;		// l'objet intersecté


	// Opérateur de tri des intersections
	int operator <(const Intersection & i) const {
		return dist < i.dist;
	}
	int operator >(const Intersection & i) const {
		return dist > i.dist;
	}
};



#endif