#include "minishell.h"
#include "libft.h"

char	*ft_replaceall(const char *str, char c)
{
	char	*nstr;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != c)
			len++;
		i++;
	}
	i = 0;
	j = 0;
	nstr = ft_calloc(len + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] != c)
		{
			nstr[j] = str[i];
			j++;
		}
		i++;
	}
	return (nstr);
}
