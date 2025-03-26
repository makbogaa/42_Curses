/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_srcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:04:43 by makboga           #+#    #+#             */
/*   Updated: 2025/03/26 16:06:22 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **rafa)
{
	size_t	i;

	i = 0;
	if (!rafa)
		return ;
	while (rafa[i])
	{
		free(rafa[i]);
		i++;
	}
	free(rafa);
}

int	open_file(char *av, int a)
{
	int	res;

	if (a == -1)
		exit(127);
	if (a == 0)
		res = open(av, O_RDONLY, 0777);
	if (a == 1)
		res = open(av, O_CREAT | O_APPEND | O_WRONLY | O_TRUNC, 0777);
	return (res);
}

char	*file_control(char *base, char *cmd)
{
	char	*path;
	char	*file;

	path = ft_strjoin(base, "/");
	file = ft_strjoin(path, cmd);
	free(path);
	if (!access(file, F_OK))
	{
		if (!access(file, X_OK))
			return (file);
	}
	free(file);
	return (NULL);
}

char	*path_control(char *path, char **env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		str = ft_substr(env[i], 0, j);
		if (ft_strncmp(str, path, j) == 0)
			return (free(str), env[i] + j + 1);
		free(str);
		i++;
	}
	return (NULL);
}

void	*path_split(char *cmd, char **env)
{
	int		i;
	char	*file;
	char	**s_cmd;
	char	**path;

	i = 0;
	path = ft_split(path_control("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (path[i])
	{
		file = file_control(path[i], s_cmd[0]);
		if (file)
		{
			ft_free(path);
			ft_free(s_cmd);
			return (file);
		}
		i++;
	}
	ft_free(path);
	ft_free(s_cmd);
	return (NULL);
}
