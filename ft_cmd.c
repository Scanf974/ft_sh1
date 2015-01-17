/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 04:20:38 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/15 18:05:56 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int			ft_cmd(char **env)
{
	char	*cmd;
	int		ret;
	char	**path;

	ret = 0;
	path = NULL;
	while (1)
	{
		if (path)
			free(path);
		path = ft_getpath(env);
		if (path == NULL)
		{
			path = (char **)malloc(sizeof(char *) * 2);
			path[0] = ft_strdup("");
			path[1] = NULL;
		}
		cmd = ft_prompt(env, ret);
		ret = ft_what(cmd, &env, path, ret);
		free(cmd);
	}
	return (0);
}
