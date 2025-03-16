/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:58:02 by makboga           #+#    #+#             */
/*   Updated: 2025/03/16 22:46:08 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	coin_control(t_win *pnc)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (pnc->map->mappin[++i])
	{
		while (pnc->map->mappin[i][++j])
		{
			if (pnc->map->mappin[i][j] == 'C')
				pnc->map->coin_cnt = pnc->map->coin_cnt + 1;
		}
		j = 0;
	}
	if (pnc->map->coin_cnt <= 0)
	{
		ft_printf("Error: Not Found Coin in Map!\n");
		close_frame(pnc);
		exit(1);
	}
}

void flood_fill_two(char **map, int x, int y, t_map *map_data)
{
    if (x < 0 || x >= map_data->h || y < 0 || y >= map_data->w)
        return ;
    if (map[x][y] == '1' || map[x][y] == 'E' || map[x][y] == 'F')
        return ; 
    map[x][y] = 'F';
    flood_fill_two(map, x + 1, y, map_data);
    flood_fill_two(map, x - 1, y, map_data);
    flood_fill_two(map, x, y + 1, map_data);
    flood_fill_two(map, x, y - 1, map_data);
}

int is_coin_surrounded(t_map *map, int i, int j)
{
    char **temp;
	int px;
	int py;

    temp = ft_map_dup(map->mappin, map->h);
    find_player(map, &px, &py);
    flood_fill_two(temp, px, py, map);
    i = 0;
    while (i < map->h)
    {
        j = 0;
        while (j < map->w)
        {
            if (map->mappin[i][j] == 'C' && temp[i][j] != 'F')
            {
                ft_printf("Error: Coin is unreachable!\n");
                ft_free_map(temp, map->h);
                exit(1);
            }
            j++;
        }
        i++;
    }
    ft_free_map(temp, map->h);
    return (0);
}

void	file_control(char *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	if (fd <= 0)
	{
		ft_printf("Error: Wrong File Path!\n");
		close(fd);
		exit(1);
	}
	close(fd);
}

void	char_control(t_win *pnc)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (pnc->map->mappin[++i])
	{
		while (pnc->map->mappin[i][++j])
		{
			if (pnc->map->mappin[i][j] != '0'
				&& pnc->map->mappin[i][j] != '1'
				&& pnc->map->mappin[i][j] != 'P'
				&& pnc->map->mappin[i][j] != 'C'
				&& pnc->map->mappin[i][j] != 'E')
			{
				ft_printf("Error: Undefined Char!\n");
				close_frame(pnc);
				exit(1);
			}
		}
		j = 0;
	}
}
