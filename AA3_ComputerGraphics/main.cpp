#include <GL/glut.h>
#include "Player.h"
#include "Sun.h"
#include "Moon.h"
#include "Island.h"
#include "Pin.h"
#include <conio.h>

Player player;

Island island;
Lighthouse lighthouse;
Sun sun;
Moon moon;

bool keyStates[256] = { false };
bool specialKeyStates[256] = { false };
bool shiftPressed = false;


void dayNightCycleTimer(int value)
{
    sun.Rotate();
    moon.Rotate();

    glutPostRedisplay();
    glutTimerFunc(50, dayNightCycleTimer, 0);
}

void gameplayTimer(int value)
{
    player.Update(keyStates, specialKeyStates, island.GetColliders());
    glutPostRedisplay();
    glutTimerFunc(16, gameplayTimer, 0);
}

void lighting()
{
    sun.Lighting();
    moon.Lighting();
    island.GetLighthouse().light();
}

void drawObjects()
{
    glPushMatrix();
    island.RenderAllContents();
    sun.Render();
    moon.Render();
    glPopMatrix();
}



void renderMinimap()
{
    Pin pin;
    float colorPlayerPin[3] = { 1.f, 0.3, 0.4 };
    float circleRadiusPin = 2.f;
    float coneHeightPin = 0.07f;
    float posXZ[2] = { 0.0f,0.0f };


    glPushAttrib(GL_VIEWPORT_BIT);  // Guarda el viewport original
    glViewport(1280.0-200, 720-200, 200, 200); // Minimapa en esquina superior derecha
    

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 100.0); // Proyecci�n con perspectiva

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // C�mara desde arriba mirando hacia abajo
    gluLookAt(
        0.0, 12.0, 0.0,   // posici�n de la c�mara (elevada)
        0.0, 0.0, 0.0,    // hacia d�nde mira
        0.0, 0.0, 1.0     // "arriba" es hacia el eje Z
    );

    drawObjects(); // Renderiza sin transformaciones de c�mara
    pin.drawMapPin(circleRadiusPin, coneHeightPin, colorPlayerPin, posXZ);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib(); // Restaura el viewport original*/
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
    gluPerspective(45.0, 1280.0 / 720.0, 0.05, 100.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


    sun.InitLighting();
    moon.InitLighting();

    island.Init(3.f);

    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // --- C�mara principal ---
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    lighting(); // <- ahora aqu�, despu�s de colocar la c�mara principal

    // Materiales
    float diffuse[4] = { 0.65f, 0.0f, 0.0f, 1.0f };
    float specular[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
    float shininess = 1;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    player.ApplyView();
    player.ApplyFlashlight();

    glPushMatrix();

    island.RenderAllContents();
    sun.Render();
    moon.Render();

    glPopMatrix();

    // --- Minimapa ---
    renderMinimap();

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
