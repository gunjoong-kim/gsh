/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dic_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:27 by gunjkim           #+#    #+#             */
/*   Updated: 2023/06/02 13:10:59 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dic_bonus.h"

t_dic	*init_dictionary(void)
{
	t_dic	*new_dic;

	new_dic = (t_dic *)xmalloc(sizeof(t_dic));
	new_dic->head = NULL;
	new_dic->size = 0;
	new_dic->return_value = 0;
	return (new_dic);
}

t_dic_element	*new_dic_element(char *key, char *value)
{
	t_dic_element	*new_element;
	char			*key_copy;
	char			*value_copy;

	key_copy = xstrdup(key);
	value_copy = xstrdup(value);
	new_element = (t_dic_element *)xmalloc(sizeof(t_dic_element));
	new_element->key = key_copy;
	new_element->value = value_copy;
	new_element->next = NULL;
	return (new_element);
}

t_dic_element	*add_dic(t_dic *dic, char *key, char *value)
{
	t_dic_element	*new;
	t_dic_element	*cur;
	t_dic_element	*last;
	char			*value_copy;

	cur = dic->head;
	while (cur != NULL)
	{
		if (ft_strequal(cur->key, key))
		{
			value_copy = xstrdup(value);
			free(cur->value);
			cur->value = value_copy;
			return (cur);
		}
		last = cur;
		cur = cur->next;
	}
	new = new_dic_element(key, value);
	if (dic->head == NULL)
		dic->head = new;
	else
		last->next = new;
	dic->size++;
	return (new);
}

void	delete_dic(t_dic *dic, char *key)
{
	t_dic_element	*target;
	t_dic_element	*target_prev;

	target = dic->head;
	target_prev = dic->head;
	while (target != NULL)
	{
		if (ft_strequal(target->key, key))
		{
			if (target == dic->head)
				dic->head = target->next;
			else
				target_prev->next = target->next;
			free(target->key);
			free(target->value);
			free(target);
			dic->size--;
			return ;
		}
		target_prev = target;
		target = target->next;
	}
}

void	clear_dic(t_dic *dic)
{
	t_dic_element	*target;
	t_dic_element	*target_next;

	target = dic->head;
	while (target != NULL)
	{
		target_next = target->next;
		free(target->key);
		free(target->value);
		free(target);
		target = target_next;
	}
	free(dic);
}
