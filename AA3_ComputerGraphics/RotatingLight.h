#pragma once
#include "Object.h"
#include <vector>

struct LightPhase {
	float angle;
	Color color;
};

class RotatingLight : public Object
{
protected:
	float LIGHT_DISTANCE = 20.f;
	float MODEL_DISTANCE = 15.f;
	float ANGULAR_INCREMENT = 1.f;

	float baseIntensity;
	float maxIntensity;

	int currentRotationAngle = 0;
	float intensity = 0.f;
	Color currentLightColor = Color(0.f, 0.f, 0.f);

	GLenum lightID;
	std::vector<LightPhase> lightPhases;

	virtual void GetToPosition()
	{
		glRotatef(currentRotationAngle, 0, 0, 1);
		glRotatef(-90.f, 0, 0, 1);
		glTranslatef(0.f, MODEL_DISTANCE, 0.f);
	}

public:
	RotatingLight() = default;

	void Rotate()
	{
		currentRotationAngle += ANGULAR_INCREMENT;

		if (currentRotationAngle >= 360)
			currentRotationAngle -= 360;
	}

	void SetCurrentLightColor()
	{
		float interpolation = 0;

		int numActualPosition = 0;
		int numNextPosition = 1;

		if (lightPhases.size() == 1) {
			currentLightColor = lightPhases[0].color;
			return;
		}
		for (int i = 0; i < lightPhases.size() - 1; ++i)
		{
			if (currentRotationAngle >= lightPhases[i].angle && currentRotationAngle < lightPhases[i + 1].angle)
			{
				float range = lightPhases[i + 1].angle - lightPhases[i].angle;
				float interpolation = (currentRotationAngle - lightPhases[i].angle) / range;

				Color& c1 = lightPhases[i].color;
				Color& c2 = lightPhases[i + 1].color;

				currentLightColor.r = (1 - interpolation) * c1.r + interpolation * c2.r;
				currentLightColor.g = (1 - interpolation) * c1.g + interpolation * c2.g;
				currentLightColor.b = (1 - interpolation) * c1.b + interpolation * c2.b;
				break;
			}
		}
	}

	virtual void SetLightIntensity()
	{
		float intensityCurve = sinf(currentRotationAngle * 3.14159265f / 180.0f);
		intensity = baseIntensity + (maxIntensity - baseIntensity) * fmax(0.0f, intensityCurve);
	}

	void UpdateLightConfiguration()
	{
		SetCurrentLightColor();
		SetLightIntensity();
	}

	void InitLighting()
	{
		glEnable(lightID);
		glLightf(lightID, GL_CONSTANT_ATTENUATION, 0.5f);
		glLightf(lightID, GL_LINEAR_ATTENUATION, 0.5f);
		glLightf(lightID, GL_QUADRATIC_ATTENUATION, 0.01f);
	
		float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glLightfv(lightID, GL_AMBIENT, black);

	}

	void Lighting()
	{
		glPushMatrix();

		UpdateLightConfiguration();

		GLfloat lightColor[] = { currentLightColor.r * intensity, currentLightColor.g * intensity, currentLightColor.b * intensity, 1.0f };

		glLightfv(lightID, GL_DIFFUSE, lightColor);
		glLightfv(lightID, GL_SPECULAR, lightColor);

		GetToPosition();
		float position[4] = { 0.0f , 0.0f, 0.0f, 1.0f };

		glLightfv(lightID, GL_POSITION, position);

		glPopMatrix();
	}
};