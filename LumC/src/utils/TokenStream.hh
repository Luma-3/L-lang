/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TokenStream.hh                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:04:16 by jbrousse          #+#    #+#             */
/*   Updated: 2024/11/27 22:33:02 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMC_UTILS_TOKENSTREAM_HH
#define LUMC_UTILS_TOKENSTREAM_HH

#include <cstddef>
#include <vector>

#include "Token.hh"

/**
 * @brief TokenStream class representing a stream of tokens
 *
 * A TokenStream is a container of Token objects that provides methods to
 * manipulate the tokens in the stream. It allows for operations such as
 * consuming tokens, peeking at tokens, rewinding the stream, and advancing
 * the stream.
 */
class TokenStream
{
  private:
	std::vector< Token > _tokens;
	size_t				 _index = 0;

  public:
	TokenStream() = default;
	/**
	 * @brief Construct a new TokenStream object
	 *
	 * @param tokens A vector of Token objects to initialize the stream with
	 */
	explicit TokenStream(std::vector< Token > tokens) : _tokens(tokens) {};
	/**
	 * @brief Copy constructor
	 *
	 * @param src The TokenStream object to copy
	 */
	TokenStream(const TokenStream &src);
	/**
	 * @brief Assignment operator
	 *
	 * @param rhs The TokenStream object to assign
	 * @return A reference to the assigned TokenStream object
	 */
	TokenStream &operator=(const TokenStream &rhs);
	~TokenStream() = default;

	/**
	 * @brief Checks if the token stream has reached the end.
	 *
	 * This function returns true if the token stream has reached the end,
	 * i.e., the current index is equal to or greater than the size of the token
	 * list.
	 *
	 * @return true if the token stream has reached the end, false otherwise.
	 */
	bool eof() const noexcept;

	/**
	 * @brief Clears the token stream.
	 *
	 * This function clears the internal token container and resets the index to
	 * zero. It ensures that the token stream is empty and ready for reuse.
	 *
	 * @note This function is marked as noexcept, indicating that it does not
	 * throw any exceptions.
	 */
	void clear() noexcept;

	/**
	 * @brief Returns the number of tokens in the stream.
	 *
	 * This function provides the size of the token stream by returning
	 * the number of tokens currently stored in the stream.
	 *
	 * @return size_t The number of tokens in the stream.
	 */
	size_t size() const noexcept;

	/**
	 * @brief Checks if the token stream is empty.
	 *
	 * This function returns true if there are no tokens in the stream,
	 * otherwise it returns false.
	 *
	 * @return true if the token stream is empty, false otherwise.
	 */
	bool empty() const noexcept;

	/**
	 * @brief Peeks at a token in the stream without advancing the current
	 * position.
	 *
	 * This function returns a reference to the token at the specified lookahead
	 * position from the current index. If the lookahead position is out of
	 * range, it throws an std::out_of_range exception.
	 *
	 * @param lookahead The number of tokens ahead of the current index to peek
	 * at.
	 * @return const Token& A reference to the token at the lookahead position.
	 * @throws std::out_of_range If the lookahead position is beyond the end of
	 * the token stream.
	 */
	const Token &peek(size_t lookahead = 0);

	/**
	 * @brief Consumes the next token in the stream.
	 *
	 * This function returns a reference to the next token in the token stream
	 * and increments the internal index to point to the subsequent token.
	 * If the end of the token stream is reached, an std::out_of_range exception
	 * is thrown.
	 *
	 * @return const Token& A reference to the next token in the stream.
	 * @throws std::out_of_range If the internal index is out of the token
	 * stream's range.
	 */
	const Token &consume();

	/**
	 * @brief Rewinds the token stream by a specified number of steps.
	 *
	 * This function moves the current index of the token stream backwards
	 * by the given number of steps. If the number of steps is greater than
	 * the current index, the index is set to 0.
	 *
	 * @param steps The number of steps to rewind the token stream.
	 */
	void rewind(size_t steps = 1) noexcept;

	/**
	 * @brief Rewinds the token stream to the specified index.
	 *
	 * This function sets the current index of the token stream to the given
	 * index. If the specified index is out of the range of the token stream, an
	 * std::out_of_range exception is thrown.
	 *
	 * @param index The index to rewind to.
	 * @throws std::out_of_range If the specified index is greater than or equal
	 * to the size of the token stream.
	 */
	void rewindTo(size_t index);

	/**
	 * @brief Advances the token stream by a specified number of steps.
	 *
	 * This function increments the current index of the token stream by the
	 * given number of steps. If the resulting index exceeds the size of the
	 * token list, it will be capped at the size of the token list.
	 *
	 * @param steps The number of steps to advance the token stream.
	 */
	void advance(size_t steps = 1) noexcept;

	/**
	 * @brief Advances the token stream to the specified index.
	 *
	 * This function sets the current index of the token stream to the given
	 * index. If the index is out of range, it throws a std::out_of_range
	 * exception.
	 *
	 * @param index The index to advance to.
	 * @throws std::out_of_range If the index is greater than or equal to the
	 * size of the token stream.
	 */
	void advanceTo(size_t index);

	/**
	 * @brief Adds a token to the token stream.
	 *
	 * This function appends the given token to the end of the internal token
	 * list.
	 *
	 * @param token The token to be added to the token stream.
	 */
	void push(const Token &token);

	/**
	 * @brief Adds a collection of tokens to the end of the token stream.
	 *
	 * This function takes a vector of tokens and appends them to the existing
	 * token stream, preserving the order of the tokens.
	 *
	 * @param tokens A vector of Token objects to be added to the token stream.
	 */
	void push(const std::vector< Token > &tokens);

	/**
	 * @brief Inserts a token at the specified index in the token stream.
	 *
	 * @param index The position at which to insert the token.
	 * @param token The token to be inserted.
	 *
	 * @throws std::out_of_range If the index is out of the range of the token
	 * stream.
	 */
	void insert(size_t index, const Token &token);

	/**
	 * @brief Inserts a sequence of tokens into the token stream at the
	 * specified index.
	 *
	 * @param index The position in the token stream where the tokens should be
	 * inserted. Must be less than the current size of the token stream.
	 * @param tokens A vector of tokens to be inserted into the token stream.
	 *
	 * @throws std::out_of_range If the index is greater than or equal to the
	 * size of the token stream.
	 */
	void insert(size_t index, const std::vector< Token > &tokens);

	/**
	 * @brief Erases a token from the token stream at the specified index.
	 *
	 * This function removes the token at the given index from the token stream.
	 * If the index is out of range, it throws a std::out_of_range exception.
	 *
	 * @param index The position of the token to be removed.
	 * @throws std::out_of_range If the index is greater than or equal to the
	 * size of the token stream.
	 */
	void erase(size_t index);

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
	void erase(size_t start, size_t end);

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
	void erase(const Token &token);

	/**
	 * @brief Replaces the token at the specified index with the given token.
	 *
	 * @param index The index of the token to replace.
	 * @param token The new token to place at the specified index.
	 * @throws std::out_of_range If the index is out of the range of the token
	 * stream.
	 */
	void replace(size_t index, const Token &token);

	/**
	 * @brief Replaces an existing token in the token stream with a new token.
	 *
	 * This function searches for the specified old token in the token stream.
	 * If the old token is found, it is replaced with the new token. If the old
	 * token is not found, an std::out_of_range exception is thrown.
	 *
	 * @param oldToken The token to be replaced.
	 * @param newToken The token to replace with.
	 * @throws std::out_of_range If the old token is not found in the token
	 * stream.
	 */
	void replace(const Token &oldToken, const Token &newToken);

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
	const Token &operator[](size_t index) const;

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
	Token &operator[](size_t index);

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
	const Token &at(size_t index) const;

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
	Token &at(size_t index);

	/**
	 * @brief TokenStream iterator class
	 *
	 * This class provides an iterator interface for the TokenStream class,
	 * allowing for iteration over the tokens in the stream.
	 *
	 * @param _stream The TokenStream object to iterate over.
	 * @param _index The current index of the iterator.
	 */
	class iterator
	{
	  private:
		TokenStream *_stream;
		size_t		 _index;

	  public:
		iterator() = default;

		/**
		 * @brief Construct a new iterator object
		 *
		 * @param stream The TokenStream object to iterate over.
		 * @param index The current index of the iterator.
		 */
		iterator(TokenStream *stream, size_t index) :
			_stream(stream),
			_index(index) {};

		/**
		 * @brief Copy constructor
		 *
		 * @param src The iterator object to copy.
		 */
		iterator(const iterator &src) :
			_stream(src._stream),
			_index(src._index) {};

		/**
		 * @brief Assignment operator
		 * @param rhs The iterator object to assign.
		 * @return A reference to the assigned iterator object.
		 */

		iterator &operator=(const iterator &rhs)
		{
			_stream = rhs._stream;
			_index = rhs._index;
			return *this;
		};
		~iterator() = default;

		iterator &operator++()
		{
			++_index;
			return *this;
		};
		iterator operator++(int)
		{
			iterator tmp = *this;
			++_index;
			return tmp;
		};
		iterator &operator--()
		{
			--_index;
			return *this;
		};
		iterator operator--(int)
		{
			iterator tmp = *this;
			--_index;
			return tmp;
		};
		iterator &operator+=(size_t steps)
		{
			_index += steps;
			return *this;
		};
		iterator &operator-=(size_t steps)
		{
			_index -= steps;
			return *this;
		};
		Token *operator->() { return &(_stream->at(_index)); };
		Token &operator*() { return _stream->at(_index); };

		bool operator==(const iterator &rhs) const
		{
			return _index == rhs._index;
		};
		bool operator!=(const iterator &rhs) const
		{
			return _index != rhs._index;
		};
	};

	/**
	 * @brief Returns an iterator pointing to the beginning of the token stream.
	 *
	 * This function returns an iterator pointing to the first token in the
	 * token stream.
	 *
	 * @return iterator An iterator pointing to the beginning of the token
	 * stream.
	 */
	iterator begin() { return iterator(this, 0); };

	/**
	 * @brief Returns an iterator pointing to the end of the token stream.
	 *
	 * This function returns an iterator pointing to the end of the token
	 * stream.
	 *
	 * @return iterator An iterator pointing to the end of the token stream.
	 */
	iterator end() { return iterator(this, size()); };
};

#endif // LUMC_UTILS_TOKENSTREAM_HH