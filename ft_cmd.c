/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 04:20:38 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/14 06:23:38 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static int	ft_builtins(char *cmd, char ***env, int rt)
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
		ret = ft_env(*env, after);
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

static int	ft_what(char *cmd, char ***env, char **path, int rt)
{
	int		ret;
	int		i;

	i = 0;
	ret = rt;
	cmd = ft_strtrim_new(cmd);
	if (cmd)
	{
		if ((ret = ft_builtins(cmd, env, rt)) == -1)
			return (-1);
		else if (!ft_onlyesp(cmd) && ret == 1)
		{
			while (path[i] && !ft_cmd_is_in_path(ft_getcmd(cmd), path[i]))
				i++;
			if (!path[i])
				ret = ft_fuckyou(cmd, env);
			else if (path[i])
			{
				ret = ft_exec(ft_strjoin(ft_strjoin(path[i], "/"),
							ft_getcmd(cmd)), cmd, *env);
				return (ret);
			}
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
