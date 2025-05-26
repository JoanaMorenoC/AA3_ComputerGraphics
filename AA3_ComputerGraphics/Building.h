#pragma once
#include "Object.h"

class Building : public Object
{
public:
	void Render() override
	{
		glPushMatrix();

		ApplyTransformations();
	
		glColor3f(0.5f, 0.5f, 0.5f);
		glTranslatef(0.f, 0.5f, 0.f);
		glScalef(1.f, 2.f, 1.f);
		glutSolidCube(1);

		glPopMatrix();
	}
};