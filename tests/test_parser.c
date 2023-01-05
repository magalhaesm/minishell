#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "parser.h"

Test(parser, empty)
{
	t_scanner	scanner;
	t_node		*root;

	scanner = init_scanner("");
	root = parse(&scanner);
	cr_assert(eq(root, NULL));
	free_tree(root);
}

Test(parser, command)
{
	t_scanner	scanner;
	t_node		*root;

	scanner = init_scanner("test");
	root = parse(&scanner);
	cr_assert(eq(root->type, COMMAND));
	free_tree(root);
}

Test(parser, input)
{
	t_scanner	scanner;
	t_node		*root;

	scanner = init_scanner("< file");
	root = parse(&scanner);
	cr_assert(eq(root->type, INPUT));
	free_tree(root);
}

Test(parser, output)
{
	t_scanner	scanner;
	t_node		*root;

	scanner = init_scanner("> file");
	root = parse(&scanner);
	cr_assert(eq(root->type, OUTPUT));
	free_tree(root);
}

Test(parser, here_doc)
{
	t_scanner	scanner;
	t_node		*root;

	scanner = init_scanner("<< file");
	root = parse(&scanner);
	cr_assert(eq(root->type, HERE_DOC));
	free_tree(root);
}

Test(parser, append)
{
	t_scanner	scanner;
	t_node		*root;

	scanner = init_scanner(">> file");
	root = parse(&scanner);
	cr_assert(eq(root->type, APPEND));
	free_tree(root);
}

Test(parser, redirection_sequence)
{
	t_scanner	scanner;
	t_node		*root;
	t_node		*lhs;
	t_node		*rhs;

	scanner = init_scanner("cmd < in > out");
	root = parse(&scanner);
	cr_assert(eq(root->type, INPUT), "Failed: cmd < in > out");
	lhs = root->data.pair.left;
	cr_assert(eq(lhs->type, OUTPUT), "Failed: cmd < in > out");
	rhs = root->data.pair.right;
	cr_assert(eq(rhs->type, COMMAND), "Failed: cmd < in > out");
	free_tree(root);

	scanner = init_scanner("< in cmd > out");
	root = parse(&scanner);
	cr_assert(eq(root->type, INPUT), "Failed: < in cmd > out");
	lhs = root->data.pair.left;
	cr_assert(eq(lhs->type, OUTPUT), "Failed: < in cmd > out");
	rhs = root->data.pair.right;
	cr_assert(eq(rhs->type, COMMAND), "Failed: < in cmd > out");
	free_tree(root);

	scanner = init_scanner("< in > out cmd");
	root = parse(&scanner);
	cr_assert(eq(root->type, INPUT), "Failed: < in > out cmd");
	lhs = root->data.pair.left;
	cr_assert(eq(lhs->type, OUTPUT), "Failed: < in > out cmd");
	rhs = root->data.pair.right;
	cr_assert(eq(rhs->type, COMMAND), "Failed: < in > out cmd");
	free_tree(root);
}

Test(parser, concatenate_parameters)
{
	t_scanner	scanner;
	t_node		*root;
	t_node		*lhs;

	scanner = init_scanner("echo Hello World!");
	root = parse(&scanner);
	cr_assert(eq(str, root->data.cmd[0], "echo"));
	cr_assert(eq(str, root->data.cmd[1], "Hello"));
	cr_assert(eq(str, root->data.cmd[2], "World!"));
	free_tree(root);

	scanner = init_scanner("sort < infile -r");
	root = parse(&scanner);
	lhs = root->data.pair.left;
	cr_assert(eq(str, lhs->data.cmd[0], "sort"));
	cr_assert(eq(str, lhs->data.cmd[1], "-r"));
	free_tree(root);
}

Test(parser, pipes)
{
	t_scanner	scanner;
	t_node		*root;
	t_node		*rhs;

	scanner = init_scanner("ls | grep");
	root = parse(&scanner);
	cr_assert(eq(root->type, PIPE), "Pipeline failed");
	free_tree(root);

	scanner = init_scanner("ls | grep txt | head -1");
	root = parse(&scanner);
	rhs = root->data.pair.right;
	cr_assert(eq(rhs->type, PIPE), "Pipeline failed");
	free_tree(root);
}

Test(parser, conditionals)
{
	t_scanner	scanner;
	t_node		*root;
	t_node		*node;

	scanner = init_scanner("ls && grep");
	root = parse(&scanner);
	cr_assert(eq(root->type, AND), "Logical AND failed");
	free_tree(root);

	scanner = init_scanner("ls || grep");
	root = parse(&scanner);
	cr_assert(eq(root->type, OR), "Logical OR failed");
	free_tree(root);

	scanner = init_scanner("cmd1 && cmd2 && cmd3 && cmd4");
	root = parse(&scanner);
	cr_assert(eq(root->type, AND));
	cr_assert(eq(root->data.pair.right->type, COMMAND));
	node = root->data.pair.left;
	cr_assert(eq(node->type, AND));
	cr_assert(eq(node->data.pair.right->type, COMMAND));
	node = node->data.pair.left;
	cr_assert(eq(node->type, AND));
	cr_assert(eq(node->data.pair.left->type, COMMAND));
	cr_assert(eq(node->data.pair.right->type, COMMAND));
	free_tree(root);

	scanner = init_scanner("cmd1 || cmd2 || cmd3 || cmd4");
	root = parse(&scanner);
	cr_assert(eq(root->type, OR));
	cr_assert(eq(root->data.pair.right->type, COMMAND));
	node = root->data.pair.left;
	cr_assert(eq(node->type, OR));
	cr_assert(eq(node->data.pair.right->type, COMMAND));
	node = node->data.pair.left;
	cr_assert(eq(node->type, OR));
	cr_assert(eq(node->data.pair.left->type, COMMAND));
	cr_assert(eq(node->data.pair.right->type, COMMAND));
	free_tree(root);

	scanner = init_scanner("echo a && echo b || echo c && echo d");
	root = parse(&scanner);
	cr_assert(eq(root->type, AND));
	cr_assert(eq(root->data.pair.right->type, COMMAND));
	node = root->data.pair.left;
	cr_assert(eq(node->type, OR));
	cr_assert(eq(node->data.pair.right->type, COMMAND));
	node = node->data.pair.left;
	cr_assert(eq(root->type, AND));
	cr_assert(eq(node->data.pair.left->type, COMMAND));
	cr_assert(eq(node->data.pair.right->type, COMMAND));
	free_tree(root);
}

Test(parser, subshell)
{
	t_scanner	scanner;
	t_node		*root;

	scanner = init_scanner("(cd)");
	root = parse(&scanner);
	cr_assert(eq(root->type, SUBSHELL), "Subshell failed");
	free_tree(root);
}
