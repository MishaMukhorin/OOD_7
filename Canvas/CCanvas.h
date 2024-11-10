//
// Created by Misha on 11.04.2024.
//

#ifndef OOP_4_CCANVAS_H
#define OOP_4_CCANVAS_H

#include <string>
#include "../Interfaces/ICanvas.h"
#include "../Interfaces/ICanvasDrowable.h"

const int WIDTH = 1000;
const int HEIGHT = 1000;
const std::string TITLE = "Canvas";

class CCanvas: public ICanvas
{
public:

    CCanvas() { texture.create(WIDTH, HEIGHT); }

    void DrawLine(CPoint from, CPoint to, Color lineColor) override;

    void FillPolygon(std::vector<CPoint> points, Color fillColor) override;

    void DrawCircle(CPoint center, float radius, Color lineColor) override;

    void FillCircle(CPoint center, float radius, Color fillColor) override;

    sf::RenderTexture& GetTexture();

    void DrawShapesOnTexture(const std::vector<std::unique_ptr<ICanvasDrowable>> &shapes);


private:
    sf::RenderTexture texture; // done настроить матрицу проецирования (cgcourse)
    // done сделать хранение RenderTarget

};

#endif //OOP_4_CCANVAS_H

