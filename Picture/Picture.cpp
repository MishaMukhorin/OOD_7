//
// Created by mrLogic on 7/10/2024.
//

#include <algorithm>
#include <iostream>
#include "Picture.h"

using namespace std;

void Picture::AddShape(const std::string& id, std::unique_ptr<ShapeUnit> shape)
{
    if (m_shapes.contains(id))
    {
        throw invalid_argument("Shape with given ID already exists");
    }
    m_shapes.emplace(id, std::move(shape));
}

void Picture::DeleteShape(const string &id)
{
    auto it = m_shapes.find(id);
    if (it == m_shapes.end())
    {
        throw invalid_argument("Shape with given ID does not exist");
    }
    m_shapes.erase(it);
}

void Picture::ListShapeDescriptions() const
{
    int number = 1;
    for (const auto& shape : m_shapes)
    {
        cout << number++ << " " << shape.second->ToString() << endl;
    }
}

string Picture::GetShapeFillColorById(const string& id) const
{
    if (!m_shapes.contains(id))
    {
        return "";
    }
    auto shape = m_shapes.at(id).get();
    return shape->GetFillStyle()->GetColor()->ToString();
}

string Picture::GetShapeStrokeColorById(const string& id) const
{
    if (!m_shapes.contains(id))
    {
        return "";
    }
    auto shape = m_shapes.at(id).get();
    return shape->GetStrokeStyle()->GetColor()->ToString();
}

string Picture::GetShapeById(const string& id) const
{
    if (!m_shapes.contains(id))
    {
        return "";
    }

    auto shape = m_shapes.at(id).get();
    return shape->GetType() + " " + shape->GetColor() + " " + shape->GetShapeParamsString();
}

void Picture::ChangeShapeColor(const std::string &id, const std::string &color)
{
    if (!m_shapes.contains(id))
    {
        throw invalid_argument("Shape with given ID does not exist");
    }

    return m_shapes.at(id)->SetColor(color);
}

void Picture::DrawShape(const string &id, ICanvas &canvas) const
{
    if (!m_shapes.contains(id))
    {
        throw invalid_argument("Shape with given ID does not exist");
    }
    m_shapes.at(id)->Draw(canvas);
}

void Picture::DrawPicture(ICanvas &canvas) const
{
    for (const auto& shape : m_shapes)
    {
        shape.second->Draw(canvas);
    }
}




