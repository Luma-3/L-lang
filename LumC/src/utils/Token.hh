/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hh                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:51:44 by jbrousse          #+#    #+#             */
/*   Updated: 2024/11/24 23:46:34 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HH
#define TOKEN_HH

#include <string>
#include <vector>

/**
 * @brief Token class representing a token in the source code
 * A token is a pair of a type and a value
 *
 * @param _type The type of the token
 * @param _value The value of the token
 * @param _line The line where the token is located
 * @param _column The column where the token is located
 */
class Token
{
  public:
	enum class Type {
		IDENTIFIER,
		NUMBER,
		FUNCTION,
		RETURN,
		PLUS,
		MINUS,
		MULTIPLY,
		DIVIDE,
		EQUAL,
		SEMICOLON,
		OPEN_PARENTHESIS,
		CLOSE_PARENTHESIS,
		OPEN_BRACE,
		CLOSE_BRACE,
		COMMA,
		END_OF_FILE
	};

	Token() = default;
	Token(Type type, std::string value = "", size_t line = 0,
		  size_t column = 0) :
		_type(type),
		_value(value),
		_line(line),
		_column(column) {};

	~Token() = default;

	Type		getType() const { return _type; };
	std::string getValue() const { return _value; };
	size_t		getLine() const { return _line; };
	size_t		getColumn() const { return _column; };

	bool operator==(const Token &rhs) const
	{
		return _type == rhs._type && _value == rhs._value;
	}

  private:
	Type		_type;
	std::string _value;
	size_t		_line;
	size_t		_column;
};

#endif // TOKEN_HH