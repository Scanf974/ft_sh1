/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_not_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/14 06:29:40 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/14 06:35:01 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int		ft_not_dir(char *path)
{
	struct stat		buf;

	if (ft_nbargv(path) > 1)
		path = ft_strtrim_new(path + ft_strlen(ft_getcmd(path)));
	if (ft_onlyesp(path) ||
			ft_strnequ(path, "-", 1) || ft_strnequ(path, "~", 1))
		return (0);
	if (lstat(path, &buf) == 0 &&
			!S_ISDIR(buf.st_mode) && !S_ISLNK(buf.st_mode))
	{
		ft_putstr_fd("cd: Not a directory :", 2);
		ft_putendl_fd(path, 2);
		return (-1);
	}
	else if (lstat(path, &buf))
	{
		ft_putstr_fd("cd: No such file or directory: ", 2);
		ft_putendl_fd(path, 2);
		return (-1);
	}
	return (0);
}
