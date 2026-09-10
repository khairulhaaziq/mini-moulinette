// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_btree.h"
#include "../../../../ex01/btree_apply_prefix.c"
#include "../../../utils/constants.h"

static t_btree *moul_new_node(int value)
{
	t_btree *node;
	int *data;

	data = malloc(sizeof(int));
	*data = value;
	node = malloc(sizeof(t_btree));
	node->item = data;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static t_btree *moul_build_tree(void)
{
	t_btree *root = moul_new_node(4);

	root->left = moul_new_node(2);
	root->right = moul_new_node(6);
	root->left->left = moul_new_node(1);
	root->left->right = moul_new_node(3);
	root->right->left = moul_new_node(5);
	root->right->right = moul_new_node(7);
	return (root);
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

static int g_calls[16];
static int g_call_count;

static void moul_record(void *item)
{
	if (g_call_count < 16)
		g_calls[g_call_count] = *(int *)item;
	g_call_count++;
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
	t_btree *root = moul_build_tree();
	int expected[] = {4, 2, 1, 3, 6, 5, 7};
	int i;
	int ok;

	g_call_count = 0;
	btree_apply_prefix(root, &moul_record);

	ok = (g_call_count == 7);
	for (i = 0; ok && i < 7; i++)
	{
		if (g_calls[i] != expected[i])
			ok = 0;
	}
	if (!ok)
		printf("    " RED "[1] btree_apply_prefix() did not visit nodes in prefix order (root, left, right)\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] btree_apply_prefix() visited nodes in prefix order (root, left, right)\n" DEFAULT);
	moul_free_tree(root);
	return (ok ? 0 : -1);
}
