#pragma once
#include "Object.h"

class Tree : public Object
{
private:
    const Color BROWN = Color(0.6f, 0.3f, 0.1f);
    const Color GREEN = Color(0.0f, 1.0f, 0.0f);

public:

    Tree()
        : Object(new CylinderCollider(pos, 1)) { }

    void Render() override
    {
        glPushMatrix();

        ApplyTransformations();

        // Trunk
        SetColor(BROWN);
        DrawCylinder(0.3f, 0.3f, 1.5f, 16, 16);

        glTranslatef(0.0f, 1.2f, 0.0f);
        SetColor(GREEN);
        // Cone 1
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(1.2f, 2.0f, 16, 16);

        // Cone 2
        glTranslatef(0.0f, 0.0f, 1.0f);
        glutSolidCone(1.0f, 2.0f, 16, 16);

        glPopMatrix();
    }
};