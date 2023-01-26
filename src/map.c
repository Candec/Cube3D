/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:08:49 by tpereira          #+#    #+#             */
/*   Updated: 2023/01/26 16:13:18 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_map(t_mlx *cube)
{
	int	x;
	int	y;

	y = 0;
	while (y != (int)cube->map.height)
	{
		x = 0;
		while (cube->map.map[y][x] != '\0' && x != (int)cube->map.width)
		{
			printf("%c", cube->map.map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	draw_map_2D(t_mlx *cube)
{
	int	x;
	int	y;
	int xo;
	int yo;

	y = 0;
	blackout(cube);
	print_map(cube);
	while (y != (int)cube->map.height)
	{
		yo = y * 32;
		x = 0;
		while (cube->map.map[y][x] != '\0' && x != (int)cube->map.width)
		{
			xo = x * 32;
			if (cube->map.map[y][x] == '1')
				draw_square(cube, (xo), (yo), 30, WHITE);
			else if (cube->map.map[y][x] == '0')
				draw_square(cube, (xo), (yo), 30, BLUE);
			else if (ft_strchr("NSEW", cube->map.map[y][x]))
				draw_square(cube, (xo), (yo), 30, BLUE);
			else
				draw_square(cube, (xo), (yo), 30, GREEN);
			x++;
		}
		y++;
	}
	draw_player_2D(cube);
}

void	img_pix_put(t_mlx *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->frame.bpp - 8;
    pixel = img->frame.img + (y * img->frame.size_l + x * (img->frame.bpp / 8));
	while (i >= 0)
	{
		if (img->frame.endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->frame.bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void mlx_line_to(t_mlx *mlx,int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;
    while (1)
    {
        img_pix_put(mlx, x1, y1, color);
        if (x1 == x2 && y1 == y2) 
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void	draw_player_2D(t_mlx *cube)
{
	int	x;
	int	y;
	double xo;
	double yo;

	y = 0;
	while (y != (int)cube->map.height)
	{
		x = 0;
		yo = cube->player.posy * 32;
		while (x != (int)cube->map.width)
		{
			xo = cube->player.posx * 32;
			if (cube->map.map[y][x] == '0')
			{
				printf("x: %d, y: %d, cos(angle): %f, sin(angle): %f, angle: %f\n", x, y, cos(cube->player.angle), sin(cube->player.angle), cube->player.angle);
				draw_square(cube, xo + 0.5, yo + 0.5, 8, YELLOW);
				printf("dirx = %f, diry = %f\n", cube->player.dirx, cube->player.diry);
				draw_square(cube, xo + 4 + cube->player.dirx, yo + 4 + cube->player.diry, 16, RED);
				draw_line(cube, xo, yo, 49.914742, -2.918673, RED);
				draw_line(cube, xo + 4, yo + 4, xo + 4 + cube->player.dirx, yo + 4 + cube->player.diry, RED);
				//  mlx_line_to(cube, xo + 4, yo + 4, cube->player.dirx, cube->player.diry, RED);
				//   draw_line(cube, xo + 4, yo + 4, xo + 4 + cube->player.dirx, yo + 4 + cube->player.diry, RED);
				//    draw_line(cube, xo + 4 + cube->player.dirx, yo + 4 + cube->player.diry, xo + 4, yo + 4, RED);
				//    draw_line(cube, xo + 4, yo + 4, xo + 4 + cube->player.dirx * 50, yo + 4 + cube->player.diry * 50, RED);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->frame.img, 0, 0);
}
