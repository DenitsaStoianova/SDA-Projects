// Task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "CircularWordsList.h"

int main()
{
	CircularWordsList list;

	std::string line;
	while (std::getline(std::cin, line))
	{
		list.pushBack(line);
	}

	list.print();
	list.findLongestWord();
	list.concatenateWords();
	list.print();
	list.sortList();
	list.print();

	return 0;
}
