#include "minishell.h"

t_parser_result	*parser_result_init(char **arr, bool *quotes)
{
	t_parser_result	*result;

	result = (t_parser_result *)malloc(sizeof(t_parser_result));
	if (!result)
		return (NULL);
	result->command = arr;
	result->quotes = quotes;
	return (result);
}

void	parser_result_free(t_parser_result *result)
{
	free_string_array(result->command);
	free(result->quotes);
	free(result);
}
