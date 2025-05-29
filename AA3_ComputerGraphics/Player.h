#pragma once
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

    bool flashlightOn = false;
    bool fKeyPreviouslyPressed = false;

	const float CAMERA_ROTATION_SPEED = 1.5f;

public:
    Player()
        : collider(pos, 0.1f)
    {

    }

	void Update(bool (&keyStates)[256], bool(&specialKeyStates)[256], std::vector<Collider*> colliders)
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
        }
        fKeyPreviouslyPressed = fPressedNow;

        SetPos(camera.GetPos());

        CheckCollisions(colliders);
	}

    void ApplyFlashlight()
    {
        if (flashlightOn)
        {
            camera.ApplySpotlight(GL_LIGHT2);
        }
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
};