#include "Plan.h"
#include "Rayon.hpp"

Plan::Plan(glm::vec3 pt, glm::vec3 norm, Material *mat)
{
	this->pt = pt;
	this->norm = glm::normalize(norm);
	this->mat = mat;
}


Plan::~Plan()
{
}


bool Plan::calculIntersection(const Rayon *r, std::vector<Intersection> *I)
{ 
	float B = glm::dot(r->Vect(), norm);
	if (B == 0)
	{
		return false;
	}
	float A = glm::dot((pt - (r->Orig())), norm);
	float t = A / B;
	if (t < 0)
	{
		return false;
	}
	Intersection* inter = new Intersection();
	inter->normal = norm;
	inter->dist = t;
	inter->Objet = this;
	I->push_back(*inter);
	delete inter;
	return true;

}