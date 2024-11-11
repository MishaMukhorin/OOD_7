//
// Created by Misha on 11.04.2024.
//

#ifndef OOP_4_CCANVAS_H
#define OOP_4_CCANVAS_H

#include <string>
#include <memory>
#include "SFML/Graphics.hpp"
#include "../Interfaces/ICanvas.h"
#include "../Interfaces/ICanvasDrowable.h"

const int WIDTH = 1000;
const int HEIGHT = 1000;
const std::string TITLE = "Canvas";

class CCanvas: public ICanvas
{
public:

    CCanvas() { texture.create(WIDTH, HEIGHT); }

    void DrawLine(CPoint from, CPoint to, Color lineColor, float lineWidth) override;

    void FillPolygon(std::vector<CPoint> points, Color fillColor) override;

    void DrawEllipse(CPoint center, float radiusX, float radiusY, Color lineColor, float lineWidth) override;

    void FillEllipse(CPoint center, float radiusX, float radiusY, Color fillColor) override;

    sf::RenderTexture& GetTexture();

    void DrawShapesOnTexture(const std::vector<std::shared_ptr<ICanvasDrowable>> &shapes);


private:
    sf::RenderTexture texture;

};

#endif //OOP_4_CCANVAS_H

