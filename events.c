/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:48:34 by oladams           #+#    #+#             */
/*   Updated: 2023/07/22 21:34:07 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_in(double x, double y, t_fract *f, double zoom_factor)
{
	double	x_shrink;
	double	y_shrink;

	x_shrink = zoom_factor * (f->x_end - f->x_start);
	y_shrink = zoom_factor * (f->y_end - f->y_start);
	f->x_start += x_shrink * x / WIN_WIDTH;
	f->x_end -= x_shrink * (1 - x / WIN_WIDTH);
	f->y_start += y_shrink * y / WIN_HEIGHT;
	f->y_end -= y_shrink * (1 - y / WIN_HEIGHT);
}

void	zoom_out(double x, double y, t_fract *f, double zoom_factor)
{
	double	x_expand;
	double	y_expand;

	x_expand = zoom_factor * (f->x_end - f->x_start);
	y_expand = zoom_factor * (f->y_end - f->y_start);
	f->x_start -= x_expand * x / WIN_WIDTH;
	f->x_end += x_expand * (1 - x / WIN_WIDTH);
	f->y_start -= y_expand * y / WIN_HEIGHT;
	f->y_end += y_expand * (1 - y / WIN_HEIGHT);
}

int	deal_mouse(int button, int x, int y, t_fract *f)
{
	if (button == 3)
		zoom_in(x, y, f, 0.8);
	if (button == 4)
		zoom_in(x, y, f, 0.09);
	else if (button == 5)
		zoom_out(x, y, f, 0.11);
	draw_fractal (f);
	return (0);
}

int	deal_key(int key, t_fract *f)
{
	if (key == ESC)
	{
		mlx_destroy_window(f->mlx_ptr, f->win_ptr);
		end_program (f);
	}
	else if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
		move_frame(f, key);
	else if (key == ENTER)
		zoom_in(WIN_WIDTH / 2, WIN_HEIGHT / 2, f, 0.036);
	else if (key == DEL)
		zoom_out(WIN_WIDTH / 2, WIN_HEIGHT / 2, f, 0.044);
	else if (key == PLUS)
		f->max_iter += 2 * (int)(log2(f->max_iter));
	else if (key == MINUS)
		f->max_iter -= (int)(log(f->max_iter));
	else if (key == SPACE)
		set_start_frame_values(f);
	else if (key == S)
		f->smooth *= -1;
	else if (key == ONE || key == TWO)
		change_colour_scheme(f, key);
	else
		return (key);
	draw_fractal (f);
	return (key);
}

int	end_program(t_fract *f)
{
	(void)f;
	exit(0);
	return (0);
}
