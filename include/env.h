/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:25:33 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/16 17:53:51 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../libft/libft.h"

typedef struct s_envnode
{
	char	*var;
	char	*val;
}	t_envnode;

char		**make_env(char **env);

int			ft_getenvi(char *var, char **env);
char		*ft_getenv(char	*var, char **env);

char		*make_envvar(char *var, char *val);
int			ft_setenv(char *var, char *val, char ***env);

int			ft_addenv(char *var, char *val, char ***env);

int			ft_unsetenv(char *var, char ***env);




int			make_sudoenv(char **env, t_list **sudoenv);

void		free_envnode(t_envnode *node);

t_envnode	*make_envnode_from_env(char *envstr);
t_envnode	*make_envnode(char *var, char *val);

t_list		*get_envnode(t_list *sudoenv, char *var);

int			set_sudoenv(t_list **sudoenv, char *var, char *val);
int			set_sudoenv_from_env(t_list	**sudoenv, char *envstr);

int			add_sudoenv(t_list **sudoenv, char *var, char *val);

int			unset_sudoenv(t_list **sudoenv, char *var);

void		print_sudoenv(t_list *sudoenv);

#endif
