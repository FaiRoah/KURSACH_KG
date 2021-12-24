#include "Rect.h"

Rect::Rect(Point3D _point1, Point3D _point2, Point3D _point3, Point3D _point4, COLORREF _color) {
	triangles.push_back(Triangle(_point1, _point2, _point3, _color));
	triangles.push_back(Triangle(_point2, _point3, _point4, _color));
}