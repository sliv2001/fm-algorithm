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
#include "FM.hpp"

using namespace std;

bool debug=0;

int main(int argc, char **argv) {
	Parser parser(argc, argv);
	Reader *reader;

	try {
		cout << parser.getInput() << endl;
		debug=parser.getDebug();
		reader = new Reader(parser.getInput());
		if (debug)
			reader->printMatrix();

		Partition partition(reader->getVertexCount());
#ifdef DEBUG
		partition.setSamplePartition();
#else
		partition.setOneZeroPartition();
#endif
		FM solver(*reader, partition);
		solver.calculate();
		solver.save(parser.getInput()+".part.2");
	}
	catch (string &exception) {
		cerr<<exception;
		return -1;
	}

	return 0;
}

