#pragma once
#include <string>
#include <vector>
#include <map>
#include <ostream>

struct Address
{
	std::string streetAddress;
	std::string city;
};

class Person
{
public:
	Person& operator=(std::map<std::string, std::string> obj);
	friend std::ostream& operator<<(std::ostream& out, Person& data);

	std::string firstName;
	std::string lastName;
	Address address;
	std::vector<std::string> phoneNumbers;
};