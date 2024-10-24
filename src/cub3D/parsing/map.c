/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:05:36 by vzurera-          #+#    #+#             */
/*   Updated: 2024/06/19 18:47:07 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	Remove empty lines from the end of the map
static void	remove_empty_rows(t_data *data)
{
	t_map_lst	*current;
	t_map_lst	*tmp;

	current = data->map_lst;
	while (current && current->next)
		current = current->next;
	while (current && ft_isspace_s(current->row))
	{
		free(current->row);
		tmp = current->prev;
		free(current);
		current = tmp;
		if (current)
			current->next = NULL;
	}
}

//	Add a node to de map list
void	add_map_node(t_data *data, t_map_lst *new_row, char *line)
{
	t_map_lst	*current;

	if (!data->map_lst)
		data->map_lst = new_row;
	else
	{
		current = data->map_lst;
		while (current && current->next)
			current = current->next;
		current->next = new_row;
		current->next->prev = current;
	}
	if (ft_isspace_s(line) && data->map.empty_line == 0)
		data->map.empty_line = 1;
	else if (!ft_isspace_s(line) && data->map.empty_line == 1)
	{
		data->map.empty_line = 2;
		data->error = 1;
	}
}

//	Create a linked list containing the map
void	map_to_list(t_data *data, char *line)
{
	t_map_lst	*new_row;
	int			len;

	if (!data->extra && ft_isspace_s(line))
		return ;
	data->extra = 1;
	if (!ft_isspace_s(line))
		data->map.map_h++;
	new_row = ft_calloc(1, sizeof(t_map_lst));
	if (!new_row)
		exit_error(data, NO_MEMORY, NULL, true);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	new_row->row = ft_strdup(line);
	len = ft_strlen(new_row->row);
	while (len--)
		if (new_row->row[len] == '1')
			break ;
	if (data->map.map_w < len + 1)
		data->map.map_w = len + 1;
	if (!new_row->row)
		exit_error(data, NO_MEMORY, NULL, true);
	add_map_node(data, new_row, line);
	remove_empty_rows(data);
}

//	Add or cut the row to keep the map rectangular
char	*fixed_len(t_data *data, char *row)
{
	char	*new_row;
	int		spaces;
	int		len;

	spaces = 0;
	if (ft_strlen(row) > data->map.map_w)
		row[data->map.map_w] = '\0';
	new_row = malloc((data->map.map_w + 1) * sizeof(char));
	if (!new_row)
		exit_error(data, NO_MEMORY, NULL, false);
	len = ft_strlen(row);
	spaces = ft_abs(len - data->map.map_w);
	ft_strcpy(new_row, row);
	free(row);
	while (spaces--)
		new_row[len++] = ' ';
	new_row[len] = '\0';
	return (new_row);
}

//	Convert the map from a list to an array
int	map_to_array(t_data *data)
{
	t_map_lst	*current;
	t_map_lst	*tmp;
	int			i;

	i = 0;
	if (!data->extra)
		data->error = exit_error(data, MAP_NO, NULL, false);
	current = data->map_lst;
	if (!data->extra || !current)
		return (0);
	data->map.map = malloc((data->map.map_h + 1) * sizeof(char *));
	if (!data->map.map)
		exit_error (data, NO_MEMORY, NULL, true);
	while (i < data->map.map_h && current)
	{
		data->map.map[i] = fixed_len(data, current->row);
		current->row = NULL;
		tmp = current->next;
		free(current);
		current = tmp;
		i++;
	}
	data->map_lst = NULL;
	data->map.map[i] = NULL;
	return (0);
}
