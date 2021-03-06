#include "engin/collisionapproch.hpp"

bool RectPoint(SDL_Rect rect, SDL_Point point){
    return SDL_PointInRect(&point, &rect);
}

bool RectRect(SDL_Rect rect1, SDL_Rect rect2){
    return SDL_IntersectRect(&rect1, &rect2, NULL);
}

bool RectLine(SDL_Rect rect, SDL_Line line){
    return SDL_IntersectRectAndLine(&rect, &line.p1.x, &line.p1.y, &line.p2.x, &line.p2.y);
}

bool CircleCircle(SDL_Circle c1, SDL_Circle c2){
    double distance = GetDistance(c1.center.x, c1.center.y, c2.center.x, c2.center.y);
    if(fabs(distance-(c1.r+c2.r))>EPS)
        return false;
    return true;
}

bool CircleRect(SDL_Rect rect, SDL_Circle circle){
    //TODO 这个地方打算直接用调用SAT
}

//TODO 未实现SAT
bool SAT(SDL_Point poly1[], int num1, SDL_Point poly2[], int num2);

bool CirlePoint(SDL_Circle c, SDL_Point p){
    if(fabs(GetDistance(p.x, p.y, c.center.x, c.center.y) - c.r) <= EPS)
        return true;
    return false;
}

bool RotRectPoint(SDL_RotRect rrect, SDL_Point p){
    return RotateRectPointByAngle(rrect.rect, p, rrect.degree);
}

bool RotateRectPoint(SDL_Point vertices[], SDL_Point p){
    float degree = GetRotRectAngle(vertices);
    SDL_Point center = {(vertices[0].x+vertices[2].x)/2, (vertices[0].x+vertices[2].y)/2};
    SDL_Point newverts[4];
    SDL_memcpy(newverts, vertices, sizeof(SDL_Point)*4);
    for(int i=0;i<4;i++)
        RotatePointGroup(&center, newverts, 4, degree);
    SDL_Rect rect = {newverts[0].x, newverts[0].y, abs(newverts[2].x-newverts[0].x), abs(newverts[2].y-newverts[0].y)};
    return RotateRectPointByAngle(rect, p, degree);
}

bool RotateRectPointByAngle(SDL_Rect rect, SDL_Point point, real degree){
    SDL_Point center = GetRectangleCenter(&rect);
    RotatePointSelf(&center, &point, degree);
    return RectPoint(rect, point);
}