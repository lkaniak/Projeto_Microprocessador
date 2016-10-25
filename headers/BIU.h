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
	REGISTER *ip;
	MEMORY *memory;
	QUEUE *queue;
	DECODER *decoder;

public:
	BIU(std::ifstream *file);
	~BIU();

	void execute();
};

