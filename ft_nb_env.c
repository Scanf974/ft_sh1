int		ft_nb_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
