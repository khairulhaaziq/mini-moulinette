// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_btree.h"
#include "../../../../ex05/btree_search_item.c"
#include "../../../utils/constants.h"

static t_btree *moul_new_node(int value, int *stored)
{
	t_btree *node;

	*stored = value;
	node = malloc(sizeof(t_btree));
	node->item = stored;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static int moul_cmp_int(void *a, void *b)
{
	return (*(int *)a - *(int *)b);
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
	int *v4 = malloc(sizeof(int));
	int *v2 = malloc(sizeof(int));
	int *v6 = malloc(sizeof(int));
	int *v1 = malloc(sizeof(int));
	int *v3 = malloc(sizeof(int));
	int *v5 = malloc(sizeof(int));
	int *v7 = malloc(sizeof(int));
	t_btree *root = moul_new_node(4, v4);
	int search_for;
	void *result;
	int ok;

	root->left = moul_new_node(2, v2);
	root->right = moul_new_node(6, v6);
	root->left->left = moul_new_node(1, v1);
	root->left->right = moul_new_node(3, v3);
	root->right->left = moul_new_node(5, v5);
	root->right->right = moul_new_node(7, v7);

	ok = 1;
	search_for = 5;
	result = btree_search_item(root, &search_for, &moul_cmp_int);
	if (result != v5)
		ok = 0;

	search_for = 42;
	result = btree_search_item(root, &search_for, &moul_cmp_int);
	if (result != NULL)
		ok = 0;

	if (!ok)
		printf("    " RED "[1] btree_search_item() did not return the correct item, or NULL when not found\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] btree_search_item() returned the correct item, and NULL when not found\n" DEFAULT);
	moul_free_tree(root);
	return (ok ? 0 : -1);
}
