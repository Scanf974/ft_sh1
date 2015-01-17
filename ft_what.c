/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_what.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 18:01:48 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/17 09:08:09 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static int	ft_builtins(char *cmd, char ***env, char **path, int rt)
{
	int		ret;
	char	*after;

	ret = rt;
	if (ft_onlyesp(cmd))
		return (rt);
	after = ft_strdup(cmd + ft_strlen(ft_getcmd(cmd)));
	if (ft_strequ(ft_getcmd(cmd), "exit"))
		exit(0);
	if (ft_strequ(ft_getcmd(cmd), "env"))
		ret = ft_env(env, after, path, rt);
	else if (ft_strequ(ft_getcmd(cmd), "cd"))
		ret = ft_cd(env, after);
	else if (ft_strequ(ft_getcmd(cmd), "pwd"))
	{
		ft_putendl(ft_pwd());
		ret = 0;
	}
	else if (ft_strequ(ft_getcmd(cmd), "export"))
		ret = ft_setenv(env, after);
	else if (ft_strequ(ft_getcmd(cmd), "unset"))
		ret = ft_unsetenv(env, after);
	else if (!ft_onlyesp(cmd))
		ret = 1;
	return (ret);
}

static int	ft_fuckyou(char *cmd, char ***env)
{
	if (access(ft_getcmd(cmd), X_OK) == 0)
		return (ft_exec(ft_getcmd(cmd), cmd, *env));
	else
	{
		ft_putstr_fd("ft_sh1: command not found: ", 2);
		ft_putendl_fd(ft_getcmd(cmd), 2);
		return (-1);
	}
}

int			ft_what(char *cmd, char ***env, char **path, int rt)
{
	int		ret;
	int		i;

	i = 0;
	ret = rt;
	cmd = ft_strtrim_new(cmd);
	if (cmd)
	{
		if ((ret = ft_builtins(cmd, env, path, rt)) == -1)
			return (-1);
		else if (!ft_onlyesp(cmd) && ret == 1)
		{
			while (path[i] && !ft_cmd_is_in_path(ft_getcmd(cmd), path[i]))
				i++;
			if (!path[i])
				ret = ft_fuckyou(cmd, env);
			else if (path[i] && !ft_strequ(ft_getcmd(cmd), "env"))
			{
				ret = ft_exec(ft_strjoin(ft_strjoin(path[i], "/"),
							ft_getcmd(cmd)), cmd, *env);
				return (ret);
			}
		}
	}
	return (ret);
}
