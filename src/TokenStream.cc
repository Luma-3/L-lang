/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TokenStream.cc                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:53:21 by jbrousse          #+#    #+#             */
/*   Updated: 2024/11/24 23:06:59 by jbrousse         ###   ########.fr       */
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

/**
 * @brief Checks if the token stream has reached the end.
 *
 * This function returns true if the token stream has reached the end,
 * i.e., the current index is equal to or greater than the size of the token
 * list.
 *
 * @return true if the token stream has reached the end, false otherwise.
 */
bool TokenStream::eof() const noexcept
{
	return _index >= _tokens.size();
}

/**
 * @brief Clears the token stream.
 *
 * This function clears the internal token container and resets the index to
 * zero. It ensures that the token stream is empty and ready for reuse.
 *
 * @note This function is marked as noexcept, indicating that it does not throw
 * any exceptions.
 */
void TokenStream::clear() noexcept
{
	_tokens.clear();
	_index = 0;
}

/**
 * @brief Returns the number of tokens in the stream.
 *
 * This function provides the size of the token stream by returning
 * the number of tokens currently stored in the stream.
 *
 * @return size_t The number of tokens in the stream.
 */
size_t TokenStream::size() const noexcept
{
	return _tokens.size();
}

/**
 * @brief Checks if the token stream is empty.
 *
 * This function returns true if there are no tokens in the stream,
 * otherwise it returns false.
 *
 * @return true if the token stream is empty, false otherwise.
 */
bool TokenStream::empty() const noexcept
{
	return _tokens.empty();
}

/**
 * @brief Peeks at a token in the stream without advancing the current position.
 *
 * This function returns a reference to the token at the specified lookahead
 * position from the current index. If the lookahead position is out of range,
 * it throws an std::out_of_range exception.
 *
 * @param lookahead The number of tokens ahead of the current index to peek at.
 * @return const Token& A reference to the token at the lookahead position.
 * @throws std::out_of_range If the lookahead position is beyond the end of the
 * token stream.
 */
const Token &TokenStream::peek(size_t lookahead)
{
	if (_index + lookahead >= _tokens.size())
		throw std::out_of_range("TokenStream::peek out of range");
	return _tokens[_index + lookahead];
}

/**
 * @brief Consumes the next token in the stream.
 *
 * This function returns a reference to the next token in the token stream
 * and increments the internal index to point to the subsequent token.
 * If the end of the token stream is reached, an std::out_of_range exception
 * is thrown.
 *
 * @return const Token& A reference to the next token in the stream.
 * @throws std::out_of_range If the internal index is out of the token stream's
 * range.
 */
const Token &TokenStream::consume()
{
	if (_index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::consume out of range");
	}
	return _tokens[_index++];
}

/**
 * @brief Rewinds the token stream by a specified number of steps.
 *
 * This function moves the current index of the token stream backwards
 * by the given number of steps. If the number of steps is greater than
 * the current index, the index is set to 0.
 *
 * @param steps The number of steps to rewind the token stream.
 */
void TokenStream::rewind(size_t steps) noexcept
{
	_index = (steps > _index) ? 0 : _index - steps;
}

/**
 * @brief Rewinds the token stream to the specified index.
 *
 * This function sets the current index of the token stream to the given index.
 * If the specified index is out of the range of the token stream, an
 * std::out_of_range exception is thrown.
 *
 * @param index The index to rewind to.
 * @throws std::out_of_range If the specified index is greater than or equal to
 * the size of the token stream.
 */
void TokenStream::rewindTo(size_t index)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::rewindTo out of range");
	}
	_index = index;
}

/**
 * @brief Advances the token stream by a specified number of steps.
 *
 * This function increments the current index of the token stream by the given
 * number of steps. If the resulting index exceeds the size of the token list,
 * it will be capped at the size of the token list.
 *
 * @param steps The number of steps to advance the token stream.
 */
void TokenStream::advance(size_t steps) noexcept
{
	_index = std::min(_index + steps, _tokens.size());
}

/**
 * @brief Advances the token stream to the specified index.
 *
 * This function sets the current index of the token stream to the given index.
 * If the index is out of range, it throws a std::out_of_range exception.
 *
 * @param index The index to advance to.
 * @throws std::out_of_range If the index is greater than or equal to the size
 * of the token stream.
 */
void TokenStream::advanceTo(size_t index)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::advanceTo out of range");
	}
	_index = index;
}

/**
 * @brief Adds a token to the token stream.
 *
 * This function appends the given token to the end of the internal token list.
 *
 * @param token The token to be added to the token stream.
 */
void TokenStream::push(const Token &token)
{
	_tokens.push_back(token);
}

/**
 * @brief Adds a collection of tokens to the end of the token stream.
 *
 * This function takes a vector of tokens and appends them to the existing
 * token stream, preserving the order of the tokens.
 *
 * @param tokens A vector of Token objects to be added to the token stream.
 */
void TokenStream::push(const std::vector< Token > &tokens)
{
	_tokens.insert(_tokens.end(), tokens.begin(), tokens.end());
}

/**
 * @brief Inserts a token at the specified index in the token stream.
 *
 * @param index The position at which to insert the token.
 * @param token The token to be inserted.
 *
 * @throws std::out_of_range If the index is out of the range of the token
 * stream.
 */
void TokenStream::insert(size_t index, const Token &token)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::insert out of range");
	}
	_tokens.insert(_tokens.begin() + index, token);
}

/**
 * @brief Inserts a sequence of tokens into the token stream at the specified
 * index.
 *
 * @param index The position in the token stream where the tokens should be
 * inserted. Must be less than the current size of the token stream.
 * @param tokens A vector of tokens to be inserted into the token stream.
 *
 * @throws std::out_of_range If the index is greater than or equal to the size
 * of the token stream.
 */
void TokenStream::insert(size_t index, const std::vector< Token > &tokens)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::insert out of range");
	}
	_tokens.insert(_tokens.begin() + index, tokens.begin(), tokens.end());
}

/**
 * @brief Erases a token from the token stream at the specified index.
 *
 * This function removes the token at the given index from the token stream.
 * If the index is out of range, it throws a std::out_of_range exception.
 *
 * @param index The position of the token to be removed.
 * @throws std::out_of_range If the index is greater than or equal to the size
 * of the token stream.
 */
void TokenStream::erase(size_t index)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::erase out of range");
	}
	_tokens.erase(_tokens.begin() + index);
}

/**
 * @brief Erases a range of tokens from the token stream.
 *
 * This function removes tokens from the token stream starting at the
 * specified start index and ending at the specified end index.
 *
 * @param start The starting index of the range to erase (inclusive).
 * @param end The ending index of the range to erase (exclusive).
 *
 * @throws std::out_of_range if either start or end is out of the range
 *         of the token stream.
 */
void TokenStream::erase(size_t start, size_t end)
{
	if (start >= _tokens.size() || end >= _tokens.size()) {
		throw std::out_of_range("TokenStream::erase out of range");
	}
	_tokens.erase(_tokens.begin() + start, _tokens.begin() + end);
}

/**
 * @brief Erases a token from the token stream.
 *
 * This function searches for the specified token in the token stream and
 * removes it if found. If the token is not found, it throws an
 * std::out_of_range exception.
 *
 * @param token The token to be erased from the token stream.
 *
 * @throws std::out_of_range If the token is not found in the token stream.
 */
void TokenStream::erase(const Token &token)
{
	auto it = std::find(_tokens.begin(), _tokens.end(), token);
	if (it == _tokens.end()) {
		throw std::out_of_range("TokenStream::erase out of range");
	}
	_tokens.erase(it);
}

/**
 * @brief Replaces the token at the specified index with the given token.
 *
 * @param index The index of the token to replace.
 * @param token The new token to place at the specified index.
 * @throws std::out_of_range If the index is out of the range of the token
 * stream.
 */
void TokenStream::replace(size_t index, const Token &token)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::replace out of range");
	}
	_tokens[index] = token;
}

/**
 * @brief Replaces a range of tokens in the token stream with a single token.
 *
 * This function removes the tokens in the range [start, end) and inserts the
 * given token at the start position.
 *
 * @param start The starting index of the range to be replaced.
 * @param end The ending index of the range to be replaced.
 * @param token The token to insert at the start position.
 *
 * @throws std::out_of_range If either start or end is out of the bounds of the
 * token stream.
 */
void TokenStream::replace(size_t start, size_t end, const Token &token)
{
	if (start >= _tokens.size() || end >= _tokens.size()) {
		throw std::out_of_range("TokenStream::replace out of range");
	}
	_tokens.erase(_tokens.begin() + start, _tokens.begin() + end);
	_tokens.insert(_tokens.begin() + start, token);
}

/**
 * @brief Replaces an existing token in the token stream with a new token.
 *
 * This function searches for the specified old token in the token stream.
 * If the old token is found, it is replaced with the new token. If the old
 * token is not found, an std::out_of_range exception is thrown.
 *
 * @param oldToken The token to be replaced.
 * @param newToken The token to replace with.
 * @throws std::out_of_range If the old token is not found in the token stream.
 */
void TokenStream::replace(const Token &oldToken, const Token &newToken)
{
	auto it = std::find(_tokens.begin(), _tokens.end(), oldToken);
	if (it == _tokens.end()) {
		throw std::out_of_range("TokenStream::replace out of range");
	}
	*it = newToken;
}

/**
 * @brief Overloaded subscript operator to access tokens by index.
 *
 * This operator allows read-only access to the tokens in the TokenStream
 * by providing an index. It returns a constant reference to the token
 * at the specified index.
 *
 * @param index The index of the token to access.
 * @return const Token& A constant reference to the token at the specified
 * index.
 */
const Token &TokenStream::operator[](size_t index) const
{
	return _tokens[index];
}

/**
 * @brief Overloaded subscript operator to access tokens by index.
 *
 * This operator allows read-only access to the tokens in the TokenStream
 * by providing an index. It returns a constant reference to the token
 * at the specified index.
 *
 * @param index The index of the token to access.
 * @return const Token& A constant reference to the token at the specified
 * index.
 */
Token &TokenStream::operator[](size_t index)
{
	return _tokens[index];
}

/**
 * @brief Retrieves the token at the specified index.
 *
 * This function returns a reference to the token at the given index in the
 * token stream. If the index is out of range, it throws a std::out_of_range
 * exception.
 *
 * @param index The index of the token to retrieve.
 * @return const Token& A reference to the token at the specified index.
 * @throws std::out_of_range If the index is out of the range of the token
 * stream.
 */
const Token &TokenStream::at(size_t index) const
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::at out of range");
	}
	return _tokens[index];
}

/**
 * @brief Retrieves the token at the specified index.
 *
 * This function returns a reference to the token at the given index in the
 * token stream. If the index is out of range, it throws a std::out_of_range
 * exception.
 *
 * @param index The index of the token to retrieve.
 * @return const Token& A reference to the token at the specified index.
 * @throws std::out_of_range If the index is out of the range of the token
 * stream.
 */
Token &TokenStream::at(size_t index)
{
	if (index >= _tokens.size()) {
		throw std::out_of_range("TokenStream::at out of range");
	}
	return _tokens[index];
}