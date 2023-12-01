#include <algorithm>
#include "rayon.hpp"

// --------------------------------------------------------------------------
//
// Methodes (et operations) sur les rayons
//
// --------------------------------------------------------------------------


glm::vec3 Rayon::Lancer(Scene &sc, int recur) const {
	glm::vec3 res; // Couleur resultante

	if (recur < 0)
	{
		return glm::vec3(0.0, 0.0, 0.0);
	}
	// Au depart, le point au bout du rayon est noir
	res = glm::vec3(0, 0, 0);


	Rayon *r = new Rayon();
	r->Orig(orig);
	r->Vect(vect);

	// Calcul des intersections du rayon avec la scène
	std::vector<Intersection>* I = new std::vector<Intersection>();

	for (int i = 0; i < sc.listObjets.size(); i++)
	{
		Objet3D *obj = sc.listObjets.at(i);
		obj->calculIntersection(r, I);
	}
	if (I->size() > 0)
	{
		// Traiter l'intersection la plus proche de l'origine
		std::sort(I->begin(), I->end());

		// Calculer et retourner la couleur du rayon
		res += I->at(0).Objet->mat->getColor(&(I->at(0)), &sc, this, recur);
	}
	I->clear();
	delete I;
	delete r;
	
	
		
	return res;
}


bool Rayon::LancerS(Scene &sc) const {
	
	// C'est un rayon de calcul d'occlusion simplement donc 
	// on a pas besoin de renvoyer une couleur mais juste 
	// la présence d'au moins un objet entre la lumière  et le point de départ
	Rayon *r = new Rayon();
	r->Orig(orig);
	r->Vect(vect);

	// Calcul des intersections du rayon avec la scène
	std::vector<Intersection>* I = new std::vector<Intersection>();

	Intersection inter;
	for (int i = 0; i < sc.listObjets.size(); i++)
	{
		Objet3D *obj = sc.listObjets.at(i);
		obj->calculIntersection(r, I);
	}
	if (I->size() > 0)
	{
		I->clear();
		delete r ;
		delete I ;
		return true;
	}
	else
	{
		I->clear();
		delete r ;
		delete I ;
		return false;
	}
	

}
