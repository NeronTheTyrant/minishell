/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:28:41 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/25 18:42:31 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"

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
	return (0);
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
