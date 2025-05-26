#include <GL/glut.h>
#include "Camera.h"
#include "Sun.h"
#include "Moon.h"
#include "Island.h"

Camera camera;

Island island;
Lighthouse lighthouse;
Sun sun;
Moon moon;

bool keyStates[256] = { false };
bool specialKeyStates[256] = { false };
bool shiftPressed = false;

const float CAMERA_ROTATION_SPEED = 1.f;

void updateCamera()
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
}

void dayNightCycleTimer(int value)
{
    sun.Rotate();
    moon.Rotate();

    glutPostRedisplay();
    glutTimerFunc(50, dayNightCycleTimer, 0);
}

void gameplayTimer(int value)
{
    updateCamera();
    glutPostRedisplay();
    glutTimerFunc(16, gameplayTimer, 0);
}

void lighting()
{
    sun.Lighting();
    moon.Lighting();
    island.GetLighthouse().light();
}

int init(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1280.0 / 720.0, 1.0, 100.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    sun.InitLighting();
    moon.InitLighting();

    island.Init();
    island.SetScale(0.2f);

    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    lighting();


    float diffuse[4] = { 0.65f, 0.0f, 0.0f, 1.0f };
    float specular[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
    float shininess = 1;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    camera.ApplyView();

    glPushMatrix();

    island.RenderAllContents();
    sun.Render();
    moon.Render();

    glPopMatrix();

    glFlush();
}

void keyDown(unsigned char key, int x, int y)
{
    keyStates[key] = true;
}

void keyUp(unsigned char key, int x, int y)
{
    keyStates[key] = false;
}

void specialKeyDown(int key, int x, int y)
{
    specialKeyStates[key] = true;
}

void specialKeyUp(int key, int x, int y)
{
    specialKeyStates[key] = false;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Illumination model");

    init();
    glutDisplayFunc(display);

    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(specialKeyUp);

    glutTimerFunc(100, dayNightCycleTimer, 0);
    glutTimerFunc(16, gameplayTimer, 0);

    glutMainLoop();

    return 0;
}
