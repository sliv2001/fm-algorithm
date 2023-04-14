/*
 * Parser.cpp
 *
 *  Created on: 11 апр. 2023 г.
 *      Author: ivans
 */

#include "Parser.hpp"
#include <iostream>

Parser::Parser(int argc, char** argv) : options("FM-splitter", "Program to divide graphs with FM-algorithm"){
	options.add_options()
			("input", "Input file path", cxxopts::value<std::string>());
	options.parse_positional({"input"});
	result=options.parse(argc, argv);
}

std::string Parser::getInput() {
	try{
		return result["input"].as<std::string>();
	}
	catch (cxxopts::exceptions::option_has_no_value &e){
		std::cerr<<e.what()<<std::endl;
		return "";
	}
}
