/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nontty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 20:30:40 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 20:32:04 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "core.h"
#include "error.h"
#include "libft.h"

int	read_and_check(int fd, char *buffer)
{
	int	i;
	int	ret;

	i = 0;
	ft_bzero(buffer, BUFFER_SIZE + 1);
	while (i < BUFFER_SIZE)
	{
		ret = read(fd, buffer + i, 1);
		buffer[i + 1] = '\0';
		if (ret == 0)
			return (0);
		if (ret == -1)
			return (-1);
		if (ft_isprint(buffer[i]) == 0 && ft_iswspace(buffer[i]) == 0)
			return (-2);
		if (buffer[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

int	gnl_nontty_2(int fd, char **line)
{
	char	buffer[BUFFER_SIZE + 1];
	int		ret;
	char	*res;
	char	*tmp;

	res = ft_strdup("");
	if (res == NULL)
		return (-1);
	while (1)
	{
		ret = read_and_check(fd, buffer);
		if (ret < 0)
			free(res);
		if (ret < 0)
			return (ret);
		tmp = res;
		res = ft_strjoin(res, buffer);
		free(tmp);
		if (res == NULL)
			return (-1);
		if (ret == 0)
			*line = res;
		if (ret == 0)
			return (0);
	}
}

char	*get_nontty_line(t_term *t, char *prevline)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = gnl_nontty_2(STDIN_FILENO, &line);
	if (ret == -1)
		error_exit(ERR_MALLOC, NULL, t, 1);
	if (ret == -2)
	{
		free(line);
		error_exit(ERR_STDIN, NULL, t, 1);
	}
	if (line == NULL || *line == '\0')
	{
		if (line)
			free(line);
		exit_free(t, 1);
	}
	if (prevline)
		free(prevline);
	return (line);
}
