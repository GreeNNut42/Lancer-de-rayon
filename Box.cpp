#include "Box.h"
#include "Rayon.hpp"
#include "const.hpp"


Box::Box(float r, glm::vec3 c, glm::vec3 b, Material *mat)
{
	this->R = r;
	this->center = c;
	this->b = b;
	this->mat = mat;
}


Box::~Box()
{
}

bool Box::calculIntersection(const Rayon *r, std::vector<Intersection> *I)
{
	glm::vec3 Ro = r->Orig();
	glm::vec3 Rd = r->Vect();

	float t = 0;
	float dt = h(Ro + Rd*t);
	while (t < MAXDISTANCE && dt > EPSILONRAYMARCH)
	{
		t += glm::max(dt, MINSTEPS);
		dt = h(Ro + Rd*t);
	}
	if (t <= MAXDISTANCE)
	{
		Intersection* inter = new Intersection();
		inter->normal = computeNormal(Ro + Rd*t);
		inter->dist = t;
		inter->Objet = this;
		I->push_back(*inter);
		delete inter;
		return true;
	}
	return false;

}




float Box::h(glm::vec3 X)
{
	float principal = glm::length(glm::max(glm::abs(X - center) - b, glm::vec3(0, 0, 0))) - R;
	float top = glm::length(glm::max(glm::abs(X - (center + glm::vec3(-4.0,3.0,-4.0)) - (2.0f*b)), glm::vec3(0, 0, 0))) - (1.0);
	return min(principal, top, 5);
}


glm::vec3 Box::computeNormal(glm::vec3 p)
{
	glm::vec3 eps = glm::vec3(0.001, 0.0, 0.0);
	glm::vec3 nor = glm::vec3(
		h(p + glm::vec3(eps.x, eps.y, eps.y)) - h(p - glm::vec3(eps.x, eps.y, eps.y)),
		h(p + glm::vec3(eps.y, eps.x, eps.y)) - h(p - glm::vec3(eps.y, eps.x, eps.y)),
		h(p + glm::vec3(eps.y, eps.y, eps.x)) - h(p - glm::vec3(eps.y, eps.y, eps.x)));
	return glm::normalize(nor);
}


float Box::min(float a, float b, float k)
{
	float h = glm::clamp(0.5 + 0.5*(b - a) / k, 0.0, 1.0);
	return glm::mix(b, a, h) - k*h*(1.0 - h);
}