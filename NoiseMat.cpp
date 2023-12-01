#include "NoiseMat.h"


NoiseMat::NoiseMat(glm::vec3 col, float a, float d, float s, float t, float m, float r, float f)
{
	color = col;
	ka = a;
	kd = d;
	ks = s;
	transparent = t;
	reflective = m;
	refraction = r;
	fresnel = f;
}


glm::vec3 NoiseMat::getColor(Intersection *I, Scene *S, const Rayon *R, int current)
{

	color = glm::vec3(glm::perlin(R->Orig()+I->dist*R->Vect()));
	if (current == 0) return color;
	
	// Composante Ambiante
	glm::vec3 amb = ka*color;

	// Composante Diffuse
	glm::vec3 dif = glm::vec3(0.0, 0.0, 0.0);
	for (int i = 0; i < S->listLum.size(); i++)
	{
		float theta;
		if (S->listLum.at(i)->Ponctual())
		{
			theta = glm::dot(glm::normalize(I->normal), glm::normalize((S->listLum[i]->getDir() - (R->Orig() + I->dist*R->Vect()))));
		}
		else
		{
			theta = glm::dot(glm::normalize(I->normal), glm::normalize(S->listLum[i]->getDir()));
		}
		float diff = theta*kd;
		dif += diff * color;
	}

	// Composante Spéculaire
	glm::vec3 spe = glm::vec3(0.0, 0.0, 0.0);
	for (int i = 0; i < S->listLum.size(); i++)
	{
		int coeff = 128;
		float alpha;
		if (S->listLum.at(i)->Ponctual())
		{
			alpha = glm::max(glm::dot(glm::normalize(glm::reflect((R->Vect()), I->normal)), glm::normalize((S->listLum[i]->getDir() - (R->Orig()+I->dist*R->Vect())))), 0.0f);
		}
		else
		{
			alpha = glm::max(glm::dot(glm::normalize(glm::reflect((R->Vect()), I->normal)), glm::normalize(S->listLum[i]->getDir())), 0.0f);
		}
		if(reflective!= 0 ) coeff *= 1 / reflective;
		if(transparent != 0) coeff *= 1 / transparent;
		float spec = pow(alpha, coeff) * ks;
		spe += glm::vec3(1.0, 1.0, 1.0) * spec;
	}
	

	// Final
	glm::vec3 finalColor = amb + dif + spe;

	//Fin des récursions
	if (current == 0) return finalColor;
	
	
	// Cas réflechissant

	glm::vec3 ReColor = glm::vec3(0.0,0.0,0.0);
	if (reflective > 0)
	{
		Rayon ray;
		glm::vec3 ReColor;
		ray.Orig(R->Orig()+(I->dist*R->Vect()) + (0.0001f*I->normal));
		ray.Vect(glm::reflect((R->Vect()), I->normal));
		ReColor = ray.Lancer(*S, current-1);
		finalColor += fresnel*(reflective * ReColor);
	}

	// Cas transparent


	glm::vec3 TrColor = glm::vec3(0.0,0.0,0.0);
	if (transparent > 0)
	{
		Rayon ray2;
		float refract = refraction;
		if (glm::dot(R->Vect(), I->normal) > 0)
		{
			refract = 1/refraction;
		}
		ray2.Vect(glm::normalize(glm::refract((R->Vect()), I->normal, refract)));
		ray2.Orig(R->Orig() + (I->dist*R->Vect()) - (0.001f*(I->normal)));
		TrColor = ray2.Lancer(*S, current - 1);
		
		finalColor += (1-fresnel)*(transparent*TrColor);
	}

	


	finalColor = shadows(finalColor, (R->Orig() + (I->dist*R->Vect()) + (0.001f*I->normal)), S, I);
	return finalColor;
}



// Calcul des ombres portées
glm::vec3 NoiseMat::shadows(glm::vec3 color, glm::vec3 pt, Scene *s, Intersection *I)
{
	int numLight = s->listLum.size();
	int numOcc = 0;
	for (int i = 0; i < numLight; i++)
	{
		

		Rayon ray;
		ray.Orig(pt);
		if (s->listLum.at(i)->Ponctual())
		{
			ray.Vect((s->listLum.at(i)->getDir()-pt));
		}
		else
		{
			ray.Vect((s->listLum.at(i)->getDir()));
		}
		if (glm::dot(ray.Vect(), I->normal) >= 0)
		{
			if (ray.LancerS(*s))
			{
				numOcc++;
			}
		}
	}
	if (numOcc != 0)
	{
		return color / (float)(numOcc+1);
	}

	return color;

}
