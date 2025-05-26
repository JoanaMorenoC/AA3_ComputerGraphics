#pragma once
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

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(float newX, float newY, float newZ)
	{
		x = newX;
		y = newY;
		z = newZ;
	}

	Vector3 operator+(const Vector3& other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}
};

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

	void SetPos(float x, float y, float z)
	{
		pos.x = x;
		pos.y = y;
		pos.z = z;
	}

	void SetPos(Vector3 newPos)
	{
		pos = newPos;
	}

	void SetScale(float newScale)
	{
		scale.x = newScale;
		scale.y = newScale;
		scale.z = newScale;
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