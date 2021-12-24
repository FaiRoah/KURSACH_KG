#include "FaceTriangle.h"

FaceTriangle::FaceTriangle(Point3D _point1, Point3D _point2, Point3D _point3, COLORREF _color) {
	triangles.push_back(Triangle(_point1, _point2, _point3, _color));
}