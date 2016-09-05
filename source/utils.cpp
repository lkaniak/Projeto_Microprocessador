/* 
 * File:   utils.cpp
 * Author: Rafael Teixeira
 * 
 * Created on September 3, 2016, 10:21 AM
 */

#include "./../headers/utils.h"

utils *utils::instancia = nullptr;

utils *utils::get_instancia()
{
    if (!instancia)
    {
        instancia = new utils();
    }
    
    return instancia;
}

utils::utils()
{
}

std::vector<std::string> utils::split_line(const std::string &text, const char sep) {
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        std::string temp = text.substr(start, end - start);
        if (temp != "") tokens.push_back(temp);
        start = end + 1;
    }
    std::string temp = text.substr(start);
    if (temp != "") tokens.push_back(temp);
    return tokens;
}
