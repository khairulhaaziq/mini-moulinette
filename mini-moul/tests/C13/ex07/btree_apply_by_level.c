// ALLOWED_FUNCTIONS: malloc, free
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_btree.h"
#include "../../../../ex07/btree_apply_by_level.c"
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

static int g_values[16];
static int g_levels[16];
static int g_first[16];
static int g_count;

static void moul_record(void *item, int current_level, int is_first_elem)
{
	if (g_count < 16)
	{
		g_values[g_count] = *(int *)item;
		g_levels[g_count] = current_level;
		g_first[g_count] = is_first_elem;
	}
	g_count++;
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
	int expected_values[] = {4, 2, 6, 1, 3, 5, 7};
	int expected_levels[] = {0, 1, 1, 2, 2, 2, 2};
	int expected_first[] = {1, 1, 0, 1, 0, 0, 0};
	int i;
	int ok;

	g_count = 0;
	btree_apply_by_level(root, &moul_record);

	ok = (g_count == 7);
	for (i = 0; ok && i < 7; i++)
	{
		if (g_values[i] != expected_values[i])
			ok = 0;
		if (g_levels[i] != expected_levels[i])
			ok = 0;
		if ((g_first[i] != 0) != (expected_first[i] != 0))
			ok = 0;
	}
	if (!ok)
		printf("    " RED "[1] btree_apply_by_level() did not visit nodes level by level with the correct level/is_first flags\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] btree_apply_by_level() visited nodes level by level with the correct level/is_first flags\n" DEFAULT);
	moul_free_tree(root);
	return (ok ? 0 : -1);
}
