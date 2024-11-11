//
// Created by Misha on 11.04.2024.
//

#ifndef OOP_4_ICANVAS_H
#define OOP_4_ICANVAS_H

#include <vector>
#include "../Shapez/CPoint.h"
#include "../Shapez/CColor.h"

class ICanvas
{
public:
    virtual ~ICanvas() = default;
    virtual void DrawLine(CPoint from, CPoint to, Color lineColor, float lineWidth) = 0;
    virtual void FillPolygon(std::vector<CPoint> points, Color fillColor) = 0;

    virtual void DrawEllipse(CPoint center, float radiusX, float radiusY, Color lineColor, float lineWidth) = 0;
    virtual void FillEllipse(CPoint center, float radiusX, float radiusY, Color fillColor) = 0;

};


#endif //OOP_4_ICANVAS_H

