/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 03:24:48 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/03 03:04:42 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static char	*ft_get_dirname(void)
{
	char	*path;
	int		len;

	path = ft_pwd();
	len = ft_strlen(path);
	while (path[len] != '/')
		len--;
	if (!path[len - 1])
		return (path + len);
	return (path + len + 1);
}

static char	*ft_delone(char *cmd)
{
	cmd[ft_strlen(cmd) - 1] = '\0';
	return (cmd);
}

static void	ft_prompt2(char **env, int ret, int id_usr)
{
	ft_putstr("\033[2K\r");
	if (ret == 0)
	{
		ft_putstr("➜ ");
		ft_putstr("\033[1;30;47m"); //Blanc
	}
	else
	{
		ft_putstr("\x1b[31m➜ ");
		ft_putstr("\033[1;31;47m"); //Rouge
	}
	if (id_usr != -1 && ft_strequ(ft_get_dirname(), &env[id_usr][5]))
		ft_putstr("~");
	else
		ft_putstr(ft_get_dirname());
	ft_putstr("\033[0;37;40m ");
}

char		**ft_make_history(int *nb_hist)
{
	char	*line;
	char	**tab;
	int		fd;
	int		i;

	fd = open(".minishell1_history", O_CREAT | O_RDWR, 0600);
	while (get_next_line(fd, &line) > 0)
		(*nb_hist)++;
	close(fd);
	fd = open(".minishell1_history", O_CREAT | O_RDONLY);
	i = 0;
	tab = (char **)malloc(sizeof(char *) * (*nb_hist + 1));
	while (get_next_line(fd, &line) > 0)
	{
		tab[i] = ft_strdup(line);
		i++;
	}
	tab[i] = NULL;
	close(fd);
	return (tab);
}

char		*ft_prompt(char **env, int ret)
{
	char			*cmd;
	char			**history;
	int				ret_gnl;
	int				id_usr;
	char			c[2];
	char			cac;
	int				fd;
	int				nb;
	int				i;

	nb = 0;
	history = ft_make_history(&nb);
	ret_gnl = 0;
	id_usr = ft_get_id_var(env, "USER");
	ft_prompt2(env, ret, id_usr);
	cmd = ft_strnew(1);
	i = nb;
	while (read(0, &cac, 1) != 0 && cac != '\n')
	{
		if (cac == '\033')
		{
			read(0, c, 1);
			read(0, c, 1);
			if (*c == 'A')
			{
				i--;
				if (i < 0)
					i = 0;
			}
			if (*c == 'B')
			{
				i++;
				if (i > nb)
					i = nb;
			}
			if (i == nb && (*c == 'A' || *c == 'B'))
				cmd = ft_strdup("");
			else if (*c == 'A' || *c == 'B')
				cmd = ft_strdup(history[i]);
		}
		else
		{
			c[0] = cac;
			c[1] = '\0';
			if (cac != 127)
				cmd = ft_strjoin(cmd, c);
			else
				cmd = ft_delone(cmd);
		}
		ft_prompt2(env, ret, id_usr);
		ft_putstr(cmd);
	}
	ft_putchar(10);
	fd = open(".minishell1_history", O_WRONLY | O_APPEND);
	write(fd, cmd, ft_strlen(cmd));
	write(fd, "\n", 1);
	close(fd);
	return (cmd);
}
