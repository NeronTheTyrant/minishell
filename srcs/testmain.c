#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "token.h"
#include "lexer.h"
#include <stdio.h>
#include "core.h"
#include "error.h"

char	*ft_getenv(char	*var, char **env)
{
	int	i;
	int	varlen;

	if (!var || !env)
		return (NULL);
	varlen = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], varlen) == 0 && env[i][varlen] == '=')
			return (&env[i][varlen + 1]);
		i++;
	}
	return (NULL);
}

int	ft_getenvi(char *var, char **env)
{
	int	i;
	int	varlen;

	if (!var || !env)
		return (-1);
	varlen = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], varlen) == 0 && env[i][varlen] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*make_envvar(char *var, char *val)
{
	int		varsize;
	char	*envvar;

	varsize = ft_strlen(var) + ft_strlen(val) + 2;
	envvar = malloc(sizeof(*envvar) * (varsize));
	if (envvar == NULL)
		return (NULL);
	ft_bzero(envvar, sizeof(*envvar) * varsize);
	ft_strlcat(envvar, var, varsize);
	ft_strlcat(envvar, "=", varsize);
	ft_strlcat(envvar, val, varsize);
	return (envvar);
}

int	ft_setenv(char *var, char *val, char ***env)
{
	int		envlen;
	int		varindex;
	char	*envvar;

	envlen = ft_argcount(*env);
	varindex = ft_getenvi(var, *env);
	envvar = make_envvar(var, val);
	if (envvar == NULL)
		return (-1);
	if (varindex == -1)
	{
		*env = ft_realloc(*env, sizeof(**env) * (envlen),
			sizeof(**env) * (envlen + 1));
		if (*env == NULL)
			return (-1);
		*env[envlen] = envvar;
		*env[envlen + 1] = NULL;
	}
	else
	{
		free(*env[varindex]);
		*env[varindex] = envvar;
	}
}

char	**make_env(char **env)
{
	int		i;
	char	**new_env;

	new_env = NULL;
	i = 0;
	while (env[i])
	{
		new_env = ft_realloc(new_env, sizeof(*new_env) * (i + 1),
			sizeof(*new_env) * (i + 2));
		if (new_env == NULL)
			return (NULL);
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	print_token_list(t_list *toklst)
{
	t_token	*token;

	while (toklst != NULL)
	{
		token = (t_token *)toklst->content;
		print_token(*token);
		toklst = toklst->next;
	}
}

void	free_lexer(t_term *t)
{
	if (t->toklst != NULL)
		ft_lstclear(&t->toklst, &clear_token);
}

void	free_everything(t_term *t)
{
	if (t == NULL)
		return ;
	free_lexer(t);
	free(t->cmdline);
}

void	handle_sig(t_term *t)
{
	if (t->sig == SIG_RESTART)
	{
		if (t != NULL)
			free_lexer(t);
	}
	else if (t->sig == SIG_FATAL)
	{
		free_everything(t);
		exit(1);
	}
}

char	*rl_gets(char *prompt, char *prevline)
{
	char	*line;

	line = readline(prompt);
	if (line && *line)
	{
		if (prevline && ft_strcmp(line, prevline) == 0)
		{
			free(line);
			return (prevline);
		}
		else
		{
			add_history(line);
			if (prevline)
				free(prevline);
			return (line);
		}
	}
	return (line);
}

int	main(int argc, char **argv, char **env)
{
	t_term	*t;

	t = malloc(sizeof(*t));
	if (t == NULL)
		return (error_fatal(ERR_MALLOC));
	ft_bzero(t, sizeof(*t));
	(void)argc;
	(void)argv;
	t->env = make_env(env);
	printf("PATH=%s\n", ft_getenv("PATH", t->env));
	while (1)
	{
		t->cmdline = rl_gets("minishell> ", t->cmdline);
		if (!t->cmdline || !*t->cmdline)
			continue ;
		t->sig = lexer(t->cmdline, &t->toklst);
		if (t->sig > 0)
		{
			handle_sig(t);
			continue ;
		}
		print_token_list(t->toklst);
		free_lexer(t);
	}
	return (0);
}
