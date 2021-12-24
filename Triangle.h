#pragma once
#include "Point3D.h"
#include "matrix.h"
#include <vector>

class Triangle
{
private:
	bool isNanBorder = false;
	int maxX = 0, maxY = 0;
	COLORREF color = WHITE;
	std::vector<Point3D> points;
	std::vector<Point3D> pointsProjection;
	Point3D center, minBorder, maxBorder;

	void changeCoordinates(std::vector<Point3D>& _points, double** matr);
	void transfer(std::vector<Point3D>& _points, double dx, double dy, double dz);
	void updateBorders(std::vector<Point3D>& _points);
	void rendering_pixels(double x, double y);
	bool affiliation_point(double x, double y);
	double Square(Point3D p1, Point3D p2, Point3D p3);

public:
	Triangle() {}
	Triangle(Point3D _point1, Point3D _point2, Point3D _point3, COLORREF _color);

	void print(double shift = 0);
	void transfer(double dx, double dy, double dz);
	void scale(Point3D center, double sx, double sy, double sz);
	void rotation(Point3D center, double angle, Axises axis);
	void centerTask();
	void projection(Point3D _center);
	void painting();
	void setMax(int _maxX, int _maxY) { maxX = _maxX; maxY = _maxY; }
	Triangle getShadowTriangle(Point3D l);

	double getCenterX() { return center.getX(); }
	double getCenterY() { return center.getY(); }
	double getCenterZ() { return center.getZ(); }
	double getMidZ();
	bool getIsNanBorder() { return isNanBorder; }
};

