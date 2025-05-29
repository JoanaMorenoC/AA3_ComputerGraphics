#pragma once
#define _USE_MATH_DEFINES

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
    const int TREES_AMOUNT = 20;

    float waterSize = 10.f;
    Vector3 rockScale;

    std::vector<CylinderCollider*> treeColliders;

    Vector3 GetRandomPositionInsideGrass(float height, float minRadius, float maxRadius)
    {
        float radius = minRadius + (maxRadius - minRadius) * std::sqrt(static_cast<float>(std::rand()) / RAND_MAX);
        float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.0f * 3.14159265f;

        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);
        float y = height;

        return Vector3(x, y, z);
    }
public:
    void Init(float totalScale)
    {
        SetScale(totalScale * 0.2f);

        float islandFloorHeight = totalScale * 0.1f;
        lighthouse.SetPos(pos + Vector3(0.f, islandFloorHeight, 0.f));
        lighthouse.SetScale(totalScale * 0.1f);
        building.SetPos(GetRandomPositionInsideGrass(islandFloorHeight, totalScale * 0.6f, totalScale * 1.2f));
        building.SetScale(totalScale * 0.5f);
        rockScale = Vector3(1.0f, 0.5f, 0.8f);

        for (int i = 0; i < TREES_AMOUNT; i++)
        {
            trees.emplace_back(); // agrega el árbol directamente en el vector
            trees.back().SetScale(totalScale * 0.06f);
            trees.back().SetPos(GetRandomPositionInsideGrass(islandFloorHeight, totalScale * 0.3f, totalScale * 1.4f));
            treeColliders.push_back(trees.back().GetCollider());
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
        DrawClosedCylinder(1.0, 1.0, 1.0, 32, 32);
        glPopMatrix();

        // --- Grass ---
        glPushMatrix();
        SetColor(GRASS);
        glTranslatef(0.0f, -1.3f, 0.0f); 
        glScalef(9.0f, 1.8f, 9.0f);     
        DrawClosedCylinder(1.0, 1.0, 1.01, 32, 32);
        glPopMatrix();

        // --- Rock ---
        glPushMatrix();
        glTranslatef(-4.0f, 0.0f, -3.0f);
        SetColor(ROCK);
        glScalef(rockScale.x, rockScale.y, rockScale.z);
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

    std::vector<CylinderCollider*> GetTreeColliders()
    {
        return treeColliders;
    }

    void SetWaterSize(float newSize)
    {
        waterSize = newSize;
    }
};
