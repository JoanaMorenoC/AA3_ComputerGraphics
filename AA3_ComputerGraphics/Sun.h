#pragma once
#include "RotatingLight.h"
#include <GL/glut.h>

class Sun : public RotatingLight
{
private:
    Color YELLOW = Color(0.9216, 0.7059, 0.2039);

    void ChangeSkyColor(Color color)
    {
        glClearColor(color.r, color.g, color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

public:
    Sun()
    {
        lightID = GL_LIGHT0;

        baseIntensity = 0.f;
        maxIntensity = 0.5f;

        lightPhases = {
            {0, Color(1.0f, 0.7f, 0.2f) },       // Dawn
            {15, Color(0.443f, 0.757f, 0.874f) }, // Morning
            {90, Color(0.259f, 0.678f, 1.000f) }, // Noon
            {170, Color(0.341f, 0.529f, 0.800f) }, // Bright afternoon
            {180, Color(0.780f, 0.212f, 0.173f) }, // Sunset
            {185, Color(0.0f, 0.0f, 0.3f) },       // Dusk
            {350, Color(0.055f, 0.055f, 0.212f) }, // Dead of night
            {360, Color(1.0f, 0.7f, 0.2f) }        // Start of new cycle
        };
    }

    void Render() override
    {
        glPushMatrix();

        ApplyTransformations();

        GetToPosition();

        glDisable(GL_LIGHTING);

        SetColor(YELLOW);
        glutSolidSphere(0.5, 16, 16);

        glEnable(GL_LIGHTING);

        glPopMatrix();
    }

    void Lighting()
    {
        RotatingLight::Lighting();

        float globalAmbient[4] = { intensity, intensity, intensity, 1.0f };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

        ChangeSkyColor(currentLightColor);
    }

};
