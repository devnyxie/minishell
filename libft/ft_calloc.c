/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:06:26 by tafanasi          #+#    #+#             */
/*   Updated: 2024/12/16 17:07:32 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// SIZE_MAX is the maximum value representable by an object of type size_t.
void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*arr;
	char			*ptr;
	size_t			i;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
	{
		return (NULL);
	}
	arr = malloc(nmemb * size);
	if (arr == NULL)
	{
		return (NULL);
	}
	ptr = (char *)arr;
	i = 0;
	while (i < (nmemb * size))
	{
		ptr[i] = 0;
		i++;
	}
	return (arr);
}

// int main(void){
// 	int *arr = (int *)ft_calloc(5, sizeof(int));
// 	if(arr == NULL){
// 		printf("Error - not allocated");
// 		return(0);
// 	}
//     	for (int i = 0; i < 5; i++) {
//         	printf("%d\n", arr[i]);  // Safely access each element
//     	}

//     	free(arr);  // Free allocated memory
// 	return(0);
// }
