/* 
 * File:   Operator.h
 * Author: Rafael Teixeira
 *
 * Created on September 2, 2016, 6:06 PM
 */

#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>

class Operator 
{
private:
    const std::string name;
    std::string address;
    const std::string op_code;
    
public:
    Operator(const std::string name, const std::string op_code);
    void update_address(std::string address);
    std::string get_name() const;
    std::string get_address() const;
    std::string get_op_code() const;

};

#endif /* OPERATOR_H */

