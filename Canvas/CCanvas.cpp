//
// Created by Misha on 18.04.2024.
//

#include "CCanvas.h"

void CCanvas::DrawLine(CPoint from, CPoint to, Color lineColor) //done по ссылке передавать окно
{
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(from.getX(), from.getY());
    line[1].position = sf::Vector2f(to.getX(), to.getY());
    line[0].color = sf::Color(lineColor.GetInt());
    line[1].color = sf::Color(lineColor.GetInt());
    texture.draw(line);
};

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

void CCanvas::DrawCircle(CPoint center, float radius, Color lineColor)
{
    sf::CircleShape circle(radius);
    circle.setPosition(sf::Vector2f(center.getX(), center.getY()));
    circle.setOutlineColor(sf::Color(lineColor.GetInt()));
    circle.setFillColor(sf::Color(0));
    circle.setOutlineThickness(2);
    texture.draw(circle);
};

void CCanvas::FillCircle(CPoint center, float radius, Color fillColor)
{
    sf::CircleShape circle(radius);
    circle.setPosition(sf::Vector2f(center.getX(), center.getY()));
    circle.setFillColor(sf::Color(fillColor.GetInt()));
    circle.setOutlineThickness(0);
    texture.draw(circle);
};

sf::RenderTexture& CCanvas::GetTexture()
{
    return texture;
}

void CCanvas::DrawShapesOnTexture(const std::vector<std::unique_ptr<ICanvasDrowable>> &shapes)
{
    texture.clear();
    for (const auto& shape: shapes)
    {
        shape->Draw(this);
    }
}



