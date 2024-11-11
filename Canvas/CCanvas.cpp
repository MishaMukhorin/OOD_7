//
// Created by Misha on 18.04.2024.
//

#include <complex>
#include "CCanvas.h"

void CCanvas::DrawLine(CPoint from, CPoint to, Color lineColor, float lineWidth)
{
    float dx = to.getX() - from.getX();
    float dy = to.getY() - from.getY();
    float length = std::sqrt(dx * dx + dy * dy);

    float ux = dx / length;
    float uy = dy / length;

    sf::Vector2f offset(-uy * lineWidth / 2.0f, ux * lineWidth / 2.0f);

    sf::VertexArray line(sf::Quads, 4);
    line[0].position = sf::Vector2f(from.getX(), from.getY()) + offset;
    line[1].position = sf::Vector2f(from.getX(), from.getY()) - offset;
    line[2].position = sf::Vector2f(to.getX(), to.getY()) - offset;
    line[3].position = sf::Vector2f(to.getX(), to.getY()) + offset;

    sf::Color sfColor(lineColor.GetInt());
    for (int i = 0; i < 4; ++i) {
        line[i].color = sfColor;
    }

    // Draw the line as a thick rectangle
    texture.draw(line);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, Color fillColor)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(points.size());
    for (size_t i = 0; i < points.size(); ++i)
    {
        polygon.setPoint(i, sf::Vector2f(points[i].getX(), points[i].getY()));
    }

    polygon.setFillColor(sf::Color(fillColor.GetInt()));
    texture.draw(polygon);
};

void CCanvas::DrawEllipse(CPoint center, float radiusX, float radiusY, Color lineColor, float lineWidth)
{
    sf::CircleShape ellipse(radiusX);
    ellipse.setScale(1.0f, radiusY / radiusX);
    ellipse.setPosition(sf::Vector2f(center.getX(), center.getY()));
    ellipse.setOutlineColor(sf::Color(lineColor.GetInt()));
    ellipse.setFillColor(sf::Color(0, 0, 0, 0));
    ellipse.setOutlineThickness(lineWidth);
    texture.draw(ellipse);
}

void CCanvas::FillEllipse(CPoint center, float radiusX, float radiusY, Color fillColor)
{
    sf::CircleShape ellipse(radiusX);
    ellipse.setScale(1.0f, radiusY / radiusX);
    ellipse.setPosition(sf::Vector2f(center.getX(), center.getY()));
    ellipse.setFillColor(sf::Color(fillColor.GetInt()));
    ellipse.setOutlineThickness(0);
    texture.draw(ellipse);
}


sf::RenderTexture& CCanvas::GetTexture()
{
    return texture;
}

void CCanvas::DrawShapesOnTexture(const std::vector<std::shared_ptr<ICanvasDrowable>> &shapes)
{
    texture.clear();
    for (const auto& shape: shapes)
    {
        shape->Draw(this);
    }
}



