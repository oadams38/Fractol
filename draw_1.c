/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:12:52 by oladams           #+#    #+#             */
/*   Updated: 2023/07/22 21:30:33 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move_frame(t_fract *f, int key)
{
	double	shift;

	if (key == UP || key == DOWN)
	{
		shift = (f->y_end - f->y_start) * MOVE_RATE;
		if (key == UP)
			shift *= -1;
		f->y_start += shift;
		f->y_end += shift;
	}
	if (key == LEFT || key == RIGHT)
	{
		shift = (f->x_end - f->x_start) * MOVE_RATE;
		if (key == LEFT)
			shift *= -1;
		f->x_start += shift;
		f->x_end += shift;
	}
}

double	smoother(double zx, double zy)
{
	double	var;

	var = 1 - log(log2(sqrt(zx * zx + zy * zy)));
	if (!isnan(var))
		return (var);
	return (0);
}

double	iterate(t_fract *f, double n, double zx, double zy)
{
	double	dx;
	double	dy;
	double	zx_tmp;
	double	zy_tmp;

	dx = zx;
	dy = zy;
	if (f->type == 'j')
	{
		dx = f->c_real;
		dy = f->c_imag;
	}
	while ((zx * zx + zy * zy) < 4 && n < f->max_iter)
	{
		zx_tmp = zx * zx - zy * zy + dx;
		zy_tmp = 2 * zx * zy + dy;
		zx = zx_tmp;
		zy = zy_tmp;
		n++;
	}
	if (f->smooth == 1)
		return (n + smoother(zx, zy));
	return (n);
}

void	colorize_pixel(t_fract *f, int x, int y, double n)
{
	int	*img_addr;
	int	pix;
	int	colour;

	img_addr = (int *) f->img_addr;
	pix = (y * WIN_WIDTH) + x;
	if ((int)n >= f->max_iter)
		colour = get_colour(0, 0, 0, 0);
	else
		colour = f->colourizer(f, n);
	img_addr[pix] = colour;
}

void	draw_fractal(t_fract *f)
{
	int		y;
	int		x;
	double	n;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			n = iterate(f, 0,
					f->x_start
					+ ((double)x / WIN_WIDTH) * (f->x_end - f->x_start),
					f->y_start
					+ ((double)y / WIN_HEIGHT) * (f->y_end - f->y_start));
			colorize_pixel(f, x, y, n);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img_id, 0, 0);
}
