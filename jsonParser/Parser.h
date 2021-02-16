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
	
// ѕубличный метод дл€ преобразовани€ json строки в map <поле:значение>
	std::map<std::string, std::string> parse(std::string jsonString);
private:
// —тади€ лексинга, где каждой лексеме сопоставл€етс€ токен
	void tokenize(std::string jsonString);

//	¬спомогательные методы из стадии лексинга
	void addToken(TokenType type, std::string lexem);
	void addString(std::string str);
	void skipWhiteSpace(std::string str);

	void parseToken();

//	ћетод определ€ющий начало структуры или массива
//  вызывает parseObj или parseArray 
	void whatWeParse();
	void parseObj();
	void parseArray();
	
private:
	int m_current;	// определ€ет текущую позицию в векторе токенов или json строке
	std::vector<Token> m_tokenizedString;
	std::map<std::string, std::string> m_filedValue;
};

