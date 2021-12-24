#pragma once
#include "Figure.h"
#include "Rect.h"
#include "FaceTriangle.h"

class Tetraedr : public Figure
{
public:
	Tetraedr(Point3D _point1, Point3D _point2, Point3D _point3, Point3D _point4,
		COLORREF _color1, COLORREF _color2, COLORREF _color3, COLORREF _color4);
};

