#include "CheckMat.h"


CheckMat::CheckMat(glm::vec3 col, glm::vec3 col2, int Csize, float a , float d, float t, float m, float r)
{
	color = col;
	color2 = col2;
	case_size = Csize;
	ka = a;
	kd = d;
	transparent = t;
	reflective = m;
	refraction = r;

}


glm::vec3 CheckMat::getColor(Intersection *I, Scene *S, const Rayon *R, int current)
{
	glm::vec3 Ccolor;
	glm::vec3 pt = R->Orig() + (I->dist*R->Vect());

	int superX = pt.x / case_size;
	int superY = pt.y / case_size;
	int superZ = pt.z / case_size;

	if (superZ % 2 == 0)
	{
		if ((superX % 2) == 0)
		{
			Ccolor = color;
		}
		else
		{
			Ccolor = color2;
		}
	}
	else
	{
		if ((superX % 2) == 0 )
		{
			Ccolor = color2;
		}
		else
		{
			Ccolor = color;
		}
	}
	if (current == 0) return Ccolor;
	// Ambient
	glm::vec3 amb = ka*Ccolor;

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
		dif += diff * Ccolor;
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
		ray2.Orig(R->Orig() + (I->dist*R->Vect()) + (0.000001f*I->normal));
		ray2.Vect(glm::reflect((R->Vect()), I->normal));

		ReColor = ray2.Lancer(*S, current - 1);

		finalColor += transparent*TrColor;

	}

	finalColor = shadows(finalColor, (R->Orig() + (I->dist*R->Vect()) + (0.0001f*I->normal)), I->normal, S);
	return finalColor ;
}

glm::vec3 CheckMat::shadows(glm::vec3 color, glm::vec3 pt, glm::vec3 Norm, Scene *s)
{
	int numLight = s->listLum.size();
	int numOcc = 0;
	for (int i = 0; i < numLight; i++)
	{
		Rayon ray;
		ray.Orig(pt);
		if (s->listLum.at(i)->Ponctual())
		{
			ray.Vect((s->listLum.at(i)->getDir() - pt));
		}
		else
		{
			ray.Vect((s->listLum.at(i)->getDir()));
		}

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
