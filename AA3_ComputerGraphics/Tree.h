#pragma once
#include "InteractableObject.h"

class Tree : public InteractableObject
{
private:
    const Color BROWN = Color(0.6f, 0.3f, 0.1f);
    const Color GREEN = Color(0.0f, 1.0f, 0.0f);

public:

    Tree()
        : InteractableObject(new CylinderCollider(pos, 1)) { }

    void DrawGeometry(bool withColors) override
    {
        glPushMatrix();
        // Trunk
        if (withColors)
            SetColor(BROWN);
        DrawCylinder(0.3f, 0.3f, 1.5f, 16, 16);

        glTranslatef(0.0f, 1.2f, 0.0f);
        if (withColors)
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