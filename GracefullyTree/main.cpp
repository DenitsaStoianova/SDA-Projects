#include "pch.h"
#include <iostream>
#include "GracefullyTree.h"

/*
	Празното дърво с произволен брой наследници се чете от текстов файл.

	Например дървото
					  0
					/ | \
				   0  0  0
				  / \
				 0   0
	има следната структура при четене от файла:

				[0[0[0][0]][0][0]]

	Ако подаденото дърво може да бъде попълнено, така че да е грациозно,
	то отново се записва в текстов файл имайки същата структура.
*/

int main(int argc, char* argv[])
{
	char* textFilePath = argv[1];

	Tree tree;
	tree.readEmptyTreeFromTextFile(textFilePath);

	return 0;
}
