/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 03:24:48 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/03 03:04:42 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static char	*get_dirname(void)
{
	char	*path;
	int		len;

	path = ft_pwd();
	len = ft_strlen(path);
	while (path[len] != '/')
		len--;
	if (!path[len - 1])
		return (path + len);
	return (path + len + 1);
}

char		*ft_prompt(char **env, int ret)
{
	char	*cmd;
	int		id_usr;

	id_usr = ft_get_id_var(env, "USER");
	if (ret == 0)
	{
		ft_putstr("➜ ");
		ft_putstr("\033[1;30;47m"); //Blanc
	}
	else
	{
		ft_putstr("\x1b[31m➜ ");
		ft_putstr("\033[1;31;47m"); //Rouge
	}
	if (id_usr != -1 && ft_strequ(get_dirname(), &env[id_usr][5]))
		ft_putstr("~");
	else
		ft_putstr(get_dirname());
	ft_putstr("\033[0;37;40m ");
	get_next_line(0, &cmd);
	return (cmd);
}
