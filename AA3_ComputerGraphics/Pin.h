#pragma once
#include <GL/glut.h>
#include <math.h>

class Pin
{
    void drawCircle(float radius, int segments, bool filled = false)
    {
        if (filled)
            glBegin(GL_POLYGON); // círculo sólido
        else
            glBegin(GL_LINE_LOOP); // solo borde

        for (int i = 0; i < segments; ++i)
        {
            float angle = 2.0f * 3.1415926f * float(i) / float(segments);
            float x = radius * cosf(angle);
            float z = radius * sinf(angle);
            glVertex3f(x, 4.f, z); // plano XZ (y=0)
        }

        glEnd();
    }

public:
    void drawMapPin(
        float circleRadius,
        float coneHeight,
        const float color[3]
    )
    {
        glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING);
        // --- Dibuja el círculo ---
        int circleSegments = 16;
        glPushMatrix();
        glColor3fv(color);
        drawCircle(circleRadius, circleSegments, true);
        glPopMatrix();

        // --- Dibuja el cono apuntando hacia abajo ---
        glPushMatrix();
        glColor3fv(color);
        glTranslatef(0.0f, 4.0f, 0.0f);
        glRotatef(-180.0f, 0.0f, 1.0f, 0.0f);
        glutSolidCone(circleRadius, coneHeight, 20, 20);
        glPopMatrix();

        glPopAttrib();
    }
};