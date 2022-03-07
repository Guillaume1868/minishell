#include "minishell.h"

int		is_seperator(char c)
{
	if (c == ' ' | c == '<' | c == '>')
		return (1);
	return (0);
}

char *malloc_word(char *start, char *end)
{
	char	quote;
	int		i;
	char	*res;
	int		count;

	//printf("\nmaking command:\n");
	quote = '0';
	i = -1;
	count = 0;
	while (start + ++i <= end)
	{
		quotes(*(start + i), &quote);
		if (*(start + i) != quote)
			count++;
		//printf("%c", *(start + i));
	}
	res = ft_calloc(sizeof(char), count + 1);
	i = -1;
	count = -1;
	quote = '0';
	while (start + ++i <= end)
	{
		//quotes(*(start + i), &quote);
		if (quotes(*(start + i), &quote) && *(start + i) != quote)
			res[++count] = start[i];
	}
	//printf("\n------------\n");
	printf("res=|%s|\n", res);
	return (res);
}

int	quotes(char c, char *quote)
{
	if (*quote == '0' && (c == '\'' || c == '\"'))
		*quote = c;
	else if (*quote != '0' && c == *quote)
	{
		*quote = '0';
		return(0);
	}
	return (1);
}