//
// Created by mrLogic on 10/9/2024.
//
#include "ShapeFactory.h"

ShapeFactory::ShapeFactory()
{
    const std::string S = R"(\s+)";
    const std::string SHAPE_TYPE = R"([\w]+)";
    const std::string ID = R"(([\w\d]+))";
    const std::string DESCRIPTION = R"((.+))";

    shapeRegex = std::regex(SHAPE_TYPE + S + ID + S + DESCRIPTION);
}

std::unique_ptr<ShapeUnit> ShapeFactory::CreateShape(const std::string &shapeDescription)
{
    std::smatch match;
    if (regex_match(shapeDescription, match, shapeRegex))
    {
        std::string id = match[1].str();
        std::string shapeDetails = match[3].str();
        return std::make_unique<ShapeUnit>(id, shapeTypeFactory.CreateShape(shapeDetails));
    }
    else throw std::invalid_argument("Can't parse shape description");
}
