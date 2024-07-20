/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:41:56 by mde-souz          #+#    #+#             */
/*   Updated: 2024/04/29 18:47:00 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Adds the node ’new’ at the end of the list.
 * @param lst: The address of a pointer to the first link of a list.
 * @param new: The address of a pointer to the node to be added to the list.
 */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		ft_lstlast(*lst)->next = new;
	}
}
/* #include <stdio.h>
void ft_printlst(t_list *head)
{
	t_list *temp = head;
	
	if (!head)
		printf("Lista inexistente\n");
	else
	{
	while (temp != NULL)
	{
		printf("%d ", *(int *)temp->content);
		temp = temp->next;
	}
	printf("\n");
	}
}

int	*ft_seq_int_arr(int rand_num)
{
	int	*p_num;

	p_num = (int *)malloc(sizeof(int) * rand_num);
	if(!p_num)
		return (NULL);
	while(rand_num--)
		p_num[rand_num] = rand_num;
	return (p_num);
}
int	main(void)
{
	int	num = 4;
	int	*p_num = ft_seq_int_arr(num);//gera um array sequencial 0,1,2...
	t_list	*head;
	int	last_int = 99;
	
	head = NULL;
 	while (num--)//lista array sequencial comecando pelo primeiro, o zero.
		ft_lstadd_back(&head,ft_lstnew(p_num++));
	ft_printlst(head);
	printf("Adicionando mais um numero a lista: %d\n", last_int);
	ft_lstadd_back(&head,ft_lstnew(&last_int));
	printf("Chmando funcao ft_lstlast\n");
	printf("O ultimo elemento é %d\n",*(int *)ft_lstlast(head)->content);
	return (0);
} */