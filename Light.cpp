#include "Light.h"


Light::Light(glm::vec3 d, glm::vec3 col, bool p)
{
	dir = d;
	color = col;
	ponctual = p;
}


Light::~Light()
{
}

glm::vec3 Light::getDir()
{
	return this-> dir;
}

bool Light::Ponctual()
{
	return ponctual;
}