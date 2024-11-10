//
// Created by Misha on 11.04.2024.
//

#ifndef OOP_4_ICANVAS_H
#define OOP_4_ICANVAS_H

#include <vector>
#include "SFML/Graphics.hpp"
#include "../Shapez/CPoint.h"
#include "../Shapez/CColor.h"

class ICanvas
{
public:
    virtual ~ICanvas() = default;
    virtual void DrawLine(CPoint from, CPoint to, Color lineColor) = 0;
    virtual void FillPolygon(std::vector<CPoint> points, Color fillColor) = 0;
    virtual void DrawCircle(CPoint center, float radius, Color lineColor) = 0;
    virtual void FillCircle(CPoint center, float radius, Color fillColor) = 0;

};


#endif //OOP_4_ICANVAS_H

