#include "BaseFigure.h"

void BaseFigure::print() {
    for (int i = 0; i < triangles.size(); i++)
        triangles[i].print();
}

void BaseFigure::transfer(double dx, double dy, double dz, bool isBorder) {
    isNanBorder = false;
    for (int i = 0; i < triangles.size(); i++) {
        triangles[i].transfer(dx, dy, dz);
        if (triangles[i].getIsNanBorder())
            isNanBorder = true;
    }
}

void BaseFigure::scale(Point3D _center, double sx, double sy, double sz, bool isBorder) {
    isNanBorder = false;
    for (int i = 0; i < triangles.size(); i++) {
        triangles[i].scale(_center, sx, sy, sz);
        if (triangles[i].getIsNanBorder())
            isNanBorder = true;
    }
}

void BaseFigure::rotation(Point3D _center, double angle, Axises axis, bool isBorder) {
    isNanBorder = false;
    for (int i = 0; i < triangles.size(); i++) {
        triangles[i].rotation(_center, angle, axis);
        if (triangles[i].getIsNanBorder())
            isNanBorder = true;
    }
}

void BaseFigure::setMax(int _maxX, int _maxY) {
    maxX = _maxX;
    maxY = _maxY;
    for (int i = 0; i < triangles.size(); i++)
        triangles[i].setMax(maxX, maxY);
}

BaseFigure* BaseFigure::getShadowFigure(Point3D l) {
    std::vector<Triangle> shadowTriangles;
    for (int i = 0; i < triangles.size(); i++)
        shadowTriangles.push_back(triangles[i].getShadowTriangle(l));
    return new BaseFigure(shadowTriangles);
}

double BaseFigure::getMidZ() {
    double midZ = 0;
    for (int i = 0; i < triangles.size(); i++) {
        midZ += triangles[i].getMidZ();
    }

    return (triangles.size() == 0 ? INT32_MAX : midZ / double(triangles.size()));
}

void BaseFigure::centerTask() {

    double minX = INT32_MAX, minY = INT32_MAX, minZ = INT32_MAX, maxX = INT32_MIN, maxY = INT32_MIN, maxZ = INT32_MIN;

    //нахождение крайних точек  
    for (int i = 0; i < triangles.size(); i++)
    {
        triangles[i].centerTask();
        if (triangles[i].getCenterX() < minX)
            minX = triangles[i].getCenterX();
        if (triangles[i].getCenterX() > maxX)
            maxX = triangles[i].getCenterX();

        if (triangles[i].getCenterY() < minY)
            minY = triangles[i].getCenterY();
        if (triangles[i].getCenterY() > maxY)
            maxY = triangles[i].getCenterY();

        if (triangles[i].getCenterZ() < minZ)
            minZ = triangles[i].getCenterZ();
        if (triangles[i].getCenterZ() > maxZ)
            maxZ = triangles[i].getCenterZ();
    }
    //вычисление центра
    center.setX((minX + maxX) / 2.0);
    center.setY((minY + maxY) / 2.0);
    center.setZ((minZ + maxZ) / 2.0);
}

void BaseFigure::projection(Point3D _center) {
    for (int i = 0; i < triangles.size(); i++)
        triangles[i].projection(_center);
}

void BaseFigure::painting() {
    for (int i = 0; i < triangles.size(); i++)
        triangles[i].painting();
}