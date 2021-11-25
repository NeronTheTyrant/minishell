/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_extension.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:09:33 by mlebard           #+#    #+#             */
/*   Updated: 2021/08/07 01:12:58 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Usage: checks that the path string ends with the extension string
** @param 1: file path to check for valid extension (ex: "song.mp3")
** @param 2: extension to check at the end of path (ex: ".mp3")
** Return: -1 if extension is not found, 0 if OK
*/

int	check_file_extension(char *path, char *extension)
{
	char	*temp;

	temp = ft_strrchr(path, '.');
	if (temp == NULL || ft_strcmp(temp, extension) != 0)
		return (-1);
	else
		return (0);
}
