/*
 * main.cpp
 *
 *  Created on: 11 апр. 2023 г.
 *      Author: ivans
 */

#include <iostream>
#include "Parser.hpp"
#include "Reader.hpp"
#include "Partition.hpp"

using namespace std;

int main(int argc, char **argv) {
	Parser parser(argc, argv);
	Reader *reader;
	Partition partition;
	try {
		cout << parser.getInput() << endl;

		reader = new Reader(parser.getInput());
		reader->printMatrix();
		partition.initPartition(reader->getVertexCount());
		partition.setOneZeroPartition();

	}
	catch (string &exception) {
		cerr<<exception;
	}


	return 0;
}

