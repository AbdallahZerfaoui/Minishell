/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:54:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/30 23:25:17 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Function to print the tree
// void	print_tree(t_tree_node *root, int depth)
// {
// 	// printf("depth = %d\n", depth);
// 	if (root == NULL)
// 		return ;
// 	// if (depth == 0)
// 	// 	printf("%s\n", root->value);
// 	// Print indentation based on depth
// 	for (int i = 0; i < depth; i++)
// 	{
// 		if (i == depth - 1)
// 			printf("├── ");
// 		else if (root->next_sibling == NULL)
// 			printf("└── ");
// 		else
// 			printf("│   ");
// 	}
// 	// Print the value of the current node
// 	printf("%s\n", root->value);
// 	// Recursively print children
// 	if (root->children)
// 		print_tree(root->children, depth + 1);
// 	// Recursively print siblings
// 	if (root->next_sibling)
// 		print_tree(root->next_sibling, depth);
// }
// void print_tree(const t_tree_node *root, const char *prefix, bool is_last)
// {
//     if (!root)
//         return;

//     // Print the current prefix plus the branch symbol
//     printf("%s", prefix);
//     if (is_last)
//         printf("└── ");
//     else
//         printf("├── ");

//     // Print this node's value
//     printf("%s\n", root->value);

//     // Build the prefix for children:
//     // if this node is the last sibling, we use spaces; otherwise use vertical bar.
//     char child_prefix[256];
//     snprintf(child_prefix, sizeof(child_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

//     // Traverse all children
//     t_tree_node *child = root->children;
//     while (child)
//     {
//         // Determine if the child is the last one in its sibling list
//         t_tree_node *next_sibling = child->next_sibling;
//         bool child_is_last = (next_sibling == NULL);

//         // Recurse for each child
//         print_tree(child, child_prefix, child_is_last);
//         child = next_sibling;
//     }
// }

// void print_tree_wrapper(const t_tree_node *root)
// {
//     // The root is considered "last" in the sense that there's no sibling at the same level
//     // This simplifies the initial call
//     print_tree(root, "", true);
// }

void print_tree(t_tree_node *node, int depth, int is_last)
{
    if (!node)
        return;

    // Print indentation based on depth
    for (int i = 0; i < depth; i++)
    {
        if (i == depth - 1)
            printf(is_last ? "└── " : "├── ");
        else
            printf("    ");
    }

    // Print the value of the current node
    printf("%s\n", node->value);

    // Recursively print children
    t_tree_node *child = node->children;
    while (child)
    {
        // Check if this is the last child
        int is_child_last = (child->next_sibling == NULL);
        print_tree(child, depth + 1, is_child_last);
        child = child->next_sibling;
    }
}

// Helper function to create a new tree node
// t_tree_node	*create_node(char *value)
// {
// 	t_tree_node	*node;

// 	node = (t_tree_node *)malloc(sizeof(t_tree_node));
// 	node->value = value;
// 	node->children = NULL;
// 	node->next_sibling = NULL;
// 	return (node);
// }

// int	main(void)
// {
// 	// Create the tree structure
// 	t_tree_node *root = create_node("A");
// 	root->children = create_node("B");
// 	root->children->next_sibling = create_node("C");
// 	root->children->next_sibling->next_sibling = create_node("G");

// 	root->children->children = create_node("D");
// 	root->children->children->next_sibling = create_node("E");

// 	root->children->next_sibling->children = create_node("F");

// 	// Print the tree
// 	print_tree(root, 0);

// 	// Free the tree (not shown for brevity)
// 	return (0);
// }