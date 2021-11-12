/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:28:22 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/10 20:51:05 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "lexer.h"
#include "../../libft/libft.h"
#include <stdio.h>

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
	else
		delimlen = 0;
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
	else if (c == '\'')
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
	static t_lexstate	statetab[8][10] = 
	{
		// STATE_GENERAL
		{STATE_WORD, STATE_NAME, STATE_CONT, STATE_QUOTE, STATE_DBQUOTE,
		STATE_PIPE, STATE_RDIR_I, STATE_RDIR_O, STATE_WORD, STATE_EOF},
		//STATE_WORD
		{STATE_CONT, STATE_CONT, STATE_END, STATE_QUOTE, STATE_DBQUOTE,
		STATE_END, STATE_END, STATE_END, STATE_CONT, STATE_EOF},
		// STATE_NAME
		{STATE_WORD, STATE_NAME, STATE_END, STATE_QUOTE, STATE_DBQUOTE,
		STATE_END, STATE_END, STATE_END, STATE_WORD, STATE_EOF},
		// STATE_QUOTE
		{STATE_CONT, STATE_CONT, STATE_CONT, STATE_WORD, STATE_CONT,
		STATE_CONT, STATE_CONT, STATE_CONT, STATE_CONT, STATE_EOF},
		// STATE_DBQUOTE
		{STATE_CONT, STATE_CONT, STATE_CONT, STATE_CONT, STATE_WORD,
		STATE_CONT, STATE_CONT, STATE_CONT, STATE_CONT, STATE_EOF},
		// STATE_PIPE
		{STATE_END, STATE_END, STATE_END, STATE_END, STATE_END,
		STATE_END, STATE_END, STATE_END, STATE_END, STATE_EOF},
		// STATE_RDIR_I
		{STATE_END, STATE_END, STATE_END, STATE_END, STATE_END,
		STATE_END, STATE_RDIR_I, STATE_END, STATE_END, STATE_EOF},
		// STATE RDIR_O
		{STATE_END, STATE_END, STATE_END, STATE_END, STATE_END,
		STATE_END, STATE_END, STATE_RDIR_O, STATE_END, STATE_EOF},
	};
	t_lexstate	next_state;

	if (state == STATE_EOF)
	{
		printf("What are YOUUUUUUU doing here????\n");
		return (STATE_EOF);
	}
	next_state = statetab[state][cat];
	if (next_state == STATE_CONT)
		return (state);
	else
		return (next_state);
}

t_toktype	get_token_type(t_lexstate state, size_t toklen)
{
	if (state == STATE_WORD)
		return (WORD);
	if (state == STATE_NAME)
		return (NAME);
	if (state == STATE_PIPE)
		return (PIPE);
	if (state == STATE_RDIR_I && toklen == 1)
		return (RDIR_IN);
	if (state == STATE_RDIR_I && toklen == 2)
		return (RDIR_HEREDOC);
	if (state == STATE_RDIR_O && toklen == 1)
		return (RDIR_OUT);
	if (state == STATE_RDIR_O && toklen == 2)
		return (RDIR_A_OUT);
	return (-1);
}

t_token	*generate_token(char *cmdline, t_lexstate state, size_t toklen)
{
	t_token	*newtoken;

	newtoken = malloc(sizeof(*newtoken));
	if (newtoken == NULL)
		return (NULL);
	newtoken->toktype = get_token_type(state, toklen);
	newtoken->toklen = toklen;
	newtoken->tokstr = malloc(sizeof(*newtoken->tokstr) * (toklen + 1));
	if (newtoken->tokstr == NULL)
	{
		free(newtoken);
		return (NULL);
	}
	ft_strlcpy(newtoken->tokstr, cmdline - toklen, toklen + 1);
	return (newtoken);
}

int	check_token_end(t_lexstate state, t_lexstate next_state, size_t toklen)
{
	if (next_state == STATE_END)
		return (1);
	else if (next_state == STATE_EOF && state != STATE_GENERAL)
		return (1);
	else if ((state == STATE_RDIR_I || state == STATE_RDIR_O) && toklen == 2)
		return (1);
	else
		return (0);
}

int	check_token_valid(t_lexstate state)
{
	if (state == STATE_GENERAL)
	{
		printf("Error: ended on general state\n");
		return (0);
	}
	else if (state == STATE_QUOTE)
	{
		printf("Error: unclosed simple quote\n");
		return (0);
	}
	else if (state == STATE_DBQUOTE)
	{
		printf("Error: unclosed double quote\n");
		return (0);
	}
	else if (state == STATE_EOF)
	{
		printf("Error: ended on EOF state\n");
		return (0);
	}
	else if (state == STATE_END || state == STATE_CONT)
	{
		printf("Error: ended on END or CONT state\n");
		return (0);
	}
	else
		return (1);
}

int	find_token(char **cmdline, t_token **token)
{
	t_lexstate	state;
	t_lexstate	next_state;
	size_t		toklen;

	state = STATE_GENERAL;
	toklen = 0;
	while (state != STATE_EOF)
	{
		next_state = get_next_lexstate(state, get_lexchar(**cmdline));
		if (check_token_end(state, next_state, toklen) == 1)
		{
			if (check_token_valid(state) == 0)
				return (-1); // Error - bad token, or other
			*token = generate_token(*cmdline, state, toklen);
			if (*token == NULL)
				return (-1); // Think about error handling... Maybe print errors directly and then just send a signal back to leave shell
			return (1);
		}
		else if (next_state != STATE_GENERAL)
			toklen++;
		state = next_state;
		*cmdline = *cmdline + 1;
	}
	return (0);
}

char	*token_type_to_str(t_toktype toktype)
{
	if (toktype == WORD)
		return ("WORD");
	if (toktype == NAME)
		return ("NAME");
	if (toktype == RDIR_IN)
		return ("RDIR_IN");
	if (toktype == RDIR_OUT)
		return ("RDIR_OUT");
	if (toktype == RDIR_HEREDOC)
		return ("RDIR_HEREDOC");
	if (toktype == RDIR_A_OUT)
		return ("RDIR_A_OUT");
	if (toktype == PIPE)
		return ("PIPE");
	return ("UNKNOWN TOKEN");
}

void	print_token(t_token token)
{
	printf("Token type = %s\n", token_type_to_str(token.toktype));
	printf("Token string = %s\n", token.tokstr);
	printf("Token length = %zu\n", token.toklen);
}

void	clear_token(t_token *token)
{
	free(token->tokstr);
	free(token);
}

int	add_token_to_list(t_list **toklst, t_token *token)
{
	t_list	*new;

	new = ft_lstnew(token);
	if (new == NULL)
	{
		free(token);
		ft_lstclear(toklst, &clear_token);
		*toklst = NULL;
		return (-1);
	}
	ft_lstadd_back(toklst, new);
	return (0);
}



t_list	*lexer(char *cmdline)
{
	t_list	*toklst;
	t_token	*token;
	int		ret;

	toklst = NULL;
	while (cmdline && *cmdline)
	{
		ret = find_token(&cmdline, &token);
		if (ret == -1)
		{
			printf("Error!!!\n");
			ft_lstclear(&toklst, &clear_token);
			return (NULL);
			//TODO ERROR
		}
		if (ret == 0)
		{
			printf("No Token Found!!!\n");
			//TODO END
		}
		if (add_token_to_list(&toklst, token) == -1)
			return (NULL); // ERROR MALLOC
	}
	return (toklst);

}

int	main(int argc, char **argv)
{
	char	*cmdline;
	t_list	*toklst;
	t_list	*ptr;

	cmdline = argstostr(&argv[1], argc - 1, " ");
	printf("cmdline:\n%s\n", cmdline);
	toklst = lexer(cmdline);
	ptr = toklst;
	while (ptr != NULL)
	{
		print_token(*(t_token *)ptr->content);
		ptr = ptr->next;
	}
	free(cmdline);
	return (0);
}
