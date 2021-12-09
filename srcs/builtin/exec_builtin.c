/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:19:39 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/09 18:00:14 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "core.h"

int	is_builtin(char *cmd)
{
	static char	*builtin_names[] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit"};
	int			i;

	if (cmd == NULL)
		return (-1);
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd, builtin_names[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	exec_builtin(int i, char **args, t_term *t)
{
	static int	(*builtin_func[])(char **, void *) = {&ft_echo, &ft_cd,
		&ft_pwd, &ft_export, &ft_unset, &ft_env, &ft_exit};

	return ((*builtin_func[i])(args, t));
}
