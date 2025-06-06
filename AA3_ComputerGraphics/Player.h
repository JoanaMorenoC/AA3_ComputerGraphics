#pragma once
#include "InteractableObject.h"
#include "Vector3.h"
#include "Camera.h"
#include "CylinderCollider.h"
#include <vector>

class Player
{
private:
	Vector3 pos;
	Camera camera;
    CylinderCollider collider;

    InteractableObject* selectedObject;

    bool flashlightOn = false;
    bool fKeyPreviouslyPressed = false;

	const float CAMERA_ROTATION_SPEED = 1.5f;
    const float MAX_DISTANCE_TO_SELECT = 1.3f;
    const float MAX_ANGLE_DEGREES_TO_SELECT = 15.f;
    const float CLOSE_SELECTING_DISTANCE = 0.8f;
    const float MAX_ANGLE_DEGREES_TO_SELECT_WHEN_CLOSE = 50.f;

    InteractableObject* GetLookedAtObject(const std::vector<InteractableObject*>& objects)
    {
        InteractableObject* closestObject = nullptr;
        float closestDistance = MAX_DISTANCE_TO_SELECT;

        for (InteractableObject* obj : objects)
        {
            obj->SetSelected(false);
            Vector3 toObject = obj->GetCollider()->GetPos() - pos;
            float distance = toObject.length();

            if (distance > MAX_DISTANCE_TO_SELECT)
                continue;

            toObject = toObject.Normalized();
            float dot = camera.GetFront().Dot(toObject);
            float angle = acosf(dot) * 180.0f / M_PI;

            if (distance < closestDistance)
            {
                bool insideAngleRange;
                if (distance < CLOSE_SELECTING_DISTANCE)
                    insideAngleRange = angle <= MAX_ANGLE_DEGREES_TO_SELECT_WHEN_CLOSE;
                else
                    insideAngleRange = angle <= MAX_ANGLE_DEGREES_TO_SELECT;

                if (insideAngleRange)
                {
                    closestDistance = distance;
                    closestObject = obj;
                }

            }
        }

        return closestObject;
    }

public:
    Player()
        : collider(pos, 0.1f)
    {

    }

	void Update(bool (&keyStates)[256], bool(&specialKeyStates)[256], std::vector<Collider*> colliders, std::vector<InteractableObject*> interactableObjects)
	{
        if (keyStates['w'] || keyStates['W'])
            camera.MoveForward();
        if (keyStates['s'] || keyStates['S'])
            camera.MoveBackward();
        if (keyStates['a'] || keyStates['A'])
            camera.MoveLeft();
        if (keyStates['d'] || keyStates['D'])
            camera.MoveRight();

        if (specialKeyStates[GLUT_KEY_LEFT])
            camera.RotateYaw(-CAMERA_ROTATION_SPEED);
        if (specialKeyStates[GLUT_KEY_RIGHT])
            camera.RotateYaw(CAMERA_ROTATION_SPEED);
        if (specialKeyStates[GLUT_KEY_UP])
            camera.RotatePitch(CAMERA_ROTATION_SPEED);
        if (specialKeyStates[GLUT_KEY_DOWN])
            camera.RotatePitch(-CAMERA_ROTATION_SPEED);

        bool fPressedNow = keyStates['f'] || keyStates['F'];
        if (fPressedNow && !fKeyPreviouslyPressed)
        {
            flashlightOn = !flashlightOn;
            glDisable(GL_LIGHT3);
        }
        fKeyPreviouslyPressed = fPressedNow;

        SetPos(camera.GetPos());

        CheckCollisions(colliders);
        CheckSelections(interactableObjects);
	}

    void ApplyFlashlight()
    {
        if (flashlightOn)
        {
            camera.ApplySpotlight(GL_LIGHT3);
        }
    }

    Vector3 GetPos()
    {
        return pos;
    }

    void SetPos(Vector3 newPos)
    {
        pos = newPos;
        collider.SetPos(newPos);
        camera.SetPos(newPos);
    }

    void ApplyView()
    {
        camera.ApplyView();
    }

    void CheckCollisions(std::vector<Collider*> colliders)
    {
        for (int i = 0; i < colliders.size(); i++)
        {
            collider.CollidesWith(colliders[i]);
        }
        SetPos(collider.GetPos());
    }

    void CheckSelections(std::vector<InteractableObject*> interactableObjects)
    {
        selectedObject = GetLookedAtObject(interactableObjects);

        if (selectedObject != nullptr)
            selectedObject->SetSelected(true);
    }
};