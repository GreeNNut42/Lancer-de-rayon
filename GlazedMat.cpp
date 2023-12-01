#include "GlazedMat.h"


GlazedMat::GlazedMat(glm::vec3 col, float a, float d, float t, float m, float r)
{
	color = col;
	ka = a;
	kd = d;
	transparent = t;
	reflective = m;
	refraction = r;

}


glm::vec3 GlazedMat::getColor(Intersection *I, Scene *S, const Rayon *R, int current)
{
	if (current == 0) return color;
	
	
	// Ambient
	glm::vec3 amb = ka*color;

	// Diffuse
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

	// Final
	glm::vec3 finalColor = amb + dif;

	// Reflective
	if (reflective > 0)
	{
		Rayon ray;
		glm::vec3 ReColor;
		ray.Orig(R->Orig()+(I->dist*R->Vect()) + (0.0001f*I->normal));
		ray.Vect(glm::reflect((R->Vect()), I->normal));
		ReColor = ray.Lancer(*S, current-1);

		finalColor += reflective*ReColor;

	}

	if (transparent > 0)
	{
		Rayon ray2;
		glm::vec3 TrColor;
		glm::vec3 ReColor;
		ray2.Orig(R->Orig() + (I->dist*R->Vect()) + (0.0001f*I->normal));
		ray2.Vect(glm::reflect((R->Vect()), I->normal));
		ReColor = ray2.Lancer(*S, current - 1);

		finalColor += transparent*TrColor;

	}

	
	finalColor = shadows(finalColor, (R->Orig() + (I->dist*R->Vect()) + (0.0001f*I->normal)), S);
	return finalColor;
}

glm::vec3 GlazedMat::shadows(glm::vec3 color, glm::vec3 pt, Scene *s)
{
	int numLight = s->listLum.size();
	int numOcc = 0;
	for (int i = 0; i < numLight; i++)
	{
		Rayon ray;
		ray.Orig(pt);
		ray.Vect((s->listLum.at(i)->getDir()));

		if (ray.LancerS(*s))
		{
			numOcc++;
		}
	}
	if (numOcc != 0)
	{
		return color / (float)(numOcc + 1);
	}

	return color;

}


