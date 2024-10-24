/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:36:48 by vzurera-          #+#    #+#             */
/*   Updated: 2024/06/22 11:07:40 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	Get the RGB value from the readed line
static char	*get_value(t_data *data, char *line)
{
	char	*value;
	int		i;

	i = 0;
	while (line && line[i] && line[i] != ',' && !ft_isspace(line[i]))
		i++;
	value = ft_substr(line, 0, i);
	if (!value)
		exit_error(data, NO_MEMORY, NULL, true);
	if (!ft_isdigit_s(value))
	{
		free(value);
		return (NULL);
	}
	return (value);
}

//	Convert to a number and validate the RGB value
static int	load_rgb_value(t_data *data, uint8_t *rgb_value, char **line)
{
	char	*value;
	long	number;

	value = get_value(data, *line);
	if (!value)
		return (1);
	while (*line && (*line)[0] && (*line)[0] != ',')
		(*line)++;
	if (**line == ',')
		(*line)++;
	while (*line && ft_isspace(**line))
		(*line)++;
	if (!ft_isdigit_s(value))
	{
		free(value);
		return (1);
	}
	number = ft_atol(value);
	free(value);
	if (errno == ERANGE || number < 0 || number > 255)
		return (1);
	*rgb_value = number;
	return (0);
}

//	Load the RGB values for the floor
int	load_rgb_f(t_data *data, char *line, int error)
{
	int	len;
	int	cerror;

	cerror = 0;
	if (!line || !*line)
		cerror = exit_error(data, FILE_ERR, NULL, false);
	else
	{
		while (line && ft_isspace(*line))
			line++;
		len = ft_strlen(line);
		while (len-- && ft_isspace(line[len]))
			line[len] = '\0';
		cerror = load_rgb_value(data, &data->txs.f[0], &line);
		if (!cerror)
			cerror = load_rgb_value(data, &data->txs.f[1], &line);
		if (!cerror)
			cerror = load_rgb_value(data, &data->txs.f[2], &line);
		data->txs.f[3] = 255;
		if (cerror)
			return (exit_error(data, MAP_F_RGB, NULL, false));
	}
	return ((cerror || error));
}

//	Load the RGB values for the ceiling
int	load_rgb_c(t_data *data, char *line, int error)
{
	int	len;
	int	cerror;

	cerror = 0;
	if (!line || !*line)
		cerror = exit_error(data, FILE_ERR, NULL, false);
	else
	{
		while (line && ft_isspace(*line))
			line++;
		len = ft_strlen(line);
		while (len-- && ft_isspace(line[len]))
			line[len] = '\0';
		cerror = load_rgb_value(data, &data->txs.c[0], &line);
		if (!cerror)
			cerror = load_rgb_value(data, &data->txs.c[1], &line);
		if (!cerror)
			cerror = load_rgb_value(data, &data->txs.c[2], &line);
		data->txs.c[3] = 255;
		if (cerror)
			return (exit_error(data, MAP_C_RGB, NULL, false));
	}
	return ((cerror || error));
}
