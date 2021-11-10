/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:15:36 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/25 22:54:01 by Tsak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 4096
# include "ft_list.h"

typedef struct s_gnl
{
	int		fd;
	char	remainder[BUFFER_SIZE + 1];
}t_gnl;

int		get_next_line(int fd, char **line, int stop);
int		handle_stop(int fd, int stop, t_list **lst);
int		fill_result(t_list **lst, t_list **origin, int *flag, char **result);
int		split_first_nl(char *nl, t_list **lst, char **result);
int		read_file(int fd, t_list **lst, t_list **tmp, char *result);
t_list	*set_fd_lst(int fd, t_list **lst);

#endif
