#pragma once
#include "BaseFigure.h"

class Figure
{
protected:
	std::vector<BaseFigure*> baseFigures;
	Point3D center;
	int maxX = 0, maxY = 0;
	void centerTask();
public:
	Figure() {}
	Figure(std::vector<BaseFigure*> baseFigures) : baseFigures(baseFigures) {}

	void print();
	void transfer(double dx, double dy, double dz, bool isBorder = true);
	void scale(double sx, double sy, double sz, bool isBorder = true);
	void rotation(double angle, Axises axis, bool isBorder = true);
	void projection();
	void painting();
	void setMax(int _maxX, int _maxY);
	void printShadow(Point3D l);

	void setTriandles(std::vector<BaseFigure*> baseFigures) { baseFigures = baseFigures; }
	std::vector<BaseFigure*> getTriandles() { return baseFigures; }
};

