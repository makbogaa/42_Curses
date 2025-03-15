/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:57:19 by makboga           #+#    #+#             */
/*   Updated: 2025/03/15 15:05:08 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	putchr(t_win *pnc, int keycode)
{
	if (keycode == 2)
		pnc->chr->chr_cur = pnc->chr->chr_right;
	if (keycode == 0)
		pnc->chr->chr_cur = pnc->chr->chr_left;
	if (keycode == 13)
		pnc->chr->chr_cur = pnc->chr->chr_back;
	if (keycode == 1)
		pnc->chr->chr_cur = pnc->chr->chr_front;
}

void	find_player(t_map *map, int *px, int *py)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->h)
	{
		j = -1;
		while (++j < map->w)
		{
			if (map->mappin[i][j] == 'P')
			{
				*px = i;
				*py = j;
				return ;
			}
		}
	}
}

void	check_square_map(t_map *map)
{
	int	i;
	int	row_length;

	if (!map || !map->mappin)
	{
		write(1, "Error: Map is invalid.\n", 23);
		exit(1);
	}
	row_length = ft_strlen(map->mappin[0]);
	i = 1;
	while (map->mappin[i]) 
	{
		if (ft_strlen(map->mappin[i]) != row_length)
			return ;
		i++;
	}
	if (i == row_length)
	{
		write(1, "Error: The map is square.\n", 26);
		exit(1);
	}
}

void	move_p(t_win *pnc, int side, int x, int y)
{
	if (pnc->map->cb == 0 && pnc->map->mappin[y / 64][x / 64] == 'E')
	{
		pnc->chr->point += 1;
		ft_printf("%d\nYou Win!\n", pnc->chr->point);
		close_frame(pnc);
	}
	else if (pnc->map->mappin[y / 64][x / 64] != '1'
				&& pnc->map->mappin[y / 64][x / 64] != 'E')
	{
		putchr(pnc, side);
		pnc->chr->point += 1;
		if (pnc->map->mappin[y / 64][x / 64] == 'C')
			pnc->map->cb -= 1;
		pnc->map->mappin[pnc->chr->l_y / 64][pnc->chr->l_x / 64] = '0';
		pnc->map->mappin[pnc->map->gate_y / 64][pnc->map->gate_x / 64] = 'E';
		pnc->map->mappin[y / 64][x / 64] = 'P';
		pnc->chr->l_x = x;
		pnc->chr->l_y = y;
		ft_printf("Yeni Pozisyon: (%d, %d)\n", pnc->chr->l_x, pnc->chr->l_y);
		ft_printf("%d\n", pnc->chr->point);
	}
}

int	walk(int keycode, void *param)
{
	t_win	*pnc;

	pnc = param;
	if (!pnc || !pnc->chr)
		return (keycode);
	mlx_clear_window(pnc->mlx, pnc->win);
	ft_printf("Keycode: %d\n", keycode);
	if (keycode == 100)
		move_p(pnc, keycode, pnc->chr->l_x + 64, pnc->chr->l_y);
	if (keycode == 97)
		move_p(pnc, keycode, pnc->chr->l_x - 64, pnc->chr->l_y);
	if (keycode == 119)
		move_p(pnc, keycode, pnc->chr->l_x, pnc->chr->l_y - 64);
	if (keycode == 115)
		move_p(pnc, keycode, pnc->chr->l_x, pnc->chr->l_y + 64);
	if (keycode == 65307)
		close_frame(pnc);
	render_map(pnc);
	return (keycode);
}
