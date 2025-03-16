/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_xpm_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:58:10 by makboga           #+#    #+#             */
/*   Updated: 2025/03/16 17:01:34 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	endln_control(char line)
{
	if (line == '\n')
	{
		ft_printf("Error: Empty Line In Map!\n");
		exit(1);
	}
}

void	xpm_control(void)
{
	int	fd_bg;
	int	fd_block;
	int	fd_coin;

	fd_bg = open("./textures/bg.xpm", O_RDWR);
	fd_block = open("./textures/block.xpm", O_RDWR);
	fd_coin = open("./textures/coin.xpm", O_RDWR);
	if (fd_bg <= 0 || fd_block <= 0 || fd_coin <= 0)
	{
		ft_printf("Error: Missing XPM File!\n");
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

	fd_endgate = open("./textures/endgate.xpm", O_RDWR);
	fd_front = open("./textures/player.xpm", O_RDWR);
	if (fd_endgate <= 0 || fd_front <= 0)
	{
		ft_printf("Error: Missing XPM File!\n");
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
		ft_printf("Error: Wrong File Extension!\n");
		exit(1);
	}
}
