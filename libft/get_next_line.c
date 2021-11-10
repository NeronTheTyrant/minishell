/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:19:07 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/25 23:16:05 by Tsak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

t_list	*set_fd_lst(int fd, t_list **lst)
{
	t_gnl	*gnl;
	t_list	*new;

	if (!lst)
		return (NULL);
	if (*lst)
		new = *lst;
	else
		new = NULL;
	while (new)
	{
		gnl = new->content;
		if (gnl->fd == fd)
			return (new);
		new = new->next;
	}
	gnl = (t_gnl *)malloc(sizeof(t_gnl));
	if (!gnl)
		return (NULL);
	ft_memset(gnl->remainder, 0, BUFFER_SIZE + 1);
	gnl->fd = fd;
	new = ft_lstnew(gnl);
	ft_lstadd_back(lst, new);
	return (ft_lstlast(*lst));
}

int	read_file(int fd, t_list **lst, t_list **tmp, char *result)
{
	t_gnl	*gnl;
	int		ret;

	gnl = (*tmp)->content;
	ret = 0;
	if (!(gnl->remainder[0]))
	{
		ret = read(fd, gnl->remainder, BUFFER_SIZE);
		if (ret <= 0 || (!ret && !(gnl->remainder[0])))
		{
			if (!ret && result)
				return (1);
			if (result)
				free(result);
			ft_lstdelone(lst, *tmp, &free);
			return (ret);
		}
	}
	return (1);
}

int	split_first_nl(char *nl, t_list **lst, char **result)
{
	t_gnl	*gnl;
	char	*tmp;
	char	*tmp2;
	int		index;

	gnl = (*lst)->content;
	index = nl - gnl->remainder;
	tmp = NULL;
	tmp = ft_strndup(gnl->remainder, index);
	if (!tmp)
	{
		if (*result)
			free(*result);
		return (-1);
	}
	tmp2 = *result;
	*result = ft_strjoin(*result, tmp);
	free(tmp);
	if (tmp2)
		free(tmp2);
	if (!*result)
		return (-1);
	ft_memcpy(gnl->remainder, nl + 1, ft_strlen(nl + 1) + 1);
	return (0);
}

int	fill_result(t_list **lst, t_list **origin, int *flag, char **result)
{
	char	*str;
	t_gnl	*gnl;

	gnl = (*lst)->content;
	str = ft_strchr(gnl->remainder, '\n');
	if (str)
	{
		if (split_first_nl(str, lst, result) < 0)
		{
			ft_lstdelone(lst, *origin, &free);
			return (-1);
		}
		*flag = 1;
	}
	else
	{
		str = *result;
		*result = ft_strjoin(*result, gnl->remainder);
		ft_memset(gnl->remainder, 0, BUFFER_SIZE);
		if (str)
			free(str);
		if (!result)
			return (-1);
	}
	return (0);
}

int	get_next_line(int fd, char **line, int stop)
{
	static t_list	*lst;
	t_list			*tmp;
	char			*result;
	int				ret;
	int				flag;

	if (fd < 0 || handle_stop(fd, stop, &lst) < 0)
		return (-1);
	else if (!line || BUFFER_SIZE < 1)
		return (-1);
	result = NULL;
	tmp = set_fd_lst(fd, &lst);
	if (!tmp)
		return (-1);
	flag = 0;
	while (!flag)
	{
		ret = read_file(fd, &lst, &tmp, result);
		if (ret < 1)
			return (ret);
		if (fill_result(&tmp, &lst, &flag, &result) < 0)
			return (-1);
	}
	*line = result;
	return (1);
}
