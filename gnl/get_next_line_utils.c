/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:11:12 by adelaloy          #+#    #+#             */
/*   Updated: 2023/11/06 10:28:59 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	i;
	size_t	ss_len;

	i = 0;
	if (!s)
		return (NULL);
	ss_len = ft_strlen(s) - start;
	if (len > ss_len)
		len = ss_len;
	ss = (char *)malloc(len + 1);
	if (!ss)
		return (NULL);
	while (i < len)
	{
		ss[i] = s[start];
		i++;
		start++;
	}
	ss[i] = '\0';
	return (ss);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	while (s1[i])
		dst[j++] = s1[i++];
	i = 0;
	while (s2[i])
		dst[j++] = s2[i++];
	dst[j] = '\0';
	free(s1);
	return (dst);
}

char	*ft_strdup(char *src)
{
	char	*dst;
	int		i;

	dst = malloc(ft_strlen(src) + 1);
	if (!dst)
		return ((void *)0);
	i = 0;
	while (src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}
