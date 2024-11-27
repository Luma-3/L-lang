/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TokenStream.cc                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:53:21 by jbrousse          #+#    #+#             */
/*   Updated: 2024/11/27 22:00:54 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TokenStream.hh"

#include <algorithm>
#include <optional>
#include <stdexcept>

TokenStream::TokenStream(const TokenStream &src)
{
	_tokens = src._tokens;
	_index = src._index;
}

TokenStream &TokenStream::operator=(const TokenStream &rhs)
{
	if (this != &rhs) {
		_tokens = rhs._tokens;
		_index = rhs._index;
	}
	return *this;
}

bool TokenStream::eof() const noexcept
{
	return _index >= _tokens.size();
}

void TokenStream::clear() noexcept
{
	_tokens.clear();
	_index = 0;
}

size_t TokenStream::size() const noexcept
{
	return _tokens.size();
}

bool TokenStream::empty() const noexcept
{
	return _tokens.empty();
}

const Token &TokenStream::peek(size_t lookahead)
{
	if (_index + lookahead >= _tokens.size())
		throw std::out_of_range("TokenStream::peek out of range");
	return _tokens[_index + lookahead];
}

const Token &TokenStream::consume()
{
	if (_index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::consume out of range");
	}
	return _tokens[_index++];
}

void TokenStream::rewind(size_t steps) noexcept
{
	_index = (steps > _index) ? 0 : _index - steps;
}

void TokenStream::rewindTo(size_t index)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::rewindTo out of range");
	}
	_index = index;
}

void TokenStream::advance(size_t steps) noexcept
{
	_index = std::min(_index + steps, _tokens.size());
}

void TokenStream::advanceTo(size_t index)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::advanceTo out of range");
	}
	_index = index;
}

void TokenStream::push(const Token &token)
{
	_tokens.push_back(token);
}

void TokenStream::push(const std::vector< Token > &tokens)
{
	_tokens.insert(_tokens.end(), tokens.begin(), tokens.end());
}

void TokenStream::insert(size_t index, const Token &token)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::insert out of range");
	}
	_tokens.insert(_tokens.begin() + index, token);
}

void TokenStream::insert(size_t index, const std::vector< Token > &tokens)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::insert out of range");
	}
	_tokens.insert(_tokens.begin() + index, tokens.begin(), tokens.end());
}

void TokenStream::erase(size_t index)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::erase out of range");
	}
	_tokens.erase(_tokens.begin() + index);
}

void TokenStream::erase(size_t start, size_t end)
{
	if (start >= _tokens.size() || end >= _tokens.size()) {
		throw std::out_of_range("TokenStream::erase out of range");
	}
	_tokens.erase(_tokens.begin() + start, _tokens.begin() + end + 1);
}

void TokenStream::erase(const Token &token)
{
	auto it = std::find(_tokens.begin(), _tokens.end(), token);
	if (it == _tokens.end()) {
		throw std::out_of_range("TokenStream::erase out of range");
	}
	_tokens.erase(it);
}

void TokenStream::replace(size_t index, const Token &token)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::replace out of range");
	}
	_tokens[index] = token;
}

void TokenStream::replace(const Token &oldToken, const Token &newToken)
{
	auto it = std::find(_tokens.begin(), _tokens.end(), oldToken);
	if (it == _tokens.end()) {
		throw std::invalid_argument("TokenStream::replace old token not found");
	}
	*it = newToken;
}

const Token &TokenStream::operator[](size_t index) const
{
	return _tokens[index];
}

Token &TokenStream::operator[](size_t index)
{
	return _tokens[index];
}

const Token &TokenStream::at(size_t index) const
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::at out of range");
	}
	return _tokens[index];
}

Token &TokenStream::at(size_t index)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::at out of range");
	}
	return _tokens[index];
}