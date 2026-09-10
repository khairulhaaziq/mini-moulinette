// ALLOWED_FUNCTIONS: btree_create_node
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_btree.h"
#include "../../../../ex04/btree_insert_data.c"
#include "../../../utils/constants.h"

static int moul_cmp_int(void *a, void *b)
{
	return (*(int *)a - *(int *)b);
}

static int g_walk[16];
static int g_walk_count;

static void moul_infix_walk(t_btree *root)
{
	if (!root)
		return ;
	moul_infix_walk(root->left);
	if (g_walk_count < 16)
		g_walk[g_walk_count] = *(int *)root->item;
	g_walk_count++;
	moul_infix_walk(root->right);
}

static void moul_free_tree(t_btree *root)
{
	if (!root)
		return ;
	moul_free_tree(root->left);
	moul_free_tree(root->right);
	free(root->item);
	free(root);
}

int test1(void);

int main(void)
{
	if (test1() != 0)
		return (-1);
	return (0);
}

int test1(void)
{
	t_btree *root;
	int values[] = {5, 2, 8, 1, 3, 7, 9, 4, 6};
	int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int i;
	int ok;
	int *data;

	root = NULL;
	i = 0;
	while (i < 9)
	{
		data = malloc(sizeof(int));
		*data = values[i];
		btree_insert_data(&root, data, &moul_cmp_int);
		i++;
	}

	g_walk_count = 0;
	moul_infix_walk(root);
	ok = (g_walk_count == 9);
	for (i = 0; ok && i < 9; i++)
	{
		if (g_walk[i] != expected[i])
			ok = 0;
	}
	if (!ok)
		printf("    " RED "[1] btree_insert_data() did not build a correctly ordered binary search tree\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] btree_insert_data() built a correctly ordered binary search tree\n" DEFAULT);
	moul_free_tree(root);
	return (ok ? 0 : -1);
}
