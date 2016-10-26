#include "../headers/BIU.h"

BIU *BIU::instancia = nullptr;

BIU *BIU::get_instancia()
{
	if (!instancia)
	{
		instancia = new BIU();
	}

	return instancia;
}

BIU::BIU()
{
	this->ip = new REGISTER("ip");
	this->memory = new MEMORY(255);
	this->decoder = new DECODER();
	this->queue = new QUEUE();
}


BIU::~BIU()
{
}

bool BIU::execute()
{
	auto instruction = queue->get_instruction();
	auto decoded_instruction = decoder->decode(instruction);

	if (decoded_instruction[0].compare("END") == 0)
		return true;
	else if (decoded_instruction.size() == 3)
	{
		try
		{			
			EU::get_instancia()->process(decoded_instruction[0],
				decoded_instruction[1],
				std::stoi(decoded_instruction[2]));
		}
		catch (std::exception)
		{
			EU::get_instancia()->process(decoded_instruction[0],
				decoded_instruction[1],
				decoded_instruction[2]);
		}
	}
	else if (decoded_instruction.size() == 2)
	{
		try
		{
			/*EU::get_instancia()->process(decoded_instruction[0],
				std::stoi(decoded_instruction[1]));*/
		}
		catch (std::exception)
		{
			EU::get_instancia()->process(decoded_instruction[0],
				decoded_instruction[1]);
		}
	}
	else
	{
		EU::get_instancia()->process(decoded_instruction[0]);
	}

	// Incrementa IP em 1
//	this->increment_ip();

	return false;

}

int BIU::increment_ip()
{
	this->ip->set_value(ip->get_value() + 1);
	return ip->get_value();
}

int BIU::set_ip_value(int new_ip)
{
	ip->set_value(new_ip);
	queue->clear();
	return ip->get_value();
}

int BIU::get_ip_value()
{
	return ip->get_value();
}

void BIU::load_file(std::ifstream * file)
{
	this->memory->load_file(file);
}

std::string BIU::get_address_from_memory_with_ip()
{
	return memory->load_from_address(this->ip->get_value());
}

const int BIU::get_memory_size_limit()
{
	return this->memory->get_size_limit() - 1;
}

