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

//	������� ��� �����
	TokenType type() const;
	std::string lexeme() const;

private:
    TokenType m_type;           // ���� ������
    std::string m_lexeme;       // �������� ����
};

