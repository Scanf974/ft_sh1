/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_is_in_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 23:10:02 by bsautron          #+#    #+#             */
/*   Updated: 2014/12/26 00:01:14 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int		ft_cmd_is_in_path(char *cmd, char *path)
{
	struct dirent	*lect;
	DIR				*dirp;

	if ((dirp = opendir(path)) != NULL)
	{
		while ((lect = readdir(dirp)) != NULL)
		{
			if (ft_strequ(lect->d_name, cmd))
			{
				closedir(dirp);
				return (1);
			}
		}
		closedir(dirp);
	}
	return (0);
}
