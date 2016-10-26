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
#include <algorithm>

#include "headers/utils.h"
#include "headers/BIU.h"

void build(std::vector<std::string> commands, int size)
{
	auto parser = Parser::get_instancia();
    std::ifstream programa;
	programa.open(commands[size - 2]);

	if (!programa.is_open())
	{
		throw std::runtime_error("Erro ao abrir arquivo de instrucoes.\nVerifique se o caminho esta correto.\n");
	}
	try
	{
		std::cout << parser->make_object(programa, commands[size - 1]) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << std::endl << std::endl << "###" << e.what() << std::endl;
	}
}

void run(std::vector<std::string> commands, int size)
{
	std::ifstream programa;
	programa.open(commands[size - 1]);

	if (!programa.is_open())
	{
		throw std::runtime_error("Erro ao abrir arquivo de instrucoes.\nVerifique se o caminho esta correto.\n");
	}
	try
	{ 
		auto bui = new BIU(&programa);
		auto end = false;
		while (!end)
		{
			end = bui->execute();
		}
	}
	catch (std::exception &e)
	{
		std::cout << std::endl << std::endl << "###" << e.what() << std::endl;
	}
}

int main(int argc, char** argv)
{
	auto utils_inst = utils::get_instancia();
	std::string command = "";

	while (command.find("exit") != 0)
	{
		std::cout << ">";
		std::getline(std::cin, command);

		if (command.find("build") == 0)
		{
			auto build_command =  utils_inst->split_line(command, ' ');
			if (build_command.size() > 2)
			{
				try
				{
					build(build_command, build_command.size());
				}
				catch (std::exception &e)
				{
					std::cout << std::endl << std::endl << "###\n" << e.what() << "###\n" << std::endl;
				}
			}
			else
			{
				std::cout << "Uso incorreto do commando BUILD\nBUILD [PARAM] <INPUT FILE> <OUTPUT FOLDER>\n\n";
			}
		}

		if (command.find("run") == 0)
		{
			auto run_command = utils_inst->split_line(command, ' ');
			if (run_command.size() > 1)
			{
				try
				{
					run(run_command, run_command.size());
				}
				catch (std::exception &e)
				{
					std::cout << std::endl << std::endl << "###\n" << e.what() << "###\n" << std::endl;
				}
			}
			else
			{
				std::cout << "Uso incorreto do commando BUILD\nBUILD [PARAM] <INPUT FILE> <OUTPUT FOLDER>\n\n";
			}
		}
		// Manda o commando inserido para minusculo
		std::transform(command.begin(), command.end(), command.begin(), ::tolower);
	}
}

