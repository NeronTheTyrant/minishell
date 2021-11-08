/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 02:45:52 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/01 04:50:54 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	err_exit(char **line)
{
	*line = NULL;
	return (-1);
}

static int	read_next_line(int fd, char *buf, char **stock, int *nl_ind)
{
	char	*temp;
	int		ret;

	ret = read(fd, buf, BUFFER_SIZE);
	while (ret != 0)
	{
		if (ret == -1)
		{
			free(*stock);
			return (-1);
		}
		buf[ret] = '\0';
		temp = *stock;
		*stock = ft_strjoin(*stock, buf);
		free(temp);
		if (*stock == NULL)
			return (-1);
		*nl_ind = ft_isin('\n', *stock);
		if (*nl_ind != -1)
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	if (ret == 0)
		*nl_ind = ft_strlen(*stock);
	return (ret > 0);
}

static int	find_next_line(int fd, char *buf, char **stock, char **line)
{
	int		ret;
	int		nl_ind;
	char	*temp;

	nl_ind = ft_isin('\n', *stock);
	if (nl_ind == -1)
	{
		ret = read_next_line(fd, buf, stock, &nl_ind);
		if (ret == -1)
			return (-1);
	}
	else
		ret = 1;
	*line = ft_substr(*stock, 0, nl_ind);
	temp = *stock;
	if (ret == 0)
		ft_strlcpy(buf, "", BUFFER_SIZE + 1);
	else
		ft_strlcpy(buf, &temp[nl_ind + 1], BUFFER_SIZE + 1);
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char	buf[FD_MAX][BUFFER_SIZE + 1];
	char		*stock;
	int			ret;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (err_exit(line));
	stock = ft_strdup(buf[fd]);
	if (stock == NULL)
		return (err_exit(line));
	ret = find_next_line(fd, buf[fd], &stock, line);
	free(stock);
	if (ret == -1)
		return (err_exit(line));
	if (!*line)
		return (-1);
	return (ret);
}
