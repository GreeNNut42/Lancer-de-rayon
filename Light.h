#pragma once
#include"glm/glm.hpp"
class Light
{
protected:

	glm::vec3 dir;
	glm::vec3 color;
	// Permet de déterminer le type de lumière (eg. pontuelle ou directionnelle)
	bool ponctual;



public:
	Light(glm::vec3 d, glm::vec3 col, bool p);
	~Light();
	glm::vec3 getDir();
	bool Ponctual();
};

