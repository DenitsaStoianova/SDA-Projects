#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Stack.h"

const int BUFF_SIZE = 256;

bool isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool isSymbol(char c)
{
	return c != '\\' && c != '"' && c != '(' && c != ')' && !isDigit(c);
}

bool isExpressionValid(const std::string& expr)
{
	size_t exprSize = expr.size();
	int bracketsCount = 0;
	for (size_t i = 0; i < exprSize; i++)
	{
		if (expr[i] == '\\')
		{
			if (i == exprSize - 1)
			{
				std::cout << "Invalid expression, you must have symbol after \\.\n";
				return false;
			}
		
			if (expr[i + 1] == '"')
			{
				i++;
			}
			
		}
		else if (isDigit(expr[i]))
		{
			if (expr[i] == '0')
			{
				std::cout << "Invalid expression, digit cannot be 0.\n";
				return false;
			}

			int index = i;
			int count = -1;
			while (expr[index] != '(' || index == exprSize - 1)
			{
				if (!isDigit(expr[index]))
				{
					std::cout << "Invalid expression, you cannot have symbols, different from opening bracket after digit.\n";
					return false;
				}
				count++;
				index++;
			}
			i += count;
		}
		else if (expr[i] == '(')
		{
			
			if (i == 0)
			{
				std::cout << "Invalid expression, you can have only digits before opening bracket.\n";
				return false;
			}

			bracketsCount++;
		}
		else if (expr[i] == ')')
		{
			if (bracketsCount == 0)
			{
				std::cout << "Invalid expression, brackets are not balanced.\n";
				return false;
			}

			bracketsCount--;
		}
		else if (expr[i] == '"')
		{
			int index = i + 1;
			int count = 1;
			while (expr[index] != '"' || (expr[index - 1] == '\\' && expr[index] == '"'))
			{
				count++;
				if (index == exprSize)
				{
					std::cout << "Invalid expression, other \" is missing.\n";
					return false;
				}
				index++;
			}
			
			i += count;
		}
	}

	if (bracketsCount != 0)
	{
		std::cout << "Invalid expression, brackets are not balanced.\n";
		return false;
	}

	return true;
}

void writeToResultTextFile(const char* secondTextFileName, char symbol)
{
	std::fstream file;
	file.open(secondTextFileName, std::ios::out | std::ios::app);

	if (!file)
	{
		std::cout << "Canot open " << secondTextFileName << " text file.\n";
		return;
	}

	file << symbol;
	file.close();
}

void readPartFromResultTextFile(const char* secondTextFileName, const int& count, int& numToRepeat, int& countWrittenSymbols)
{
	char buffer[BUFF_SIZE];

	int countOfSymbolsToWriteInFile = countWrittenSymbols - count;

	if (BUFF_SIZE > countOfSymbolsToWriteInFile)
	{
		std::ifstream file;
		file.open(secondTextFileName, std::ios::in);
		file.seekg(count, std::ios::beg);
		if (!file)
		{
			std::cout << "Canot open " << secondTextFileName << " text file.\n";
		}
		else
		{
			file.read(buffer, countOfSymbolsToWriteInFile);

			file.close();
		}

		std::ofstream ofile;
		ofile.open(secondTextFileName, std::ios::out | std::ios::app);
		if (!ofile)
		{
			std::cout << "Canot open " << secondTextFileName << " text file.\n";
		}
		else
		{
			while (--numToRepeat > 0)
			{
				for (int i = 0; i < countOfSymbolsToWriteInFile; i++)
				{
					ofile << buffer[i];
				}

				countWrittenSymbols += countOfSymbolsToWriteInFile;
			}

			ofile.close();
		}
	}
	else
	{
		int timesToWrite = countOfSymbolsToWriteInFile * (numToRepeat - 1);
		int pointerCount = count;
		while (timesToWrite > BUFF_SIZE)
		{
			std::ifstream file;
			file.open(secondTextFileName, std::ios::in);
			file.seekg(pointerCount, std::ios::beg);
			if (!file)
			{
				std::cout << "Canot open " << secondTextFileName << " text file.\n";
			}
			else
			{
				file.read(buffer, BUFF_SIZE);
				file.close();
			}

			std::ofstream ofile;
			ofile.open(secondTextFileName, std::ios::out | std::ios::app);
			if (!ofile)
			{
				std::cout << "Canot open " << secondTextFileName << " text file.\n";
			}
			else
			{
				for (int i = 0; i < BUFF_SIZE; ++i)
				{
					ofile << buffer[i];
				}

				countWrittenSymbols += BUFF_SIZE;
				pointerCount += BUFF_SIZE;

				ofile.close();
			}

			timesToWrite -= BUFF_SIZE;
		}

		if (timesToWrite != 0)
		{
			std::ifstream file;
			file.open(secondTextFileName, std::ios::in);
			file.seekg(pointerCount, std::ios::beg);
			if (!file)
			{
				std::cout << "Canot open " << secondTextFileName << " text file.\n";
			}
			else
			{

				file.read(buffer, timesToWrite);

				file.close();
			}

			std::ofstream ofile;
			ofile.open(secondTextFileName, std::ios::out | std::ios::app);
			if (!ofile)
			{
				std::cout << "Canot open " << secondTextFileName << " text file.\n";
			}
			else
			{
				for (int i = 0; i < timesToWrite; ++i)
				{
					ofile << buffer[i];
				}

				countWrittenSymbols += timesToWrite;

				ofile.close();
			}
		}

	}
}

int convertCharToNum(const std::string& expr, size_t& i)
{
	int charToNum = 0;
	while (isDigit(expr[i]))
	{
		charToNum = (charToNum * 10) + (expr[i++] - '0');
	}
	i--;
	return charToNum;
}

void makeString(const std::string& expr, size_t& i, int& countWrittenSymbols, const char* secondTextFileName)
{
	int index = i + 1;
	int count = 1;
	while (expr[index] != '"' || (expr[index - 1] == '\\' && expr[index] == '"'))
	{
		count++;
		writeToResultTextFile(secondTextFileName, expr[index]);
		countWrittenSymbols++;
		index++;
	}

	i += count;
}

void decompressExpr(const std::string& expr, const char* secondTextFileName)
{
	if (isExpressionValid(expr))
	{
		Stack stack;

		int countWrittenSymbols = 0;
		size_t exprSize = expr.size();
		for (size_t i = 0; i < exprSize; i++)
		{
			if (isSymbol(expr[i]))
			{
				writeToResultTextFile(secondTextFileName, expr[i]);
				countWrittenSymbols++;
			}
			else if (isDigit(expr[i]))
			{
				stack.push(convertCharToNum(expr, i));
			}
			else if (expr[i] == '(')
			{
				stack.push(countWrittenSymbols);
			}
			else if (expr[i] == ')')
			{
				int position = stack.getTop(); stack.pop();
				int numToRepeat = stack.getTop(); stack.pop();

				readPartFromResultTextFile(secondTextFileName, position, numToRepeat, countWrittenSymbols);

			}
			else if (expr[i] == '\\')
			{
				writeToResultTextFile(secondTextFileName, expr[i + 1]);
				i++;
				countWrittenSymbols++;
			}
			else if (expr[i] == '"')
			{
				makeString(expr, i, countWrittenSymbols, secondTextFileName);
			}
		}
	}
}

void readFromFirstTextFile(const char* firstTextFileName, const char* secondTextFileName)
{
	std::string fileLine;
	std::ifstream firstFile(firstTextFileName);

	if (!firstFile)
	{
		std::cout << "Cannot open " << firstTextFileName << " text file.\n";
	}
	else
	{
		while (firstFile.good())
		{
			std::getline(firstFile, fileLine);
		}

		firstFile.close();
	}

	decompressExpr(fileLine, secondTextFileName);
}

int main(int argc, char* argv[])
{
	char* firstTextFileName = argv[1];
	char* secondTextFileName = argv[2];

	readFromFirstTextFile(firstTextFileName, secondTextFileName);

	return 0;
}

