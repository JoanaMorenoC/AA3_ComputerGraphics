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
        : collider(pos, 1)
    {

    }

	void Update(bool (&keyStates)[256], bool(&specialKeyStates)[256], std::vector<CylinderCollider*> colliders)
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

        std::cout << "Camera pos: "<<camera.GetPos().x << " "<< camera.GetPos().y<<std::endl;
        pos = camera.GetPos();

        CheckCollisions(colliders);
        camera.SetPos(pos);
	}

    void ApplyFlashlight()
    {
        if (flashlightOn)
        {
            camera.ApplySpotlight(GL_LIGHT2);
        }
    }

    void ApplyView()
    {
        camera.ApplyView();
    }

    void CheckCollisions(std::vector<CylinderCollider*> colliders)
    {

        for (int i = 0; i < colliders.size(); i++)
        {
            std::cout << " I: " << i << std::endl;
            std::cout << "Player position: " << pos.x << " " << pos.y << std::endl;

            collider.CollidesWith(colliders[i]);
        }
        pos = collider.GetPos();
        std::cout << std::endl;
    }
};