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
	static REGISTER *ip;
	MEMORY *memory;
	QUEUE *queue;
	DECODER *decoder;

public:
	BIU(std::ifstream *file);
	~BIU();

	bool execute();
	int increment_ip();
	int set_ip(int new_ip);
	static int get_ip();
};

