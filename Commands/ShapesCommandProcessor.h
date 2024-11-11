//
// Created by Misha on 06.04.2024.
//

#include <regex>
#include <iostream>
#include <string>
#include <fstream>
#include "../Shapez/CTriangle.h"
#include "../Shapez/CCircle.h"
#include "../Shapez/CRectangle.h"
#include "../Shapez/CompositeShape.h"
#include "../Canvas/CCanvas.h"

#ifndef OOP_4_SHAPESCOMMANDPROCESSOR_H
#define OOP_4_SHAPESCOMMANDPROCESSOR_H


void CommandProcessor(std::istream& str);
void PrintShape(const ISolidShape *shape);

ISolidShape* GetMinPerimeter(std::vector<ISolidShape *> shapes);
ISolidShape* GetMaxArea(std::vector<ISolidShape *> &shapes);





#endif //OOP_4_SHAPESCOMMANDPROCESSOR_H
