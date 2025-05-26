#include <GL/glut.h>
#include "Sun.h"
#include "Moon.h"
#include "Island.h"
#include "Pin.h"
#include <conio.h>

struct Angles
{
    float alpha = 0;
    float delta = 0.1;
    float beta = 0;
};

Angles defaultView = { 0, 0.86776, -275 };
Angles downView = { -5, 0.86776, -360 };
Angles topView = { 15, 0.780984, -375 };
Angles cameraAngles = defaultView;

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
    float circleRadiusPin = 0.03f;
    float coneHeightPin = 0.07f;


    glPushAttrib(GL_VIEWPORT_BIT);  // Guarda el viewport original
    glViewport(600, 600, 200, 200); // Minimapa en esquina superior derecha
    

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 100.0); // Proyección con perspectiva

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Cámara desde arriba mirando hacia abajo
    gluLookAt(
        0.0, 5.0, 0.0,   // posición de la cámara (elevada)
        0.0, 0.0, 0.0,    // hacia dónde mira
        0.0, 0.0, 1.0     // "arriba" es hacia el eje Z
    );

    drawObjects(); // Renderiza sin transformaciones de cámara
    pin.drawMapPin(circleRadiusPin, coneHeightPin, colorPlayerPin);
    
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
    glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);

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

    // --- Cámara principal ---
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glRotatef(cameraAngles.beta, 0, 1, 0);
    glRotatef(cameraAngles.alpha, 1, 0, 0);
    glScalef(cameraAngles.delta, cameraAngles.delta, cameraAngles.delta);

    lighting(); // <- ahora aquí, después de colocar la cámara principal

    // Materiales
    float diffuse[4] = { 0.65f, 0.0f, 0.0f, 1.0f };
    float specular[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
    float shininess = 1;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    island.RenderAllContents();
    sun.Render();
    moon.Render();

    glPopMatrix();

    // --- Minimapa ---
    renderMinimap();

    glFlush();
}


void keyPressed_special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        cameraAngles = defaultView;
        island.SetWaterSize(10.f);
        break;
    case GLUT_KEY_RIGHT:
        cameraAngles = topView;
        island.SetWaterSize(10.f);
        break;
    case GLUT_KEY_DOWN:
        cameraAngles = downView;
        island.SetWaterSize(3.5f);
        break;
    }

    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y)
{
    if (key == 'e' || key == 'E') 
    {
        island.GetLighthouse().activeLighthouse = !island.GetLighthouse().activeLighthouse;
    }

    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Illumination model");

    init();
    glutDisplayFunc(display);
    glutSpecialFunc(keyPressed_special);
    glutKeyboardFunc(keyPressed);
    glutTimerFunc(100, timer, 0);
    glutMainLoop();

    return 0;
}
