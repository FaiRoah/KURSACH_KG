#include "Figure.h"

void Figure::print() {
    for (int i = 0; i < baseFigures.size(); i++)
        baseFigures[i]->print();
}

void Figure::transfer(double dx, double dy, double dz, bool isBorder) {
    bool isNanBorder = false;
    for (int i = 0; i < baseFigures.size(); i++) {
        baseFigures[i]->transfer(dx, dy, dz);
        if (baseFigures[i]->getIsNanBorder())
            isNanBorder = true;
    }
    if (isNanBorder && isBorder)
        for (int i = 0; i < baseFigures.size(); i++)
            baseFigures[i]->transfer(-dx, -dy, -dz);
}

void Figure::scale(double sx, double sy, double sz, bool isBorder) {
    centerTask();
    bool isNanBorder = false;
    for (int i = 0; i < baseFigures.size(); i++) {
        baseFigures[i]->scale(center, sx, sy, sz);
        if (baseFigures[i]->getIsNanBorder())
            isNanBorder = true;
    }
    if (isNanBorder && isBorder)
        for (int i = 0; i < baseFigures.size(); i++)
            baseFigures[i]->scale(center, 1.0 / sx, 1.0 / sy, 1.0 / sz);
}

void Figure::rotation(double angle, Axises axis, bool isBorder) {
    centerTask();
    bool isNanBorder = false;
    for (int i = 0; i < baseFigures.size(); i++) {
        baseFigures[i]->rotation(center, angle, axis);
        if (baseFigures[i]->getIsNanBorder())
            isNanBorder = true;
    }
    if (isNanBorder && isBorder)
        for (int i = 0; i < baseFigures.size(); i++)
            baseFigures[i]->rotation(center, -angle, axis);
}

void Figure::setMax(int _maxX, int _maxY) {
    maxX = _maxX;
    maxY = _maxY;
    for (int i = 0; i < baseFigures.size(); i++)
        baseFigures[i]->setMax(maxX, maxY);
}

void Figure::printShadow(Point3D l) {
    std::vector<BaseFigure*> shadowTriangles;
    for (int i = 0; i < baseFigures.size(); i++)
        shadowTriangles.push_back(baseFigures[i]->getShadowFigure(l));   
    Figure shadowFigure(shadowTriangles);
    shadowFigure.setMax(maxX, maxY);
    shadowFigure.rotation(20, Axises::X, false);
    shadowFigure.projection();
    shadowFigure.print();
    shadowFigure.painting();
}

void Figure::centerTask() {

    double minX = INT32_MAX, minY = INT32_MAX, minZ = INT32_MAX, maxX = INT32_MIN, maxY = INT32_MIN, maxZ = INT32_MIN;

    //нахождения крайних точек  
    for (int i = 0; i < baseFigures.size(); i++)
    {
        baseFigures[i]->centerTask();
        if (baseFigures[i]->getCenterX() < minX)
            minX = baseFigures[i]->getCenterX();
        if (baseFigures[i]->getCenterX() > maxX)
            maxX = baseFigures[i]->getCenterX();

        if (baseFigures[i]->getCenterY() < minY)
            minY = baseFigures[i]->getCenterY();
        if (baseFigures[i]->getCenterY() > maxY)
            maxY = baseFigures[i]->getCenterY();

        if (baseFigures[i]->getCenterZ() < minZ)
            minZ = baseFigures[i]->getCenterZ();
        if (baseFigures[i]->getCenterZ() > maxZ)
            maxZ = baseFigures[i]->getCenterZ();
    }
    //вычисление центра
    center.setX((minX + maxX) / 2.0);
    center.setY((minY + maxY) / 2.0);
    center.setZ((minZ + maxZ) / 2.0);
}

void Figure::projection() {
    centerTask();
    for (int i = 0; i < baseFigures.size(); i++)
        baseFigures[i]->projection(center);
}

void Figure::painting() {
    for (int i = 0; i < baseFigures.size(); i++)
        baseFigures[i]->painting();
}