#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node {
    int val;
    struct _node *left, *right;
} Node;

void n_init(Node *n, int v)
{
    n->val = v;
    n->left = NULL;
    n->right = NULL;
}

Node* bt_insert(Node *root, int v)
{
    Node *nn = malloc(sizeof(Node));
    n_init(nn, v);

    if (root == NULL) {
        printf("insert %d\n", v);
        return nn;
    }

    if (root->val > v) {
        root->left = bt_insert(root->left, v);
    } else if (root->val < v) {
        root->right = bt_insert(root->right, v);
    }
    return root;
}

bool is_leaf(Node root) 
{
    return root.left == NULL && root.right == NULL;
}

size_t n_child_count(Node n) {
    size_t out = 0;
    if (n.left != NULL) out += 1;
    if (n.right!= NULL) out += 1;
    return out;
}

size_t bt_search(int val, Node root, Node *dst)
{
    if (root.val == val) {
        printf("Found %d\n", val);
        dst = &root;
        return 1;
    }
    
    if (root.val > val) {
        if (root.left != NULL) {
            return bt_search(val, *root.left, dst);
        }
    } else if (root.val < val) {
        if (root.right != NULL) {
            return bt_search(val, *root.right, dst);
        }
    }
    printf("BST does not contain %d\n", val);
    return 0;
}

Node* bt_find_max(Node *root)
{
    if (root->right == NULL) {
        return root;
    }
    return bt_find_max(root->right);
}

Node* bt_find_min(Node *root)
{
    if (root->left == NULL) {
        return root;
    }
    return bt_find_min(root->left);
}

Node* bt_delete(int v, Node *root)
{
    if (root == NULL) {
        return NULL;
    }
    
    if (v < root->val) {
        root->left = bt_delete(v, root->left);
    } else if (v > root->val) {
        root->right = bt_delete(v, root->right);
    } else {
        // no children
        if (is_leaf(*root)) {
            printf("delete %d\n", v);
            free(root);
            return NULL;
        }

        // One child
        if (root->left == NULL || root->right == NULL) {
            Node *cn;
            if (root->left != NULL) {
                cn = root->left;
                printf("delete left child %d\n", v);
            }
            if (root->right != NULL) {
                cn = root->right;
                printf("delete right child %d\n", v);
            }
            free(root);
            return cn; 
        } else {
            // Two children
            // This implementation of deletion works by replacing the root with the minimum node of the right subtree
            Node *mrn = bt_find_min(root->right);
            printf("Replaced %d with %d\n", root->val, mrn->val);
            root->val = mrn->val;
            root->right = bt_delete(mrn->val, root->right);
        }
    }
    return root;
}

// Inorder traversal
// LEFT subtree - ROOT - RIGHT subtree
void bt_inorder_traversal(Node *root)
{
    if (root == NULL) {
        return;
    }
    bt_inorder_traversal(root->left);
    printf("%d\n", root->val);
    bt_inorder_traversal(root->right);
}

// Preorder traversal
// ROOT - LEFT subtree - RIGHT subtree
void bt_preorder_traversal(Node *root)
{
    if (root == NULL) {
        return;
    }
    printf("%d\n", root->val);
    bt_preorder_traversal(root->left);
    bt_preorder_traversal(root->right);
}

// Preorder traversal
// ROOT - LEFT subtree - RIGHT subtree
void bt_postorder_traversal(Node *root)
{
    if (root == NULL) {
        return;
    }
    bt_postorder_traversal(root->left);
    bt_postorder_traversal(root->right);
    printf("%d\n", root->val);
}

int bt_height(Node *root)
{
    if (root == NULL) {
        return -1;
    } 

    int lst = bt_height(root->left);
    int rst = bt_height(root->right);
    return 1 + (lst > rst ? lst : rst);
}

int main()
{
    Node root = {
        .val = 8,
        .left = NULL,
        .right = NULL,
    };

    printf("---------------------------------\n");
    bt_insert(&root, 2);
    bt_insert(&root, 5);
    bt_insert(&root, 4);
    bt_insert(&root, 1);
    bt_insert(&root, 8);
    bt_insert(&root, 3);
    printf("---------------------------------\n");
    printf("Height %d\n", bt_height(&root));
    printf("---------------------------------\n");
    Node dst = {0};
    bt_search(6, root, &dst);
    bt_search(3, root, &dst);
    bt_search(5, root, &dst);
    printf("---------------------------------\n");
    bt_delete(6, &root);
    printf("---------------------------------\n");
    bt_search(6, root, &dst);
    bt_search(5, root, &dst);
    
    return 0;
}
