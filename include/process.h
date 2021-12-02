/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:48:38 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/02 19:17:45 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

#include "../libft/libft.h"

typedef struct s_process
{
	char	**cmd;
	t_list	*redir;
	char	*heredoc_filename;
}	t_process;

int		make_process_list(t_list *toklst, t_list **plst);
int		make_process(t_process *p, t_list **plst);
void	ft_clear_process(t_process *p);
void	print_cmd_list(char **cmd);
void	print_plist(t_list *p);
int		make_cmd(t_list **toklst, char ***cmd);
int		fill_cmd(t_list **toklst, char **newcmd);
int		get_cmd_size(t_list *toklst);

#endif
