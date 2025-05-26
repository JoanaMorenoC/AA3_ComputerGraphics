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

void timer(int value)
{
    sun.Rotate();
    moon.Rotate();
    glutPostRedisplay();
    glutTimerFunc(50, timer, 0);
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

void keyPressed(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        camera.moveForward();
        break;
    case 's':
    case 'S':
        camera.moveBackward();
        break;
    case 'a':
    case 'A':
        camera.moveLeft();
        break;
    case 'd':
    case 'D':
        camera.moveRight();
        break;
    }
    glutPostRedisplay();
}

void keyPressed_special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        camera.rotateYaw(-2.0f);
        break;
    case GLUT_KEY_RIGHT:
        camera.rotateYaw(2.0f);
        break;
    case GLUT_KEY_UP:
        camera.rotatePitch(2.0f);
        break;
    case GLUT_KEY_DOWN:
        camera.rotatePitch(-2.0f);
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Illumination model");

    init();
    glutDisplayFunc(display);
    glutSpecialFunc(keyPressed_special);
    glutTimerFunc(100, timer, 0);
    glutMainLoop();

    return 0;
}
