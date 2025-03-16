/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:57:30 by makboga           #+#    #+#             */
/*   Updated: 2025/03/16 22:48:30 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./minilibx-linux/mlx.h"
# include "./libft/libft.h"
# include "./printf/ft_printf.h"
# include <stdlib.h>
# include <fcntl.h>
# include "./gnl/get_next_line.h"

typedef struct s_char
{
	int		l_x;
	int		l_y;
	int		point;
	void	*chr_front;
	void	*chr_back;
	void	*chr_left;
	void	*chr_right;
	void	*chr_cur;
}	t_char;

typedef struct s_map
{
	char	**mappin;
	int		w;
	int		h;
	int		cb;
	int		gate_x;
	int		gate_y;
	int		p_cnt;
	int		end_cnt;
	int		coin_cnt;
}	t_map;

typedef struct s_win
{
	t_map	*map;
	t_char	*chr;
	void	*win;
	void	*mlx;
	void	*img_bg;
	void	*block_bg;
	void	*c_bg;
	void	*end_bg;
	int		height;
	int		width;
}	t_win;

int		walk(int keycode, void *param);
void	putchr(t_win *pnc, int keycode);
char	*read_file(char	*path, t_map *map);
t_map	*read_map(char *path);
void	put_element(char c, t_win *pnc, int x, int y);
void	render_map(t_win *pnc);
int		close_frame(void *param);
void	player_control(t_win *pnc);
void	get_img(t_win *pnc, int x, int y);
void	wall_control(t_win *pnc);
void	map_size_control(t_win	*pnc);
void	end_control(t_win *pnc);
void	endln_control(char line);
void	coin_control(t_win *pnc);
void	file_control(char *path);
void	char_control(t_win *pnc);
void	xpm_control(void);
void	xpm_control_two(void);
void	path_checker(char *path);
void	find_player(t_map *map, int *px, int *py);
void	check_square_map(t_map *map);
int		check_valid_path(t_map *map);
char	**ft_map_dup(char **map, int rows);
void	ft_free_map(char **map, int rows);
int		is_player_surrounded(t_map *map);
int		is_coin_surrounded(t_map *map, int i, int j);
#endif
