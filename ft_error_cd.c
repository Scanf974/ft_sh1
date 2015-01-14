/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/14 06:27:53 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/14 06:34:27 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int		ft_error_cd(char **env, char *path)
{
	int		id;

	id = ft_get_id_var(env, "PWD");
	if (id == -1)
		return (0);
	if (ft_nbargv(path) > 1)
	{
		if (ft_nbargv(path) > 2)
		{
			ft_putendl_fd("cd: too many arguments", 2);
			return (-1);
		}
		else if (!ft_strequ(ft_strstr(ft_pwd(), ft_getcmd(path)),
					ft_getcmd(path)))
		{
			ft_putstr_fd("cd: string not in pwd: ", 2);
			ft_putendl_fd(ft_getcmd(path), 2);
			return (-1);
		}
	}
	return (0);
}
