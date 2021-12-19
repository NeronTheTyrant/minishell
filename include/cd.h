/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:40:21 by acabiac           #+#    #+#             */
/*   Updated: 2021/12/19 14:34:30 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H
# include "core.h"
# include "libft.h"

int		cd_return_error(int ret, char *err_msg);
char	*get_curpath(char **arg, char **args, int *output, t_term *t);
int		init_cd_arg(char **arg, char **args, int *output, t_term *t);
char	*init_curpath(char *arg, int *output, t_term *t);
int		search_in_cdpath(char **curpath, char *arg, int *output, t_term *t);
int		srch_cdpath_cycle(char *cdpath, char *arg, char **curpath, int *output);
int		check_cdpath_dir(char *path, int *output);
char	*set_curpath_canonical(char *curpath, char *arg);
int		init_canonical(char *curpath, char ***split, t_list **lst);
int		get_list_from_split(t_list **lst, char **split);
void	handle_dots(t_list **head);
char	*get_final_curpath(t_list **head, char *curpath);
int		change_dir_or_die(char *curpath, char *arg, t_term *t);
int		swap_pwd_vars(char *pwd, char *oldpwd, t_term *t);

#endif
