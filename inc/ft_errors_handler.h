/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_handler.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhmichi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 17:43:26 by mhmichi           #+#    #+#             */
/*   Updated: 2026/09/02 12:39:54 by mhmichi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERRORS_HANDLER_H
# define FT_ERRORS_HANDLER_H

void	free_double_pointer(void **p, unsigned int elements, unsigned int element_size);
void	ft_puterror(char *msg);
void	ft_putnotice(char *msg);
#endif
