/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:26:57 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/14 15:26:07 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include "global.h"
#include "error.h"
#include <stdio.h>

void	waitprocess(int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		error_nonfatal(NULL, NULL);
	if (WIFEXITED(status) == 1)
	{
		g_ret = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status) == 1)
	{
		g_ret = 128 + WTERMSIG(status);
	}
}
