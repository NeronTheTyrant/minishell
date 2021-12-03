#ifndef	BUILTIN_H
# define BUILTIN_H

int	ft_echo(char **args);
int	ft_cd(char **args);
int	ft_pwd(char **args);
int	ft_export(char **args);
int	ft_unset(char **args);
int	ft_env(char **args);
int	ft_exit(char **args);
int	is_builtin(char *cmd);
int	exec_builtin(int i, char **args);

#endif
