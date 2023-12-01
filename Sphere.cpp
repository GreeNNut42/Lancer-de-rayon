#include "Sphere.h"
#include "Rayon.hpp"


Sphere::Sphere(float r, glm::vec3 c, Material *mat)
{
	this->center = c;
	this->R = r;
	this->mat = mat;
}


Sphere::~Sphere()
{
}

bool Sphere::calculIntersection(const Rayon *r, std::vector<Intersection> *I)
{

	float A = ((r->Vect().x*r->Vect().x) + (r->Vect().y*r->Vect().y) + (r->Vect().z*r->Vect().z));
	float C = (((r->Orig().x - center.x)*(r->Orig().x - center.x)) + ((r->Orig().y - center.y)*(r->Orig().y - center.y)) + ((r->Orig().z - center.z)*(r->Orig().z - center.z))-R*R);
	float B = 2 * (((r->Vect().x)*(r->Orig().x - center.x)) + ((r->Vect().y)*(r->Orig().y - center.y))+((r->Vect().z)*(r->Orig().z - center.z)));

	float delta = (B*B) - (4 * (A*C));
	if (delta < 0)
	{
		return false;
	}
	
	if (delta == 0)
	{
		float dist = (-B) / (2 * A);
		Intersection* inter = new Intersection();
		inter->normal = glm::normalize((r->Orig() + dist*r->Vect()) - center);
		inter->dist = dist;
		inter->Objet = this;
		I->push_back(*inter);
		delete inter;
		return true;

	}


	if (delta > 0)
	{
		float dist1 = (-B-sqrt(delta))/2 ;
		float dist2 = (-B + sqrt(delta)) / 2;
		if (dist1 > dist2 && dist2 >0)
		{
			Intersection* inter = new Intersection();
			inter->normal = glm::normalize((r->Orig() + dist2*r->Vect()) - center);
			inter->dist = dist2;
			inter->Objet = this;
			I->push_back(*inter);
			delete inter;
			return true;
		}
		if (dist2 > dist1 && dist1 >0)
		{
			Intersection* inter = new Intersection();
			inter->normal = glm::normalize((r->Orig() + dist1*r->Vect()) - center);
			inter->dist = dist1;
			inter->Objet = this;
			I->push_back(*inter);
			delete inter;
			return true;
		}


	}
	return false;


}