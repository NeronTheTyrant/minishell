/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:30:43 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/16 20:32:04 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "env.h"

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
		*env = ft_realloc(*env, sizeof(**env) * (envlen + 1),
				sizeof(**env) * (envlen + 2));
		if (*env == NULL)
			return (-1);
		(*env)[envlen] = envvar;
		(*env)[envlen + 1] = NULL;
	}
	else
	{
		free((*env)[varindex]);
		(*env)[varindex] = envvar;
	}
	return (0);
}

int	ft_unsetenv(char *var, char ***env)
{
	int		varindex;
	int		envlen;
	char	**newenv;

	varindex = ft_getenvi(var, *env);
	if (varindex == -1)
		return (0);
	envlen = ft_argcount(*env);
	newenv = malloc(sizeof(*newenv) * envlen);
	if (newenv == NULL)
		return (1);
	ft_memcpy(newenv, *env, sizeof(*newenv) * envlen);
	ft_memcpy(&newenv[varindex], &(*env)[varindex + 1],
		sizeof(*newenv) * (envlen - varindex));
	free((*env)[varindex]);
	free(*env);
	*env = newenv;
	return (0);
}

int	ft_addenv(char *var, char *val, char ***env)
{
	int		varindex;
	char	*envval;
	char	*envstr;

	varindex = ft_getenvi(var, *env);
	if (varindex == -1)
		return (ft_setenv(var, val, env));
	envval = ft_strchr((*env)[varindex], '=') + 1;
	envval = ft_strjoin(envval, val);
	envstr = make_envvar(var, envval);
	if (envstr == NULL)
		return (-1);
	free((*env)[varindex]);
	(*env)[varindex] = envstr;
	return (0);
}
