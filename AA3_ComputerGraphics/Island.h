#pragma once
#include "Object.h"
#include "Lighthouse.h"
#include "Building.h"
#include "Tree.h"
#include <vector>
#include <cmath>
#include <iostream>

class Island : public Object
{
    const Color WATER = Color(0.0f, 0.4f, 0.8f);
    const Color SAND = Color(0.9f, 0.8f, 0.5f);   // playa
    const Color GRASS = Color(0.1f, 0.6f, 0.2f);  // c�sped
    const Color ROCK = Color(0.3f, 0.3f, 0.3f);

    Lighthouse lighthouse;
    Building building;
    std::vector<Tree> trees;
    const int TREES_AMOUNT = 12;

    float waterSize = 10.f;

    Vector3 GetRandomPositionInsideGrass(float minRadius, float maxRadius)
    {
        float minHeight = 0.2f;
        float maxHeight = 0.08f;

        float radius = minRadius + (maxRadius - minRadius) * std::sqrt(static_cast<float>(std::rand()) / RAND_MAX);
        float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.0f * 3.14159265f;

        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);


        float y = minHeight - (radius - minRadius) / (maxRadius - minRadius) * (minHeight - maxHeight);

        return Vector3(x, y, z);
    }
public:
    void Init()
    {
        lighthouse.SetPos(pos + Vector3(0.f, 0.08f, 0.f));
        lighthouse.SetScale(0.1f);
        building.SetPos(GetRandomPositionInsideGrass(0.6f, 1.2f));
        building.SetScale(0.5f);

        for (int i = 0; i < TREES_AMOUNT; i++)
        {
            Tree tree;
            tree.SetScale(0.1f);

            tree.SetPos(GetRandomPositionInsideGrass(0.3f, 1.4f));
            trees.push_back(tree);
        }
    }

    void Render() override
    {
        glPushMatrix();
        ApplyTransformations();

        // --- Water ---
        glPushMatrix();
        SetColor(WATER);
        glTranslatef(0.0f, -1.5f-5.f, 0.0f);
        glScalef(100.0f, waterSize, 100.0f);
        glutSolidCube(1.0);
        glPopMatrix();

        // --- Sand ---
        glPushMatrix();
        SetColor(SAND);
        glTranslatef(0.0f, -2.0f, 0.0f);
        glScalef(10.0f, 2.5f, 10.0f); 
        glutSolidSphere(1.0, 32, 32);
        glPopMatrix();

        // --- Grass ---
        glPushMatrix();
        SetColor(GRASS);
        glTranslatef(0.0f, -1.3f, 0.0f); 
        glScalef(9.0f, 1.8f, 9.0f);     
        glutSolidSphere(1.0, 32, 32);
        glPopMatrix();

        // --- Rock ---
        glPushMatrix();
        glTranslatef(-4.0f, 0.0f, -3.0f);
        SetColor(ROCK);
        glScalef(1.0f, 0.5f, 0.8f);
        glutSolidDodecahedron();
        glPopMatrix();

        glPopMatrix();
    }

    void RenderAllContents()
    {
        Render();
        lighthouse.Render();
        building.Render();
        for (int i = 0;i < trees.size(); i++)
            trees[i].Render();
    }

    Lighthouse GetLighthouse()
    {
        return lighthouse;
    }

    void SetWaterSize(float newSize)
    {
        waterSize = newSize;
    }
};
