/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:48:38 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 21:05:07 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "../libft/libft.h"

/******************************************************************************/
/*                                                                            */
/*                           Structures                                       */
/*                                                                            */
/******************************************************************************/

/*
**  t_process: node content for process linked list
**
** cmd              -> command array, contains command name and arguments
** redir            -> a redirection linked list, see redir.h
** heredoc_filename -> name of the file used to write heredoc input 
**                     for this process
** ambig_redir      -> will be == 1 if this process contains an 
**                     ambiguous redirection
*/

typedef struct s_process
{
	char	**cmd;
	t_list	*redir;
	char	*heredoc_filename;
	int		ambig_redir;
}	t_process;

/******************************************************************************/
/*                                                                            */
/*                          Constructor & Free                                */
/*                                                                            */
/******************************************************************************/

int		make_process_list(t_list *toklst, t_list **plst);
int		make_process(t_process *p, t_list **plst);

void	ft_clear_process(t_process *p);
void	ft_clear_process_no_unlink(t_process *p);

/******************************************************************************/
/*                                                                            */
/*                          Command array utils                               */
/*                                                                            */
/******************************************************************************/

int		make_cmd(t_list **toklst, char ***cmd);
int		fill_cmd(t_list **toklst, char **newcmd);
int		get_cmd_size(t_list *toklst);

/******************************************************************************/
/*                                                                            */
/*                          Process list utils                                */
/*                                                                            */
/******************************************************************************/

void	print_cmd_list(char **cmd);
void	print_plist(t_list *p);

#endif
