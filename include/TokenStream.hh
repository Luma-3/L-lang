/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TokenStream.hh                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:04:16 by jbrousse          #+#    #+#             */
/*   Updated: 2024/11/24 23:14:58 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENSTREAM_HH
#define TOKENSTREAM_HH

#include <cstddef>
#include <vector>

#include "Token.hh"

class TokenStream
{
  private:
	std::vector< Token > _tokens;
	size_t				 _index = 0;

  public:
	TokenStream() = default;
	explicit TokenStream(std::vector< Token > tokens) : _tokens(tokens) {};
	TokenStream(const TokenStream &src);
	TokenStream &operator=(const TokenStream &rhs);
	~TokenStream() = default;

	bool   eof() const noexcept;
	void   clear() noexcept;
	size_t size() const noexcept;
	bool   empty() const noexcept;

	const Token &peek(size_t lookahead = 0);
	const Token &consume();

	void rewind(size_t steps = 1) noexcept;
	void rewindTo(size_t index);

	void advance(size_t steps = 1) noexcept;
	void advanceTo(size_t index);

	void push(const Token &token);
	void push(const std::vector< Token > &tokens);

	void insert(size_t index, const Token &token);
	void insert(size_t index, const std::vector< Token > &tokens);

	void erase(size_t index);
	void erase(size_t start, size_t end);
	void erase(const Token &token);

	void replace(size_t index, const Token &token);
	void replace(size_t start, size_t end, const Token &token);
	void replace(const Token &oldToken, const Token &newToken);

	const Token &operator[](size_t index) const;
	Token		&operator[](size_t index);

	const Token &at(size_t index) const;
	Token		&at(size_t index);

	class iterator
	{
	  private:
		TokenStream *_stream;
		size_t		 _index;

	  public:
		iterator(TokenStream *stream, size_t index) :
			_stream(stream),
			_index(index) {};
		iterator(const iterator &src) :
			_stream(src._stream),
			_index(src._index) {};
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

	iterator begin() { return iterator(this, 0); };
	iterator end() { return iterator(this, size()); };
};

#endif