#pragma once
#include "Triangle.h"
#include <vector>

class BaseFigure
{
protected:
	std::vector<Triangle> triangles;
	Point3D center;
	int maxX = 0, maxY = 0;
	bool isNanBorder = false;
public:
	BaseFigure() {}
	BaseFigure(std::vector<Triangle> _triangles) : triangles(_triangles) {}

	void print();
	void transfer(double dx, double dy, double dz, bool isBorder = true);
	void scale(Point3D center, double sx, double sy, double sz, bool isBorder = true);
	void rotation(Point3D center, double angle, Axises axis, bool isBorder = true);
	void projection(Point3D _center);
	void painting();
	void setMax(int _maxX, int _maxY);
	void centerTask();

	BaseFigure* getShadowFigure(Point3D l);

	void setTriandles(std::vector<Triangle> _triangles) { triangles = _triangles; }
	std::vector<Triangle> getTriandles() { return triangles; }

	double getCenterX() { return center.getX(); }
	double getCenterY() { return center.getY(); }
	double getCenterZ() { return center.getZ(); }
	double getMidZ();
	bool getIsNanBorder() { return isNanBorder; }
};

