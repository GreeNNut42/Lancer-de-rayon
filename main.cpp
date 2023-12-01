#include <stdio.h>
#include "camera.hpp"
#include "pixelmap.hpp"
#include "Scene.hpp"
#include "Objet3D.hpp"
#include "Plan.h"
#include "Sphere.h"
#include "PhongMat.h"
#include "Triangle.h"
#include "GlazedMat.h"
#include "CheckMat.h"
#include "Box.h"
#include "BumpMat.h"
#include "NoiseMat.h"


int main(void) {
	
	// Une image Pixelmap
	Pixelmap pixmap(1920, 1440);
	//Pixelmap pixmap(900, 670);
	//Pixelmap pixmap(400, 300);
	// Une image Bitmap
	Image bitmap;

	Scene scene;
	// Initialisation des matériaux
	PhongMat *reflexion1 = new PhongMat(glm::vec3(0.0, 0.0, 0.0), 0.2, 0.6, 1.0, 0.0, 1.0, 0.0, 1.0);
	PhongMat *refraction1 = new PhongMat(glm::vec3(0.0, 0.0, 0.0), 0.2, 0.6, 1.0, 1.0, 0.0, 1.0003/1.62, 0.0);
	PhongMat *refraction2 = new PhongMat(glm::vec3(0.0, 0.0, 0.0), 0.2, 0.6, 1.0, 1.0, 0.1, 1.0003 /5.13, 0.3);
	PhongMat *Phong1 = new PhongMat(glm::vec3(1.0, 0.0, 1.0), 0.2, 0.6, 0.5, 0.0, 0.0, 0.0, 0.0);
	GlazedMat *matx = new GlazedMat(glm::vec3(1.0, 0.0, 0.0), 0.2, 0.6, 0.0, 0.2, 0.0);
	GlazedMat *matz = new GlazedMat(glm::vec3(0.0, 0.0, 1.0), 0.2, 0.6, 0.0, 0.2, 0.0);
	CheckMat *damier = new CheckMat(glm::vec3(1.0, 1.0, 1.0),glm::vec3(0.0,0.0,0.0),5, 0.4, 0.6, 0.0, 0.0, 0.0);
	NoiseMat *bruit = new NoiseMat(glm::vec3(1.0, 0.0, 1.0), 0.2, 0.6, 0.5, 0.0, 0.0, 0.0, 0.0);
	BumpMat *bruit2 = new BumpMat(glm::vec3(0.0, 1.0, 0.0), 0.2, 0.6, 0.5, 0.0, 0.0, 0.0, 0.0);;
	
	// Création de la lumière 
	Light *l = new Light(glm::vec3(240.0, 200.0, -100.0), glm::vec3(1.0, 1.0, 1.0), true);
	Light *l2 = new Light(glm::vec3(10.0, 20.0, -5.0), glm::vec3(1.0, 1.0, 1.0), false);

	// Ajout de la (les) lumière(s) à la scène
	scene.ajouterLum(l);
	scene.ajouterLum(l2);


	// Initialisation des objets
	Sphere* s1 = new Sphere(4.0, glm::vec3(200, 4, 50), refraction2);
	Sphere* s2 = new Sphere(4.0, glm::vec3(215, 4, 50), reflexion1);
	Sphere* s3 = new Sphere(4.0, glm::vec3(185, 4, 50), bruit);
	Sphere* s4 = new Sphere(4.0, glm::vec3(200, 4, 80), bruit2);
	Sphere* s5 = new Sphere(4.0, glm::vec3(185, 4, 80), refraction1);
	Plan* px = new Plan(glm::vec3(175.0,0.0,0.0), glm::vec3(1.0,0.0,0.0),matx);
	Plan* py = new Plan(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), damier);
	Plan* pz = new Plan(glm::vec3(0.0, 0.0, 100.0), glm::vec3(0.0, 0.0, -1.0), matz);
	Triangle* test = new Triangle(glm::vec3(185,0,100), glm::vec3(175,6,100), glm::vec3(175,0,90), glm::vec3(1.0, 1.0, -1.0), glm::vec3(1.0, 1.0, -1.0), glm::vec3(1.0, 1.0, -1.0), bruit2);
	Box* round = new Box(1.5, glm::vec3(215, 3.0, 80), glm::vec3(2.0,2.0,2.0), Phong1);
	
	// Ajouter les objets à la scene
	scene.ajouterObjet(s1);
	scene.ajouterObjet(s2);
	scene.ajouterObjet(s3);
	scene.ajouterObjet(s4);
	scene.ajouterObjet(s5);
	scene.ajouterObjet(px);
	scene.ajouterObjet(py);
	scene.ajouterObjet(pz);
	scene.ajouterObjet(test);
	scene.ajouterObjet(round);


	// la Camera
	Camera cam;
	cam.Centre(glm::vec3(200, 20, 12));
	cam.Dir(glm::vec3(0, -0.5, 1));
	//cam.Centre(glm::vec3(200,5,12));
	//cam.Dir(glm::vec3(0,0,1));
	cam.Haut(glm::vec3(0, 1, 0));
	cam.Largeur((5.6 * 513) / 384);
	cam.Hauteur(5.6);


	cam.Calculer_image(pixmap, scene, 10);

	pixmap.Transferer(bitmap);
	bitmap.Enregistrer("image.bmp");

	return 0;
}
