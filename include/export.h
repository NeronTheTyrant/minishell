/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:06:50 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 20:43:37 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "../libft/libft.h"
# include "core.h"

# define NONE	0
# define EQ		1
# define PLUSEQ	2

# define ERR_WRITE_EXPORT "export: write error: No space left on device"

int		print_export(t_list *sudoenv);
int		export_var(char *arg, t_term *t);
char	*get_export_val(char *arg);
int		get_export_op(char *arg);
char	*get_export_var(char *arg);
#endif
