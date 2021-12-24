#pragma once
#include "Figure.h"
#include "Rect.h"

class Parallelepiped : public Figure
{
public:
	Parallelepiped(Point3D _point1, Point3D _point2, Point3D _point3, Point3D _point4,
		Point3D _point5, Point3D _point6, Point3D _point7, Point3D _point8,
		COLORREF _color1, COLORREF _color2, COLORREF _color3, COLORREF _color4, COLORREF _color5, COLORREF _color6);
};

