#pragma once
#include <GL/glut.h>
#include <math.h>

class Pin
{
    void drawCircle(float radius, int segments, bool filled, float posXZ[2])
    {
        float heightIcone = 8.0f;
        if (filled)
            glBegin(GL_POLYGON); 
        else
            glBegin(GL_LINE_LOOP); 

        for (int i = 0; i < segments; ++i)
        {
            float angle = 2.0f * 3.1415926f * float(i) / float(segments);
            float x = radius * cosf(angle);
            float z = radius * sinf(angle);
            glVertex3f(posXZ[0] + x, heightIcone, posXZ[1] + z);
        }

        glEnd();
    }

public:
    void drawMapPin(
        float circleRadius,
        float coneHeight,
        const float color[3],
        float posXZ[2]
    )
    {
        glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING);
        // --- Dibuja el círculo ---
        int circleSegments = 16;
        glPushMatrix();
        glColor3fv(color);
        drawCircle(circleRadius, circleSegments, true, posXZ);
        glPopMatrix();

        // --- Dibuja el cono apuntando hacia abajo ---
        glPushMatrix();
        glColor3fv(color);
        glTranslatef(posXZ[0], 4.0f, posXZ[1]);
        glRotatef(-180.0f, 0.0f, 1.0f, 0.0f);
        glutSolidCone(circleRadius, coneHeight, 20, 20);
        glPopMatrix();

        glPopAttrib();
    }
};