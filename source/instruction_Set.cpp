#ifdef _WIN32
#define instructions_file "./data/symbols.d"
#define operators_file "./data/operator.d"
#define build_file "./build/temp.obj"

#else // UNIX
#define instructions_file "../data/symbols.d"
#define operators_file "../data/operator.d"
#define build_file "../build/temp.obj"

#endif 

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
{/*
    for(auto it = this->operators.begin(); it !=  this->operators.end(); it++)
    {
        delete it;
    }
    for(auto it = this->instructions.begin(); it !=  this->instructions.end(); it++)
    {
        delete it;
    }
   */ 
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

//////////////////////////////////////
//  LISTA DE INSTRUCOES COMECA AQUI //
//////////////////////////////////////
void instruction_Set::execute_instruction(instruction_line op)
{

}
/*
void instruction_Set::execute_instruction(instruction_line op)
{

}*/

void instruction_Set::mov(Operator r1, Operator r2)
{
}

void instruction_Set::mov(Operator r1, int num)
{
}

void instruction_Set::add(Operator r1, Operator r2)
{
}

void instruction_Set::sub(Operator r1, Operator r2)
{
}

void instruction_Set::div(Operator r1, Operator r2)
{
}

void instruction_Set::mul(Operator r1, Operator r2)
{
}

void instruction_Set::cmp(Operator r1)
{
}

void instruction_Set:: _and(Operator r1)
{
}

void instruction_Set:: _or(Operator r1)
{
}

void instruction_Set:: _xor(Operator r1)
{
}

void instruction_Set::push(Operator r1)
{
}

void instruction_Set::pop(Operator r1)
{
}

void instruction_Set::_not(Operator r1)
{
}

void instruction_Set::inc(Operator r1)
{
}

void instruction_Set::dec(Operator r1)
{
}

void instruction_Set::load(Operator r1)
{
}

void instruction_Set::store(Operator r1)
{
}

void instruction_Set::interrupt(Operator r1)
{
}

void instruction_Set::jmp(Operator r1)
{
}

void instruction_Set::jg(Operator r1)
{
}

void instruction_Set::je(Operator r1)
{
}

void instruction_Set::jne(Operator r1)
{
}

void instruction_Set::jl(Operator r1)
{
}

void instruction_Set::jz(Operator r1)
{
}

void instruction_Set::jnz(Operator r1)
{
}

void instruction_Set::ja(Operator r1)
{
}

void instruction_Set::jb(Operator r1)
{
}

void instruction_Set::ret(Operator r1)
{
}

void instruction_Set::call(Operator r1)
{
}

void instruction_Set::start()
{
}

void instruction_Set::end()
{
}
