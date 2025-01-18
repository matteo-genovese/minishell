#include "minishell.h"

#define IS_SEPARATOR(x) (x == ' ' || x == '\t' || x == '\n' || x == '\0')

static char	*join_char(char *s, char c)
{
	char	*out;

	out = ft_calloc(ft_strlen(s) + 2, sizeof(char));
	ft_strlcat(out, s, ft_strlen(s) + 1);
	out[ft_strlen(s)] = c;
	return (out);
}

static char	*joinfree(char *s, char *s2)
{
	char	*out;

	out = ft_calloc(ft_strlen(s) + ft_strlen(s2) + 1, sizeof(char));
	ft_strlcat(out, s, ft_strlen(s) + 1);
	ft_strlcat(out, s2, ft_strlen(s) + ft_strlen(s2) + 1);
	free(s);
	return (out);
}

static char	*env_handler(char *s, char *dest, size_t *i, t_tools *tools)
{
	char	*env;
	char	*out;
	size_t	j;
	char	*val;

	j = 0;
	while (s[*i + j] && !IS_SEPARATOR(s[*i + j]))
		j++;
	env = ft_substr(s, *i, j);
	val = get_value_envp(env + 1, tools->envp);
	out = ft_strjoin(dest, val);
	free(env);
	*i += j;
	return (out);
}

char	*preprocessed(char *s, t_tools *tools, int last_exit_code)
{
	char	*out;
	size_t	i;

	i = 0;
	out = ft_strdup("");
	while (s[i])
	{
		if (s[i] != '$')
		{
			out = join_char(out, s[i]);
			i++;
			continue ;
		}
		if (s[i + 1] == '?')
		{
			out = joinfree(out, ft_itoa(last_exit_code));
			i += 2;
			continue ;
		}
		out = env_handler(s, out, &i, tools);
	}
	return (out);
}

char	**stringarr_from_list(struct s_list *l)
{
	char **out;
	size_t i;

	if (!l)
		return (NULL);
	out = ft_calloc(ft_lstsize(l) + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	while (l)
	{
		out[i] = l->content;
		l = l->next;
		i++;
	}
	out[i] = NULL;
	ft_lstclear(&l, NULL);
	return (out);
}