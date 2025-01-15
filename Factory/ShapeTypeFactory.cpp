//
// Created by mrLogic on 10/9/2024.
//

#include "ShapeTypeFactory.h"
#include "../Shapez/CRectangle.h"
#include "../Shapez/CEllipse.h"
#include "../Shapez/CTriangle.h"
#include "../Shapez/CLineSegment.h"
#include "../Shapez/CPoint.h"
#include "../Shapez/CompositeShape.h"

ShapeTypeFactory::ShapeTypeFactory()
{
    const std::string NUM = R"((\d+(?:\.\d+)?))";
    const std::string FLOATNUM = R"((-?\d+(?:\.\d+)?))";
    const std::string SPACE = R"(\s+)";
    const std::string POINT = FLOATNUM + SPACE + FLOATNUM;
    const std::string COLOR = R"(([0-9A-Fa-f]{8}))";
    const std::string IDS = R"((?:([\w\d]+)/s)+)";
    const std::string ID = R"(([\w\d]+))";

    // Line: line <id> <x1> <y1> <x2> <y2> <lineColor> <m_width>
    std::string LINE_REGEX;
    LINE_REGEX = R"(line\s+)" + ID + SPACE + POINT + SPACE + POINT + SPACE + COLOR + SPACE + NUM;

    // Line: <id> rectangle <x> <y> <m_width> <m_height>
    std::string RECTANGLE_REGEX;
    RECTANGLE_REGEX = R"(rectangle\s+)" + ID + SPACE + POINT + SPACE + NUM + SPACE + NUM +
            SPACE + COLOR + SPACE + COLOR + SPACE + NUM;

    // Line: ellipse <id> <x1> <y1> <xradius> <yradius> <lineColor> <fillColor> <m_width>
    std::string ELLIPSE_REGEX;
    ELLIPSE_REGEX = R"(ellipse\s+)" + ID + SPACE + POINT + SPACE + NUM + SPACE + NUM + SPACE + COLOR + SPACE + COLOR +
                 SPACE + NUM;

    // Line: triangle <id> <x1> <y1> <x2> <y2> <x3> <y3> <lineColor> <fillColor> <m_width>
    std::string TRIANGLE_REGEX;
    TRIANGLE_REGEX = R"(triangle\s+)" + ID + SPACE + POINT + SPACE + POINT + SPACE + POINT + SPACE +
                 COLOR + SPACE + COLOR + SPACE + NUM;

    // Line: group <id> <ids>
    std::string GROUP_REGEX;
    GROUP_REGEX = R"(group/s+)" + ID + SPACE + IDS;


    shapeMap = {
            // Line: line <id> <x1> <y1> <x2> <y2> <lineColor> <m_width>
            //regex(R"(line\s+)" + ID + SPACE + POINT + SPACE + POINT + SPACE + COLOR + SPACE + NUM
            {std::regex(LINE_REGEX),
                [](const std::smatch &match)
                {

                    float x1 = stof(match[2]);
                    float y1 = stof(match[3]);
                    float x2 = stof(match[4]);
                    float y2 = stof(match[5]);
                    Color lineColor = Color(match[6]);
                    float lineWidth = stof(match[7]);

                    return std::move(
                            std::make_unique<CLineSegment>(CPoint(x1, y1), CPoint(x2, y2),
                                                           LineStyle(lineColor, lineWidth)));

                }
            },
            // Line: <id> rectangle <x> <y> <m_width> <m_height>
            //regex(R"(rectangle\s+)" + ID + SPACE + POINT + SPACE + NUM + SPACE + NUM + SPACE + COLOR + SPACE + COLOR + SPACE + NUM)
            {std::regex(RECTANGLE_REGEX),
                [](const std::smatch &match)
                {
                    float x = stof(match[2].str());
                    float y = stof(match[3].str());
                    float width = stof(match[4].str());
                    float height = stof(match[5].str());
                    Color lineColor = Color(match[6]);
                    Color fillColor = Color(match[7]);
                    float lineWidth = stof(match[8]);

                    return std::move(
                            std::make_unique<CRectangle>(CPoint(x, y), width, height,
                                                         LineStyle(lineColor, lineWidth),
                                                         FillStyle(fillColor)));
                }
            },

            // Line: ellipse <id> <x> <y> <xradius> <yradius> <lineColor> <fillColor> <m_width>
            {std::regex(ELLIPSE_REGEX),
                [](const std::smatch &match)
                {
                    float x = stof(match[2].str());
                    float y = stof(match[3].str());
                    float xradius = stof(match[4].str());
                    float yradius = stof(match[5].str());
                    Color lineColor = Color(match[6]);
                    Color fillColor = Color(match[7]);
                    float lineWidth = stof(match[8]);

                    return std::move(
                            std::make_unique<CEllipse>(CPoint(x, y), xradius, yradius,
                                                       LineStyle(lineColor, lineWidth),
                                                       FillStyle(fillColor)));

                }
            },

            // Line: triangle <id> <x1> <y1> <x2> <y2> <x3> <y3> <lineColor> <fillColor> <m_width>
            {std::regex(TRIANGLE_REGEX),
                [](const std::smatch &match)
                {
                    float x1 = stof(match[2].str());
                    float y1 = stof(match[3].str());
                    float x2 = stof(match[4].str());
                    float y2 = stof(match[5].str());
                    float x3 = stof(match[6].str());
                    float y3 = stof(match[7].str());
                    Color lineColor = Color(match[8]);
                    Color fillColor = Color(match[9]);
                    float lineWidth = stof(match[10]);

                    return std::move(
                            std::make_unique<CTriangle>(CPoint(x1, y1), CPoint(x2, y2),
                                                        CPoint(x3, y3),
                                                        LineStyle(lineColor, lineWidth),
                                                        FillStyle(fillColor)));
                }
            },


            // Line: group <id> <ids>
            {std::regex(GROUP_REGEX),
                [](const std::smatch &match)
                {
                    std::vector<std::string> shapesToGroup{};

                    std::unique_ptr<CompositeShape> comp = std::make_unique<CompositeShape>();

                    for (int i = 2; i++; i <= match.size())
                    {
                        comp->AddUnresolvedId(match[i]);

                        shapesToGroup.push_back(match[i]);
                    }
                    return std::move(comp);
                }
            },
    };
}

std::unique_ptr<IShape> ShapeTypeFactory::CreateShape(const std::string& shapeDetails)
{
    for (const auto& shape : shapeMap)
    {
        std::regex shapeRegex(shape.first);
        std::smatch match;
        if (std::regex_search(shapeDetails, match, shapeRegex))
        {
            return shape.second(match);
        }
    }
    throw std::invalid_argument("Can't parse shape details");
}

