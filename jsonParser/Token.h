#pragma once
#include <string>

enum class TokenType {
    beginObject,    // {
    endObject,      // }
    beginArray,     // [
    endArray,       // ]
    comma,          // ','
    colon,          // ':'
    valueString     // string
};

class Token
{
public:
	Token(TokenType type, std::string lexem);

//	Геттеры для полей
	TokenType type() const;
	std::string lexeme() const;

private:
    TokenType m_type;           // Типы лексем
    std::string m_lexeme;       // Значение поля
};

