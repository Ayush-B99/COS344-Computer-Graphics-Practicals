#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>
using namespace std;

void addVertex(vector<float>& v, float x, float y, float z, float r, float g, float b);

void addLine(vector<float>& v, float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b);

void addTriangle(vector<float>& v, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3,
float r, float g, float b);

void addCuboid(vector<float>& tri, vector<float>& lines, float cx, float cy, float cz, float hx, float hy, float hz,
float r, float g, float b);

void addCylinder(vector<float>& tri, vector<float>& lines, float cx, float cy, float cz, float radius, float halfHeight, int segments,
float r, float g, float b);

void addCylinderZ(vector<float>& tri, vector<float>& lines, float cx, float cy, float cz, float radius, float halfDepth, int segments,
float r, float g, float b);

void addCone(vector<float>& tri, vector<float>& lines, float cx, float cy, float cz, float radius, float height, int segments,
float r, float g, float b);

void addTriangularPrism(vector<float>& tri, vector<float>& lines, float x0, float y0, float x1, float y1, float x2, float y2,
float cz, float hd, float r, float g, float b);

void addCylinderX(vector<float>& tri, vector<float>& lines, float cx, float cy, float cz, float radius, float halfDepth, int segments,
float r, float g, float b);

void addTriangularPrismAlongX(vector<float>& tri, vector<float>& lines, float y0, float z0, float y1, float z1, float y2, float z2,
float cx, float hd, float r, float g, float b);

void addSphere(vector<float>& tri, vector<float>& lines, float cx, float cy, float cz, float radius, int rings, int sectors,
float r, float g, float b);

void addFlatQuad(vector<float>& tri, vector<float>& lines, float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2,
float x3, float y3, float z3, float r, float g, float b);

#endif