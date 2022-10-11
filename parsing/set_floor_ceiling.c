/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_floor_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:11:06 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/11 15:11:30 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	*ft_set_forc(void)
{
	int	*f_or_c;

	f_or_c = malloc(sizeof(int) * 3);
	f_or_c[0] = -1;
	f_or_c[1] = -1;
	f_or_c[2] = -1;
	return (f_or_c);
}
