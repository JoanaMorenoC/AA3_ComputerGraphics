#pragma once
#include "Object.h"
#include <cmath>
#include <iostream>

class Lighthouse : public Object
{
	Color WHITE = Color(1.0f, 1.0f, 1.0f);
	Color RED = Color(1.0f, 0.0f, 0.0f);
    Color GRAY = Color(0.5f, 0.5f, 0.5f);

    float intensityLight = 0.05;
        

    void DrawLighthouseBody(float baseRadius, float topRadius, float height, int stripesAmount)
    {
        glPushMatrix();
        const int slices = 16;
        const int stacks = 16 / stripesAmount;

        float stripeHeight = height / stripesAmount;

        for (int i = 0; i < stripesAmount; ++i)
        {
            if (i % 2 == 0)
                SetColor(RED);
            else
                SetColor(WHITE);

            float r1 = baseRadius - (baseRadius - topRadius) * (float(i) / stripesAmount);
            float r2 = baseRadius - (baseRadius - topRadius) * (float(i + 1) / stripesAmount);

            DrawCylinder(r1, r2, stripeHeight, slices, stacks);
            glTranslatef(0.0f, stripeHeight, 0.0f);
        }
        glPopMatrix();
    }
public:

    bool activeLighthouse = true;

    void Render() override
    {
        glPushMatrix();

        ApplyTransformations();

        DrawLighthouseBody(1.5f, 1.f, 6.f, 4);
        
        SetColor(RED);
        glTranslatef(0.0f, 5.8f, 0.0f);
        DrawSphereSlice(3.f, 1.0f, 32, 32);

        SetColor(GRAY);
        glPushMatrix();
        glTranslatef(0.0f, 0.94f, 0.0f);
        DrawCylinder(2.2, 2.2, 0.5, 16, 16);
        glPopMatrix();

        SetColor(WHITE);
        glTranslatef(0.0f, 0.2f, 0.0f);
        DrawCylinder(0.95f, 0.95f, 3, 16, 16);

        SetColor(RED);
        glTranslatef(0.0f, 1.8f, 0.0f);
        DrawCylinder(1.0f, 1.0f, 1.5f, 16, 16);

        SetColor(WHITE);
        glTranslatef(0.0f, 1.5f, 0.0f);
        glRotatef(-90.f, 1, 0, 0);
        glutSolidCone(1.3f, 0.8f, 16, 16);


        glPopMatrix();
    }
    
    void configurationLight()
    {
        float r = 0.94, g = 0.94, b = 0.48;


        GLfloat lightColor[] = { r * intensityLight, g * intensityLight, b * intensityLight, 1.0f };

        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor);
    }


    void light()
    {
        if (!activeLighthouse)
        {
            glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 0);
            return;
        }
        glPushMatrix();
        configurationLight();

        float position[4] = { 0.0f, 8.0f, 0.0f, 1.0f };
        float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT1, GL_POSITION, position);

        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180);

        float globalAmbient[4] = { 1, 1, 1, 1.0f };
        

        glPopMatrix();

    }

};