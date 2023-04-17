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

Parser PRS;

int main(int argc, char **argv) {
	PRS = Parser(argc, argv);
	Reader *reader;

	try {
		cout << PRS.getInput() << endl;
		reader = new Reader(PRS.getInput());
		if (PRS.getDebug())
			reader->printMatrix();

		Partition partition(reader->getVertexCount());
#ifdef DEBUG
		partition.setSamplePartition();
#else
		partition.setOneZeroPartition();
#endif
		FM solver(*reader, partition);
		solver.calculate();
		solver.save(PRS.getInput()+".part.2");
	}
	catch (string &exception) {
		cerr<<exception;
		return -1;
	}

	return 0;
}

