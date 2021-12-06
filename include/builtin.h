#ifndef	BUILTIN_H
# define BUILTIN_H

int	ft_echo(char **args, t_term *t);
int	ft_cd(char **args, t_term *t);
int	ft_pwd(char **args, t_term *t);
int	ft_export(char **args, t_term *t);
int	ft_unset(char **args, t_term *t);
int	ft_env(char **args, t_term *t);
int	ft_exit(char **args, t_term *t);
int	is_builtin(char *cmd);
int	exec_builtin(int i, char **args, t_term *t);

#endif
