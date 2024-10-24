/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:55:49 by vzurera-          #+#    #+#             */
/*   Updated: 2024/06/22 16:48:46 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	Rotate player
void	rotate_player(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->pl.r_accum_time = 0.0;
		data->pl.dir += ROT_SP;
		if (data->pl.dir > 359)
			data->pl.dir = data->pl.dir - 360;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->pl.r_accum_time = 0.0;
		data->pl.dir -= ROT_SP;
		if (data->pl.dir < 0)
			data->pl.dir = 360 + data->pl.dir;
	}
}

//	Check if the move dont cross through a corner
static int	valid_move(t_data *data, int nx, int ny)
{
	int	x;
	int	y;

	x = data->pl.x / GRID_SIZE;
	y = data->pl.y / GRID_SIZE;
	if (x < nx && y < ny)
		if (data->map.map[y][x + 1] == '1' && data->map.map[y + 1][x] == '1')
			return (1);
	if (x < nx && y > ny)
		if (data->map.map[y][x + 1] == '1' && data->map.map[y - 1][x] == '1')
			return (1);
	if (x > nx && y < ny)
		if (data->map.map[y][x - 1] == '1' && data->map.map[y + 1][x] == '1')
			return (1);
	if (x > nx && y > ny)
		if (data->map.map[y][x - 1] == '1' && data->map.map[y - 1][x] == '1')
			return (1);
	return (0);
}

//	Check if there is a colision with a wall and apply the correct move
static void	apply_move(t_data *data, int mv_y, int mv_x)
{
	int	temp_y;
	int	temp_x;

	temp_y = (data->pl.y + roundf(mv_y)) / GRID_SIZE;
	temp_x = (data->pl.x + roundf(mv_x)) / GRID_SIZE;
	if (data->map.map[temp_y][temp_x] != '1'
		&& !valid_move(data, temp_x, temp_y))
	{
		data->pl.y += roundf(mv_y);
		data->pl.x += roundf(mv_x);
	}
}

//	Move player
static void	move_player(t_data *data, int key, int speed)
{
	double	mv_y;
	double	mv_x;

	speed *= 1 + ((mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT)));
	if (key == MLX_KEY_W || key == MLX_KEY_UP)
	{
		mv_y = (speed * sin(data->pl.dir * (PI / 180.0))) * -1;
		mv_x = speed * cos(data->pl.dir * (PI / 180.0));
	}
	if (key == MLX_KEY_S || key == MLX_KEY_DOWN)
	{
		mv_y = (speed * sin((data->pl.dir + 180) * (PI / 180.0))) * -1;
		mv_x = speed * cos((data->pl.dir + 180) * (PI / 180.0));
	}
	if (key == MLX_KEY_A)
	{
		mv_y = roundf((speed * sin((data->pl.dir + 90) * (PI / 180.0))) * -1);
		mv_x = (speed * cos((data->pl.dir + 90) * (PI / 180.0)));
	}
	if (key == MLX_KEY_D)
	{
		mv_y = (speed * sin((data->pl.dir - 90) * (PI / 180.0))) * -1;
		mv_x = speed * cos((data->pl.dir - 90) * (PI / 180.0));
	}
	apply_move(data, mv_y, mv_x);
}

//	Check if the key to move is pressed and move the player
void	check_moves(t_data *data)
{
	int	speed;

	speed = MOV_SP;
	if ((mlx_is_key_down(data->mlx, 87) || mlx_is_key_down(data->mlx, 83) || \
			mlx_is_key_down(data->mlx, 265) || mlx_is_key_down(data->mlx, 264))
		&& (mlx_is_key_down(data->mlx, 65) || mlx_is_key_down(data->mlx, 68)))
		speed = speed / 2;
	if (mlx_is_key_down(data->mlx, 87) || mlx_is_key_down(data->mlx, 265))
		move_player(data, MLX_KEY_W, speed);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S)
		|| mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		move_player(data, MLX_KEY_S, speed);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player(data, MLX_KEY_A, speed);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player(data, MLX_KEY_D, speed);
	if (mlx_is_key_down(data->mlx, 87) || mlx_is_key_down(data->mlx, 83)
		|| mlx_is_key_down(data->mlx, 265) || mlx_is_key_down(data->mlx, 264)
		|| mlx_is_key_down(data->mlx, 65) || mlx_is_key_down(data->mlx, 68))
	{
		data->pl.pos_y = data->pl.y / GRID_SIZE;
		data->pl.pos_x = data->pl.x / GRID_SIZE;
		data->pl.m_accum_time = 0.0;
	}
}
