//
// Created by mrLogic on 10/9/2024.
//

#ifndef OOD_4_ISHAPEFACTORY_H
#define OOD_4_ISHAPEFACTORY_H

#pragma once
#include <string>
#include "../Interfaces/IShape.h"
#include "../Interfaces/ShapeUnit.h"


class IShapeFactory
{
public:
    virtual ~IShapeFactory() = default;
    virtual std::unique_ptr<ShapeUnit> CreateShape(const std::string& shapeDescription) = 0;
};

#endif //OOD_4_ISHAPEFACTORY_H
