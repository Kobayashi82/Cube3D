/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:04:28 by vzurera-          #+#    #+#             */
/*   Updated: 2024/06/22 16:19:47 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	Free the map in the bidimensional array
static void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.map && data->map.map[i])
		free(data->map.map[i++]);
	free(data->map.map);
}

//	Free the map in the linked list
static void	free_map_lst(t_data *data)
{
	t_map_lst	*current;
	t_map_lst	*tmp;

	current = data->map_lst;
	while (current)
	{
		free(current->row);
		tmp = current->next;
		free(current);
		current = tmp;
	}
}

//	Free the textures of MLX42
static void	free_textures(t_data *data)
{
	if (data->txs.no)
		mlx_delete_texture(data->txs.no);
	if (data->txs.so)
		mlx_delete_texture(data->txs.so);
	if (data->txs.we)
		mlx_delete_texture(data->txs.we);
	if (data->txs.ea)
		mlx_delete_texture(data->txs.ea);
}

//	Free the main data structure
void	free_data(t_data *data)
{
	free_map_lst(data);
	free_map(data);
	free_textures(data);
	free(data->projection);
	if (data->map.fd != -1)
		close(data->map.fd);
}

//	Protect malloc safely
void	*safe_malloc(t_data *data, int size)
{
	void	*temp;

	temp = malloc(size);
	if (temp == NULL)
		exit_error(data, NO_MEMORY, NULL, true);
	return (temp);
}
