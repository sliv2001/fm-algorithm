/*
 * Parser.hpp
 *
 *  Created on: 18 апр. 2023 г.
 *      Author: ivans
 */

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "cxxopts.hpp"

class Parser {
private:
	cxxopts::Options options;
	cxxopts::ParseResult result;
public:
	Parser():options("", ""){};
	Parser(int argc, char** argv);
	virtual ~Parser(){};
	std::string getPath();
	bool getMod();
};

#endif /* PARSER_HPP_ */
