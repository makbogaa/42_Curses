/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_control_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:58:10 by makboga           #+#    #+#             */
/*   Updated: 2025/03/13 11:53:28 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	xpm_control(void)
{
	int	fd_bg;
	int	fd_block;
	int	fd_coin;

	fd_bg = open("./img/bg.xpm", O_RDWR);
	fd_block = open("./img/block.xpm", O_RDWR);
	fd_coin = open("./img/coin.xpm", O_RDWR);
	if (fd_bg <= 0 || fd_block <= 0 || fd_coin <= 0)
	{
		write(1, "Missing XPM File\n", 18);
		close(fd_bg);
		close(fd_block);
		close(fd_coin);
		exit(1);
	}
	close(fd_bg);
	close(fd_block);
	close(fd_coin);
}

void	xpm_control_two(void)
{
	int	fd_endgate;
	int	fd_front;

	fd_endgate = open("./img/endgate.xpm", O_RDWR);
	fd_front = open("./img/player.xpm", O_RDWR);
	if (fd_endgate <= 0 || fd_front <= 0)
	{
		write(1, "Missing XPM File\n", 18);
		close(fd_endgate);
		close(fd_front);
		exit(1);
	}
	close(fd_endgate);
	close(fd_front);
}

void	path_checker(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (path[len - 1] != 'r' || path[len - 2] != 'e'
		|| path[len - 3] != 'b' || path[len - 4] != '.')
	{
		write(1, "Wrong File Extension", 21);
		exit(1);
	}
}
