/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 03:21:58 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/03 02:22:41 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int		ft_nb_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int		main(int argc, char **argv, char **env)
{
	char	**saint_env;

	(void)argc;
	(void)argv;
	saint_env = (char **)malloc(sizeof(char *) * 2);
	if (ft_nb_env(env))
	{
		ft_setenv(&env, "OLDPWD= ");
		ft_cmd(env, ft_getpath(env));
	}
	else
	{
		ft_setenv(&saint_env, "PWD=/Volumes/Data/nfs/zfs-student-3/users/2014/bsautron/Semestre01/ft_sh1");
		ft_setenv(&saint_env, "USER=bsautron");
		ft_setenv(&saint_env, "PATH=/bin:/usr/bin");
		ft_cmd(saint_env, ft_getpath(saint_env));
	}

	return (0);
}
