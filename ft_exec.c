/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 02:25:48 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/15 21:05:38 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int			ft_exec(char *bin, char *cmd, char **env)
{
	pid_t		child;
	int			status;

	child = fork();
	if (child < 0)
		return (-1);
	if (child > 0)
		waitpid(child, &status, 0);
	else
	{
		execve(bin, ft_strsplit_whitespace(cmd), env);
		exit(-1);
	}
	return (WEXITSTATUS(status));
}
