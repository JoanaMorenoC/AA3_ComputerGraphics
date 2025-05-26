#pragma once
#include "RotatingLight.h"
#include <GL/glut.h>

class Moon : public RotatingLight
{
private:
    Color GRAY = Color(0.6, 0.6, 0.6);

    void GetToPosition()
    {
        glRotatef(currentRotationAngle, 0, 0, 1);
		glRotatef(90.f, 0, 0, 1);
		glTranslatef(0.f, MODEL_DISTANCE, 0.f);
    }

    void SetLightIntensity() override
    {
        float shiftedAngle = (currentRotationAngle + 180) % 360;
        float intensityCurve = sinf(shiftedAngle * 3.14159265f / 180.0f);

        intensity = baseIntensity + (maxIntensity - baseIntensity) * fmax(0.0f, intensityCurve);
    }

public:
    Moon()
    {
        lightID = GL_LIGHT2;

        baseIntensity = 0.f;
        maxIntensity = 0.1f;

        lightPhases = {
            {   0,  Color(1.0f, 1.0f, 1.0f) }
        };
    }

    void Render() override
    {
        glPushMatrix();

        ApplyTransformations();

        GetToPosition();

        glDisable(GL_LIGHTING);

        SetColor(GRAY);
        glutSolidSphere(0.1, 16, 16);

        glEnable(GL_LIGHTING);

        glPopMatrix();
    }

};
