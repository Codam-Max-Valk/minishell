#include "tokens.h"
#include "minishell.h"

void	info_addback(t_info **info, t_info *new)
{
	t_info	*tmp_nod;

	if (!*info)
	{
		*info = new;
		return ;
	}
	tmp_nod = *info;
	while (tmp_nod->next)
		tmp_nod = tmp_nod->next;
	tmp_nod->next = new;
}