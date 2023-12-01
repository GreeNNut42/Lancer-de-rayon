#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <iostream>
#include "Intersection.hpp"
#include <vector>
#include "Material.h"

class Rayon;
class Objet3D
{
 protected:


  
 public:

	 Material* mat;
	 Objet3D(){};

	 virtual bool calculIntersection(const Rayon *r, std::vector<Intersection> *I){ return false;};


};


#endif 
