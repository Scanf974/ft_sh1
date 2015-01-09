/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 04:20:38 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/03 03:01:23 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"
#include <stdio.h> //pqs de printf

static int	ft_builtins(char *cmd, char ***env, int rt)
{
	int		ret;
	char	*after;

	ret = rt;
	if (ft_onlyesp(cmd))
		return (rt);
	after = ft_strdup(cmd + ft_strlen(ft_getcmd(cmd)));
	if (ft_strnequ(cmd, "exit", 4))
		exit(0);
	if (ft_strnequ(cmd, "env", 3))
		ret = ft_env(*env, after);
	else if (ft_strnequ(cmd, "cd", 2))
		ret = ft_cd(env, after);
	else if (ft_strnequ(cmd, "pwd", 3))
	{
		ft_putendl(ft_pwd());
		ret = 0;
	}
	else if (ft_strnequ(cmd, "export", 6))
		ret = ft_setenv(env, after);
	else if (ft_strnequ(cmd, "unset", 5))
		ret = ft_unsetenv(env, after);
	else if (!ft_onlyesp(cmd))
		ret = 1;
	return (ret);
}

static int	ft_what(char *cmd, char ***env, char **path, int rt)
{
	int		ret;
	int		i;

	i = 0;
	cmd = ft_strtrim_new(cmd);
	if ((ret = ft_builtins(cmd, env, rt)) == -1)
		return (-1);
	else if (!ft_onlyesp(cmd) && ret == 1)
	{
		while (path[i] && !ft_cmd_is_in_path(ft_getcmd(cmd), path[i]))
			i++;
		if (!path[i])
		{

			if (access(ft_getcmd(cmd), X_OK) == 0)
				ret = ft_exec(ft_getcmd(cmd), cmd, *env);
			else
			{
				ft_putstr("ft_sh1: command not found: ");
				ft_putendl(ft_getcmd(cmd));
				return (-1);
			}
		}
		else if (path[i])
		{
			ret = ft_exec(ft_strjoin(ft_strjoin(path[i], "/"), ft_getcmd(cmd)), cmd, *env);
			return (ret);
		}
	}
	return (ret);
}

int			ft_cmd(char **env)
{
	char	*cmd;
	int		ret;
	char	**path;

	ret = 0;
	cmd = ft_strdup("");
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
	}
	return (0);
}
