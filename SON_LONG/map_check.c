/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:57:51 by makboga           #+#    #+#             */
/*   Updated: 2025/03/15 15:49:31 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void player_control(t_win *pnc)
{
    int i;
    int j;

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
        write(2, "Error: Player Count Error", 26);
        close_frame(pnc);
        exit(1);
    }
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
			write(1, "Wall Error", 11);
			close_frame(pnc);
			exit(1);
		}
	}
	i = -1;
	last = pnc->map->w - 1;
	while (pnc->map->mappin[++i])
	{
		if (pnc->map->mappin[i][0] != '1' || pnc->map->mappin[i][last] != '1')
		{
			write(1, "Wall Error", 11);
			close_frame(pnc);
			exit(1);
		}
	}
}

void	map_size_control(t_win *pnc)
{
	int	i;
	int	len;

	i = 0;
	len = pnc->map->w;
	while (pnc->map->mappin[i])
	{
		if (ft_strlen(pnc->map->mappin[i]) != len)
		{
			write(1, "Line Size Error", 16);
			close_frame(pnc);
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
	if (pnc->map->end_cnt < 1)
	{
		write (1, "End Door Count Error", 21);
		close_frame(pnc);
		exit(1);
	}
}
