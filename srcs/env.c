/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:28:41 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/17 15:15:29 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
