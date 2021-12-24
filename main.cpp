#include "graphics.h"
#include "Tetraedr.h"
#include "Parallelepiped.h"
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;


void painterAlgo(vector<Figure*>& figures);

void drawShadow(vector<Figure*>& figures, Point3D l);

void setMax(vector<Figure*>& figures, int maxX, int maxY);

void drawScene(vector<Figure*>& figures, Point3D& l);

void transfer(vector<Figure*>& figures, int number, double toX, double toY, double toZ);

void scale(vector<Figure*>& figures, int number, double toX, double toY, double toZ);

void rotate(vector<Figure*>& figures, int number, double angle, Axises axis);

vector<Figure*> createFigures();

int main() {
    //окно для отрисовки 
    int gm, gd = DETECT;
    char a[2] = " ";
    initgraph(&gd, &gm, a);
    setbkcolor(15);
    const int maxX = getmaxx() - 10, maxY = getmaxy() - 10;
    vector<Figure*> figures = createFigures();
    setMax(figures, maxX, maxY);

    double range = 10, rel = 1.1, angle = 10;

    Point3D light(0, 0, 0);  //источник света

    drawScene(figures, light);
    bool isExit = false;
    int mode = 0;
    while (!isExit)
    {
        //обработка нажатий
        switch (getch())
        {
        case 48: //0
            mode = 0;
            break;
        case 49: //1
            mode = 1;
            break;
        case 50: //2
            mode = 2;
            break;
        case 116: //t
            transfer(figures, mode, 0, 0, range);
            drawScene(figures, light);
            break;
        case 103: //g
            transfer(figures, mode, 0, 0, -range);
            drawScene(figures, light);
            break;
        case 119: //w
            transfer(figures, mode, 0, -range, 0);
            drawScene(figures, light);
            break;
        case 115: //s
            transfer(figures, mode, 0, range, 0);
            drawScene(figures, light);
            break;
        case 97: //a
            transfer(figures, mode, -range, 0, 0);
            drawScene(figures, light);
            break;
        case 100: //d
            transfer(figures, mode, range, 0, 0);
            drawScene(figures, light);
            break;
        case 102: //minus - f
            scale(figures, mode, 1.0 / rel, 1.0 / rel, 1.0 / rel);
            drawScene(figures, light);
            break;
        case 114: //plus - r
            scale(figures, mode, rel, rel, rel);
            drawScene(figures, light);
            break;
        case 113: //q      
            rotate(figures, mode, -angle, Axises::Z);
            drawScene(figures, light);
            break;
        case 101: //e
            rotate(figures, mode, angle, Axises::Z);
            drawScene(figures, light);
            break;
        case 72: //Up      
            rotate(figures, mode, -angle, Axises::X);
            drawScene(figures, light);
            break;
        case 80: //Down
            rotate(figures, mode, angle, Axises::X);
            drawScene(figures, light);
            break;
        case 75: //Left    
            rotate(figures, mode, angle, Axises::Y);
            drawScene(figures, light);
            break;
        case 77: //Right
            rotate(figures, mode, -angle, Axises::Y);
            drawScene(figures, light);
            break;
        case 27:
            isExit = true;
            break;
        }
    }
    //закрытие графического окна
    closegraph();
}

void painterAlgo(vector<Figure*>& figures) {
    vector<BaseFigure*> triangles;
    for (int i = 0; i < figures.size(); i++) {
        figures[i]->projection();
        vector<BaseFigure*> tmp = figures[i]->getTriandles();
        for (auto triangle : tmp)
            triangles.push_back(triangle);
    }
    for (int i = 1; i < triangles.size(); i++) {
        for (int j = 0; j < triangles.size() - i; j++)
            if (triangles[j]->getMidZ() < triangles[j + 1]->getMidZ())
                swap(triangles[j], triangles[j + 1]);
    }

    for (int i = 0; i < triangles.size(); i++) {
        triangles[i]->print();
        triangles[i]->painting();
    }
}

void drawShadow(vector<Figure*>& figures, Point3D l) {
    for (int i = 0; i < figures.size(); i++)
        figures[i]->printShadow(l);
}

void setMax(vector<Figure*>& figures, int maxX, int maxY) {
    for (int i = 0; i < figures.size(); i++)
        figures[i]->setMax(maxX, maxY);
}

void drawScene(vector<Figure*>& figures, Point3D& l) {
    cleardevice();
    painterAlgo(figures);
    drawShadow(figures, l);
}

void transfer(vector<Figure*>& figures, int number, double toX, double toY, double toZ) {
    for (int i = 0; i < figures.size(); i++)
        if (number == 0 || i == number - 1)
            figures[i]->transfer(toX, toY, toZ);
}

void scale(vector<Figure*>& figures, int number, double toX, double toY, double toZ) {
    for (int i = 0; i < figures.size(); i++)
        if (number == 0 || i == number - 1)
            figures[i]->scale(toX, toY, toZ);
}

void rotate(vector<Figure*>& figures, int number, double angle, Axises axis) {
    for (int i = 0; i < figures.size(); i++)
        if (number == 0 || i == number - 1)
            figures[i]->rotation(angle, axis);
}

vector<Figure*> createFigures() {
    Parallelepiped* parallelepiped = new Parallelepiped(
        Point3D(50, 50, 100), Point3D(100, 50, 100), Point3D(100, 100, 100), Point3D(50, 100, 100),
        Point3D(50, 50, 200), Point3D(100, 50, 200), Point3D(100, 100, 200), Point3D(50, 100, 200),
        BLUE, GREEN, RED, YELLOW, CYAN, BROWN);
    Tetraedr* tetraedr = new Tetraedr(
        Point3D(100, 100, 100), Point3D(200, 200, 100), 
        Point3D(150, 100, 100), Point3D(200, 200, 200), 
        BLUE, GREEN, RED, YELLOW);
    vector<Figure*> figures;
    figures.push_back(parallelepiped);
    figures.push_back(tetraedr);
    return figures;
}