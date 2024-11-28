/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hh                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:32:02 by jbrousse          #+#    #+#             */
/*   Updated: 2024/11/27 23:01:49 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMC_LEXER_LEXER_HH
#define LUMC_LEXER_LEXER_HH

#include <istream>

#include "utils/Token.hh"
#include "utils/TokenStream.hh"

class Lexer
{
  private:
	std::istream &input;
	TokenStream	  tokenStream;
};

#endif // LUMC_LEXER_LEXER_HH