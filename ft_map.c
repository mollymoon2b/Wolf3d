/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 09:52:27 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/02 13:38:04 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		size_word(char *s, char c)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		res++;
	}
	return (res);
}

void	put_int_in_tab(int nb_w, char c, int *tab, char *s)
{
	int	i;
	int	j;
	int	size;

	size = 0;
	i = 0;
	j = 0;
	while (s[i] != '\0' && j < nb_w)
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1] != '\0') ||
			(s[0] != c && i == 0))
		{
			if (s[i] == c)
				i++;
			size = size_word(&s[i], c);
			tab[j] = ft_atoi(ft_strsub(s, i, size));
			j++;
		}
		i++;
	}
}

int		*ft_strsplitint(char const *s, char c)
{
	int	*tab;
	int	nb_w;
	int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	nb_w = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1] != '\0') ||
			(s[0] != c && i == 0))
			nb_w++;
		i++;
	}
	tab = (int *)malloc(sizeof(int) * nb_w);
	if (tab)
		put_int_in_tab(nb_w, c, tab, (char*)s);
	else
		return (NULL);
	return (tab);
}

void	init_map(t_env *e)
{
	int		fd;
	char	*buff;
	int		i;

	i = 0;
	buff = NULL;
	e->world_map = (int**)malloc(sizeof(int*) * MAP_HEIGHT);
	fd = open("./map.txt", O_RDONLY);
	if (fd == -1)
		ft_error("Map mot found.");
	while (get_next_line(fd, &buff) == 1)
	{
		e->world_map[i] = ft_strsplitint(buff, ' ');
		free(buff);
		i++;
	}
	close (fd);
}
