#pragma once
#include "Object.h"

class InteractableObject : public Object
{
protected:
	bool selected = false;

	virtual void DrawGeometry(bool withColors) = 0;

public:
    InteractableObject(CylinderCollider* colliderPointer)
        : Object(colliderPointer)
    {
    }

    void Render() override
    {
        glPushMatrix();
        ApplyTransformations();

        if (selected)
            RenderOutline();

        DrawGeometry(true);

        glPopMatrix();
    }

    void RenderOutline()
    {
        glPushAttrib(GL_ALL_ATTRIB_BITS);

        glPushMatrix();
        glScalef(1.05f, 1.05f, 1.05f);

        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        glColor3f(1.0f, 1.0f, 0.0f);
        glLineWidth(2.0f);

        DrawGeometry(false);

        glCullFace(GL_BACK);
        glPopMatrix();
        glPopAttrib();
    }

    virtual void SetSelected(bool newState)
    {
        selected = newState;
    }

    virtual void Interact() = 0;
};