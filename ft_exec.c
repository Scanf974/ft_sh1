/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 02:25:48 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/03 02:35:46 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int                 ft_exec(char *bin, char *cmd, char **env)
{
	pid_t           child;
	int             status;
	char            **tab;

	child = fork();
	if (child < 0)
		return (-1);
	if (child > 0)
	{
		waitpid(child, &status, 0);
	}
	else
	{
		tab = ft_strsplit_white_space(cmd);
		execve(bin, tab, env);
		exit(-1);
	}
	return (WEXITSTATUS(status));
}
