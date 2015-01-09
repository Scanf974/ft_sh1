/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 03:51:20 by bsautron          #+#    #+#             */
/*   Updated: 2014/12/25 23:17:21 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

char	**ft_getpath(char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (env[i] && !ft_strnequ(env[i], "PATH", 4))
		i++;
	if (i >= ft_nb_env(env))
		return (NULL);
	path = ft_strsplit(&env[i][5], ':');
	return (path);
}
