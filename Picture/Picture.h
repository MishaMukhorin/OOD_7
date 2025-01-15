//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_4_PICTURE_H
#define OOD_4_PICTURE_H

#include "../Interfaces/ShapeUnit.h"
#include <vector>
#include <map>

class Picture
{
public:

    void AddShape(const std::string& id, std::unique_ptr<ShapeUnit> shape);
    void DeleteShape(const std::string& id);

    [[nodiscard]] std::string GetShapeStrokeColorById(const std::string& id) const;
    [[nodiscard]] std::string GetShapeFillColorById(const std::string& id) const;

    [[nodiscard]] std::string GetShapeById(const std::string& id) const;
    void ListShapeDescriptions() const;

    void ChangeShapeColor(const std::string& id, const std::string& color);

    void DrawShape(const std::string& id, ICanvas& canvas) const;
    void DrawPicture(ICanvas& canvas) const;

private:
    std::map<std::string, std::unique_ptr<ShapeUnit>> m_shapes;
};


#endif //OOD_4_PICTURE_H
