#include "Shapes.hpp"
#include <cmath>

void addVertex(vector<float>& v, float x, float y, float z, float r, float g, float b) {
    v.push_back(x); 
    v.push_back(y); 
    v.push_back(z);
    v.push_back(r); 
    v.push_back(g); 
    v.push_back(b);
}

void addLine(vector<float>& v, float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b) {
    addVertex(v, x1, y1, z1, r, g, b);
    addVertex(v, x2, y2, z2, r, g, b);
}

void addTriangle(vector<float>& v, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float r, float g, float b) {
    addVertex(v, x1, y1, z1, r, g, b);
    addVertex(v, x2, y2, z2, r, g, b);
    addVertex(v, x3, y3, z3, r, g, b);
}

void addCuboid(vector<float>& tri, vector<float>& lines, float cx, float cy, float cz, float hx, float hy, float hz, float r, float g, float b) {
    float x0 = cx - hx, x1c = cx + hx;
    float y0 = cy - hy, y1c = cy + hy;
    float z0 = cz - hz, z1c = cz + hz;

    float vx[8] = {x0, x1c, x1c, x0, x0, x1c, x1c, x0};
    float vy[8] = {y0, y0,  y1c, y1c, y0, y0,  y1c, y1c};
    float vz[8] = {z1c,z1c, z1c, z1c, z0, z0,  z0,  z0};

    int faces[6][4] = 
    {
        {0,1,2,3},
        {5,4,7,6},
        {4,0,3,7},
        {1,5,6,2},
        {3,2,6,7},
        {4,5,1,0}
    };

    for (int f = 0; f < 6; f++) 
    {
        int i0 = faces[f][0], i1 = faces[f][1], i2 = faces[f][2], i3 = faces[f][3];
        addTriangle(tri, vx[i0],vy[i0],vz[i0], vx[i1],vy[i1],vz[i1], vx[i2],vy[i2],vz[i2], r,g,b);
        addTriangle(tri, vx[i0],vy[i0],vz[i0], vx[i2],vy[i2],vz[i2], vx[i3],vy[i3],vz[i3], r,g,b);
    }

    int edges[12][2] = 
    {
        {0,1},{1,2},{2,3},{3,0},
        {4,5},{5,6},{6,7},{7,4},
        {0,4},{1,5},{2,6},{3,7}
    };

    for (int e = 0; e < 12; e++) 
    {
        int i0 = edges[e][0], i1 = edges[e][1];
        addLine(lines, vx[i0],vy[i0],vz[i0], vx[i1],vy[i1],vz[i1], r,g,b);
    }
}

void addCylinder(vector<float>& tri, vector<float>& lines,float cx, float cy, float cz,float radius, float halfHeight, int segments,
float r, float g, float b) {
    float topY = cy + halfHeight;
    float botY = cy - halfHeight;

    vector<float> cosA(segments), sinA(segments);
    for (int i = 0; i < segments; i++) 
    {
        float angle = 2.0f * M_PI * i / segments;
        cosA[i] = cos(angle);
        sinA[i] = sin(angle);
    }

    for (int i = 0; i < segments; i++) 
    {
        int next = (i + 1) % segments;
        float px0 = cx + radius * cosA[i],   pz0 = cz + radius * sinA[i];
        float px1 = cx + radius * cosA[next], pz1 = cz + radius * sinA[next];

        addTriangle(tri, cx, topY, cz, px0, topY, pz0, px1, topY, pz1, r, g, b);
        addTriangle(tri, cx, botY, cz, px1, botY, pz1, px0, botY, pz0, r, g, b);
        addTriangle(tri, px0, botY, pz0, px1, botY, pz1, px1, topY, pz1, r, g, b);
        addTriangle(tri, px0, botY, pz0, px1, topY, pz1, px0, topY, pz0, r, g, b);

        addLine(lines, px0, topY, pz0, px1, topY, pz1, r, g, b);
        addLine(lines, px0, botY, pz0, px1, botY, pz1, r, g, b);
        addLine(lines, px0, topY, pz0, px0, botY, pz0, r, g, b);
    }
}

void addCylinderZ(vector<float>& tri, vector<float>& lines, float cx, float cy, float cz, float radius, float halfDepth, int segments,
float r, float g, float b) {
    float frontZ = cz + halfDepth;
    float backZ  = cz - halfDepth;

    vector<float> cosA(segments), sinA(segments);
    for (int i = 0; i < segments; i++) 
    {
        float angle = 2.0f * M_PI * i / segments;
        cosA[i] = cos(angle);
        sinA[i] = sin(angle);
    }

    for (int i = 0; i < segments; i++) 
    {
        int next = (i + 1) % segments;
        float px0 = cx + radius * cosA[i],   py0 = cy + radius * sinA[i];
        float px1 = cx + radius * cosA[next], py1 = cy + radius * sinA[next];

        addTriangle(tri, cx, cy, frontZ, px0, py0, frontZ, px1, py1, frontZ, r, g, b);
        addTriangle(tri, cx, cy, backZ, px1, py1, backZ, px0, py0, backZ, r, g, b);
        addTriangle(tri, px0, py0, backZ, px1, py1, backZ, px1, py1, frontZ, r, g, b);
        addTriangle(tri, px0, py0, backZ, px1, py1, frontZ, px0, py0, frontZ, r, g, b);

        addLine(lines, px0, py0, frontZ, px1, py1, frontZ, r, g, b);
        addLine(lines, px0, py0, backZ,  px1, py1, backZ,  r, g, b);
        addLine(lines, px0, py0, frontZ, px0, py0, backZ,  r, g, b);
    }
}

void addCone(vector<float>& tri, vector<float>& lines, float cx, float cy, float cz, float radius, float height, int segments,
float r, float g, float b) {
    float tipY = cy + height;

    vector<float> cosA(segments), sinA(segments);
    for (int i = 0; i < segments; i++) 
    {
        float angle = 2.0f * M_PI * i / segments;
        cosA[i] = cos(angle);
        sinA[i] = sin(angle);
    }

    for (int i = 0; i < segments; i++) 
    {
        int next = (i + 1) % segments;
        float px0 = cx + radius * cosA[i],   pz0 = cz + radius * sinA[i];
        float px1 = cx + radius * cosA[next], pz1 = cz + radius * sinA[next];

        addTriangle(tri, cx, cy, cz, px1, cy, pz1, px0, cy, pz0, r, g, b);
        addTriangle(tri, cx, tipY, cz, px0, cy, pz0, px1, cy, pz1, r, g, b);

        addLine(lines, px0, cy, pz0, px1, cy, pz1, r, g, b);
        addLine(lines, px0, cy, pz0, cx, tipY, cz, r, g, b);
    }
}

void addTriangularPrism(vector<float>& tri, vector<float>& lines, float x0, float y0, float x1, float y1, float x2, float y2,
float cz, float hd, float r, float g, float b) {
    float zf = cz + hd;
    float zb = cz - hd;

    addTriangle(tri, x0,y0,zf, x1,y1,zf, x2,y2,zf, r,g,b);
    addTriangle(tri, x0,y0,zb, x2,y2,zb, x1,y1,zb, r,g,b);

    float px[3] = {x0, x1, x2};
    float py[3] = {y0, y1, y2};

    for (int i = 0; i < 3; i++) 
    {
        int j = (i + 1) % 3;
        addTriangle(tri, px[i],py[i],zf, px[j],py[j],zf, px[j],py[j],zb, r,g,b);
        addTriangle(tri, px[i],py[i],zf, px[j],py[j],zb, px[i],py[i],zb, r,g,b);
    }

    for (int i = 0; i < 3; i++) 
    {
        int j = (i + 1) % 3;
        addLine(lines, px[i],py[i],zf, px[j],py[j],zf, r,g,b);
        addLine(lines, px[i],py[i],zb, px[j],py[j],zb, r,g,b);
        addLine(lines, px[i],py[i],zf, px[i],py[i],zb, r,g,b);
    }
}

// Cylinder along X axis
void addCylinderX(vector<float>& tri, vector<float>& lines,float cx, float cy, float cz, float radius, float halfDepth, int segments,
float r, float g, float b) {
    float rightX = cx + halfDepth;
    float leftX  = cx - halfDepth;

    vector<float> cosA(segments), sinA(segments);
    for (int i = 0; i < segments; i++) 
    {
        float angle = 2.0f * M_PI * i / segments;
        cosA[i] = cos(angle);
        sinA[i] = sin(angle);
    }

    for (int i = 0; i < segments; i++)
    {
        int next = (i + 1) % segments;
        float py0 = cy + radius * cosA[i],   pz0 = cz + radius * sinA[i];
        float py1 = cy + radius * cosA[next], pz1 = cz + radius * sinA[next];

        // Right cap
        addTriangle(tri, rightX, cy, cz, rightX, py0, pz0, rightX, py1, pz1, r, g, b);
        // Left cap
        addTriangle(tri, leftX, cy, cz, leftX, py1, pz1, leftX, py0, pz0, r, g, b);
        // Side
        addTriangle(tri, leftX, py0, pz0, leftX, py1, pz1, rightX, py1, pz1, r, g, b);
        addTriangle(tri, leftX, py0, pz0, rightX, py1, pz1, rightX, py0, pz0, r, g, b);

        addLine(lines, rightX, py0, pz0, rightX, py1, pz1, r, g, b);
        addLine(lines, leftX, py0, pz0, leftX, py1, pz1, r, g, b);
        addLine(lines, rightX, py0, pz0, leftX, py0, pz0, r, g, b);
    }
}

// Triangular prism with triangle in YZ plane, extruded along X
void addTriangularPrismAlongX(vector<float>& tri, vector<float>& lines, float y0, float z0, float y1, float z1, float y2, float z2,
float cx, float hd, float r, float g, float b) {
    float xr = cx + hd;
    float xl = cx - hd;

    // triangle cpas
    addTriangle(tri, xr,y0,z0, xr,y1,z1, xr,y2,z2, r,g,b);
    addTriangle(tri, xl,y0,z0, xl,y2,z2, xl,y1,z1, r,g,b);

    // 3 rectangle sides
    float py[3] = {y0, y1, y2};
    float pz[3] = {z0, z1, z2};
    for (int i = 0; i < 3; i++) 
    {
        int j = (i + 1) % 3;
        addTriangle(tri, xr,py[i],pz[i], xr,py[j],pz[j], xl,py[j],pz[j], r,g,b);
        addTriangle(tri, xr,py[i],pz[i], xl,py[j],pz[j], xl,py[i],pz[i], r,g,b);
    }

    // wireframe edges
    for (int i = 0; i < 3; i++) 
    {
        int j = (i + 1) % 3;
        addLine(lines, xr,py[i],pz[i], xr,py[j],pz[j], r,g,b);
        addLine(lines, xl,py[i],pz[i], xl,py[j],pz[j], r,g,b);
        addLine(lines, xr,py[i],pz[i], xl,py[i],pz[i], r,g,b);
    }
}

void addSphere(vector<float>& tri, vector<float>& lines, float cx, float cy, float cz, float radius, int rings, int sectors,
float r, float g, float b) {
    vector<float> px, py, pz;
    for (int i = 0; i <= rings; i++) 
    {
        float phi = M_PI * i / rings;
        float sp = sin(phi);
        float cp = cos(phi);
        for (int j = 0; j <= sectors; j++) 
        {
            float theta = 2.0f * M_PI * j / sectors;
            float st = sin(theta);
            float ct = cos(theta);
            px.push_back(cx + radius * sp * ct);
            py.push_back(cy + radius * cp);
            pz.push_back(cz + radius * sp * st);
        }
    }

    for (int i = 0; i < rings; i++) 
    {
        for (int j = 0; j < sectors; j++) 
        {
            int a = i * (sectors + 1) + j;
            int b2 = a + sectors + 1;
            int c = a + 1;
            int d = b2 + 1;

            addTriangle(tri, px[a],py[a],pz[a], px[b2],py[b2],pz[b2], px[c],py[c],pz[c], r,g,b);
            addTriangle(tri, px[c],py[c],pz[c], px[b2],py[b2],pz[b2], px[d],py[d],pz[d], r,g,b);

            addLine(lines, px[a],py[a],pz[a], px[c],py[c],pz[c], r,g,b);
            addLine(lines, px[a],py[a],pz[a], px[b2],py[b2],pz[b2], r,g,b);
        }
    }
}

void addFlatQuad(vector<float>& tri, vector<float>& lines, float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2,
float x3, float y3, float z3, float r, float g, float b) {
    addTriangle(tri, x0,y0,z0, x1,y1,z1, x2,y2,z2, r,g,b);
    addTriangle(tri, x0,y0,z0, x2,y2,z2, x3,y3,z3, r,g,b);
    
    addLine(lines, x0,y0,z0, x1,y1,z1, r,g,b);
    addLine(lines, x1,y1,z1, x2,y2,z2, r,g,b);
    addLine(lines, x2,y2,z2, x3,y3,z3, r,g,b);
    addLine(lines, x3,y3,z3, x0,y0,z0, r,g,b);
}