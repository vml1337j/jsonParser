#include "Parser.h"
#include <stdexcept>

Parser::Parser()
	: m_current{ 0 }
{
}

Parser::~Parser() {}

std::map<std::string, std::string> Parser::parse(std::string jsonString)
{
	tokenize(jsonString);
	parseToken();

	return m_filedValue;
}

void Parser::addToken(TokenType type,std::string lexem) {
	m_tokenizedString.push_back(Token(type, lexem));
	++m_current;
}

// То что находится между ковычек считается строкой и ей дается токен stringValue
void Parser::addString(std::string lexem)
{
	std::string temp;
	++m_current;

	while (lexem[m_current] != '\"')
	{
		temp += lexem[m_current];
		++m_current;
	}

	addToken(TokenType::valueString, temp);
}

void Parser::skipWhiteSpace(std::string str) {
	while (isspace(str[m_current])) {
		++m_current;
	}
}

void Parser::parseToken() {
	whatWeParse();
}

// метод определяющий что сейчас обрабатывается
void Parser::whatWeParse()
{
	if (m_tokenizedString[m_current].type() == TokenType::beginObject) {
		++m_current;
		parseObj();
	}
	else if (m_tokenizedString[m_current].type() == TokenType::beginArray) {
		++m_current;
		parseArray();
	}
}
 
void Parser::parseObj()
{
	while (m_tokenizedString[m_current].type() != TokenType::endObject)
	{
		TokenType currentToken = m_tokenizedString[m_current].type();

	//	Если встречается : то создается пара из предыдущего токена и последующего
		if (currentToken == TokenType::colon) {
			if (m_tokenizedString[m_current + 1].type() == TokenType::valueString) {
				m_filedValue.insert(std::make_pair(m_tokenizedString[m_current - 1].lexeme(), m_tokenizedString[m_current + 1].lexeme()));
				++m_current;
			}
	//	Если не встречается : то значит начался другой объект или массив
			else {
				++m_current;
				whatWeParse();
			}
		}
		
		++m_current;
	}
}

void Parser::parseArray()
{
	std::string array;
	std::string keyForArray = m_tokenizedString[m_current - 3].lexeme(); // Название массива 

	while (m_tokenizedString[m_current].type() != TokenType::endArray)
	{
		TokenType currentToken = m_tokenizedString[m_current].type();
	//	Создаем строку (ДАННЫЕ|ДАННЫЕ|...|)
		if (currentToken == TokenType::valueString) {
			array += m_tokenizedString[m_current].lexeme();
		}
		else if (currentToken == TokenType::comma) {
			array += "|";
		}
		else {
			whatWeParse();
		}

		++m_current;
	}

	array.push_back('|');
	// добавляем в map <КЛЮЧ, string(ДАННЫЕ|ДАННЫЕ|)> чтобы потом распарсить эту строку в вектор из телефонных номеров
	m_filedValue.insert(std::make_pair(keyForArray, array)); 
}

void Parser::tokenize(std::string jsonString)
{
	while (m_current < jsonString.length())
	{
		if (jsonString[m_current] == '{') {
			
			addToken(TokenType::beginObject, "{");
		}
		else if (jsonString[m_current] == '}') {
			addToken(TokenType::endObject, "}");
		}
		else if (jsonString[m_current] == '[') {
			addToken(TokenType::beginArray, "[");
		}
		else if (jsonString[m_current] == ']') {
			addToken(TokenType::endArray, "]");
		}
		else if (jsonString[m_current] == ',') {
			addToken(TokenType::comma, ",");
		}
		else if (jsonString[m_current] == ':') {
			addToken(TokenType::colon, ":");
		}
		else if (jsonString[m_current] == '\"') {
			addString(jsonString);
		}
		else if (isspace(jsonString[m_current])) {
			skipWhiteSpace(jsonString);
		}
		else {		
			std::string error = "Unknow symbol: ";
			error += jsonString[m_current];
			throw std::runtime_error(error);
		}
	}

	m_current = 0;
}
