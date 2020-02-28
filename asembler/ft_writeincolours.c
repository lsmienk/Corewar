/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_writeincolours.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ihering- <ihering-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 10:51:20 by ihering-       #+#    #+#                */
/*   Updated: 2020/02/06 10:52:34 by ihering-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	*light_shades(char *colour)
{
	if (!ft_strcmp(colour, "grey"))
		colour = "90";
	if (!ft_strcmp(colour, "light green"))
		colour = "92";
	if (!ft_strcmp(colour, "light yellow"))
		colour = "93";
	if (!ft_strcmp(colour, "light blue"))
		colour = "94";
	if (!ft_strcmp(colour, "light magenta"))
		colour = "95";
	if (!ft_strcmp(colour, "light cyan"))
		colour = "96";
	return (colour);
}

void		ft_writeincolours(char *str, char *colour)
{
	ft_putstr("\033[");
	if (!ft_strcmp(colour, "black"))
		colour = "30";
	if (!ft_strcmp(colour, "red"))
		colour = "31";
	if (!ft_strcmp(colour, "green"))
		colour = "32";
	if (!ft_strcmp(colour, "orange"))
		colour = "33";
	if (!ft_strcmp(colour, "blue"))
		colour = "34";
	if (!ft_strcmp(colour, "magenta"))
		colour = "35";
	if (!ft_strcmp(colour, "cyan"))
		colour = "36";
	else
		colour = light_shades(colour);
	ft_putstr(colour);
	ft_putchar('m');
	ft_putstr(str);
	ft_putstr("\033[0m");
}
