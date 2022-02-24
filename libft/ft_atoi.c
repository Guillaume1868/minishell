/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 20:55:08 by gaubert           #+#    #+#             */
/*   Updated: 2021/10/14 16:24:00 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static const char	*ft_remove_spaces(char const *str)
{
	int	exit;

	exit = 0;
	while (exit == 0 && *str != '\0')
	{
		if (*str == '\t' || *str == '\v' || *str == '\r' || *str == '\n')
			str++;
		else if (*str == '\f' || *str == ' ')
			str++;
		else
			exit = 1;
	}
	return (str);
}

static const char	*ft_detect_minus(char const *str, int *minus_count)
{
	while (*str != '\0')
	{
		if (*str == '-')
		{
			*minus_count += 1;
			return (++str);
		}
		else if (*str == '+')
			return (++str);
		return (str);
	}
	return (str);
}

static void	ft_grab_int(const char *str, int *result)
{
	if (*str <= '9' && *str >= '0')
	{
		*result *= 10;
		*result += *str - '0';
		str++;
		ft_grab_int(str, result);
	}
}

int	ft_atoi(const char *str)
{
	int			minus_count;
	const char	*str_clean;
	int			result;

	result = 0;
	minus_count = 0;
	str_clean = ft_detect_minus(ft_remove_spaces(str), &minus_count);
	ft_grab_int(str_clean, &result);
	if (minus_count % 2 == 1)
		result *= -1;
	return (result);
}
