#pragma once
#include <fstream>
#include <exception>

#include "REGISTER.h"
#include "MEMORY.h"
#include "STACK.h"
#include "DECODER.h"

class QUEUE;

class BIU
{
private:
	static BIU* instancia;

	REGISTER *ip;
	MEMORY *memory;
	QUEUE *queue;
	
	BIU();
	~BIU();
public:
	static BIU* get_instancia();

	bool execute();
	int increment_ip();
	int set_ip_value(int new_ip);
	int get_ip_value();
	void load_file(std::ifstream *file);
	std::string get_address_from_memory_with_ip();
	const int get_memory_size_limit();

    std::vector<std::string> *get_memory();
};

