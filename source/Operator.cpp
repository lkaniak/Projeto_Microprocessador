/* 
 * File:   Operator.cpp
 * Author: Rafael Teixeira
 * 
 * Created on September 2, 2016, 6:06 PM
 */

#include "./../headers/Operator.h"

Operator::Operator(const std::string name, const std::string op_code)
      : name(name), 
        address(""), 
        op_code(op_code)
{
}

void Operator::update_address(std::string address)
{
    this->address = address;
}

std::string Operator::get_name() const
{
    return this->name;
}

std::string Operator::get_address() const
{
    return this->address;
}

std::string Operator::get_op_code() const
{
    return this->op_code;
}