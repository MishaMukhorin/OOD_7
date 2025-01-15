//
// Created by mrLogic on 10/9/2024.
//

#ifndef OOD_4_GEOMETRYTYPEFACTORY_H
#define OOD_4_GEOMETRYTYPEFACTORY_H

#pragma once
#include <regex>
#include <map>
#include <functional>
#include "../Interfaces/IShape.h"


class ShapeTypeFactory
{
public:
    ShapeTypeFactory();
    std::unique_ptr<IShape> CreateShape(const std::string& shapeDetails);

private:
    std::vector<std::pair<std::regex, std::function<std::unique_ptr<IShape>(const std::smatch &match)>>> shapeMap;
};


#endif //OOD_4_GEOMETRYTYPEFACTORY_H
