/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 22:15:12 by mshvets           #+#    #+#             */
/*   Updated: 2019/03/09 22:15:14 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

void	ft_startpoint_x(t_point **all, int key)
{
	int	sign;

	if (key == 125)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window((*all)->mlx_ptr, (*all)->win_ptr);
	(*all)->start_y = (*all)->start_y + sign * (*all)->c_size;
	ft_draw(all);
}

void	ft_startpoint_y(t_point **all, int key)
{
	int	sign;

	if (key == 124)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window((*all)->mlx_ptr, (*all)->win_ptr);
	(*all)->start_x = (*all)->start_x + sign * (*all)->c_size;
	ft_draw(all);
}

void	ft_z(t_point **all, int key)
{
	int	sign;

	if (key == 6)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window((*all)->mlx_ptr, (*all)->win_ptr);
	(*all)->z_size = (*all)->z_size + sign * 5;
	if ((*all)->z_size < 0)
		(*all)->z_size = 0;
	ft_draw(all);
}

void	ft_case(t_point **all, int key)
{
	int	sign;

	if (key == 69)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window((*all)->mlx_ptr, (*all)->win_ptr);
	(*all)->c_size = (*all)->c_size + sign * 5;
	if ((*all)->c_size < 0)
		(*all)->c_size = 0;
	ft_draw(all);
}

void	ft_color(t_point **all)
{
	mlx_clear_window((*all)->mlx_ptr, (*all)->win_ptr);
	(*all)->color_pos = ((*all)->color_pos + 1) % 8;
	ft_draw(all);
}
