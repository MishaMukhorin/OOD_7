//
// Created by Misha on 29.03.2024.
//
#include "ShapesCommandProcessor.h"

using namespace std;

void
LineProcessor(std::map<std::string, shared_ptr<IShape>> &shapes, const string &line) {
    const string NUM = R"((\d+(?:\.\d+)?))";
    const string FLOATNUM = R"((-?\d+(?:\.\d+)?))";
    const string SPACE = R"(\s+)";
    const string POINT = FLOATNUM + SPACE + FLOATNUM;
    const string COLOR = R"(([0-9A-Fa-f]{8}))";
    const string IDS = R"((?:([\w\d]+)/s)+)";
    const string ID = R"(([\w\d]+))";
    vector<pair<regex, function<void(const smatch &match)>>> commandMap
            {
                    {regex(R"(line\s+)" + ID + SPACE + POINT + SPACE + POINT + SPACE + COLOR + SPACE + NUM),
                            [&shapes](const smatch &match) {
                                shared_ptr<CLineSegment> line =
                                        make_shared<CLineSegment>(CPoint(stof(match[2]), stof(match[3])),
                                                                  CPoint(stof(match[4]), stof(match[5])),
                                                                  make_shared<LineStyle>(Color(match[6]),
                                                                                         stof(match[7])));

                                shapes.emplace(match[1], line);
                            }},
                            //rectangle s20 270 850 40 100 000000ff 964b00ff 2
                    {regex(R"(rectangle\s+)" + ID + SPACE + POINT + SPACE + NUM + SPACE + NUM + SPACE + COLOR + SPACE
                           + COLOR + SPACE + NUM),
                            [&shapes](const smatch &match) {
                                shared_ptr<CRectangle> rect =
                                        make_shared<CRectangle>(CPoint(stof(match[2]), stof(match[3])),
                                                                stof(match[4]),
                                                                stof(match[5]),
                                                                make_shared<LineStyle>(Color(match[6]),
                                                                                       stof(match[8])),
                                                                make_shared<FillStyle>(Color(match[7])));

                                shapes.emplace(match[1], rect);
                            }},
                    {regex(R"(ellipse\s+)" + ID + SPACE + POINT + SPACE + NUM + SPACE + NUM + SPACE + COLOR + SPACE + COLOR +
                           SPACE + NUM),
                            [&shapes](const smatch &match) { //вынести в фабрику
                                shared_ptr<CEllipse> circle = make_shared<CEllipse>(
                                        CPoint(stof(match[2]), stof(match[3])),
                                        stof(match[4]),
                                        stof(match[5]),
                                        make_shared<LineStyle>(Color(match[6]), stof(match[8])),
                                        make_shared<FillStyle>(Color(match[7])));

                                shapes.emplace(match[1], circle);
                            }},
                    {regex(R"(triangle\s+)" + ID + SPACE + POINT + SPACE + POINT + SPACE + POINT + SPACE +
                           COLOR + SPACE + COLOR + SPACE + NUM),
                            [&shapes](const smatch &match) {
                                shared_ptr<CTriangle> triangle = make_shared<CTriangle>( // заменить на unique
                                        CPoint(stof(match[2]), stof(match[3])),
                                        CPoint(stof(match[4]), stof(match[5])),
                                        CPoint(stof(match[6]), stof(match[7])),
                                        make_shared<LineStyle>(Color(match[8]),
                                                               stof(match[10])),
                                        make_shared<FillStyle>(Color(match[9])));
                                shapes.emplace(match[1], triangle);
                    }},
                    {regex(R"(group/s+)" + ID + SPACE + IDS),
                            [&shapes](const smatch &match) {
                                std::vector<std::string> shapesToGroup{};
                                for (int i = 2; i++; i <= match.size()) {
                                    if (shapes.contains(match[i])) {
                                        shapesToGroup.push_back(match[i]);
                                    } else {
                                        cout << "error: no shape with such id!" << endl;
                                        return;
                                    }
                                }
                                shared_ptr<CompositeShape> comp = make_shared<CompositeShape>();
                                for (const string &id: shapesToGroup) {
                                    comp->AddShape(shapes.at(id));
                                    shapes.erase(id);
                                }
                                shapes.emplace(match[1], comp);
                            }},

                    {regex(R"(addshape/s+)" + ID + SPACE + ID),
                            [&shapes](const smatch &match) {
                                    if (shapes.contains(match[1]) and shapes.contains(match[2])) {
                                        shapes.at(match[1])->AddShape(shapes.at(match[2]));
                                        shapes.erase(match[2]);
                                    } else {
                                        cout << "error: no shape with such id!" << endl;
                                    }
                        }},
                    {regex(R"(\/\/.*)"),
                            [](const smatch &match) {}}
            };

    for (const auto &cmd: commandMap) {
        smatch match;
        if (regex_match(line, match, cmd.first)) {
            cmd.second(match);
            return;
        }
    }
    cout << "error: invalid command!" << endl;
}


sf::RenderTexture *getTexture(CCanvas &canvas, int width = WIDTH, int height = HEIGHT) {
    sf::Sprite spriteFromRenderTexture(canvas.GetTexture().getTexture());
    auto *texture = new sf::RenderTexture;

    texture->create(width, height);
    texture->setSmooth(false);
    texture->setRepeated(false);
    texture->draw(spriteFromRenderTexture);
    return texture;
}

void
ReDrawOnWindow(const std::vector<std::shared_ptr<ICanvasDrowable>> &shapes, CCanvas &canvas, sf::RenderWindow &window,
               sf::View &view, const sf::Sprite &spriteFromTexture, const sf::Event &event) {
    canvas.DrawShapesOnTexture(shapes);
    sf::Sprite spriteFromTextureWindow(getTexture(canvas, event.size.width, event.size.height)->getTexture());

    view.setSize(event.size.width, event.size.height);
    window.clear();
    window.setSize({event.size.width, event.size.height});
    window.setView(view);
    window.draw(spriteFromTexture);
    window.display();
}

void WindowHandler(std::vector<std::shared_ptr<ICanvasDrowable>> &shapes) {
    CCanvas canvas;
    canvas.DrawShapesOnTexture(shapes);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), TITLE);

    sf::View view(sf::FloatRect(0, 0, WIDTH, HEIGHT));

    sf::Sprite spriteFromTexture(getTexture(canvas)->getTexture());
    window.setView(view);
    window.draw(spriteFromTexture);
    window.display();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Resized) {
                ReDrawOnWindow(shapes, canvas, window, view, spriteFromTexture, event);
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
}

void CommandProcessor(istream &str) {
    map<string, shared_ptr<IShape>> shapes{};


    string line;
    while (getline(str, line)) {
        if (line == "render") {
            break;
        }
        LineProcessor(shapes, line);
    }
    std::vector<std::shared_ptr<ICanvasDrowable>> shapesToDraw;
    for (const auto &[_, shape]: shapes) {
        shapesToDraw.push_back(shape);
    }
    WindowHandler(shapesToDraw);

}