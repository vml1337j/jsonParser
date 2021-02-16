#include "Token.h"

Token::Token(TokenType type, std::string lexem)
	: m_type{ type },
	  m_lexeme{ lexem }
{

}

TokenType Token::type() const {
	return m_type;
}

std::string Token::lexeme() const {
	return m_lexeme;
}
