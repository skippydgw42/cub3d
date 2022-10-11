/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:46:24 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/11 13:46:40 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_rgb(unsigned char red, unsigned char green, unsigned char blue)
{
	return ((red * 256 * 256) + (green * 256) + blue);
}
