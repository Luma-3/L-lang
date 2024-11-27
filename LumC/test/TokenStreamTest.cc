#include "TokenStream.hh"

#include <gtest/gtest.h>

#include "Token.hh"

// Test fixture for TokenStream
class TokenStreamTest : public ::testing::Test
{
};

// Test default constructor
TEST_F(TokenStreamTest, DefaultConstructor)
{
	TokenStream ts;
	EXPECT_TRUE(ts.empty());
	EXPECT_EQ(ts.size(), 0);
	EXPECT_TRUE(ts.eof());
}

// Test constructor with tokens
TEST_F(TokenStreamTest, ConstructorWithTokens)
{
	std::vector< Token > tokens = {Token(Token::Type::IDENTIFIER, "x"),
								   Token(Token::Type::NUMBER, "42")};
	TokenStream			 ts(tokens);
	EXPECT_FALSE(ts.empty());
	EXPECT_EQ(ts.size(), 2);
	EXPECT_FALSE(ts.eof());
}

// Test copy constructor
TEST_F(TokenStreamTest, CopyConstructor)
{
	std::vector< Token > tokens = {Token(Token::Type::IDENTIFIER, "x"),
								   Token(Token::Type::NUMBER, "42")};
	TokenStream			 ts1(tokens);
	TokenStream			 ts2(ts1);
	EXPECT_EQ(ts1.size(), ts2.size());
	EXPECT_EQ(ts1.peek(), ts2.peek());
}

// Test assignment operator
TEST_F(TokenStreamTest, AssignmentOperator)
{
	std::vector< Token > tokens1 = {Token(Token::Type::IDENTIFIER, "x")};
	std::vector< Token > tokens2 = {Token(Token::Type::NUMBER, "42")};
	TokenStream			 ts1(tokens1);
	TokenStream			 ts2(tokens2);
	ts2 = ts1;
	EXPECT_EQ(ts1.size(), ts2.size());
	EXPECT_EQ(ts1.peek(), ts2.peek());
}

// Test eof method
TEST_F(TokenStreamTest, Eof)
{
	TokenStream ts;
	EXPECT_TRUE(ts.eof());
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	EXPECT_FALSE(ts.eof());
	ts.consume();
	EXPECT_TRUE(ts.eof());
}

// Test clear method
TEST_F(TokenStreamTest, Clear)
{
	TokenStream ts;
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	ts.clear();
	EXPECT_TRUE(ts.empty());
	EXPECT_EQ(ts.size(), 0);
	EXPECT_TRUE(ts.eof());
}

// Test size method
TEST_F(TokenStreamTest, Size)
{
	TokenStream ts;
	EXPECT_EQ(ts.size(), 0);
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	EXPECT_EQ(ts.size(), 1);
}

// Test empty method
TEST_F(TokenStreamTest, Empty)
{
	TokenStream ts;
	EXPECT_TRUE(ts.empty());
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	EXPECT_FALSE(ts.empty());
}

// Test peek method
TEST_F(TokenStreamTest, Peek)
{
	TokenStream ts;
	Token		token(Token::Type::IDENTIFIER, "x");
	ts.push(token);
	EXPECT_EQ(ts.peek(), token);
}

// Test consume method
TEST_F(TokenStreamTest, Consume)
{
	TokenStream ts;
	Token		token(Token::Type::IDENTIFIER, "x");
	ts.push(token);
	EXPECT_EQ(ts.consume(), token);
	EXPECT_TRUE(ts.eof());
}

// Test rewind method
TEST_F(TokenStreamTest, Rewind)
{
	TokenStream ts;
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	ts.push(Token(Token::Type::NUMBER, "42"));
	ts.consume();
	ts.rewind();
	EXPECT_EQ(ts.peek().getValue(), "x");
}

// Test advance method
TEST_F(TokenStreamTest, Advance)
{
	TokenStream ts;
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	ts.push(Token(Token::Type::NUMBER, "42"));
	ts.advance();
	EXPECT_EQ(ts.peek().getValue(), "42");
}

// Test push method
TEST_F(TokenStreamTest, Push)
{
	TokenStream ts;
	Token		token(Token::Type::IDENTIFIER, "x");
	ts.push(token);
	EXPECT_EQ(ts.size(), 1);
	EXPECT_EQ(ts.peek(), token);
}

// Test insert method
TEST_F(TokenStreamTest, Insert)
{
	TokenStream ts;
	Token		token1(Token::Type::IDENTIFIER, "x");
	Token		token2(Token::Type::NUMBER, "42");
	ts.push(token1);
	ts.insert(0, token2);
	EXPECT_EQ(ts.size(), 2);
	EXPECT_EQ(ts.peek(), token2);
}

// Test erase method
TEST_F(TokenStreamTest, Erase)
{
	TokenStream ts;
	Token		token(Token::Type::IDENTIFIER, "x");
	ts.push(token);
	ts.erase(0);
	EXPECT_TRUE(ts.empty());
}

// Test replace method
TEST_F(TokenStreamTest, Replace)
{
	TokenStream ts;
	Token		token1(Token::Type::IDENTIFIER, "x");
	Token		token2(Token::Type::NUMBER, "42");
	ts.push(token1);
	ts.replace(0, token2);
	EXPECT_EQ(ts.peek(), token2);
}

// Test iterator
TEST_F(TokenStreamTest, Iterator)
{
	TokenStream ts;
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	ts.push(Token(Token::Type::NUMBER, "42"));
	TokenStream::iterator it = ts.begin();
	EXPECT_EQ((*it).getValue(), "x");
	++it;
	EXPECT_EQ((*it).getValue(), "42");
}

// Test at method
TEST_F(TokenStreamTest, At)
{
	TokenStream ts;
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	ts.push(Token(Token::Type::NUMBER, "42"));
	EXPECT_EQ(ts.at(0).getValue(), "x");
	EXPECT_EQ(ts.at(1).getValue(), "42");
}

// Test operator[] method
TEST_F(TokenStreamTest, OperatorBracket)
{
	TokenStream ts;
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	ts.push(Token(Token::Type::NUMBER, "42"));
	EXPECT_EQ(ts[0].getValue(), "x");
	EXPECT_EQ(ts[1].getValue(), "42");
}

// Test rewindTo method
TEST_F(TokenStreamTest, RewindTo)
{
	TokenStream ts;
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	ts.push(Token(Token::Type::NUMBER, "42"));
	ts.push(Token(Token::Type::IDENTIFIER, "y"));
	ts.advance();
	ts.rewindTo(0);
	EXPECT_EQ(ts.peek().getValue(), "x");
}

// Test advanceTo method
TEST_F(TokenStreamTest, AdvanceTo)
{
	TokenStream ts;
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	ts.push(Token(Token::Type::NUMBER, "42"));
	ts.push(Token(Token::Type::IDENTIFIER, "y"));
	ts.advance();
	ts.advance();
	ts.advanceTo(0);
	EXPECT_EQ(ts.peek().getValue(), "x");
}

// Test erase method with range
TEST_F(TokenStreamTest, EraseRange)
{
	TokenStream ts;
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	ts.push(Token(Token::Type::NUMBER, "42"));
	ts.push(Token(Token::Type::IDENTIFIER, "y"));
	ts.erase(0, 1);
	EXPECT_EQ(ts.size(), 1);
	EXPECT_EQ(ts.peek().getValue(), "y");
}

// Test replace method with old token
TEST_F(TokenStreamTest, ReplaceOldToken)
{
	TokenStream ts;
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	ts.push(Token(Token::Type::NUMBER, "42"));
	ts.push(Token(Token::Type::IDENTIFIER, "y"));
	ts.replace(Token(Token::Type::IDENTIFIER, "x"),
			   Token(Token::Type::NUMBER, "43"));
	EXPECT_EQ(ts.size(), 3);
	EXPECT_EQ(ts.peek().getValue(), "43");
}

// Test at method with out of range index
TEST_F(TokenStreamTest, AtOutOfRange)
{
	TokenStream ts;
	EXPECT_THROW(ts.at(0), std::out_of_range);
}

// Test insert method with out of range index
TEST_F(TokenStreamTest, InsertOutOfRange)
{
	TokenStream ts;
	EXPECT_THROW(ts.insert(1, Token(Token::Type::IDENTIFIER, "x")),
				 std::out_of_range);
}

// Test erase method with out of range index
TEST_F(TokenStreamTest, EraseOutOfRange)
{
	TokenStream ts;
	EXPECT_THROW(ts.erase(0), std::out_of_range);
}

// Test replace method with out of range index
TEST_F(TokenStreamTest, ReplaceOutOfRange)
{
	TokenStream ts;
	EXPECT_THROW(ts.replace(0, Token(Token::Type::IDENTIFIER, "x")),
				 std::out_of_range);
}

// Test rewindTo method with out of range index
TEST_F(TokenStreamTest, RewindToOutOfRange)
{
	TokenStream ts;
	EXPECT_THROW(ts.rewindTo(0), std::out_of_range);
}

// Test advanceTo method with out of range index
TEST_F(TokenStreamTest, AdvanceToOutOfRange)
{
	TokenStream ts;
	EXPECT_THROW(ts.advanceTo(0), std::out_of_range);
}

// Test erase method with out of range range
TEST_F(TokenStreamTest, EraseRangeOutOfRange)
{
	TokenStream ts;
	EXPECT_THROW(ts.erase(0, 1), std::out_of_range);
}

// Test replace method with old token not found
TEST_F(TokenStreamTest, ReplaceOldTokenNotFound)
{
	TokenStream ts;
	ts.push(Token(Token::Type::IDENTIFIER, "x"));
	ts.push(Token(Token::Type::NUMBER, "42"));
	ts.push(Token(Token::Type::IDENTIFIER, "y"));
	EXPECT_THROW(ts.replace(Token(Token::Type::IDENTIFIER, "z"),
							Token(Token::Type::NUMBER, "43")),
				 std::invalid_argument);
}
