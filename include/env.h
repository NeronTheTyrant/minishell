/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:25:33 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/23 14:31:02 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

char	**make_env(char **env);
int		ft_setenv(char *var, char *val, char ***env);
char	*make_envvar(char *var, char *val);
int		ft_getenvi(char *var, char **env);
char	*ft_getenv(char	*var, char **env);

#endif
