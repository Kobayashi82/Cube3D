/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:32:16 by vzurera-          #+#    #+#             */
/*   Updated: 2024/07/19 14:35:34 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	Create the main window
void	create_window(t_data *data)
{
	data->mlx = mlx_init(data->win.width, data->win.height, "CUBE3D", false);
	if (!data->mlx)
		exit_error(data, MLX_ERROR, NULL, true);
	data->img = mlx_new_image(data->mlx, data->win.width, data->win.height);
	ft_memset(data->img->pixels, 255, \
		data->img->width * data->img->height * sizeof(int32_t));
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

//	Initialize data structure
void	initialize(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->map.fd = -1;
	data->pl.move_time = 0.01;
	data->pl.m_accum_time = 0.01;
	data->pl.rotate_time = 0.01;
	data->pl.r_accum_time = 0.020;
	data->pl.mouse_time = 0.001;
	data->pl.ms_accum_time = 0.020;
	data->map.draw_time = 0.01;
	data->map.accum_time = 0;
	data->pl.l_x = -2;
	data->win.width = 1920;
	data->win.height = 1080;
}

//	Entry point of the program
int	main(int argc, char **argv)
{
	t_data	data;

	initialize(&data);
	if (argc != 2)
		exit_error(&data, INV_ARGS, NULL, true);
	load_map(&data, argv[1]);
	create_window(&data);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(data.mlx, delta_time, &data);
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_data(&data);
	return (0);
}
