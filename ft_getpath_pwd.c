/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/14 02:10:58 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/15 18:51:14 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

char	*ft_getpath_pwd(char *path)
{
	char	*dst;
	int		i;
	int		j;

	dst = ft_strdup(ft_pwd());
	i = ft_strlen(dst) - 1;
	j = ft_strlen(path) - 1;
	while (i >= 0 && j >= 0)
	{
		dst[i] = '\0';
		i--;
		j--;
	}
	return (dst);
}
