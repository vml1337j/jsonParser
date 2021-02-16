#pragma once
#include <string>
#include <vector>
#include <map>

#include "Token.h"

class Parser
{
public:
	Parser();
	~Parser();
	
// ��������� ����� ��� �������������� json ������ � map <����:��������>
	std::map<std::string, std::string> parse(std::string jsonString);
private:
// ������ ��������, ��� ������ ������� �������������� �����
	void tokenize(std::string jsonString);

//	��������������� ������ �� ������ ��������
	void addToken(TokenType type, std::string lexem);
	void addString(std::string str);
	void skipWhiteSpace(std::string str);

	void parseToken();

//	����� ������������ ������ ��������� ��� �������
//  �������� parseObj ��� parseArray 
	void whatWeParse();
	void parseObj();
	void parseArray();
	
private:
	int m_current;	// ���������� ������� ������� � ������� ������� ��� json ������
	std::vector<Token> m_tokenizedString;
	std::map<std::string, std::string> m_filedValue;
};

