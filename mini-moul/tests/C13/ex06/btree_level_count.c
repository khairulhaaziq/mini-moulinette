// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_btree.h"
#include "../../../../ex06/btree_level_count.c"
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
int test2(void);
int test3(void);
int test4(void);

int main(void)
{
	int error = 0;

	if (test1() != 0)
		error -= 1;
	if (test2() != 0)
		error -= 1;
	if (test3() != 0)
		error -= 1;
	if (test4() != 0)
		error -= 1;
	return (error);
}

int test1(void)
{
	int result = btree_level_count(NULL);
	int ok = (result == 0);

	if (!ok)
		printf("    " RED "[1] btree_level_count(NULL) Expected 0, got %d\n" DEFAULT, result);
	else
		printf("  " GREEN CHECKMARK GREY " [1] btree_level_count(NULL) Expected 0, got %d\n" DEFAULT, result);
	return (ok ? 0 : -1);
}

int test2(void)
{
	t_btree *root = moul_new_node(1);
	int result = btree_level_count(root);
	int ok = (result == 1);

	if (!ok)
		printf("    " RED "[2] btree_level_count() on a single node Expected 1, got %d\n" DEFAULT, result);
	else
		printf("  " GREEN CHECKMARK GREY " [2] btree_level_count() on a single node Expected 1, got %d\n" DEFAULT, result);
	moul_free_tree(root);
	return (ok ? 0 : -1);
}

int test3(void)
{
	t_btree *root = moul_new_node(4);
	int result;
	int ok;

	root->left = moul_new_node(2);
	root->right = moul_new_node(6);
	root->left->left = moul_new_node(1);
	root->left->right = moul_new_node(3);
	root->right->left = moul_new_node(5);
	root->right->right = moul_new_node(7);
	result = btree_level_count(root);
	ok = (result == 3);
	if (!ok)
		printf("    " RED "[3] btree_level_count() on a balanced 3-level tree Expected 3, got %d\n" DEFAULT, result);
	else
		printf("  " GREEN CHECKMARK GREY " [3] btree_level_count() on a balanced 3-level tree Expected 3, got %d\n" DEFAULT, result);
	moul_free_tree(root);
	return (ok ? 0 : -1);
}

int test4(void)
{
	/* a lopsided tree: the deepest branch has 4 levels, the shallow one 2 */
	t_btree *root = moul_new_node(1);
	int result;
	int ok;

	root->right = moul_new_node(2);
	root->left = moul_new_node(3);
	root->left->left = moul_new_node(4);
	root->left->left->left = moul_new_node(5);
	result = btree_level_count(root);
	ok = (result == 4);
	if (!ok)
		printf("    " RED "[4] btree_level_count() on a lopsided tree Expected 4 (largest branch), got %d\n" DEFAULT, result);
	else
		printf("  " GREEN CHECKMARK GREY " [4] btree_level_count() on a lopsided tree Expected 4 (largest branch), got %d\n" DEFAULT, result);
	moul_free_tree(root);
	return (ok ? 0 : -1);
}
