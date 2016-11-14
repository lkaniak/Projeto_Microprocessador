#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

class MEMORY
{
private:
	std::vector<std::string> memory;
	int size_limit;
public:
	MEMORY();
	MEMORY(int size);
	~MEMORY();

	bool save_to_address(int add);
	std::string load_from_address(int add);
	void load_file(std::ifstream *binary_file);

	const int get_size_limit();

    std::vector<std::string> *get_memory();
};

class cache : public MEMORY
{
private:
	int* tag;
	std::string* memory;
	int size_limit;
public:
	cache();
	cache(int size);
	~cache();
	bool cache_hit(int address);
	int mapping(int address);
	void save_to_cache(int address);
	std::string load_from_cache(int address);
	std::pair<int*,std::string*> get_cache();

};

