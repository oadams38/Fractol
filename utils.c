/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:08:10 by oladams           #+#    #+#             */
/*   Updated: 2023/04/08 17:45:00 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		value_s1;
	int		value_s2;

	if (n == 0)
		return (0);
	else
	{
		i = 0;
		while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
			i++;
		value_s1 = (int) s1[i];
		value_s2 = (int) s2[i];
		if (value_s1 < 0)
			value_s1 += 256;
		if (value_s2 < 0)
			value_s2 += 256;
		return (value_s1 - value_s2);
	}
}

static void	init_atof(char *s, int *i, double *sign)
{
	*i = 0;
	while ((s[*i] >= 9 && s[*i] <= 13) || s[*i] == 32)
		*i = *i + 1;
	*sign = 1;
	while (s[*i] == '-' || s[*i] == '+')
	{
		if (s[*i] == '-')
			*sign = *sign * -1;
		*i = *i + 1;
	}
}

double	ft_atof(char *s)
{
	double	res;
	int		i;
	int		j;
	double	sign;

	init_atof(s, &i, &sign);
	res = 0;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	if (!s[i] || (s[i] != '.' && s[i] != ','))
		return (res);
	i++;
	j = 10;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		res += (double)((s[i] - '0')) / j;
		j *= 10;
		i++;
	}
	return (res * sign);
}

int	pseudo_random(int min, int max, t_fract *f)
{
	int	tmp;
	int	a;
	int	m;
	int	rand;

	a = 16807;
	m = 2147483647;
	if (min > max)
	{
		tmp = min;
		min = max;
		max = tmp;
	}
	if (min == max)
		return (max);
	f->seed = (a * f->seed) % m;
	rand = f->seed % (max - min) + min;
	return (rand);
}
