#include "Person.h"

std::vector <std::string> splitString(std::string str);

Person& Person::operator=(std::map<std::string, std::string> obj)
{
	firstName = obj["firstName"];
	lastName = obj["lastName"];
	address.streetAddress = obj["streetAddress"];
	address.city = obj["city"];
	phoneNumbers = splitString(obj["phoneNumbers"]);

	return *this;
}

std::ostream& operator<<(std::ostream& out, Person& data)
{
	out << "FirstName: " << data.firstName << "\n";
	out << "LastName: " << data.lastName << "\n";
	out	<< "streetAddress: " << data.address.streetAddress << "\n" 
		<< "city: " << data.address.city << "\n";
	out << "PhoneNumbers: " << "\n";

	for (const auto& element : data.phoneNumbers) {
		out << element << "\n";
	}

	return out;
}

// разделение строки "ДАННЫЕ|ДАННЫЕ|...|" и занесение в вектор
std::vector<std::string> splitString(std::string str)
{
	std::string tmp;
	std::vector<std::string> array;

	for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] != '|') {
			tmp += str[i];
		}
		else {
			array.push_back(tmp);
			tmp.clear();
		}
	};

	return array;
}