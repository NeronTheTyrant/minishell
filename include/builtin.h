/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:50:09 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/17 15:43:20 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef enum e_btindex
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_btindex;

int		ft_echo(char **args, void *t);
int		ft_cd(char **args, void *t);
int		ft_pwd(char **args, void *t);
int		ft_export(char **args, void *t);
int		ft_unset(char **args, void *t);
int		ft_env(char **args, void *t);
int		ft_exit(char **args, void *t);
int		is_builtin(char *cmd);

#endif
