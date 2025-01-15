//
// Created by mrLogic on 10/9/2024.
//

#ifndef OOD_4_SHAPEFACTORY_H
#define OOD_4_SHAPEFACTORY_H

#include <regex>
#include <memory>
#include <utility>
#include <functional>
#include "IShapeFactory.h"
#include "../Interfaces/ShapeUnit.h"

#include "../Factory/ShapeTypeFactory.h"


class ShapeFactory : public IShapeFactory
{
public:
    ShapeFactory();
    std::unique_ptr<ShapeUnit> CreateShape(const std::string& shapeDescription) override;

private:
    std::regex shapeRegex;
    ShapeTypeFactory shapeTypeFactory {};
};



#endif //OOD_4_SHAPEFACTORY_H
