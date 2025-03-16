/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:57:38 by makboga           #+#    #+#             */
/*   Updated: 2025/03/16 22:52:26 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*read_file(char	*path, t_map *map)
{
	char	*line;
	char	*ret;
	int		fd;
	int		i;

	i = 0;
	fd = open(path, O_RDONLY);
	ret = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		endln_control(line[i]);
		while (line[i++])
		{
			if (line[i] == 'C')
				map->cb = map->cb + 1;
		}
		i = 0;
		strappend(&ret, line);
		free(line);
	}
	close(fd);
	return (ret);
}

t_map	*read_map(char *path)
{
	t_map	*map;
	char	*raw_map;
	int	i;

	i = 0;
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	raw_map = read_file(path, map);
	if (!raw_map)
		return (free(map), NULL);
	map->mappin = ft_split(raw_map, '\n');
	free(raw_map);
	if (!map->mappin)
		return (free(map),free(map->mappin), NULL);
	map->h = 0;
	while (map->mappin[map->h])
		map->h++;
	map->w = ft_strlen(map->mappin[0]);
	return (map);
}

void	put_element(char c, t_win *pnc, int x, int y)
{
	mlx_put_image_to_window(pnc->mlx, pnc->win, pnc->img_bg, x, y);
	if (c == 'P')
	{
		pnc->chr->l_x = x;
		pnc->chr->l_y = y;
		mlx_put_image_to_window(pnc->mlx, pnc->win, pnc->chr->chr_cur, x, y);
	}
	if (c == '1')
		mlx_put_image_to_window(pnc->mlx, pnc->win, pnc->block_bg, x, y);
	if (c == 'C')
		mlx_put_image_to_window(pnc->mlx, pnc->win, pnc->c_bg, x, y);
	if (c == 'E')
	{
		pnc->map->gate_x = x;
		pnc->map->gate_y = y;
		mlx_put_image_to_window(pnc->mlx, pnc->win, pnc->end_bg, x, y);
	}
}

void	put_score(t_win *pnc)
{
	char	*score;

	score = ft_itoa(pnc->chr->point);
	mlx_string_put(pnc->mlx, pnc->win, 20, 20, 0xFFFFFFFF, score);
	free(score);
}

void	render_map(t_win *pnc)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	if (!pnc || !pnc->map || !pnc->map->mappin)
		return ;
	while (i < pnc->map->h && pnc->map->mappin[i])
	{
		j = 0;
		x = 0;
		while (pnc->map->mappin[i][j])
		{
			put_element(pnc->map->mappin[i][j], pnc, x, y);
			j++;
			x += 64;
		}
		i++;
		y += 64;
	}
	put_score(pnc);
}
