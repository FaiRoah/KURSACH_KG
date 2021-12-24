#include "Triangle.h"

Triangle::Triangle(Point3D _point1, Point3D _point2, Point3D _point3, COLORREF _color) : color(_color) {
	points.push_back(_point1);
	points.push_back(_point2);
	points.push_back(_point3);
}

void Triangle::print(double shift) {
    setcolor(color);
    line(pointsProjection[0].getX() + shift, pointsProjection[0].getY() + shift, pointsProjection[1].getX() + shift, pointsProjection[1].getY() + shift);
    line(pointsProjection[1].getX() + shift, pointsProjection[1].getY() + shift, pointsProjection[2].getX() + shift, pointsProjection[2].getY() + shift);
    line(pointsProjection[2].getX() + shift, pointsProjection[2].getY() + shift, pointsProjection[0].getX() + shift, pointsProjection[0].getY() + shift);
}

void Triangle::transfer(double dx, double dy, double dz) {
    changeCoordinates(points, matrixTransfer(dx, dy, dz));
}

void Triangle::scale(Point3D _center, double sx, double sy, double sz) {
    transfer(-_center.getX(), -_center.getY(), -_center.getZ());
    changeCoordinates(points, matrixScale(sx, sy, sz));
    transfer(_center.getX(), _center.getY(), _center.getZ());
}

void Triangle::rotation(Point3D _center, double angle, Axises axis) {
    transfer(-_center.getX(), -_center.getY(), -_center.getZ());
    changeCoordinates(points, matrixRotation(angle, axis));
    transfer(_center.getX(), _center.getY(), _center.getZ());
}

void Triangle::centerTask() {  
    //вычисление центра
    updateBorders(points);
    center.setX((minBorder.getX() + maxBorder.getX()) / 2.0);
    center.setY((minBorder.getY() + maxBorder.getY()) / 2.0);
    center.setZ((minBorder.getZ() + maxBorder.getZ()) / 2.0);
}

void Triangle::projection(Point3D _center) {
    
    std::vector<Point3D> tmp = pointsProjection;
    bool isNanBorder = false;
    pointsProjection = points;
    transfer(pointsProjection, -_center.getX(), -_center.getY(), 0);
    changeCoordinates(pointsProjection, matrProjection());
    transfer(pointsProjection, _center.getX(), _center.getY(), 0);
    
}

Triangle Triangle::getShadowTriangle(Point3D l) {
    std::vector<Point3D> pointsShadow = points;
    changeCoordinates(pointsShadow, matrShadow(l, maxY));
    return Triangle(pointsShadow[0], pointsShadow[1], pointsShadow[2], BLACK);
}

double Triangle::getMidZ() {
    double midZ = 0;
    for (int i = 0; i < pointsProjection.size(); i++) {
        midZ += pointsProjection[i].getZ();
    }

    return (pointsProjection.size() == 0 ? INT32_MAX : midZ / double(pointsProjection.size()));
}

void Triangle::changeCoordinates(std::vector<Point3D>& _points, double** matr) {
    isNanBorder = false;
    for (int i = 0; i < _points.size(); i++)
    {
        double* curCor = new double[4];
        curCor[0] = _points[i].getX();
        curCor[1] = _points[i].getY();
        curCor[2] = _points[i].getZ();
        curCor[3] = 1;
        mulMat(curCor, matr, 4);
        _points[i].setX(curCor[0] / curCor[3]);
        _points[i].setY(curCor[1] / curCor[3]);
        _points[i].setZ(curCor[2] / curCor[3]);
        delete[] curCor;
        if (_points[i].getX() < 0 || _points[i].getX() > maxX ||
            _points[i].getY() < 0 || _points[i].getY() > maxY) 
            isNanBorder = true;
    }
    delmatr(matr, 4);
}

void Triangle::transfer(std::vector<Point3D>& _points, double dx, double dy, double dz) {
    changeCoordinates(_points, matrixTransfer(dx, dy, dz));
}

void Triangle::updateBorders(std::vector<Point3D>& _points) {

    minBorder = Point3D(INT32_MAX, INT32_MAX, INT32_MAX);
    maxBorder = Point3D(INT32_MIN, INT32_MIN, INT32_MIN);
    //нахождения крайних точек
    for (int i = 0; i < _points.size(); i++)
    {
        if (_points[i].getX() < minBorder.getX())
            minBorder.setX(_points[i].getX());
        if (_points[i].getX() > maxBorder.getX())
            maxBorder.setX(_points[i].getX());

        if (_points[i].getY() < minBorder.getY())
            minBorder.setY(_points[i].getY());
        if (_points[i].getY() > maxBorder.getY())
            maxBorder.setY(_points[i].getY());

        if (_points[i].getZ() < minBorder.getZ())
            minBorder.setZ(_points[i].getZ());
        if (_points[i].getZ() > maxBorder.getZ())
            maxBorder.setZ(_points[i].getZ());
    }
}

void Triangle::painting() {
    updateBorders(pointsProjection); 
    Point3D c; 
    for (int i = 0; i < pointsProjection.size(); i++) {
        c.setX(c.getX() + pointsProjection[i].getX());
        c.setY(c.getY() + pointsProjection[i].getY());
    }
    rendering_pixels(min(c.getX() / 3.0, maxX), min(c.getY() / 3.0, maxY)); 
}

void Triangle::rendering_pixels(double x, double y) { 
    putpixel(x, y, color); 
    if (affiliation_point(x, y)) { 
        if (y < min(maxBorder.getY(), maxY)) 
            if (getpixel(x, y + 1) != color) 
                rendering_pixels(x, y + 1);
        if (y > max(minBorder.getY(), 1))
            if (getpixel(x, y - 1) != color)
                rendering_pixels(x, y - 1);
        if (x < min(maxBorder.getX(), maxX))
            if (getpixel(x + 1, y) != color)
                rendering_pixels(x + 1, y);
        if (x > max(minBorder.getX(), 1))
            if (getpixel(x - 1, y) != color)
                rendering_pixels(x - 1, y);
    }
}

bool Triangle::affiliation_point(double x, double y)
{
    Point3D p;
    p.setX(x);
    p.setY(y);
    double square = Square(pointsProjection[0], pointsProjection[1], pointsProjection[2]);
    double s = Square(p, pointsProjection[0], pointsProjection[1]) +
        Square(p, pointsProjection[1], pointsProjection[2]) +
        Square(p, pointsProjection[2], pointsProjection[0]);

    return fabs(s - square) < 0.01;
}

double Triangle::Square(Point3D p1, Point3D p2, Point3D p3)
{
    return fabs(p2.getX() * p3.getY() - p3.getX() * p2.getY() - p1.getX() * p3.getY()
        + p3.getX() * p1.getY() + p1.getX() * p2.getY() - p2.getX() * p1.getY());
}