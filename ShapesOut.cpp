    //
// Created by Misha on 06.04.2024.
//

#include "Commands/ShapesCommandProcessor.h"
#include "Picture/Picture.h"

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        CommandProcessor(std::cin);
    }
    else if (argc == 2)
    {
        std::fstream file(argv[1]);
        CommandProcessor(file);
    }
    return 0;
}


