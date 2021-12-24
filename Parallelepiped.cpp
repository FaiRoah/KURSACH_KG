#include "Parallelepiped.h"

Parallelepiped::Parallelepiped(Point3D _point1, Point3D _point2, Point3D _point3, Point3D _point4,
	Point3D _point5, Point3D _point6, Point3D _point7, Point3D _point8,
	COLORREF _color1, COLORREF _color2, COLORREF _color3, COLORREF _color4, COLORREF _color5, COLORREF _color6) {
	
	baseFigures.push_back(new Rect(_point1, _point2, _point4, _point3, _color1));
	baseFigures.push_back(new Rect(_point5, _point6, _point8, _point7, _color2));
	baseFigures.push_back(new Rect(_point1, _point2, _point5, _point6, _color3));
	baseFigures.push_back(new Rect(_point1, _point4, _point5, _point8, _color4));
	baseFigures.push_back(new Rect(_point3, _point4, _point7, _point8, _color5));
	baseFigures.push_back(new Rect(_point2, _point3, _point6, _point7, _color6));
}