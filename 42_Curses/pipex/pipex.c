/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:32:44 by makboga           #+#    #+#             */
/*   Updated: 2025/03/26 16:02:22 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(char *cmd2, char **s_cmd, int a)
{
	ft_putstr_fd("Pipex: Command not found: ", 2);
	ft_putendl_fd(cmd2, 2);
	ft_free(s_cmd);
	exit(a);
}

void	exec(char *cmd2, char **env)
{
	char	**s_cmd;
	char	*path;

	if (!cmd2)
		ft_exit(cmd2, NULL, 1);
	s_cmd = ft_split(cmd2, ' ');
	if (!s_cmd || !s_cmd[0])
		ft_exit(cmd2, s_cmd, 127);
	path = path_split(s_cmd[0], env);
	if (!path)
	{
		ft_free(s_cmd);
		ft_putstr_fd("Pipex: Command not found: ", 2);
		ft_putendl_fd(cmd2, 2);
		exit(127);
	}
	if (execve(path, s_cmd, env) == -1)
	{
		perror("execve error");
		ft_exit(s_cmd[0], s_cmd, 127);
	}
}

void	side_process(int *fd, char **av, char **ep)
{
	int	fd2;

	fd2 = open_file(av[1], 0);
	if (fd2 == -1)
	{
		if (access(av[1], R_OK) == -1 && access(av[1], F_OK) != -1)
		{
			ft_putstr_fd(av[1], 2);
			ft_putendl_fd(": Permission denied", 2);
			exit(1);
		}
		ft_putstr_fd(av[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(1);
	}
	dup2(fd2, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	close(fd2);
	exec(av[2], ep);
}

void	main_process(int *fd, char **av, char **ep)
{
	int	fd2;

	fd2 = open_file(av[4], 1);
	if (fd2 == -1)
	{
		if (access(av[4], W_OK) == -1)
		{
			ft_putstr_fd(av[4], 2);
			ft_putendl_fd(": Permission denied", 2);
			exit (1);
		}
		ft_putstr_fd(av[4], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit (1);
	}
	dup2(fd2, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	close(fd2);
	exec(av[3], ep);
}

int	main(int ac, char **av, char **ep)
{
	pid_t	pid;
	int		fd[2];

	if (ac == 5)
	{
		pipe(fd);
		if (pipe(fd) == -1)
			return (perror("Error: Pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("Error: Fork"), 1);
		if (pid == 0)
			side_process(fd, av, ep);
		waitpid(pid, NULL, 0);
		if (pid != 0)
			main_process(fd, av, ep);
	}
	else
	{
		ft_putendl_fd("Example: ./pipex file1 cmd1 cmd2 file2", 2);
		return (1);
	}
	return (0);
}
