#include "Scene.hpp"
#include "Shapes.hpp"

// chnage rotor pos (left of windmill right like that)
const float ROTOR_CX = 1.01f;
const float ROTOR_CY = 1.5f;
const float ROTOR_CZ = 0.0f;

void buildScene(vector<float>& tri, vector<float>& lines)
{
    // floor
    addCuboid(tri, lines, 0.0f, -1.0f, 0.0f,7.0f, 0.1f, 2.0f,0.25f, 0.62f, 0.22f);

    // detailed grass
    addCuboid(tri, lines, 0.0f, -0.94f, 1.85f,7.0f, 0.04f, 0.12f,0.18f, 0.50f, 0.16f);

    addCuboid(tri, lines, 0.0f, -0.94f, -1.85f,7.0f, 0.04f, 0.12f,0.18f, 0.50f, 0.16f);

    // walls 
    addCuboid(tri, lines, 0.0f, -0.65f,  2.15f,7.15f, 0.30f, 0.12f, 0.22f, 0.12f, 0.08f);

    addCuboid(tri, lines, 0.0f, -0.65f, -2.15f,7.15f, 0.30f, 0.12f, 0.22f, 0.12f, 0.08f);

    addCuboid(tri, lines, -7.15f, -0.65f, 0.0f,0.12f, 0.30f, 2.15f, 0.22f, 0.12f, 0.08f);

    addCuboid(tri, lines,  7.15f, -0.65f, 0.0f,0.12f, 0.30f, 2.15f, 0.22f, 0.12f, 0.08f);

    // red border on walls
    addCuboid(tri, lines, 0.0f, -0.32f,  2.15f, 7.15f, 0.03f, 0.15f,0.72f, 0.12f, 0.10f);

    addCuboid(tri, lines, 0.0f, -0.32f, -2.15f,7.15f, 0.03f, 0.15f,0.72f, 0.12f, 0.10f);

    addCuboid(tri, lines, -7.15f, -0.32f, 0.0f,0.15f, 0.03f, 2.15f,0.72f, 0.12f, 0.10f);

    addCuboid(tri, lines,  7.15f, -0.32f, 0.0f, 0.15f, 0.03f, 2.15f, 0.72f, 0.12f, 0.10f);

    // mat
    addCuboid(tri, lines, -5.5f, -0.87f, 0.0f,0.82f, 0.018f, 0.82f, 0.20f, 0.10f, 0.06f);

    // 2nd layer of mac
    addCuboid(tri, lines, -5.5f, -0.86f, 0.0f, 0.70f, 0.025f, 0.70f, 0.82f, 0.72f, 0.48f);

    // Hole depression
    addCylinder(tri, lines, 5.8f, -0.96f, 0.0f, 0.28f, 0.03f, 12, 0.15f, 0.42f, 0.15f);

    // Hole 
    addCylinder(tri, lines, 5.8f, -0.95f, 0.0f,0.18f, 0.06f, 12,0.05f, 0.05f, 0.05f);

    // Flag hole
    addCylinder(tri, lines, 5.8f, -0.30f, 0.0f,0.025f, 0.65f, 8,0.55f, 0.60f, 0.30f);

    // inty red triangle for flag
    addTriangularPrism(tri, lines,5.8f,  0.35f,5.8f,  0.15f,6.15f, 0.25f, 0.0f, 0.02f, 0.82f, 0.10f, 0.10f);

    // golf ball on mat
    addSphere(tri, lines, -5.5f, -0.78f, 0.0f,0.08f, 8, 10,0.96f, 0.96f, 0.96f);


    // tori gate creation
    // L pillar
    addCylinder(tri, lines, -4.2f, -0.15f, 2.55f, 0.08f, 0.70f, 10, 0.78f, 0.10f, 0.08f);

    // R pillar
    addCylinder(tri, lines, -4.2f, -0.15f, 3.45f, 0.08f, 0.70f, 10, 0.78f, 0.10f, 0.08f);

    // Top bar
    addCuboid(tri, lines, -4.2f, 0.55f, 3.0f, 0.12f, 0.06f, 0.60f, 0.82f, 0.12f, 0.08f);

    // lower bar
    addCuboid(tri, lines, -4.2f, 0.30f, 3.0f, 0.05f, 0.04f, 0.48f, 0.82f, 0.12f, 0.08f);

    // roof
    addTriangularPrism(tri, lines, -4.32f, 0.61f, -4.08f, 0.61f, -4.20f, 0.72f, 3.0f, 0.62f, 0.22f, 0.12f, 0.08f);

    // Tree 1 
    addCylinder(tri, lines, -6.2f, -0.30f, 3.0f, 0.08f, 0.55f, 10, 0.35f, 0.20f, 0.12f);

    // add more spheres to tree 
    addSphere(tri, lines, -6.2f, 0.45f, 3.0f, 0.50f, 8, 10, 0.95f, 0.65f, 0.72f);
    addSphere(tri, lines, -6.0f, 0.60f, 3.2f, 0.35f, 7, 8, 0.97f, 0.72f, 0.78f);
    addSphere(tri, lines, -6.4f, 0.55f, 2.7f, 0.30f, 7, 8, 0.93f, 0.60f, 0.68f);

    // Tree 2 
    addCylinder(tri, lines, 5.8f, -0.30f, -3.0f, 0.07f, 0.55f, 10, 0.35f, 0.20f, 0.12f);
    addSphere(tri, lines, 5.8f, 0.45f, -3.0f, 0.45f, 8, 10, 0.95f, 0.65f, 0.72f);
    addSphere(tri, lines, 6.0f, 0.55f, -2.8f, 0.30f, 7, 8, 0.97f, 0.72f, 0.78f);

    // Tree 3 
    addCylinder(tri, lines, 3.0f, -0.35f, -3.0f, 0.06f, 0.45f, 10, 0.35f, 0.20f, 0.12f);
    addSphere(tri, lines, 3.0f, 0.30f, -3.0f, 0.40f, 8, 10, 0.97f, 0.72f, 0.78f);

    // Bamboos
    addCylinder(tri, lines, -6.5f, 0.0f, -2.5f, 0.04f, 0.85f, 8, 0.35f, 0.58f, 0.22f);
    addCylinder(tri, lines, -6.3f, -0.10f, -2.7f, 0.035f, 0.75f, 8, 0.38f, 0.62f, 0.25f);
    addCylinder(tri, lines, -6.6f, -0.05f, -2.3f, 0.03f, 0.80f, 8, 0.32f, 0.55f, 0.20f);
    addCylinder(tri, lines, -6.4f, -0.15f, -2.9f, 0.035f, 0.70f, 8, 0.40f, 0.60f, 0.28f);

    // Bamboo cone at the top
    addCone(tri, lines, -6.5f, 0.85f, -2.5f, 0.15f, 0.25f, 8, 0.30f, 0.55f, 0.18f);
    addCone(tri, lines, -6.3f, 0.65f, -2.7f, 0.12f, 0.22f, 8, 0.32f, 0.58f, 0.20f);
    addCone(tri, lines, -6.6f, 0.75f, -2.3f, 0.10f, 0.20f, 8, 0.28f, 0.52f, 0.16f);


    // tiny rocks all over the course
    addSphere(tri, lines, 2.0f, -0.88f, 1.6f, 0.10f, 6, 8, 0.45f, 0.43f, 0.40f);
    addSphere(tri, lines, 2.15f, -0.90f, 1.75f, 0.07f, 5, 6, 0.50f, 0.48f, 0.45f);
    addSphere(tri, lines, -5.0f, -0.88f, -1.5f, 0.09f, 6, 8, 0.48f, 0.46f, 0.42f);

    // windmill stuff now

    //bottom lvl
    addCuboid(tri, lines, 0.0f, -0.55f, 0.0f, 1.30f, 0.35f, 1.60f, 0.78f, 0.70f, 0.52f);

    // 2nd lvl
    addCuboid(tri, lines, 0.0f, 0.00f, 0.0f, 1.10f, 0.20f, 1.35f, 0.76f, 0.68f, 0.50f);

    // 3lvl
    addCuboid(tri, lines, 0.0f, 0.32f, 0.0f, 0.90f, 0.18f, 1.10f, 0.74f, 0.66f, 0.48f);

    // 4th lvl
    addCuboid(tri, lines, 0.0f, 0.60f, 0.0f, 0.70f, 0.15f, 0.86f, 0.72f, 0.64f, 0.46f);

    // 5th lvl
    addCuboid(tri, lines, 0.0f, 0.85f, 0.0f, 0.52f, 0.13f, 0.64f, 0.70f, 0.62f, 0.44f);

    // grey borders on top of each layer
    addCuboid(tri, lines, 0.0f, -0.19f, 0.0f, 1.15f, 0.02f, 1.40f, 0.52f, 0.55f, 0.62f);
    addCuboid(tri, lines, 0.0f, 0.20f, 0.0f, 0.95f, 0.02f, 1.16f, 0.52f, 0.55f, 0.62f);
    addCuboid(tri, lines, 0.0f, 0.50f, 0.0f, 0.75f, 0.02f, 0.92f, 0.52f, 0.55f, 0.62f);
    addCuboid(tri, lines, 0.0f, 0.72f, 0.0f,0.56f, 0.02f, 0.68f,0.82f, 0.72f, 0.38f);

    // roof
    addCone(tri, lines, 0.0f, 0.98f, 0.0f, 0.55f, 0.85f, 12, 0.52f, 0.55f, 0.60f);

    //roof cone
    addCone(tri, lines, 0.0f, 1.78f, 0.0f, 0.08f, 0.18f, 8,0.38f, 0.25f, 0.12f);

    //tunnel 
    addCuboid(tri, lines, 0.0f, -0.55f, 0.0f, 1.35f, 0.22f, 0.42f, 0.10f, 0.10f, 0.12f);
    addCylinder(tri, lines, 1.31f, -0.33f, 0.0f, 0.22f, 0.01f, 8, 0.62f, 0.55f, 0.42f);

}

void buildRotor(vector<float>& tri, vector<float>& lines)
{
    // axle rod
    addCylinderX(tri, lines, ROTOR_CX, ROTOR_CY, ROTOR_CZ, 0.10f, 0.22f, 10, 0.65f, 0.65f, 0.70f);

    // Centre piece
    addCylinderX(tri, lines, ROTOR_CX + 0.05f, ROTOR_CY, ROTOR_CZ, 0.14f, 0.06f, 10, 0.55f, 0.55f, 0.58f);

    // windmill blades

    // up blade
    // outer blade
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY + 0.85f, ROTOR_CZ, 0.02f, 0.70f, 0.03f, 0.55f, 0.35f, 0.18f);
    // inner blade
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY + 0.85f, ROTOR_CZ + 0.14f, 0.015f, 0.62f, 0.10f, 0.92f, 0.88f, 0.78f);
    // Cross bars
    addCuboid(tri, lines,ROTOR_CX + 0.08f, ROTOR_CY + 0.45f, ROTOR_CZ + 0.08f, 0.015f, 0.015f, 0.10f, 0.50f, 0.32f, 0.15f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY + 0.85f, ROTOR_CZ + 0.08f, 0.015f, 0.015f, 0.10f, 0.50f, 0.32f, 0.15f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY + 1.25f, ROTOR_CZ + 0.08f, 0.015f, 0.015f, 0.10f, 0.50f, 0.32f, 0.15f);

    // down blade
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY - 0.85f, ROTOR_CZ, 0.02f, 0.70f, 0.03f, 0.55f, 0.35f, 0.18f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY - 0.85f, ROTOR_CZ - 0.14f, 0.015f, 0.62f, 0.10f, 0.92f, 0.88f, 0.78f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY - 0.45f, ROTOR_CZ - 0.08f, 0.015f, 0.015f, 0.10f, 0.50f, 0.32f, 0.15f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY - 0.85f, ROTOR_CZ - 0.08f, 0.015f, 0.015f, 0.10f, 0.50f, 0.32f, 0.15f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY - 1.25f, ROTOR_CZ - 0.08f, 0.015f, 0.015f, 0.10f, 0.50f, 0.32f, 0.15f);

    // right blade
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY, ROTOR_CZ + 0.85f, 0.02f, 0.03f, 0.70f, 0.55f, 0.35f, 0.18f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY - 0.14f, ROTOR_CZ + 0.85f, 0.015f, 0.10f, 0.62f, 0.92f, 0.88f, 0.78f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY - 0.08f, ROTOR_CZ + 0.45f, 0.015f, 0.10f, 0.015f, 0.50f, 0.32f, 0.15f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY - 0.08f, ROTOR_CZ + 0.85f, 0.015f, 0.10f, 0.015f, 0.50f, 0.32f, 0.15f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY - 0.08f, ROTOR_CZ + 1.25f, 0.015f, 0.10f, 0.015f, 0.50f, 0.32f, 0.15f);

    // left blade
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY, ROTOR_CZ - 0.85f, 0.02f, 0.03f, 0.70f, 0.55f, 0.35f, 0.18f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY + 0.14f, ROTOR_CZ - 0.85f, 0.015f, 0.10f, 0.62f, 0.92f, 0.88f, 0.78f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY + 0.08f, ROTOR_CZ - 0.45f, 0.015f, 0.10f, 0.015f, 0.50f, 0.32f, 0.15f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY + 0.08f, ROTOR_CZ - 0.85f, 0.015f, 0.10f, 0.015f, 0.50f, 0.32f, 0.15f);
    addCuboid(tri, lines, ROTOR_CX + 0.08f, ROTOR_CY + 0.08f, ROTOR_CZ - 1.25f, 0.015f, 0.10f, 0.015f, 0.50f, 0.32f, 0.15f);
}