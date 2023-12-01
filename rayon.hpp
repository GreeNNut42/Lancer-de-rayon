#ifndef RAYON_HPP_
#define RAYON_HPP_

#include "glm/glm.hpp"
#include "Scene.hpp"
#include "Objet3D.hpp"



class Rayon {
protected:

	glm::vec3 orig; // Origine du rayon
	glm::vec3 vect; // Vecteur directeur (oriente) du rayon
	glm::vec3 inv_vect;
	bool sign[3];

public:

	Rayon() {	}

	// Lecture
	glm::vec3 Orig() const {
		return orig;
	}
	glm::vec3 Vect() const {
		return vect;
	}
	glm::vec3 Inv_vect() const{
		return inv_vect;
	}
	bool Sign(int index) const{
		return sign[index];
	}


	// Ecriture
	void Orig(const glm::vec3 & o) {
		orig = o;
	}
	void Vect(const glm::vec3 & v) {
		vect = glm::normalize(v);
		inv_vect = glm::vec3(1 / v.x, 1 / v.y, 1 / v.z);
		sign[0] = (inv_vect.x < 0);
		sign[1] = (inv_vect.y < 0);
		sign[2] = (inv_vect.z < 0);
	}


	glm::vec3 Lancer(Scene &sc,int current) const;
	bool LancerS(Scene &sc) const;
};

#endif /* RAYON_HPP_ */
