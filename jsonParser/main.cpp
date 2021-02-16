#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Parser.h"
#include "Person.h"


int main() 
{
	setlocale(LC_ALL, "Russian");

	std::ifstream jsonFile{ "file.txt" };
	std::string jsonString, tmp;



	while (!jsonFile.eof())
	{
		getline(jsonFile, tmp);
		jsonString += tmp;
	}

	Parser parser;
	Person person;
	try
	{
		person = parser.parse(jsonString);
		std::cout << person;
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << ex.what();
	}

	return 0;
}