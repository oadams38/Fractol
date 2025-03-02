/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:01:28 by oladams           #+#    #+#             */
/*   Updated: 2023/07/11 18:19:14 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_colour(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	colour_hippie(t_fract *f, double n)
{
	int	colour;

	colour = get_colour(0,
			255 * fabs(sin(f->r_sin_ratio * n)),
			255 * fabs(sin(f->v_sin_ratio * n)),
			255 * fabs(sin(f->b_sin_ratio * n)));
	return (colour);
}

int	colour_electric(t_fract *f, double n)
{
	int	colour;

	colour = get_colour(0,
			255 * fabs(sin((double)(f->r_sin_ratio) / 150 * n)),
			255 * fabs(sin((double)(f->v_sin_ratio) / 150 * n)),
			255 * fabs(sin((double)(f->b_sin_ratio) / 150 * n)));
	return (colour);
}

void	change_colour_scheme(t_fract *f, int key)
{
	f->r_sin_ratio = pseudo_random(1, 20, f);
	f->v_sin_ratio = pseudo_random(1, 20, f);
	f->b_sin_ratio = pseudo_random(1, 20, f);
	if (key == ONE)
		f->colourizer = colour_electric;
	else
		f->colourizer = colour_hippie;
	draw_fractal(f);
}
