#pragma once
#define _USE_MATH_DEFINES

#include "Vector3.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

class Camera
{
private:
    Vector3 pos;

    Vector3 front;
    Vector3 up;
    Vector3 right;

    float yaw;
    float pitch;

    const float CAMERA_MOVEMENT_SPEED = 0.01f;

    void UpdateCameraVectors()
    {
        Vector3 f;
        float yawRad = yaw * M_PI / 180.0f;
        float pitchRad = pitch * M_PI / 180.0f;

        f.x = cosf(yawRad) * cosf(pitchRad);
        f.y = sinf(pitchRad);
        f.z = sinf(yawRad) * cosf(pitchRad);
        front = f.Normalized();

        right = front.Cross(Vector3(0.0f, 1.0f, 0.0f)).Normalized();
        up = right.Cross(front).Normalized();
    }

public:
    Camera(Vector3 startPos = Vector3(0.0f, 0.0f, 5.0f),
        Vector3 startUp = Vector3(0.0f, 1.0f, 0.0f),
        float startYaw = -90.0f,
        float startPitch = 0.0f)
        : pos(startPos), up(startUp), yaw(startYaw), pitch(startPitch)
    {
        UpdateCameraVectors();
    }

    void MoveForward()
    {
        Vector3 horizontalFront = Vector3(front.x, 0.0f, front.z).Normalized();
        pos += horizontalFront * CAMERA_MOVEMENT_SPEED;
    }

    void MoveBackward()
    {
        Vector3 horizontalFront = Vector3(front.x, 0.0f, front.z).Normalized();
        pos -= horizontalFront * CAMERA_MOVEMENT_SPEED;
    }

    void MoveLeft()
    {
        pos -= right * CAMERA_MOVEMENT_SPEED;
    }

    void MoveRight()
    {
        pos += right * CAMERA_MOVEMENT_SPEED;
    }

    void RotateYaw(float angle)
    {
        yaw += angle;
        if (yaw > 360.0f) yaw -= 360.0f;
        if (yaw < 0.0f) yaw += 360.0f;
        UpdateCameraVectors();
    }

    void RotatePitch(float angle)
    {
        pitch += angle;
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
        UpdateCameraVectors();
    }

    void ApplyView()
    {
        Vector3 center = pos + front;
        gluLookAt(pos.x, pos.y, pos.z,
            center.x, center.y, center.z,
            up.x, up.y, up.z);
    }
};
