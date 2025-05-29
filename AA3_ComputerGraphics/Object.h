#pragma once
#include "Vector3.h"
#include <GL/glut.h>

void DrawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks) {
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	GLUquadric* quad = gluNewQuadric();
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluCylinder(quad, baseRadius, topRadius, height, slices, stacks);
	gluDeleteQuadric(quad);

	glPopMatrix();
}

void DrawClosedCylinder(float baseRadius, float topRadius, float height, int slices, int stacks) {
	glPushMatrix();

	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	GLUquadric* quad = gluNewQuadric();
	gluQuadricNormals(quad, GLU_SMOOTH);

	gluDisk(quad, 0.0f, baseRadius, slices, 1);
	gluCylinder(quad, baseRadius, topRadius, height, slices, stacks);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, height);
	gluDisk(quad, 0.0f, topRadius, slices, 1);
	glPopMatrix();

	gluDeleteQuadric(quad);

	glPopMatrix();
}

void DrawSphereSlice(float sphereRadius, float sliceHeight, int slices, int stacks) {
	glPushMatrix();
	glTranslatef(0.0, sphereRadius, 0.0f);
	GLUquadric* quad = gluNewQuadric();

	GLdouble planeEq[] = { 0.0, -1, 0.0, -sphereRadius + sliceHeight };
	glClipPlane(GL_CLIP_PLANE0, planeEq);
	glEnable(GL_CLIP_PLANE0);

	gluSphere(quad, sphereRadius, slices, stacks);

	glDisable(GL_CLIP_PLANE0);
	gluDeleteQuadric(quad);
	glPopMatrix();
}

struct Color
{
	float r;
	float g;
	float b;

	Color(float newR, float newG, float newB)
	{
		r = newR;
		g = newG;
		b = newB;
	}
};

class Object
{
protected:
	Vector3 pos;
	Vector3 scale;
	Vector3 rotation;

	CylinderCollider* collider = nullptr;

	void ApplyTransformations()
	{
		glTranslatef(pos.x, pos.y, pos.z);
		glRotatef(rotation.z, 0, 0, 1);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.x, 1, 0, 0);
		glScalef(scale.x, scale.y, scale.z);
	}

	void SetColor(Color color)
	{
		glColor3f(color.r, color.g, color.b);
	}

public:
	Object()
	{
		pos = { 0,0,0 };
		scale = { 1,1,1 };
		rotation = { 0,0,0 };
	}

	Object(CylinderCollider* colliderPointer)
		: pos(0, 0, 0), scale(1, 1, 1), rotation(0, 0, 0), collider(colliderPointer)

	{
	}

	CylinderCollider* GetCollider()
	{
		return collider;
	}

	void SetPos(float x, float y, float z)
	{
		pos.x = x;
		pos.y = y;
		pos.z = z;
	}

	void SetPos(Vector3 newPos)
	{
		pos = newPos;
		if (collider != nullptr)
			collider->SetPos(newPos);
	}

	void SetScale(float newScale)
	{
		scale.x = newScale;
		scale.y = newScale;
		scale.z = newScale;

		if (collider != nullptr)
		{
			collider->SetScale(newScale);
		}
	}

	void SetScale(float x, float y, float z)
	{
		scale.x = x;
		scale.y = y;
		scale.z = z;
	}

	void SetRotation(float x, float y, float z)
	{
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
	}

	virtual void Render()
	{
		glPushMatrix();

		ApplyTransformations();

		glutSolidCube(1); 

		glPopMatrix();
	}
};