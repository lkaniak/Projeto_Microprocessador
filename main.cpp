/* 
 * File:   main.cpp
 * Author: Rafael Teixeira
 * Author: Lucas Kaniak
 *
 * Created on August 28, 2016, 10:15 AM
 */

#include "./headers/parser.h"
#include <fstream>
#include <vector>
#include <exception>

int main(int argc, char** argv)
{
    auto parser = Parser::get_instancia();
    std::ifstream programa;
    programa.open("./exemple.asm");
	if (!programa.is_open())
	{
		throw std::runtime_error("erro ao abrir arquivo de instrucoes");
	}
	try
	{
		std::cout << parser->make_object(programa) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << std::endl << std::endl << "###" << e.what() << std::endl;
	}
    
    
    return 0;
}

