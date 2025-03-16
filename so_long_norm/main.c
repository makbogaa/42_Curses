/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:58:20 by makboga           #+#    #+#             */
/*   Updated: 2025/03/16 22:51:29 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_img(t_win *pnc, int x, int y)
{
	pnc->height = pnc->map->h * 64;
	pnc->width = pnc->map->w * 64;
	pnc->mlx = mlx_init();
	pnc->win = mlx_new_window(pnc->mlx, pnc->width, pnc->height, "So Long");
	pnc->chr = ft_calloc(1, sizeof(t_char));
	if (!pnc->chr)
	{
		ft_printf("Error: Character structure allocation failed!\n");
		exit(1);
	}
	pnc->chr->l_x = 0;
	pnc->chr->l_y = 0;
	pnc->chr->point = 0;
	pnc->chr->chr_front = mlx_xpm_file_to_image(pnc->mlx, \
			"./textures/player.xpm", &x, &y);
	pnc->chr->chr_cur = pnc->chr->chr_front;
	pnc->img_bg = mlx_xpm_file_to_image(pnc->mlx, "./textures/bg.xpm", &x, &y);
	pnc->block_bg = mlx_xpm_file_to_image(pnc->mlx, "./textures/block.xpm", &x, &y);
	pnc->c_bg = mlx_xpm_file_to_image(pnc->mlx, "./textures/coin.xpm", &x, &y);
	pnc->end_bg = mlx_xpm_file_to_image(pnc->mlx, "./textures/endgate.xpm", &x, &y);
}

void	free_resources(t_win *pnc)
{
	int	i;

	if (!pnc)
		return ;
	if (pnc->map)
	{
		if (pnc->map->mappin)
		{
			i = 0;
			while (i < pnc->map->h && pnc->map->mappin[i])
			{
				free(pnc->map->mappin[i]);
				i++;
			}
			free(pnc->map->mappin);
		}
		free(pnc->map);
	}
	if (pnc->chr)
	{
		mlx_destroy_image(pnc->mlx, pnc->chr->chr_front);
		free(pnc->chr);
	}
}

void	open_windows(t_win *pnc, char *path)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	pnc->map = read_map(path);
	if (!pnc->map)
	{
		ft_printf("Error: Failed to load map!\n");
		exit(1);
	}
	map_size_control(pnc);
	wall_control(pnc);
	player_control(pnc);
	end_control(pnc);
	coin_control(pnc);
	char_control(pnc);
	check_square_map(pnc->map);
	check_valid_path(pnc->map);
	is_coin_surrounded(pnc->map,x,y);
	is_player_surrounded(pnc->map);
	get_img(pnc, x, y);
}

int	close_frame(void *param)
{
	t_win	*pnc;

	if (!param)
		return (1);
	pnc = (t_win *)param;
	free_resources(pnc);
	mlx_destroy_image(pnc->mlx, pnc->c_bg);
	mlx_destroy_image(pnc->mlx, pnc->end_bg);
	mlx_destroy_image(pnc->mlx, pnc->block_bg);
	mlx_destroy_image(pnc->mlx, pnc->img_bg);
	mlx_destroy_window(pnc->mlx, pnc->win);
	mlx_destroy_display(pnc->mlx);
	free(pnc->mlx);
	free(pnc);
	exit(1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_win	*pnc;

	pnc = malloc(sizeof(t_win));
	if (argc == 2)
	{
		xpm_control();
		xpm_control_two();
		path_checker(argv[1]);
		file_control(argv[1]);
		open_windows(pnc, argv[1]);
		render_map(pnc);
		mlx_hook(pnc->win, 2, (1L << 0), walk, pnc);
		mlx_hook(pnc->win, 17, 0, close_frame, pnc);
		mlx_loop(pnc->mlx);
	}
	else
	{
		ft_printf("Error: Missing Argument!\n");
	}
	return (0);
}
