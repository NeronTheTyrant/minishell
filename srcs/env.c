/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:28:41 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/17 21:28:24 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <unistd.h>

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

	if (val == NULL)
		return (NULL);
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

char	**create_env(void)
{
	char	**new_env;

	new_env = malloc(sizeof(*new_env) * 4);
	if (new_env == NULL)
		return (NULL);
	new_env[0] = make_envvar("PWD", getcwd(NULL, 0));
	new_env[1] = make_envvar("SHLVL", "1");
	new_env[2] = make_envvar("_", "/usr/bin/env");
	new_env[3] = NULL;
	if (new_env[0] == NULL || new_env[1] == NULL || new_env[2] == NULL)
	{
		free(new_env[0]);
		free(new_env[1]);
		free(new_env[2]);
		free(new_env);
		return (NULL);
	}
	return (new_env);
}

char	**make_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	if (env[i] == NULL)
		return (create_env());
	new_env = NULL;
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
