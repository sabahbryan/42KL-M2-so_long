/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tf_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:53:01 by bryaloo           #+#    #+#             */
/*   Updated: 2024/04/04 18:16:13 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	safe_malloc(char **token_v, int position, size_t buffer)
{
	token_v[position] = malloc(buffer);
	if (token_v[position] == NULL)
		return (1);
	return (0);
}

int	fill(char **token_v, char const *s, char delimiter)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == delimiter && *s)
			++s;
		while (*s != delimiter && *s)
		{
			++len;
			++s;
		}
		if (len > 0)
		{
			if (safe_malloc(token_v, i, len + 1))
				return (1);
			ft_strlcpy(token_v[i], s - len, len + 1);
			++i;
		}
	}
	return (0);
}

size_t	count_tokens(char const *s, char delimeter)
{
	size_t	tokens;
	int		inside_token;

	tokens = 0;
	inside_token = 0;
	while (*s)
	{
		inside_token = 0;
		while (*s == delimeter && *s)
			++s;
		while (*s != delimeter && *s)
		{
			if (!inside_token)
			{
				++tokens;
				inside_token = 1;
			}
			++s;
		}
	}
	return (tokens);
}

char	**ft_split(char const *s, char c)
{
	size_t	tokens;
	char	**token_v;
	size_t	i;

	i = 0;
	if (NULL == s)
		return (NULL);
	tokens = count_tokens(s, c);
	token_v = malloc((tokens + 1) * sizeof(char *));
	if (NULL == token_v)
		return (NULL);
	token_v[tokens] = NULL;
	if (fill(token_v, s, c))
	{
		while (i < tokens)
		{
			free(token_v[i]);
			i++;
		}
		free(token_v);
		return (NULL);
	}
	return (token_v);
}

/*
	ORIGINAL

int	safe_malloc(char **token_v, int position, size_t buffer)
{
	int	i;

	i = 0;
	token_v[position] = malloc(buffer);
	if (NULL == token_v[position])
	{
		while (i < position)
			free(token_v[i++]);
		free(token_v);
		return (1);
	}
	return (0);
}

int	fill(char **token_v, char const *s, char delimiter)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == delimiter && *s)
			++s;
		while (*s != delimiter && *s)
		{
			++len;
			++s;
		}
		if (len)
		{
			if (safe_malloc(token_v, i, len + 1))
				return (1);
		}
		ft_strlcpy(token_v[i], s - len, len + 1);
		++i;
	}
	return (0);
}

size_t	count_tokens(char const *s, char delimeter)
{
	size_t	tokens;
	int		inside_token;

	tokens = 0;
	inside_token = 0;
	while (*s)
	{
		inside_token = 0;
		while (*s == delimeter && *s)
			++s;
		while (*s != delimeter && *s)
		{
			if (!inside_token)
			{
				++tokens;
				inside_token = 1;
			}
			++s;
		}
	}
	return (tokens);
}

char	**ft_split(char const *s, char c)
{
	size_t	tokens;
	char	**token_v;

	if (NULL == s)
		return (NULL);
	tokens = count_tokens(s, c);
	token_v = malloc((tokens + 1) * sizeof(char *));
	if (NULL == token_v)
		return (NULL);
	token_v[tokens] = NULL;
	if (fill(token_v, s, c))
		return (NULL);
	return (token_v);
}
*/
/*
int	main()
{
	char	*s = "   Hello there, dude!!";
	char	**v = ft_split(s, ' ');

	while (*v)
		printf("s\n, *v++);
}
*/