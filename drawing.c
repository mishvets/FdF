/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 13:26:51 by mshvets           #+#    #+#             */
/*   Updated: 2019/01/18 13:27:30 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line	*ft_drawline_init(t_xyz p1, t_xyz p2, t_point *all)
{
	t_line *line;

	if (!(line = (t_line *)malloc(sizeof(t_line))))
		exit (1);
	line->x1 = all->start_x + (int)p1.x;
	line->x2 = all->start_x + (int)p2.x;
	line->y1 = all->start_y + (int)p1.y;
	line->y2 = all->start_y + (int)p2.y;
	line->deltaX = abs((line->x2 - line->x1));
	line->deltaY = abs((line->y2 - line->y1));
	line->signX = line->x1 < line->x2 ? 1 : -1;
	line->signY = line->y1 < line->y2 ? 1 : -1;
	line->error = line->deltaX - line->deltaY;
	return (line);
}

void	ft_drawline(t_xyz p1, t_xyz p2, t_point *all)
{
	t_line *line;

	line = ft_drawline_init(p1, p2, all);
	mlx_pixel_put(all->mlx_ptr, all->win_ptr, line->x2, line->y2,
			all->color[all->color_pos]);
	while(line->x1 != line->x2 || line->y1 != line->y2)
	{
		mlx_pixel_put(all->mlx_ptr, all->win_ptr, line->x1, line->y1,
				all->color[all->color_pos]);
		line->error2 = line->error * 2;
		if(line->error2 > -line->deltaY)
		{
			line->error -= line->deltaY;
			line->x1 += line->signX;
		}
		if(line->error2 < line->deltaX)
		{
			line->error += line->deltaX;
			line->y1 += line->signY;
		}
	}
	free(line);
}

t_xyz	ft_coordinates(t_data *crawler, int x, t_point *all, t_xyz p2)
{
	p2.x = (x - all->nX/2) * all->base_m[0][0] * all->c_size
			+ (crawler->y - all->nY/2) * all->base_m[1][0] * all->c_size
			+ crawler->row[x] * all->base_m[2][0] * all->z_size;
	p2.y = (x - all->nX/2) * all->base_m[0][1] * all->c_size
			+ (crawler->y - all->nY/2) * all->base_m[1][1] * all->c_size
			+ crawler->row[x] * all->base_m[2][1] * all->z_size;
	p2.z = (x - all->nX/2) * all->base_m[0][2] * all->c_size
			+ (crawler->y - all->nY/2) * all->base_m[1][2] * all->c_size
			+ crawler->row[x] * all->base_m[2][2] * all->z_size;
	return (p2);
}

int 	ft_drawmap(t_point **all)
{
	int		j;
	t_data	*crawler;
	t_xyz	*line;
	t_xyz	p2;

	if (!(line = (t_xyz *)malloc(sizeof(*line) * (*all)->nX)))
		return (0);
	crawler = (*all)->map;
	while (crawler)
	{
		j = 0;
		while (j < (*all)->nX)
		{
			p2 = ft_coordinates(crawler, j, *all, p2);
			if (j)
				ft_drawline(line[j - 1], p2, *all);
			if (crawler->y)
				ft_drawline(line[j], p2, *all);
			line[j] = p2;
			++j;
		}
		crawler = crawler->next;
	}
	free(line);
	return (1);
}

void	ft_draw(t_point **all)
{
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 0,
			(*all)->color[(*all)->color_pos], "Rotate:");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 20,
				   (*all)->color[(*all)->color_pos], "    X - 7 or 4;");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 40,
				   (*all)->color[(*all)->color_pos], "    Y - 8 or 5;");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 60,
				   (*all)->color[(*all)->color_pos], "    Z - 9 or 6.");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 80,
				   (*all)->color[(*all)->color_pos], "Color - c");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 100,
				   (*all)->color[(*all)->color_pos], "Scale: ");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 120,
				   (*all)->color[(*all)->color_pos], "    Z - z or x;");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 140,
				   (*all)->color[(*all)->color_pos], " case - + or -;");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 160,
				   (*all)->color[(*all)->color_pos],
				   "Move:  Up, Down, Left, Right;");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 180,
				   (*all)->color[(*all)->color_pos], "Clear - p;");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 200,
				   (*all)->color[(*all)->color_pos], "Exit  - ESC.");
	ft_drawmap(all);
}
