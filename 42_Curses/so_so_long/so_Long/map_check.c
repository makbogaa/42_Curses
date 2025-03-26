/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:57:51 by makboga           #+#    #+#             */
/*   Updated: 2025/03/18 22:11:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	player_control(t_win *pnc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	pnc->map->p_cnt = 0;
	while (pnc->map->mappin[i])
	{
		j = 0;
		while (pnc->map->mappin[i][j])
		{
			if (pnc->map->mappin[i][j] == 'P')
			{
				pnc->map->p_cnt++;
			}
			j++;
		}
		i++;
	}
	if (pnc->map->p_cnt != 1)
	{
		ft_printf("Error: Player Count Error!\n");
		ft_free_game(pnc);
		exit(1);
	}
}

int		is_player_surrounded(t_win *pnc)
{
    int walls_or_end_count;
    int px;
    int py;

    walls_or_end_count = 0;
    find_player(pnc->map, &px, &py);
    if (px - 1 >= 0 && (pnc->map->mappin[px - 1][py] == '1' || pnc->map->mappin[px - 1][py] == 'E'))
        walls_or_end_count++;
    if (px + 1 < pnc->map->h && (pnc->map->mappin[px + 1][py] == '1' || pnc->map->mappin[px + 1][py] == 'E'))
        walls_or_end_count++;
    if (py - 1 >= 0 && (pnc->map->mappin[px][py - 1] == '1' || pnc->map->mappin[px][py - 1] == 'E'))
        walls_or_end_count++;
    if (py + 1 < pnc->map->w && (pnc->map->mappin[px][py + 1] == '1' || pnc->map->mappin[px][py + 1] == 'E'))
        walls_or_end_count++;
    if (walls_or_end_count == 4)
    {
        ft_printf("Error: Player is surrounded by walls or the end!\n");
		ft_free_game(pnc);
        exit(1);
    }
    return 0;
}

void	wall_control(t_win *pnc)
{
	int	i;
	int	last;

	i = -1;
	while (pnc->map->mappin[0][++i])
	{
		if (pnc->map->mappin[0][i] != '1' ||
			pnc->map->mappin[pnc->map->h - 1][i] != '1')
		{
			ft_printf("Error: Wall Error!\n");
			ft_free_game(pnc);
			exit(1);
		}
	}
	i = -1;
	last = pnc->map->w - 1;
	while (pnc->map->mappin[++i])
	{
		if (pnc->map->mappin[i][0] != '1' || pnc->map->mappin[i][last] != '1')
		{
			ft_printf("Error: Wall Error!\n");
			ft_free_game(pnc);
			exit(1);
		}
	}
}

void	map_size_control(t_win *pnc)
{
	int	i;

	i = 0;
	while (pnc->map->mappin[i])
	{
		if (ft_strlen(pnc->map->mappin[i]) != pnc->map->w)
		{
			ft_printf("Error: Line Size Error!\n");
			ft_free_game(pnc);
			exit(1);
		}
		i++;
	}
}

void	end_control(t_win *pnc)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (pnc->map->mappin[++i])
	{
		while (pnc->map->mappin[i][++j])
		{
			if (pnc->map->mappin[i][j] == 'E')
			{
				pnc->map->end_cnt = pnc->map->end_cnt + 1;
			}
		}
		j = 0;
	}
	if (pnc->map->end_cnt != 1)
	{
		ft_printf("Error: End Door Count Error!\n");
		ft_free_game(pnc);
		exit(1);
	}
}
