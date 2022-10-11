/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mini_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:02:20 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/11 15:11:33 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_check_map(t_data *data, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (x >= data->data_map.width || y >= data->data_map.height)
		return (0);
	return (data->data_map.map[y][x]);
}
