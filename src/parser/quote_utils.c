#include "minishell.h"
#include <stdbool.h>

/**
 * @param s: string
 *
 * @return 0 no quotes, 1 single quotes, 2 double quotes
 */
int	has_quotes(char *s)
{
	size_t	s_len;

	if (!s)
		return (false);
	s_len = ft_strlen(s);
	if (s[0] == '\'' && s[s_len - 1] == '\'')
		return (1);
	if (s[0] == '"' && s[s_len - 1] == '"')
		return (2);
	return (0);
}

char	*trim_quotes(char *s)
{
	char	*out;
	char	quote;

	if (!s)
		return (NULL);
	if (has_quotes(s) == 0)
		return (s);
	quote = s[0];
	out = ft_strtrim(s, &quote);
	if (!out)
		return (NULL);
	free(s);
	return (out);
}
