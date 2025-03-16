/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:00 by makboga           #+#    #+#             */
/*   Updated: 2025/03/14 20:30:00 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(char **map, int x, int y, t_map *map_data)
{
	if (x < 0 || x >= map_data->h || y < 0 || y >= map_data->w)
		return ;
	if (map[x][y] == '1' || map[x][y] == 'F' )
		return ;
	map[x][y] = 'F';
	flood_fill(map, x + 1, y, map_data);
	flood_fill(map, x - 1, y, map_data);
	flood_fill(map, x, y + 1, map_data);
	flood_fill(map, x, y - 1, map_data);
}

int	is_path_valid(t_map *map, char **temp_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			if (map->mappin[i][j] == 'C' && temp_map[i][j] != 'F')
				return (0);
			if (map->mappin[i][j] == 'E' && temp_map[i][j] != 'F')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_valid_path(t_map *map)
{
	char	**temp;
	int		px;
	int		py;

	temp = ft_map_dup(map->mappin, map->h);
	if (!temp)
	{
		ft_printf("Error: Failed to duplicate map!\n");
		exit(1);
	}
	find_player(map, &px, &py);
	flood_fill(temp, px, py, map);
	if (!is_path_valid(map, temp))
	{
		ft_free_map(temp, map->h);
		ft_printf("Error: Invalid path to End door or Coins!\n");
		exit(1);
	}
	ft_free_map(temp, map->h);
	return (0);
}

char	**ft_map_dup(char **map, int rows)
{
	char	**new_map;
	int		i;

	new_map = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
		{
			ft_free_map(new_map, i);
			return (NULL);
		}
		i++;
	}
	new_map[rows] = NULL;
	return (new_map);
}

void	ft_free_map(char **map, int rows)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
