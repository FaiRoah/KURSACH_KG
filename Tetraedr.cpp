#include "Tetraedr.h"

Tetraedr::Tetraedr(Point3D _point1, Point3D _point2, Point3D _point3, Point3D _point4,
	COLORREF _color1, COLORREF _color2, COLORREF _color3, COLORREF _color4){

	baseFigures.push_back(new FaceTriangle(_point1, _point2, _point3, _color1));
	baseFigures.push_back(new FaceTriangle(_point1, _point2, _point4, _color2));
	baseFigures.push_back(new FaceTriangle(_point2, _point3, _point4, _color3));
	baseFigures.push_back(new FaceTriangle(_point1, _point3, _point4, _color4));
}