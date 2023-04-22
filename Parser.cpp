/*
 * Parser.cpp
 *
 *  Created on: 18 апр. 2023 г.
 *      Author: ivans
 */

#include "Parser.hpp"
#include <string>

using namespace std;

Parser::Parser(int argc, char** argv) : options("FM-splitter", "Program to divide graphs with FM-algorithm"){
	options.add_options()
			("input", "Input file path", cxxopts::value<std::string>())
			("d,debug", "Set debug options")
			("m,modify", "Use modification")
			("value", "Use cut-off value in modification", cxxopts::value<int>());
	options.parse_positional({"input"});
	result=options.parse(argc, argv);
}

std::string Parser::getPath() {
	return result["input"].as<string>();
}

bool Parser::getMod() {
	try{
		return result["modify"].as<bool>();
	}
	catch (cxxopts::exceptions::option_has_no_value &e){
		return 0;
	}
}

int Parser::getModValue() {
	try{
		int res =  result["value"].as<int>();
		if (!getMod() && res>0)
			throw "You should set modification";
		return res;
	}
	catch(cxxopts::exceptions::option_has_no_value &e){
		return 0;
	}
}
