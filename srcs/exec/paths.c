/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:38:48 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/09 17:39:49 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "../libft/libft.h"
#include "env.h"

int	make_path(char **env, char ***paths)
{
	char	*tmp;

	tmp = ft_getenv("PATH", env);
	if (tmp == NULL)
	{
		*paths = NULL;
		return (0);
	}
	*paths = ft_split(tmp, ':');
	if (*paths == NULL)
		return (1);
	return (0);
}

int	try_envpath(char **cmd, char **env, char **paths)
{
	size_t	i;
	char	*cmd_path;
	size_t	cmd_len;

	i = 0;
	while (paths[i])
	{
		cmd_len = ft_strlen(paths[i]) + ft_strlen(cmd[0]) + 1;
		cmd_path = malloc(sizeof(*cmd_path) * (cmd_len + 1));
		if (cmd_path == NULL)
			return (error_fatal(ERR_MALLOC, NULL));
		ft_bzero(cmd_path, sizeof(*cmd_path) * cmd_len + 1);
		ft_strlcat(cmd_path, paths[i], cmd_len + 1);
		ft_strlcat(cmd_path, "/", cmd_len + 1);
		ft_strlcat(cmd_path, cmd[0], cmd_len + 1);
		execve(cmd_path, cmd, env);
		free(cmd_path);
		i++;
	}
	return (0);
}

int	try_relative_path(char **cmd, char **env)
{
	char	*cmd_path;
	size_t	cmd_len;

	cmd_len = ft_strlen(cmd[0]) + 2;
	cmd_path = malloc(sizeof(*cmd_path) * (cmd_len) + 1);
	if (cmd_path == NULL)
		return (error_fatal(ERR_MALLOC, NULL));
	ft_bzero(cmd_path, sizeof(*cmd_path) * cmd_len + 1);
	ft_strlcat(cmd_path, "./", cmd_len + 1);
	ft_strlcat(cmd_path, cmd[0], cmd_len + 1);
	execve(cmd_path, cmd, env);
	free(cmd_path);
	return (0);
}
