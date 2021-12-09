/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:41:24 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/09 17:42:52 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

int		fork_cmd(t_list *plist, t_term *t, char **paths, int cmdnum);
int		exec_cmd(char **cmd, char **env, char **paths);

int		make_path(char **env, char ***paths);
int		try_envpath(char **cmd, char **env, char **paths);
int		try_relative_path(char **cmd, char **env);

#endif
