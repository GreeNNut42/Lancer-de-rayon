#include "camera.hpp"
#include "pixelmap.hpp"
#include "rayon.hpp"
#include "Scene.hpp"
#include <stdio.h>

void Camera::Haut(const glm::vec3 & h) {

	haut = h - (dir * (dir * h));
	
	
	if (glm::length(haut) != 0.0)
		haut = glm::normalize(haut);
	
}

void Camera::Calculer_image(Pixelmap & pm, Scene &sc, int complexite) const {
	glm::vec3 foyer; // Foyer optique de la camera
	glm::vec3 droite; // Vecteur partant sur la droite dans le plan de l'ecran
	float dx, dy; // dimension des macro-pixels
	int x, y; // Position dans l'image du pixel en cours de calcul
	glm::vec3 hg; // Position du pixel au centre du premier macro-pixel de l'ecran (en haut a gauche)
	glm::vec3 pt; // Position de l'intersection entre le rayon a lancer et l'ecran
	Rayon ray; // Rayon a lancer
	glm::vec3 vect; // Vecteur directeur du rayon a lancer
	int index; // Indice du pixel traite

	// On calcule la position du foyer de la camera
	foyer = centre - (dir * dist);
	
	//std::cout << "centre : " << haut.x << " " << haut.y <<" " << haut.z << std::endl; 
	// On calcule le vecteur unitaire "droite" du plan
	droite = glm::cross(dir,haut);
	

	// On calcule le deltaX et le deltaY
	dx = largeur / pm.Largeur();
	dy = hauteur / pm.Hauteur();

	// On calcule la position du premier point de l'ecran que l'on calculera
	hg = centre + (droite * ((dx / 2) - (largeur / 2))) + (haut * ((hauteur / 2) - (dy / 2)));

	// Pour chaque pixel de l'image a calculer
	index = 0;
	for (y = 0; y < pm.Hauteur(); y++) {
		for (x = 0; x < pm.Largeur(); x++) {
			// On calcule la position dans l'espace de ce point
			pt = hg + (droite * (dx * x)) - (haut * (dy * y));
			glm::vec3 color = glm::vec3(0.0, 0.0, 0.0);
			// On prepare le rayon qui part du foyer et qui passe par ce point
			ray.Orig(pt);
			vect = pt - foyer;
			vect = glm::normalize(vect);
			ray.Vect(vect);
			// Et on enregistre la couleur daans une variable 
			color += ray.Lancer(sc, complexite);

			if (ANTIALIASING)
			{
				color *= 2;

				pt -= droite * (dx / 2);
				pt -= haut * (dy / 2);
				ray.Orig(pt);
				vect = pt - foyer;
				vect = glm::normalize(vect);
				ray.Vect(vect);

				color += ray.Lancer(sc, complexite);

				pt += droite * (dx / 2);
				pt -= haut * (dy / 2);
				ray.Orig(pt);
				vect = pt - foyer;
				vect = glm::normalize(vect);
				ray.Vect(vect);

				color += ray.Lancer(sc, complexite);

				pt -= droite * (dx / 2);
				pt += haut * (dy / 2);
				ray.Orig(pt);
				vect = pt - foyer;
				vect = glm::normalize(vect);
				ray.Vect(vect);

				color += ray.Lancer(sc, complexite);

				pt += droite * (dx / 2);
				pt += haut * (dy / 2);
				ray.Orig(pt);
				vect = pt - foyer;
				vect = glm::normalize(vect);
				ray.Vect(vect);

				color += ray.Lancer(sc, complexite);

				color /= (float)6;

			}
			pm.Map(index++, color);
		}
		std::cout << "Ligne " << y << std::endl; 
	}
}
