/* 
 * File:   main.cpp
 * Author: Rafael Teixeira
 * Author: Lucas Kaniak
 *
 * Created on August 28, 2016, 10:15 AM
 */

#include "./parser/parser.h"
#include <fstream>

int main(int argc, char** argv)
{
    auto parser = Parser::get_instancia();
    std::ifstream programa;
    programa.open("./exemple.asm");
    if (!programa.is_open())
        throw std::runtime_error("erro ao abrir arquivo de instrucoes");
    parser->make_object(programa);
    
    
    return 0;
}

