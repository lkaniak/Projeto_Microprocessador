
#define instructions_file "./data/symbols.d"
#define operators_file "./data/operator.d"

#include "./../headers/instruction_Set.h"

instruction_Set *instruction_Set::instancia = nullptr;

instruction_Set * instruction_Set::get_instancia()
{
    if (!instancia)
    {
        instancia = new instruction_Set();
    }

    return instancia;
}

instruction_Set::instruction_Set()
{
    this->load_instructions();
    this->load_operators();
}


instruction_Set::~instruction_Set()
{
}

void instruction_Set::execute_instruction(std::string op, REGISTER * r1, REGISTER * r2)
{
	if (op.compare("MOV") == 0)
		this->mov(r1, r2);
	else if (op.compare("ADD") == 0)
		this->add(r1, r2);
	else if (op.compare("SUB") == 0)
		this->sub(r1, r2);
	else if (op.compare("DIV") == 0)
		this->div(r1, r2);
	else if (op.compare("MUL") == 0)
		this->mul(r1, r2);
	else
		throw std::runtime_error("Instruction Not Found");
}

void instruction_Set::execute_instruction(std::string op, REGISTER * r1)
{
	if (op.compare("CMP") == 0)
		this->cmp(r1);
	else if (op.compare("AND") == 0)
		this->_and(r1);
	else if (op.compare("OR") == 0)
		this->_or(r1);
	else if (op.compare("XOR") == 0)
		this->_xor(r1);
	else if (op.compare("PUSH") == 0)
		this->push(r1);
	else if (op.compare("POP") == 0)
		this->pop(r1);
	else if (op.compare("NOT") == 0)
		this->_not(r1);
	else if (op.compare("INC") == 0)
		this->inc(r1);
	else if (op.compare("DEC") == 0)
		this->dec(r1);
	else if (op.compare("LOAD") == 0)
		this->load(r1);
	else if (op.compare("STORE") == 0)
		this->store(r1);
	else if (op.compare("INT") == 0)
		this->interrupt(r1);
	else if (op.compare("JMP") == 0)
		this->jmp(r1);
	else if (op.compare("JG") == 0)
		this->jg(r1);
	else if (op.compare("JE") == 0)
		this->je(r1);
	else if (op.compare("JNE") == 0)
		this->jne(r1);
	else if (op.compare("JL") == 0)
		this->jl(r1);
	else if (op.compare("JZ") == 0)
		this->jz(r1);
	else if (op.compare("JNZ") == 0)
		this->jnz(r1);
	else if (op.compare("JA") == 0)
		this->ja(r1);
	else if (op.compare("JB") == 0)
		this->jb(r1);
	else if (op.compare("RET") == 0)
		this->ret(r1);
	else if (op.compare("CALL") == 0)
		this->call(r1);
	else
		throw std::runtime_error("Instruction Not Found");
}

void instruction_Set::execute_instruction(std::string op)
{
	if (op.compare("START") == 0)
		this->start();
	else if (op.compare("END") == 0)
		this->end();
	else
		throw std::runtime_error("Instruction Not Found");
}

void instruction_Set::load_instructions()
{
    auto utils = utils::get_instancia();
    std::ifstream symbols_file;
    symbols_file.open(instructions_file);

    if (!symbols_file.is_open())
    {
        throw std::runtime_error("Failed to open symbols file.");
    }

    std::cout << "Loading symbols... ";
    std::string line;
    for (std::getline(symbols_file, line); !symbols_file.eof(); std::getline(symbols_file, line))
    {
        auto line_tokens = utils->split_line(line, ' ');
        auto i = new Instruction(line_tokens[0], line_tokens[1], std::stoi(line_tokens[2]));
        this->instructions.push_back(i);
    }
    symbols_file.close();
    std::cout << "Done." << std::endl;
}

void instruction_Set::load_operators()
{
    auto utils = utils::get_instancia();
    std::ifstream op_file;
    op_file.open(operators_file);

    if (!op_file.is_open())
    {
        throw std::runtime_error("Failed to open operator file.");
    }

    std::cout << "Loading operators... ";
    std::string line;
    for (std::getline(op_file, line); !op_file.eof(); std::getline(op_file, line))
    {
        auto line_tokens = utils->split_line(line, ' ');
        this->operators.push_back(new Instruction(line_tokens[0], line_tokens[1], -1));
    }
    op_file.close();
    std::cout << "Done." << std::endl;
}

Instruction *instruction_Set::get_operation_info(const std::string name)
{
    // Verifica tabela de instrucoes
    for (auto i = 0; i < this->instructions.size(); i++)
    {
        if (this->instructions[i]->get_name() == name)
        {
            return this->instructions[i];
        }
        
    }
    
    // Verifica tabela de registradores
    for (auto i = 0; i < this->operators.size(); i++)
    {
        if (this->operators[i]->get_name() == name)
        {
            return this->operators[i];
        }
    }
    
    return nullptr;
}

Instruction *instruction_Set::get_operation_name(const std::string opcode)
{
	// Verifica tabela de instrucoes
	for (auto i = 0; i < this->instructions.size(); i++)
	{
		if (this->instructions[i]->get_opcode() == opcode)
		{
			return this->instructions[i];
		}

	}

	// Verifica tabela de registradores
	for (auto i = 0; i < this->operators.size(); i++)
	{
		if (this->operators[i]->get_opcode() == opcode)
		{
			return this->operators[i];
		}
	}

	return nullptr;
}

//////////////////////////////////////
//  LISTA DE INSTRUCOES COMECA AQUI //
//////////////////////////////////////
/*
void instruction_Set::execute_instruction(instruction_line op)
{

}*/

void instruction_Set::mov(REGISTER *r1, REGISTER *r2)
{
	auto alu = ALU::get_instancia();
	auto bus = BUS::get_instancia();
	bus->transfer(r1, r2);
}

void instruction_Set::mov(REGISTER *r1, int num)
{
	auto alu = ALU::get_instancia();
	auto bus = BUS::get_instancia();
	//bus->transfer(r1, num);
}

void instruction_Set::add(REGISTER *r1, REGISTER *r2)
{
	auto alu = ALU::get_instancia();
	auto bus = BUS::get_instancia();
	bus->transfer(r1, alu->get_first());
	bus->transfer(r2, alu->get_second());
	alu->execute(r1, '+');
}

void instruction_Set::sub(REGISTER *r1, REGISTER *r2)
{
	auto alu = ALU::get_instancia();
	auto bus = BUS::get_instancia();
	bus->transfer(r1, alu->get_first());
	bus->transfer(r2, alu->get_second());
	alu->execute(r1, '-');
}

void instruction_Set::div(REGISTER *r1, REGISTER *r2)
{
	auto alu = ALU::get_instancia();
	auto bus = BUS::get_instancia();
	bus->transfer(r1, alu->get_first());
	bus->transfer(r2, alu->get_second());
	alu->execute(r1, '/');
}

void instruction_Set::mul(REGISTER *r1, REGISTER *r2)
{
	auto alu = ALU::get_instancia();
	auto bus = BUS::get_instancia();
	bus->transfer(r1, alu->get_first());
	bus->transfer(r2, alu->get_second());
	alu->execute(r1, '*');
}

void instruction_Set::cmp(REGISTER *r1)
{
	auto alu = ALU::get_instancia();
	auto bus = BUS::get_instancia();
	bus->transfer(r1, alu->get_first());
	alu->execute(r1, 'c');
}

void instruction_Set:: _and(REGISTER *r1)
{
	auto alu = ALU::get_instancia();
	auto bus = BUS::get_instancia();
	bus->transfer(r1, alu->get_first());
	alu->execute(r1, '&');
}

void instruction_Set:: _or(REGISTER *r1)
{
	auto alu = ALU::get_instancia();
	auto bus = BUS::get_instancia();
	bus->transfer(r1, alu->get_first());
	alu->execute(r1, '|');
}

void instruction_Set:: _xor(REGISTER *r1)
{
	auto alu = ALU::get_instancia();
	auto bus = BUS::get_instancia();
	bus->transfer(r1, alu->get_first());
	alu->execute(r1, 'x');
}

void instruction_Set::push(REGISTER *r1)
{
}

void instruction_Set::pop(REGISTER *r1)
{
}

void instruction_Set::_not(REGISTER *r1)
{
	auto alu = ALU::get_instancia();
	auto bus = BUS::get_instancia();
	bus->transfer(r1, alu->get_first());
	alu->execute(r1, '~');
}

void instruction_Set::inc(REGISTER *r1)
{
	auto alu = ALU::get_instancia();
	auto bus = BUS::get_instancia();
	bus->transfer(r1, alu->get_first());
	alu->execute(r1, '+');
}

void instruction_Set::dec(REGISTER *r1)
{
	auto alu = ALU::get_instancia();
	auto bus = BUS::get_instancia();
	bus->transfer(r1, alu->get_first());
	alu->execute(r1, '-');
}

void instruction_Set::load(REGISTER *r1)
{
}

void instruction_Set::store(REGISTER *r1)
{
}

void instruction_Set::interrupt(REGISTER *r1)
{
}

void instruction_Set::jmp(REGISTER *r1)
{
}

void instruction_Set::jg(REGISTER *r1)
{
}

void instruction_Set::je(REGISTER *r1)
{
}

void instruction_Set::jne(REGISTER *r1)
{
}

void instruction_Set::jl(REGISTER *r1)
{
}

void instruction_Set::jz(REGISTER *r1)
{
}

void instruction_Set::jnz(REGISTER *r1)
{
}

void instruction_Set::ja(REGISTER *r1)
{
}

void instruction_Set::jb(REGISTER *r1)
{
}

void instruction_Set::ret(REGISTER *r1)
{
}

void instruction_Set::call(REGISTER *r1)
{
}

void instruction_Set::start()
{
}

void instruction_Set::end()
{
}
