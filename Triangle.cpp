#include "Triangle.h"
#include "rayon.hpp"

glm::vec3 interpolateNormal(glm::vec3 pt, Triangle* t);

Triangle::Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 norm0, glm::vec3 norm1, glm::vec3 norm2, Material *mat)
{
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
	this->norm0 = norm0;
	this->norm1 = norm1;
	this->norm2 = norm2;
	this->mat = mat;


}


bool Triangle::calculIntersection(const Rayon *r, std::vector<Intersection> *I)
{

	glm::vec3 N = glm::normalize(glm::cross(p1-p0 ,p2-p0 ));


	float B = glm::dot(N, r->Vect());
	if ( B == 0)
	{
		return false;
	}
	float d = glm::dot(N, p0);
	float A = d - glm::dot(r->Orig(), N);
	float t = A / B;
	
	
	glm::vec3 P = r->Orig() + (t*r->Vect());

	if ((glm::dot(N, glm::cross(p1 - p0, P - p0)) < 0 ) || (glm::dot(N, glm::cross(p2 - p1, P - p1)) < 0) || (glm::dot(N, glm::cross(p0 - p2, P - p2)) < 0))
	{
		return false;
	}
	

	Intersection* inter = new Intersection();
	inter->normal = interpolateNormal(P, this);
	inter->dist = t;
	inter->Objet = this;
	I->push_back(*inter);
	delete inter;
	return true;
}




glm::vec3 interpolateNormal(glm::vec3 pt, Triangle* t)
{
	//bilinear interpolation
	float lambda1 = (((t->p1.y - t->p2.y)*(pt.x - t->p2.x)) + ((pt.y - t->p2.y)*(t->p2.x - t->p1.x))) / (((t->p1.y - t->p2.y)*(t->p0.x - t->p2.x)) + ((t->p0.y - t->p2.y)*(t->p2.x - t->p1.x)));
	float lambda2 = (((t->p2.y - t->p0.y)*(pt.x - t->p2.x)) + ((pt.y - t->p2.y)*(t->p2.x - t->p0.x))) / (((t->p1.y - t->p2.y)*(t->p0.x - t->p2.x)) + ((t->p0.y - t->p2.y)*(t->p2.x - t->p1.x)));
	float lambda3 = 1 - lambda1 - lambda2;

	return glm::normalize(((glm::vec3(lambda1*t->norm0) + (lambda2*t->norm1) + (lambda3*t->norm2))));

}