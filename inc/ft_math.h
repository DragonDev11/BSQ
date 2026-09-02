/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhmichi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 12:14:29 by mhmichi           #+#    #+#             */
/*   Updated: 2026/09/02 13:28:10 by mhmichi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H
# define ABS(x) (x >= 0 ? x : -x)
int	ft_atoi(char *str);
int	get_start_index(char *str, int *sign);
int	get_num_len(char *str, int start);
void	ft_putnbr(int nb);
#endif
