#include "RasterizationProcessor.h"
#include "Vector2.h"
#include <algorithm>
#include<iostream>
struct gradients {
    gradients(Triangle4 triangle);
    float oneOverW[3];
    float uOverW[3];
    float vOverW[3];
    float doneOverWdX, doneOverWdY;
    float duOverWdX, duOverWdY;
    float dvOverWdX, dvOverWdY;
};
gradients::gradients(Triangle4 triangle)
{
    float oneOverdX = 1 / (((triangle[1].x - triangle[2].x) * (triangle[0].y - triangle[2].y)) -
        ((triangle[0].x - triangle[2].x) * (triangle[1].y - triangle[2].y)));

    float oneOverdY = -oneOverdX;

    for (int i = 0; i < 3; i++)
    {
        oneOverW[i] = 1 / triangle[i].w;
        uOverW[i] = triangle[i].u * oneOverW[i];
        vOverW[i] = triangle[i].v * oneOverW[i];
    }

    doneOverWdX = oneOverdX * (((oneOverW[1] - oneOverW[2]) * (triangle[0].y - triangle[2].y)) -
        ((oneOverW[0] - oneOverW[2]) * (triangle[1].y - triangle[2].y)));

    doneOverWdY = oneOverdY * (((oneOverW[1] - oneOverW[2]) * (triangle[0].x - triangle[2].x)) -
        ((oneOverW[0] - oneOverW[2]) * (triangle[1].x - triangle[2].x)));

    duOverWdX = oneOverdX * (((uOverW[1] - uOverW[2]) * (triangle[0].y - triangle[2].y)) -
        ((uOverW[0] - uOverW[2]) * (triangle[1].y - triangle[2].y)));

    duOverWdY = oneOverdY * (((uOverW[1] - uOverW[2]) * (triangle[0].x - triangle[2].x)) -
        ((uOverW[0] - uOverW[2]) * (triangle[1].x - triangle[2].x)));

    dvOverWdX = oneOverdX * (((vOverW[1] - vOverW[2]) * (triangle[0].y - triangle[2].y)) -
        ((vOverW[0] - vOverW[2]) * (triangle[1].y - triangle[2].y)));

    dvOverWdY = oneOverdY * (((vOverW[1] - vOverW[2]) * (triangle[0].x - triangle[2].x)) -
        ((vOverW[0] - vOverW[2]) * (triangle[1].x - triangle[2].x)));

}

struct LineVars {
    LineVars(Vertex4 vertex1, Vertex4 vertex2);
    float uprim;
    float vprim;
    float wprim;
    Vector4 begginingPoint;
    Vector4 endingPoint;
    Vector2 drawnPoint;
    int dx;
    int dy;
    bool isSteep;
    float pk;
    int i;
    float z;
};
LineVars::LineVars(Vertex4 vertex1, Vertex4 vertex2) {
    begginingPoint = Vector4((int)vertex1.x, (int)vertex1.y, vertex1.z,vertex1.w);
    endingPoint = Vector4((int)vertex2.x, (int)vertex2.y, vertex2.z,vertex1.w);
    drawnPoint = begginingPoint;
    dx = abs(endingPoint.x - begginingPoint.x);
    dy = abs(endingPoint.y - begginingPoint.y);
    isSteep = false;
    if (dy > dx) { int temp = dx; dx = dy; dy = temp; isSteep = true; }
    else {
        isSteep = false;
    }
    pk = 2 * dy - dx;
    i = 0;
    z = begginingPoint.z;
    uprim = vertex1.u / vertex1.w;
    vprim = vertex1.v / vertex1.w;
    wprim = 1 / vertex1.w;
}

bool RasterizationProcessor::incrementLine(LineVars& line,const gradients& gra, float dyz, float dxz, SDL_Surface* texture, std::vector<Fragment>& fragments) {
    while( line.i < line.dx)
    {
        if (line.pk < 0) {
            if (line.isSteep) {
                line.drawnPoint.y--;
                line.uprim -= gra.duOverWdY;
                line.vprim -= gra.dvOverWdY;
                line.wprim -= gra.doneOverWdY;
                line.z -= dyz;
                line.pk = line.pk + 2 * line.dy;
                fragments.push_back(Fragment(line.drawnPoint.x, line.drawnPoint.y, line.uprim, line.vprim, line.wprim, line.z, texture));
                line.i++;
                return true;
            }
            else {
                line.endingPoint.x - line.begginingPoint.x > 0 ?
                    (line.drawnPoint.x++, line.z += dxz, line.wprim += gra.doneOverWdX, line.uprim += gra.duOverWdX, line.vprim += gra.dvOverWdX)
                    :
                    (line.drawnPoint.x--, line.z -= dxz, line.wprim -= gra.doneOverWdX, line.uprim -= gra.duOverWdX, line.vprim -= gra.dvOverWdX);
                line.pk = line.pk + 2 * line.dy;
                fragments.push_back(Fragment(line.drawnPoint.x, line.drawnPoint.y, line.uprim, line.vprim, line.wprim, line.z, texture));
                line.i++;
            }
        }
        else {
            line.endingPoint.x - line.begginingPoint.x > 0 ?
                (line.drawnPoint.x++, line.z += dxz, line.wprim += gra.doneOverWdX, line.uprim += gra.duOverWdX, line.vprim += gra.dvOverWdX)
                :
                (line.drawnPoint.x--, line.z -= dxz, line.wprim -= gra.doneOverWdX, line.uprim -= gra.duOverWdX, line.vprim -= gra.dvOverWdX);
            line.drawnPoint.y--;
            line.vprim -= gra.dvOverWdY;
            line.uprim -= gra.duOverWdY;
            line.wprim -= gra.doneOverWdY;
            line.z -= dyz;
            line.pk = line.pk + 2 * line.dy - 2 * line.dx;
            fragments.push_back(Fragment(line.drawnPoint.x, line.drawnPoint.y, line.uprim, line.vprim, line.wprim, line.z, texture));
            line.i++;
            return true;
        };
    }
    return false;
}

void RasterizationProcessor::drawScanLine(const LineVars& line1,const LineVars& line2,const gradients& gra, float dxz, SDL_Surface* texture, std::vector<Fragment>& fragments) {
    float scanw = line1.z;
    float scanuprim = line1.uprim;
    float scanvprim = line1.vprim;
    float scanwprim = line1.wprim;
    
    if (line1.drawnPoint.x < line2.drawnPoint.x) {
        for (int k = line1.drawnPoint.x + 1; k <= (int)line2.drawnPoint.x - 1; k++)
        {
            scanw += dxz, scanuprim += gra.duOverWdX, scanwprim += gra.doneOverWdX, scanvprim += gra.dvOverWdX;
            fragments.push_back(Fragment(k, line2.drawnPoint.y, scanuprim, scanvprim, scanwprim, scanw, texture));
        }
    }
    else {
        for (int k = line1.drawnPoint.x - 1; k >= (int)line2.drawnPoint.x+1; k--)
        {
            scanw -= dxz, scanuprim -= gra.duOverWdX, scanwprim -= gra.doneOverWdX, scanvprim -= gra.dvOverWdX;
            fragments.push_back(Fragment(k, line2.drawnPoint.y, scanuprim, scanvprim, scanwprim, scanw, texture));
        }
    }
};

//this function is slow due to the sheer amount of Fragment structs it needs to create. Add object pooling or smth to fix
std::vector<Fragment>& RasterizationProcessor::rasterizeTriangle(Triangle4& triangle, std::vector<Fragment>& fragments)
{
    fragments.clear();

    //sort vertices by ascending Y order
    std::sort(std::begin(triangle.vertices), std::end(triangle.vertices),
        [](const Vertex4& vertex1, const Vertex4& vertex2) {
            return (vertex1.y < vertex2.y);
        }
    );
    //find plane equation
    Vector3 planeNormal = Vector3::crossProduct(triangle[1] - triangle[0], triangle[2] - triangle[0]).normalized();
    double A = planeNormal.x;
    double B = planeNormal.y;
    double C = planeNormal.z;

    float dyz = -B / C;
    float dxz = -A / C;

    LineVars line1(triangle[2], triangle[0]);
    LineVars line2(triangle[2], triangle[1]);
    gradients gra(triangle);

    while (incrementLine(line2, gra, dyz, dxz,triangle.texture, fragments)) {
        incrementLine(line1, gra, dyz, dxz,triangle.texture, fragments);
        drawScanLine(line1,line2, gra, dxz,triangle.texture, fragments);
    }
    line2 = LineVars(triangle[1], triangle[0]);

    while (incrementLine(line2, gra, dyz, dxz,triangle.texture, fragments)) {
        incrementLine(line1, gra, dyz, dxz,triangle.texture, fragments);
        drawScanLine(line1,line2, gra, dxz,triangle.texture, fragments);
    }

	return fragments;
}
