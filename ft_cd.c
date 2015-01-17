/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 04:51:47 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/17 00:35:21 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

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

static char	*ft_path_tild(char **env, char *path)
{
	char	*dst;
	int		id_home;
	int		i;

	i = 0;
	dst = ft_strrchr(path, '~');
	id_home = ft_get_id_var(env, "HOME");
	if (!dst || id_home == -1)
		dst = path;
	else
	{
		while (path[i])
		{
			if (path[i] == '~')
				dst = ft_strjoin(&env[id_home][5], &path[i + 1]);
			i++;
		}
	}
	return (dst);
}

static void	ft_foock(char ***env, char *path, struct stat buf)
{
	int				id;
	char			*pwd;

	if (ft_strequ(path, "-"))
		ft_tiret(*env, path);
	ft_switch(env);
	id = ft_get_id_var(*env, "PWD");
	chdir(path);
	pwd = ft_pwd();
	if (id == -1)
	{
		ft_setenv(env, ft_strjoin("PWD=",
					ft_strjoin(ft_get_prev_dir(pwd), path)));
	}
	else if (S_ISLNK(buf.st_mode))
	{
		stat(path, &buf);
		(*env)[id] = ft_strjoin("PWD=", ft_strjoin(ft_get_prev_dir(pwd), path));
	}
	else
		(*env)[id] = ft_strjoin("PWD=", pwd);
}

int			ft_cd(char ***env, char *path)
{
	int				id_home;
	struct stat		buf;
	int				ret;
	char			**tab;
	char			*r_path;

	ret = 0;
	tab = ft_strsplit_whitespace(path);
	if (!(*tab))
		*tab = ft_strnew(1);
	tab[0] = ft_path_tild(*env, tab[0]);
	bzero(&buf, sizeof(buf));
	if (ft_onlyesp(path) ||
			ft_strnequ(tab[0], "~", 1) || ft_strnequ(tab[0], "--", 2))
		if ((id_home = ft_get_id_var(*env, "HOME")) != -1)
			tab[0] = &env[0][id_home][5];
	if (ft_error_cd(*env, tab, path) || ft_not_dir(tab, path))
		return (-1);
	r_path = tab[0];
	if (ft_nb_env(tab) > 1 && !ft_onlyesp(path))
		r_path = tab[1];
	if ((lstat(r_path, &buf) == 0 && (S_ISDIR(buf.st_mode) ||
		(S_ISLNK(buf.st_mode) && opendir(r_path)))) || ft_strequ(r_path, "-"))
		ft_foock(env, r_path, buf);
	return (ret);
}
