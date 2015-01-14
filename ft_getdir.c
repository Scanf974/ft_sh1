/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/14 02:10:39 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/14 02:10:40 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

char	*ft_getdir(char *path)
{
	char	*dst;
	int		i;

	i = ft_strlen(path) - 1;
	dst = ft_strdup(path);
	while (i >= 0 && path[i] != '/')
		i--;
	dst[i] = '\0';
	return (dst);
}
