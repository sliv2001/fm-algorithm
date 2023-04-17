/*
 * Parser.hpp
 *
 *  Created on: 11 апр. 2023 г.
 *      Author: ivans
 */

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include "cxxopts.hpp"

class Parser {
private:
	cxxopts::Options options;
	cxxopts::ParseResult result;
public:
	Parser():options("", ""){};
	Parser(int, char**);
	virtual ~Parser(){};
	std::string getInput();
	bool getDebug();
};

#endif /* PARSER_HPP_ */
