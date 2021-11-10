/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:28:22 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/10 02:32:21 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "lexer.h"
#include "libft.h"

char	*argstostr(char **args, int size, char *delim)
{
	int		len;
	int		delimlen;
	char	*str;
	int		i;

	len = 0;
	i = 0;
	while (i < size)
	{
		len += ft_strlen(args[i]);
		i++;
	}
	if (delim != NULL)
		delimlen = ft_strlen(delim);
	len += (i * delimlen);
	str = malloc(sizeof(*str) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, sizeof(*str) * (len + 1));
	i = 0;
	while (i < size)
	{
		ft_strlcat(str, args[i], len);
		if (i + 1 < size)
			ft_strlcat(str, delim, len);
		i++;
	}
	return (str);
}



t_lexchar	get_lexchar(char c)
{
	if (ft_iswspace(c) == 1)
		return (CHAR_WHITESPACE);
	else if (c == '"')
		return (CHAR_DBQUOTE);
	else if (c == ''')
		return (CHAR_QUOTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == '<')
		return (CHAR_RDIR_I);
	else if (c == '>')
		return (CHAR_RDIR_O);
	else if (c == '=')
		return (CHAR_EQUAL);
	else if (c == '\0')
		return (CHAR_EOF);
	else if (ft_isalnum(c) == 1)
		return (CHAR_ALPHANUM);
	else
		return (CHAR_GENERAL);
}

t_lexstate	get_next_lexstate(t_lexstate state, t_lexchar cat)
{
	static t_lexstate	statetab[12][10] = 
	{
		// STATE_GENERAL
		{STATE_WORD, STATE_NAME, STATE_CONT, STATE_QUOTE, STATE_DBQUOTE,
		STATE_PIPE, STATE_RDIR_I, STATE_RDIR_O, STATE_WORD, STATE_EOF},
		//STATE_WORD
		{STATE_CONT, STATE_CONT, STATE_END, STATE_QUOTE, STATE_DBQUOTE,
		STATE_END, STATE_END, STATE_END, STATE_CONT, STATE_END},
		// STATE_NAME
		{STATE_WORD, STATE_NAME, STATE_END, STATE_QUOTE, STATE_DBQUOTE,
		STATE_END, STATE_END, STATE_END, STATE_ASSIGN, STATE_END},
		// STATE_ASSIGN
		{STATE_CONT, STATE_ASSIGN, STATE_GENERAL, STATE_ASSIGN_QUOTE, STATE_ASSIGN_DBQUOTE,
		STATE_PIPE, STATE_RDIR_I, STATE_RDIR_O, STATE_ASSIGN, STATE_EOF},
		// STATE_ASSIGN_QUOTE
		{STATE_CONT, STATE_CONT, STATE_CONT, STATE_ASSIGN, STATE_CONT,
		STATE_CONT, STATE_CONT, STATE_CONT, STATE_CONT, STATE_END},
		// STATE_ASSIGN_DBQUOTE
		{STATE_CONT, STATE_CONT, STATE_CONT, STATE_ASSIGN_CONT, STATE_ASSIGN,
		STATE_CONT, STATE_CONT, STATE_CONT, STATE_CONT, STATE_CONT, STATE_END},
		// STATE_QUOTE
		{STATE_CONT, STATE_CONT, STATE_CONT, STATE_WORD, STATE_CONT,
		STATE_CONT, STATE_CONT, STATE_CONT, STATE_CONT, STATE_END},
		// STATE_DBQUOTE
		{STATE_CONT, STATE_CONT, STATE_CONT, STATE_CONT, STATE_WORD,
		STATE_CONT, STATE_CONT, STATE_CONT, STATE_CONT, STATE_END},
		// STATE_PIPE
		{STATE_END, STATE_END, STATE_END, STATE_END, STATE_END,
		STATE_END, STATE_END, STATE_END, STATE_END, STATE_END},
		// STATE_RDIR_I
		{STATE_END, STATE_END, STATE_END, STATE_END, STATE_END,
		STATE_END, STATE_RDIR_I, STATE_END, STATE_END, STATE_END},
		// STATE RDIR_O
		{STATE_END, STATE_END, STATE_END, STATE_END, STATE_END,
		STATE_END, STATE_END, STATE_RDIR_O, STATE_END, STATE_END},
	}
	t_lexstate	next_state;

	if (state == STATE_EOF)
	{
		printf("What are YOUUUUUUU doing here????\n");
	}
	next_state = statetab[state][cat];
	if (next_state == STATE_CONT)
		return (state);
}

int		find_token(char **cmdlist, t_token **token)
{
	t_lexstate	state;
	t_lexstate	next_state;
	t_lexchar	cat;
	size_t		toklen;

	state = STATE_GENERAL;
	cat = CHAR_WHITESPACE;
	toklen = 0;
	while (**cmdlist)
	{
		cat = get_lexchar(**cmdlist);
		next_state = get_next_lexstate(state, cat);
		toklen++;
		*cmdlist++;
	}


}


t_list	*lexer(char *cmdline)
{
	t_list	*toklst;
	t_token	*token;
	int		ret;

	while (cmdline && *cmdline)
	{
		ret = find_token(&cmdline, &token);
		if (ret == -1)
		{
			//TODO ERROR
		}
		if (ret == 0)
		{
			//TODO END
		}
		add_token_to_list(&toklst, token);
	}
	return (toklst);

}

int	main(int argc, char **argv)
{
	char	*cmdline;

	cmdline = argstostr(&argv[1], argc - 1, " ");
	printf("cmdline:\n%s\n", cmdline);
	return (0);
}
