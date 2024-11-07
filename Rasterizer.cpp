#include "Rasterizer.h"
#include "Triangle2D.h"
#include"Triangle3D.h"
#include <algorithm>
#include<iostream>
#include<mutex>
#include<vector>
#include <chrono>

extern double cameraPLainDistance;
extern int windowHeight;
extern int windowWidth;

//void Rasterizer::drawLine(Vector2 begginingPoint, Vector2 endingPoint) const{
//    //Bresenham's algorythm
//    Vector2 drawnPoint = begginingPoint;
//    int dx = abs(endingPoint.x - begginingPoint.x);
//    int dy = abs(endingPoint.y - begginingPoint.y);
//    bool isSteep = false;
//    if (dy > dx) { int temp = dx; dx = dy; dy = temp; isSteep = true; }
//    else {
//        isSteep = false;
//    }
//    int pk = 2 * dy - dx;
//    windowHandler.drawPoint(drawnPoint, 0xFF, 0x00, 0x00, 0xFF);
//    for (int i = 0; i < dx-1; i++)
//    {
//        if (pk < 0) {
//            if (isSteep)
//                endingPoint.y - begginingPoint.y > 0 ? drawnPoint.y++ : drawnPoint.y--;
//            else
//                endingPoint.x - begginingPoint.x > 0 ? drawnPoint.x++ : drawnPoint.x--;
//            pk = pk + 2 * dy;
//        }
//        else {
//            endingPoint.x - begginingPoint.x > 0 ? drawnPoint.x++ : drawnPoint.x--;
//            endingPoint.y - begginingPoint.y > 0 ? drawnPoint.y++ : drawnPoint.y--;
//            pk = pk + 2 * dy - 2 * dx;
//        };
//        windowHandler.drawPoint(drawnPoint, 0xFF, 0x00, 0x00, 0xFF);
//    }
//    //std::cout << dx<<"\n";
//}

void Rasterizer::drawLine(Vector2 begginingPoint, Vector2 endingPoint) const {
    //Bresenham's algorythm
    Vector2 drawnPoint = begginingPoint;
    int dx = abs(endingPoint.x - begginingPoint.x);
    int dy = abs(endingPoint.y - begginingPoint.y);
    bool isSteep = false;
    if (dy > dx) { int temp = dx; dx = dy; dy = temp; isSteep = true; }
    else {
        isSteep = false;
    }
    int pk = 2 * dy - dx;
    windowHandler.drawPoint(drawnPoint, 0xFF, 0x00, 0x00, 0xFF);

    for (int i = 0; i < dx - 1; i++)
    {
        if (pk < 0) {
            if (isSteep) {
                endingPoint.y - begginingPoint.y > 0 ? drawnPoint.y++ : drawnPoint.y--;
                pk = pk + 2 * dy;
                windowHandler.drawPoint(drawnPoint, 0xFF, 0x00, 0x00, 0xFF);
            }
            else {
                endingPoint.x - begginingPoint.x > 0 ? drawnPoint.x++ : drawnPoint.x--;
                pk = pk + 2 * dy;
                windowHandler.drawPoint(drawnPoint, 0xFF, 0x00, 0x00, 0xFF);
            }
        }
        else {
            endingPoint.x - begginingPoint.x > 0 ? drawnPoint.x++ : drawnPoint.x--;
            endingPoint.y - begginingPoint.y > 0 ? drawnPoint.y++ : drawnPoint.y--;
            pk = pk + 2 * dy - 2 * dx;
            windowHandler.drawPoint(drawnPoint, 0xFF, 0x00, 0x00, 0xFF);
        };
    }
    //std::cout << dx<<"\n";
}

Rasterizer::Rasterizer(WindowHandler& windowHandler):windowHandler(windowHandler)
{
    zbuffer = new float[windowHeight * windowWidth];
    for (int i = 0; i < windowHeight * windowWidth; i++)
    {
        zbuffer[i] = INFINITY;
    }
}

Rasterizer::~Rasterizer()
{
    delete[] zbuffer;
}

void Rasterizer::cleanzbuffer()
{
    for (int i = 0; i < windowHeight * windowWidth; i++)
    {
        zbuffer[i] = INFINITY;
    }
}

void Rasterizer::drawTriangle(Triangle2D triangle) const{
    drawLine(triangle[0], triangle[1]);
    drawLine(triangle[1], triangle[2]);
    drawLine(triangle[2], triangle[0]);
}

Uint32 getpixel(SDL_Surface* surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16*)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32*)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

struct gradients {
    gradients(Triangle3D triangle);
    float oneOverZ[3];
    float uOverZ[3];
    float vOverZ[3];
    float dOneOverZdX, dOneOverZdY;
    float dUOverZdX, dUOverZdY;
    float dVOverZdX, dVOverZdY;
};
gradients::gradients(Triangle3D triangle)
{
    float oneOverdX = 1 / (((triangle[1].x - triangle[2].x) *
        (triangle[0].y - triangle[2].y)) -
        ((triangle[0].x - triangle[2].x) *
        (triangle[1].y - triangle[2].y)));
    float oneOverdY = -oneOverdX;

    for (int i = 0; i < 3; i++)
    {
        oneOverZ[i] = 1 / triangle[i].z;
        uOverZ[i] = triangle[i].u * oneOverZ[i];
        vOverZ[i] = triangle[i].v * oneOverZ[i];
    }

    dOneOverZdX = oneOverdX * (((oneOverZ[1] - oneOverZ[2]) *
        (triangle[0].y - triangle[2].y)) -
        ((oneOverZ[0] - oneOverZ[2]) *
        (triangle[1].y - triangle[2].y)));
    dOneOverZdY = oneOverdY * (((oneOverZ[1] - oneOverZ[2]) *
        (triangle[0].x - triangle[2].x)) -
        ((oneOverZ[0] - oneOverZ[2]) *
        (triangle[1].x - triangle[2].x)));

    dUOverZdX = oneOverdX * (((uOverZ[1] - uOverZ[2]) *
        (triangle[0].y - triangle[2].y)) -
        ((uOverZ[0] - uOverZ[2]) *
        (triangle[1].y - triangle[2].y)));
    dUOverZdY = oneOverdY * (((uOverZ[1] - uOverZ[2]) *
        (triangle[0].x - triangle[2].x)) -
        ((uOverZ[0] - uOverZ[2]) *
        (triangle[1].x - triangle[2].x)));

    dVOverZdX = oneOverdX * (((vOverZ[1] - vOverZ[2]) *
        (triangle[0].y - triangle[2].y)) -
        ((vOverZ[0] - vOverZ[2]) *
        (triangle[1].y - triangle[2].y)));
    dVOverZdY = oneOverdY * (((vOverZ[1] - vOverZ[2]) *
        (triangle[0].x - triangle[2].x)) -
        ((vOverZ[0] - vOverZ[2]) *
        (triangle[1].x - triangle[2].x)));

}

struct LineVars {
    LineVars(Vertex3 vertex1, Vertex3 vertex2);
    float uprim;
    float vprim;
    float zprim;
    Vector3 begginingPoint;
    Vector3 endingPoint;
    Vector2 drawnPoint;
    int dx;
    int dy ;
    bool isSteep;
    float pk;
    int i;
    float z;
};

LineVars::LineVars(Vertex3 vertex1,Vertex3 vertex2) {
    begginingPoint = Vector3((int)vertex1.x, (int)vertex1.y, vertex1.z);
    endingPoint = Vector3((int)vertex2.x, (int)vertex2.y, vertex2.z);
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
    uprim = vertex1.u / vertex1.z;
    vprim = vertex1.v / vertex1.z;
    zprim = 1 / vertex1.z;
}

void Rasterizer::drawScanline(LineVars line1, LineVars line2, gradients gra, float dxz, Triangle3D triangle) {
    float scanz = line1.z;
    float scanuprim = line1.uprim;
    float scanvprim = line1.vprim;
    float scanzprim = line1.zprim;
    SDL_Color rgb;
    Uint32 data = getpixel(triangle.texture, 1, 1);
    SDL_GetRGB(data, triangle.texture->format, &rgb.r, &rgb.g, &rgb.b);
    for (int k = line1.drawnPoint.x; k != (int)line2.drawnPoint.x; line1.drawnPoint.x < line2.drawnPoint.x ? k++ : k--)
    {
        line1.drawnPoint.x < line2.drawnPoint.x ?
            (scanz += dxz, scanuprim += gra.dUOverZdX, scanzprim += gra.dOneOverZdX, scanvprim += gra.dVOverZdX)
            :
            (scanz -= dxz, scanuprim -= gra.dUOverZdX, scanzprim -= gra.dOneOverZdX, scanvprim -= gra.dVOverZdX);

        drawTexuredPointZ(line2.drawnPoint.y, k, scanuprim, scanvprim, scanzprim, scanz, triangle, data, rgb);
    }
};

void Rasterizer::drawTexuredPointZ(int y, int x, float uprim, float vprim, float zprim, float z, Triangle3D triangle, Uint32& data,SDL_Color& color)
{
    unsigned int offset = (windowWidth * (-y + windowHeight / 2.)) + (x + windowWidth/ 2.);
    if (abs(y) < windowHeight / 2. && abs(x) < windowWidth / 2.) {
        if (z < zbuffer[offset])
        {
            unsigned int u = uprim * triangle.texture->h / zprim;
            unsigned int v = vprim * triangle.texture->w / zprim;
            data = getpixel(triangle.texture,1,1);
            if (u < triangle.texture->w && v < triangle.texture->h)
            data = getpixel(triangle.texture, u, v);
            SDL_GetRGB(data, triangle.texture->format, &color.r, &color.g, &color.b);
            zbuffer[offset] = z;
            windowHandler.drawPoint(Vector2(x, y), color.r, color.g, color.b, 0xFF);
        }
    }
}

//SDL_Color Rasterizer::getTextureColor(const float& uprim, const float& vprim, const float& zprim, Uint32& data, SDL_Color& color)
//{
//    unsigned int u = uprim * triangle.texture->h / zprim;
//    unsigned int v = vprim * triangle.texture->w / zprim;
//    data = getpixel(triangle.texture, 1, 1);
//    if (u < triangle.texture->w && v < triangle.texture->h)
//        data = getpixel(triangle.texture, u, v);
//    SDL_GetRGB(data, triangle.texture->format, &color.r, &color.g, &color.b);
//    return SDL_Color();
//}
void Rasterizer::drawTrianglez(Triangle3D triangle)
{
    //sort vertices by ascending Y order
    std::sort(std::begin(triangle.vertices), std::end(triangle.vertices),
        [](const Vertex3& vertex1, const Vertex3& vertex2) {
            return (vertex1.y < vertex2.y);
        }
    );
    //find plane equation
    Vector3 planeNormal = Vector3::crossProduct(triangle[1] - triangle[0], triangle[2] - triangle[0]);
    double D = -planeNormal.x * triangle[0].x - planeNormal.y * triangle[0].y - planeNormal.z * triangle[0].z;
    double A = planeNormal.x;
    double B = planeNormal.y;
    double C = planeNormal.z;

    float dyz = -B / C;
    float dxz = -A / C;

    LineVars line1(triangle[2],triangle[0]);
    LineVars line2(triangle[2], triangle[1]);
    gradients gra(triangle);

    SDL_Color rgb;
    Uint32 data = getpixel(triangle.texture, 1, 1);
    SDL_GetRGB(data, triangle.texture->format, &rgb.r, &rgb.g, &rgb.b);

    drawTexuredPointZ(line1.drawnPoint.y, line1.drawnPoint.x, line1.uprim, line1.vprim, line1.zprim,line1.z,triangle, data, rgb);
    //line2 vars (short line)
   
    bool isSecond = false;

    drawTexuredPointZ(line2.drawnPoint.y, line2.drawnPoint.x, line2.uprim, line2.vprim, line2.zprim, line2.z, triangle,data,rgb);
    //line1
line1:
    for ( line1.i; line1.i < line1.dx; line1.i++)
    {
        if (line1.pk < 0) {
            if (line1.isSteep) {
                line1.drawnPoint.y--;
                line1.uprim -= gra.dUOverZdY;
                line1.vprim -= gra.dVOverZdY;
                line1.zprim -= gra.dOneOverZdY;
                line1.z -= dyz;
                line1.pk = line1.pk + 2 * line1.dy;
                drawTexuredPointZ(line1.drawnPoint.y, line1.drawnPoint.x, line1.uprim, line1.vprim, line1.zprim, line1.z, triangle, data, rgb);
                line1.i++;
                goto line2;
            }
            else {
                line1.endingPoint.x - line1.begginingPoint.x > 0 ?
                    (line1.drawnPoint.x++, line1.z += dxz, line1.zprim += gra.dOneOverZdX, line1.uprim += gra.dUOverZdX,line1.vprim += gra.dVOverZdX)
                    :
                    (line1.drawnPoint.x--, line1.z -= dxz,line1.zprim-=gra.dOneOverZdX, line1.uprim -= gra.dUOverZdX, line1.vprim -= gra.dVOverZdX);
                line1.pk = line1.pk + 2 * line1.dy;
                drawTexuredPointZ(line1.drawnPoint.y, line1.drawnPoint.x, line1.uprim, line1.vprim, line1.zprim, line1.z, triangle, data, rgb);
            }
        }
        else {
            line1.endingPoint.x - line1.begginingPoint.x > 0 ?
                (line1.drawnPoint.x++, line1.z += dxz, line1.zprim += gra.dOneOverZdX, line1.uprim += gra.dUOverZdX, line1.vprim += gra.dVOverZdX)
                :
                (line1.drawnPoint.x--, line1.z -= dxz, line1.zprim -= gra.dOneOverZdX, line1.uprim -= gra.dUOverZdX, line1.vprim -= gra.dVOverZdX);
            line1.drawnPoint.y--;
            line1.vprim -= gra.dVOverZdY;
            line1.uprim -= gra.dUOverZdY;
            line1.zprim -= gra.dOneOverZdY;
            line1.z -= dyz;
            line1.pk = line1.pk + 2 * line1.dy - 2 * line1.dx;
            drawTexuredPointZ(line1.drawnPoint.y, line1.drawnPoint.x, line1.uprim, line1.vprim, line1.zprim, line1.z, triangle, data, rgb);
            line1.i++;
            goto line2;
        };
    }
    //line2
line2:

    if (line2.i == line2.dx && !isSecond) {
        line2 = LineVars(triangle[1],triangle[0]);
        isSecond = true;
        drawTexuredPointZ(line2.drawnPoint.y, line2.drawnPoint.x, line2.uprim, line2.vprim, line2.zprim, line2.z, triangle, data, rgb);
    }
    for (line2.i; line2.i < line2.dx; line2.i++)
    {
        if (line2.pk < 0) {
            if (line2.isSteep) {
                line2.drawnPoint.y--;
                line2.uprim -= gra.dUOverZdY;
                line2.vprim -= gra.dVOverZdY;
                line2.zprim -= gra.dOneOverZdY;
                line2.z -= dyz;
                line2.pk = line2.pk + 2 * line2.dy;
                drawTexuredPointZ(line2.drawnPoint.y, line2.drawnPoint.x, line2.uprim, line2.vprim, line2.zprim, line2.z, triangle, data, rgb);
                line2.i++;
                //scanline

                drawScanline(line1, line2, gra, dxz, triangle);

                goto line1;
            }
            else {
                line2.endingPoint.x - line2.begginingPoint.x > 0 ?
                (line2.drawnPoint.x++, line2.z += dxz, line2.zprim += gra.dOneOverZdX, line2.uprim += gra.dUOverZdX, line2.vprim += gra.dVOverZdX)
                :
                (line2.drawnPoint.x--, line2.z -= dxz, line2.zprim -= gra.dOneOverZdX, line2.uprim -= gra.dUOverZdX, line2.vprim -= gra.dVOverZdX);
                line2.pk = line2.pk + 2 * line2.dy;
                drawTexuredPointZ(line2.drawnPoint.y, line2.drawnPoint.x, line2.uprim, line2.vprim, line2.zprim, line2.z, triangle, data, rgb);
            }
        }
        else {
            line2.endingPoint.x - line2.begginingPoint.x > 0 ?
                (line2.drawnPoint.x++, line2.z += dxz, line2.zprim += gra.dOneOverZdX, line2.uprim += gra.dUOverZdX, line2.vprim += gra.dVOverZdX)
                :
                (line2.drawnPoint.x--, line2.z -= dxz, line2.zprim -= gra.dOneOverZdX, line2.uprim -= gra.dUOverZdX, line2.vprim -= gra.dVOverZdX);
            line2.drawnPoint.y--;
            line2.uprim -= gra.dUOverZdY;
            line2.vprim -= gra.dVOverZdY;
            line2.zprim -= gra.dOneOverZdY;
            line2.z -= dyz;
            line2.pk = line2.pk + 2 * line2.dy - 2 * line2.dx;
            drawTexuredPointZ(line2.drawnPoint.y, line2.drawnPoint.x, line2.uprim, line2.vprim, line2.zprim, line2.z, triangle, data, rgb);
            line2.i++;
            //snacline
            drawScanline(line1, line2, gra, dxz, triangle);
            goto line1;
        };
    }

    //lineswitching scanline
    if (!isSecond) {
        drawScanline(line1, line2, gra, dxz, triangle);
    }
    if(!isSecond && (line2.dx != 0 || line2.dy != 0))goto line1;
};

void Rasterizer::drawTrianglezWire(Triangle3D triangle/*, const ZBuffer& zBuffer*/) const
{

    //sort vertices by ascending Y order
    std::sort(std::begin(triangle.vertices), std::end(triangle.vertices),
        [](const Vertex3& vertex1, const Vertex3& vertex2) {
            return (vertex1.y < vertex2.y);
        }
    );
    //find plane equation
    Vector3 planeNormal = Vector3::crossProduct(triangle[1] - triangle[0], triangle[2] - triangle[0]);
    double D = -planeNormal.x * triangle[0].x - planeNormal.y * triangle[0].y - planeNormal.z * triangle[0].z;
    double A = planeNormal.x;
    double B = planeNormal.y;
    double C = planeNormal.z;

    //line 1 vars (long line)
    Vector3 begginingPoint = Vector3((int)triangle[2].x, (int)triangle[2].y, triangle[2].z);
    Vector3 endingPoint = Vector3((int)triangle[0].x, (int)triangle[0].y, triangle[0].z);
    Vector3 drawnPoint = begginingPoint;
    int dx = abs(endingPoint.x - begginingPoint.x);
    int dy = abs(endingPoint.y - begginingPoint.y);
    bool isSteep = false;
    if (dy > dx) { int temp = dx; dx = dy; dy = temp; isSteep = true; }
    else {
        isSteep = false;
    }
    int pk = 2 * dy - dx;
    int i = 0;
    windowHandler.drawPoint(Vector2(drawnPoint.x, drawnPoint.y), 0xFF, 0x00, 0x00, 0xFF); // check for Zbuffer?

    //line2 vars (short line)
    Vector3 begginingPoint2 = Vector3((int)triangle[2].x, (int)triangle[2].y, triangle[2].z);
    Vector3 endingPoint2 = Vector3((int)triangle[1].x, (int)triangle[1].y, triangle[1].z);
    Vector3 drawnPoint2 = begginingPoint2;
    int dx2 = abs(endingPoint2.x - begginingPoint2.x);
    int dy2 = abs(endingPoint2.y - begginingPoint2.y);
    bool isSteep2 = false;
    if (dy2 > dx2) { int temp2 = dx2; dx2 = dy2; dy2 = temp2; isSteep2 = true; }
    else {
        isSteep2 = false;
    }
    int pk2 = 2 * dy2 - dx2;
    int j = 0;
    bool isSecond = false;
    windowHandler.drawPoint(Vector2(drawnPoint2.x, drawnPoint2.y), 0xFF, 0x00, 0x00, 0xFF); // check for Zbuffer?


    //line1
line1:
    for (i; i < dx - 1; i++)
    {
        if (pk < 0) {
            if (isSteep) {
                endingPoint.y - begginingPoint.y > 0 ? drawnPoint.y++ : drawnPoint.y--;
                pk = pk + 2 * dy;
                windowHandler.drawPoint(Vector2(drawnPoint.x, drawnPoint.y), 0x00, 0x00, 0xFF, 0xFF);//checkz?
                i++;
                goto line2;
            }
            else {
                endingPoint.x - begginingPoint.x > 0 ? drawnPoint.x++ : drawnPoint.x--;
                pk = pk + 2 * dy;
                windowHandler.drawPoint(Vector2(drawnPoint.x, drawnPoint.y), 0x00, 0x00, 0xFF, 0xFF);//checkz?
            }
        }
        else {
            endingPoint.x - begginingPoint.x > 0 ? drawnPoint.x++ : drawnPoint.x--;
            endingPoint.y - begginingPoint.y > 0 ? drawnPoint.y++ : drawnPoint.y--;
            pk = pk + 2 * dy - 2 * dx;
            windowHandler.drawPoint(Vector2(drawnPoint.x, drawnPoint.y), 0x00, 0x00, 0xFF, 0xFF);//checkz?
            i++;
            goto line2;
        };
    }
    //line2
line2:

    if (j == dx2 - 1 && !isSecond) {
        begginingPoint2 = Vector3((int)triangle[1].x, (int)triangle[1].y, triangle[1].z);
        endingPoint2 = Vector3((int)triangle[0].x, (int)triangle[0].y, triangle[0].z);
        drawnPoint2 = begginingPoint2;
        dx2 = abs(endingPoint2.x - begginingPoint2.x);
        dy2 = abs(endingPoint2.y - begginingPoint2.y);
        isSteep2 = false;
        if (dy2 > dx2) { int temp2 = dx2; dx2 = dy2; dy2 = temp2; isSteep2 = true; }
        else {
            isSteep2 = false;
        }
        pk2 = 2 * dy2 - dx2;
        j = 0;
        isSecond = true;
        windowHandler.drawPoint(Vector2(drawnPoint2.x, drawnPoint2.y), 0xFF, 0x00, 0x00, 0xFF);//checkz?
    }
    for (j; j < dx2 - 1; j++)
    {
        if (pk2 < 0) {
            if (isSteep2) {
                endingPoint2.y - begginingPoint2.y > 0 ? drawnPoint2.y++ : drawnPoint2.y--;
                pk2 = pk2 + 2 * dy2;
                windowHandler.drawPoint(Vector2(drawnPoint2.x, drawnPoint2.y), 0xFF, 0x00, 0x00, 0xFF);//checkz?
                j++;
                //scanline

                goto line1;
            }
            else {
                endingPoint2.x - begginingPoint2.x > 0 ? drawnPoint2.x++ : drawnPoint2.x--;
                pk2 = pk2 + 2 * dy2;
                windowHandler.drawPoint(Vector2(drawnPoint2.x, drawnPoint2.y), 0xFF, 0x00, 0x00, 0xFF);//checkz?
            }
        }
        else {
            endingPoint2.x - begginingPoint2.x > 0 ? drawnPoint2.x++ : drawnPoint2.x--;
            endingPoint2.y - begginingPoint2.y > 0 ? drawnPoint2.y++ : drawnPoint2.y--;
            pk2 = pk2 + 2 * dy2 - 2 * dx2;
            windowHandler.drawPoint(Vector2(drawnPoint2.x, drawnPoint2.y), 0xFF, 0x00, 0x00, 0xFF);//checkz?
            j++;
            //snacline
            goto line1;
        };
    }

    //lineswitching scanline
    if (!isSecond && (dx2 != 0 || dy2 != 0))goto line1;
};

void Rasterizer::drawTrianglezBBox(Triangle3D triangle)
{}
void Rasterizer::drawScene(std::vector<Triangle2D> triangles)const{
    for (int i = 0; i < triangles.size(); i++)
    {
        drawTriangle(triangles[i]);
    }
}

void Rasterizer::drawScenez(const std::vector<Triangle3D>& triangles) {
    for (int i = 0; i < triangles.size(); i++)
    {
        drawTrianglez(triangles[i]);
    }
}

void Rasterizer::drawScenezBBox(const std::vector<Triangle3D>& triangles) {
    for (int i = 0; i < triangles.size(); i++)
    {
        drawTrianglezBBox(triangles[i]);
    }
}

void Rasterizer::drawScenezWire(const std::vector<Triangle3D>& triangles)const {
    for (int i = 0; i < triangles.size(); i++)
    {
        drawTrianglezWire(triangles[i]/*, zBuffer*/);
    }
}

