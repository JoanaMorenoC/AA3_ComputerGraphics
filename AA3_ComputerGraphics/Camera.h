#pragma once
#define _USE_MATH_DEFINES

#include "Vector3.h"
#include <GL/glut.h>
#include <cmath>

class Camera
{
private:
    Vector3 pos;

    Vector3 front;
    Vector3 up;
    Vector3 right;  // Vector derecho de la cámara, para movimiento lateral

    float yaw;      // Angulo horizontal (grados)
    float pitch;    // Angulo vertical (grados)

    float cameraSpeed;

    void updateCameraVectors()
    {
        // Calcula la nueva dirección de la cámara desde yaw y pitch
        Vector3 f;
        float yawRad = yaw * M_PI / 180.0f;
        float pitchRad = pitch * M_PI / 180.0f;

        f.x = cosf(yawRad) * cosf(pitchRad);
        f.y = sinf(pitchRad);
        f.z = sinf(yawRad) * cosf(pitchRad);
        front = f.Normalized();

        // Recalcula right y up
        right = front.Cross(Vector3(0.0f, 1.0f, 0.0f)).Normalized();
        up = right.Cross(front).Normalized();
    }

public:
    Camera(Vector3 startPos = Vector3(0.0f, 0.0f, 5.0f),
        Vector3 startUp = Vector3(0.0f, 1.0f, 0.0f),
        float startYaw = -90.0f,
        float startPitch = 0.0f,
        float speed = 10.f)
        : pos(startPos), up(startUp), yaw(startYaw), pitch(startPitch), cameraSpeed(speed)
    {
        updateCameraVectors();
    }

    void moveForward()
    {
        pos += front * cameraSpeed;
    }

    void moveBackward()
    {
        pos -= front * cameraSpeed;
    }

    void moveLeft()
    {
        pos -= right * cameraSpeed;
    }

    void moveRight()
    {
        pos += right * cameraSpeed;
    }

    void rotateYaw(float angle)
    {
        yaw += angle;
        if (yaw > 360.0f) yaw -= 360.0f;
        if (yaw < 0.0f) yaw += 360.0f;
        updateCameraVectors();
    }

    void rotatePitch(float angle)
    {
        pitch += angle;
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
        updateCameraVectors();
    }

    void ApplyView()
    {
        Vector3 center = pos + front;
        gluLookAt(pos.x, pos.y, pos.z,
            center.x, center.y, center.z,
            up.x, up.y, up.z);
    }
};
