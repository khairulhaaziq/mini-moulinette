// ALLOWED_FUNCTIONS: malloc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_btree.h"
#include "../../../../ex00/btree_create_node.c"
#include "../../../utils/constants.h"

int test1(void);

int main(void)
{
	if (test1() != 0)
		return (-1);
	return (0);
}

int test1(void)
{
	int value = 42;
	t_btree *node = btree_create_node(&value);
	int ok = 1;

	if (!node)
		ok = 0;
	else
	{
		if (node->item != &value)
			ok = 0;
		if (node->left != NULL)
			ok = 0;
		if (node->right != NULL)
			ok = 0;
	}
	if (!ok)
		printf("    " RED "[1] btree_create_node() did not build a valid node (item, left and right set correctly)\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] btree_create_node() built a valid node with item, left and right set correctly\n" DEFAULT);
	if (node)
		free(node);
	return (ok ? 0 : -1);
}
