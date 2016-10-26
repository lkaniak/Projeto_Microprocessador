#pragma once
#include <fstream>

#include "REGISTER.h"
#include "MEMORY.h"
#include "QUEUE.h"
#include "STACK.h"
#include "DECODER.h"

class BIU
{
private:
	static BIU* instancia;

	REGISTER *ip;
	MEMORY *memory;
	QUEUE *queue;
	DECODER *decoder;
	
	BIU();
	~BIU();
public:
	static BIU* get_instancia();

	bool execute();
	int increment_ip();
	int set_ip_value(int new_ip);
	int get_ip_value();
	void load_file(std::ifstream *file);
};

