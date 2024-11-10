//
// Created by Misha on 29.03.2024.
//
#include "ShapesCommandProcessor.h"

using namespace std;

void LineProcessor(vector<unique_ptr<ICanvasDrowable>>& shapes, vector<ISolidShape*>& solidShapes, const string& line)
{
    const string NUM = R"((\d+(?:\.\d+)?))";
    const string FLOATNUM = R"((-?\d+(?:\.\d+)?))";
    const string SPACE = R"(\s+)";
    const string POINT = FLOATNUM + SPACE + FLOATNUM;
    const string COLOR = R"(([0-9A-Fa-f]{8}))";
    const string COLOROREMPTY = R"(([0-9A-Fa-f]{8}|))";
    vector<pair<regex, function<void(const smatch &match)>>> commandMap
        {
            {regex(R"(line\s+)" + POINT + SPACE + POINT + SPACE + COLOR),
             [&shapes](const smatch &match)
                {
                    shapes.emplace_back(make_unique<CLineSegment>(CPoint(stof(match[1]), stof(match[2])),
                                                                  CPoint(stof(match[3]), stof(match[4])),
                                                                  Color(match[5])));
                }},
            {regex(R"(rectangle\s+)" + POINT + SPACE + NUM + SPACE + NUM + SPACE + COLOR + SPACE + COLOROREMPTY),
             [&shapes, &solidShapes](const smatch &match)
                {
                    unique_ptr<CRectangle> rect = make_unique<CRectangle>(CPoint(stof(match[1]), stof(match[2])),
                                                                          stof(match[3]),
                                                                          stof(match[4]),
                                                                          Color(match[5]),
                                                                          Color(match[6]));

                    solidShapes.emplace_back(rect.get());
                    shapes.emplace_back(std::move(rect));
                }},
            {regex(R"(circle\s+)" + POINT + SPACE + NUM + SPACE + COLOR + SPACE + COLOROREMPTY),
             [&shapes, &solidShapes](const smatch &match)
                {
                    unique_ptr<CCircle> circle = make_unique<CCircle>(CPoint(stof(match[1]), stof(match[2])),
                                                    stof(match[3]),
                                                    Color(match[4]),
                                                    Color(match[5]));

                    solidShapes.emplace_back(circle.get());
                    shapes.emplace_back(std::move(circle));
                }},
            {regex(R"(triangle\s+)" + POINT + SPACE + POINT + SPACE + POINT + SPACE + COLOR + SPACE + COLOROREMPTY),
             [&shapes, &solidShapes](const smatch &match)
                {
                    unique_ptr<CTriangle> triangle = make_unique<CTriangle>(CPoint(stof(match[1]), stof(match[2])),
                                                      CPoint(stof(match[3]), stof(match[4])),
                                                      CPoint(stof(match[5]), stof(match[6])),
                                                      Color(match[7]),
                                                      Color(match[8]));
                    solidShapes.emplace_back(triangle.get());
                    shapes.emplace_back(std::move(triangle));
                }},
            {regex(R"(\/\/.*)"),
             [](const smatch &match) {}}
        };

    for (const auto& cmd : commandMap)
    {
        smatch match;
        if (regex_match(line, match, cmd.first))
        {
            cmd.second(match);
            return;
        }
    }
    cout << "error: invalid command!" << endl;
}

ISolidShape* GetMaxArea(vector<ISolidShape*> &shapes)
{
    auto largestAreaShape = *max_element(shapes.begin(), shapes.end(), [](ISolidShape* a, ISolidShape* b)
    {
        return a->GetArea() < b->GetArea();
    });
    return largestAreaShape;
}

ISolidShape* GetMinPerimeter(vector<ISolidShape *> shapes)
{
    auto smallestPerimeterShape = *min_element(shapes.begin(), shapes.end(), [](ISolidShape* a, ISolidShape* b)
    {
        return a->GetPerimeter() < b->GetPerimeter();
    });
    return smallestPerimeterShape;
}

void PrintShape(const ISolidShape *shape)
{
    cout << "Smallest perimeter shape: " << shape->ToString() << endl;
}

sf::RenderTexture* getTexture(CCanvas &canvas, int width = WIDTH, int height = HEIGHT)
{
    sf::Sprite spriteFromRenderTexture(canvas.GetTexture().getTexture());
    auto* texture = new sf::RenderTexture;

    texture->create(width, height);
    texture->setSmooth(false);
    texture->setRepeated(false);
    texture->draw(spriteFromRenderTexture);
    return texture;
}

void ReDrawOnWindow(const vector<unique_ptr<ICanvasDrowable>> &shapes, CCanvas &canvas, sf::RenderWindow &window,
                    sf::View &view, const sf::Sprite &spriteFromTexture, const sf::Event &event)
{
    canvas.DrawShapesOnTexture(shapes);
    sf::Sprite spriteFromTextureWindow(getTexture(canvas, event.size.width, event.size.height)->getTexture());

    view.setSize(event.size.width, event.size.height);
    window.clear();
    window.setSize({event.size.width, event.size.height});
    window.setView(view);
    window.draw(spriteFromTexture);
    window.display();
}

void WindowHandler(vector<unique_ptr<ICanvasDrowable>>& shapes)
{
    CCanvas canvas;
    canvas.DrawShapesOnTexture(shapes);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), TITLE);

    sf::View view(sf::FloatRect(0, 0, WIDTH, HEIGHT));

    sf::Sprite spriteFromTexture(getTexture(canvas)->getTexture());
    window.setView(view);
    window.draw(spriteFromTexture);
    window.display();

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Resized)
            {
                ReDrawOnWindow(shapes, canvas, window, view, spriteFromTexture, event);
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
}

void CommandProcessor(istream& str)
{
    vector<unique_ptr<ICanvasDrowable>> shapes{};
    vector<ISolidShape*> solidShapes{};

    string line;
    while (getline(str,line))
    {
        if (line == "render")
        {
            break;
        }
        LineProcessor(shapes, solidShapes, line);
    }
    if (solidShapes.empty())
    {
        cout << "There is no solid shapes!" << endl;
    }
    else
    {
        PrintShape(GetMaxArea(solidShapes));
        PrintShape(GetMinPerimeter(solidShapes));
    }

    WindowHandler(shapes);

}