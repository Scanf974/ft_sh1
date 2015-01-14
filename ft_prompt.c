/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/14 02:25:46 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/14 05:18:06 by bsautron         ###   ########.fr       */
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
	if (ft_strlen(cmd) > 0)
	{
		ft_putstr("\033[1D");
		ft_putstr(" ");
		ft_putstr("\033[1D");
	}
	cmd[ft_strlen(cmd) - 1] = '\0';
	return (cmd);
}

static void	ft_prompt2(char **env, int ret, int id_usr)
{
	if (ret == 0)
	{
		ft_putchar(-30);
		ft_putchar(-98);
		ft_putchar(-100);
		ft_putchar(' ');
		ft_putstr("\033[1;30;47m");
	}
	else
	{
		ft_putstr("\x1b[31m");
		ft_putchar(-30);
		ft_putchar(-98);
		ft_putchar(-100);
		ft_putchar(' ');
		ft_putstr("\033[1;31;47m");
	}
	if (id_usr != -1 && ft_strequ(ft_get_dirname(), &env[id_usr][5]))
		ft_putstr("~");
	else
		ft_putstr(ft_get_dirname());
	ft_putstr("\033[0;37;40m ");
}

static char	**ft_make_history(int *nb_hist)
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

static void	ft_nclear(size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		ft_putstr("\033[1D");
		ft_putstr(" ");
		ft_putstr("\033[1D");
		i++;
	}
}

char		*ft_prompt(char **env, int ret)
{
	char			*cmd;
	char			**history;
	int				id_usr;
	char			c[2];
	char			cac;
	int				fd;
	int				nb;
	int				i;

	nb = 0;
	history = ft_make_history(&nb);
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
			ft_nclear(ft_strlen(cmd));
			if (i == nb && (*c == 'A' || *c == 'B'))
				cmd = ft_strdup("");
			else if (*c == 'A' || *c == 'B')
				cmd = ft_strdup(history[i]);
			ft_putstr(cmd);
		}
		else
		{
			c[0] = cac;
			c[1] = '\0';
			if (cac != 127)
			{
				ft_putchar(cac);
				cmd = ft_strjoin(cmd, c);
			}
			else
				cmd = ft_delone(cmd);
		}
	}
	ft_putchar(10);
	fd = open(".minishell1_history", O_WRONLY | O_APPEND);
	write(fd, cmd, ft_strlen(cmd));
	write(fd, "\n", 1);
	close(fd);
	return (cmd);
}
