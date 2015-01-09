/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 04:51:47 by bsautron          #+#    #+#             */
/*   Updated: 2014/12/26 07:53:01 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"
#include <stdio.h> //pas de printf

static int	ft_nbargv(char *str)
{
	int		i;
	int		nb;

	nb = 0;
	i = 0;

	if (str)
	{
		while (str[i])
		{
			if (str[i] > ' ' && (str[i + 1] <= ' ' || !str[i + 1]))
				nb++;
			i++;
		}
	}
	return (nb);
}

static int	ft_error_cd(char **env, char *path)
{
	char	*after_pwd;
	int		id;

	id = ft_get_id_var(env, "PWD");
	if (id == -1)
		return (0);
	after_pwd = ft_strdup(&env[id][4]);
	if (ft_nbargv(path) > 1)
	{
		if (ft_nbargv(path) > 2)
		{
			ft_putendl("cd: too many arguments");
			return (-1);
		}
		else if (!ft_strequ(ft_strstr(ft_pwd(), ft_getcmd(path)), ft_getcmd(path)))
		{
			ft_putstr("cd: string not in pwd: ");
			ft_putendl(ft_getcmd(path));
			return (-1);
		}
	}
	return (0);
}

static int	ft_not_dir(char *path)
{
	struct stat		buf;

	if (ft_nbargv(path) > 1)
		path = ft_strtrim_new(path + ft_strlen(ft_getcmd(path)));
	if (ft_onlyesp(path) || ft_strnequ(path, "-", 1) || ft_strnequ(path, "~", 1))
		return (0);
	if (lstat(path, &buf) == 0 && !S_ISDIR(buf.st_mode) && !S_ISLNK(buf.st_mode))
	{
		ft_putstr("cd: Not a directory :");
		ft_putendl(path);
		return (-1);
	}
	else if (lstat(path, &buf))
	{
		ft_putstr("cd: No such file or directory: ");
		ft_putendl(path);
		return (-1);
	}
	return (0);
}

static void	ft_tiret(char **env, char *path)
{
	char	*pwd;
	pid_t	id;

	path = &env[ft_get_id_var(env, "OLDPWD")][7];
	pwd = ft_pwd();
	id = ft_get_id_var(env, "OLDPWD");
	env[id] = ft_strdup(ft_strjoin("OLDPWD=", pwd));
	chdir(path);
	pwd = ft_pwd();
	ft_putendl(pwd);
}

static char	*ft_get_prev_dir(char *path)
{
	int		i;

	i = ft_strlen(path) - 1;
	while (path[i] && path[i] != '/')
	{
		path[i] = '\0';
		i--;
	}
	return (path);
}

static void	ft_switch(char ***env)
{
	int		id_pwd;
	int		id_oldpwd;
	char	*temp;

	id_pwd = ft_get_id_var(*env, "PWD");
	ft_setenv(env, "OLDPWD=");
	id_oldpwd = ft_get_id_var(*env, "OLDPWD");
	if (id_pwd != -1 && id_oldpwd != -1)
	{
		temp = &env[0][id_pwd][4];
		(*env)[id_pwd] = ft_strjoin("PWD=", &env[0][id_oldpwd][7]);
		(*env)[id_oldpwd] = ft_strjoin("OLDPWD=", temp);
	}
}

int			ft_cd(char ***env, char *path)
{
	char			*pwd;
	int				id;
	int				id_home;
	struct stat		buf;
	int				ret;

	ret = 0;
	path = ft_strtrim_new(path);
	if (ft_nbargv(path) > 1)
		path = ft_strjoin(ft_getpath_pwd(ft_getcmd(path)), ft_strtrim_new(path + ft_strlen(ft_getcmd(path))));
	if (ft_error_cd(*env, path) || ft_not_dir(path))
		return (-1);
	bzero(&buf, sizeof(buf));
	if (ft_onlyesp(path) || ft_strnequ(path, "~", 1) || ft_strnequ(path, "--", 2))
	{
		if ((id_home = ft_get_id_var(*env, "HOME")) != -1)
			path = ft_strjoin(&env[0][id_home][5], path + ft_strlen(path));
	}
	if ((lstat(path, &buf) == 0 &&
				(S_ISDIR(buf.st_mode) || (S_ISLNK(buf.st_mode) && opendir(path)))) ||
			path[0] == '-')
	{
		if (ft_strnequ(path, "-", 1))
			ft_tiret(*env, path);
		ft_switch(env);
		id = ft_get_id_var(*env, "PWD");
		chdir(path);
		pwd = ft_pwd();
		if (id == -1)
			ft_setenv(env, ft_strjoin("PWD=", ft_strjoin(ft_get_prev_dir(pwd), path)));
		else if (S_ISLNK(buf.st_mode))
		{
			stat(path, &buf);
			(*env)[id] = ft_strjoin("PWD=", ft_strjoin(ft_get_prev_dir(pwd), path));
		}
		else
			(*env)[id] = ft_strjoin("PWD=", pwd);
	}
	return (ret);
}
