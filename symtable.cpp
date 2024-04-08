/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
// #include "symnode.cpp"
// #include <iostream>
// using namespace std;

// Write your code below this line

SymbolTable::SymbolTable()
{
    size = 0;
    root = NULL;
}

int h(SymNode *node)
{
    if (node == NULL)
    {
        return -1;
    }
    else
    {
        return node->height;
    }
}

int hd(SymNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return h(node->left) - h(node->right);
    }
}

SymNode *helperinsert(string k, SymNode *node, SymNode *root)
{
    if (node == NULL)
    {
        SymNode *s = new SymNode;
        s->key = k;
        node = s;
        return node;
    }
    else
    {
        if (k > node->key)
        {
            node->right = helperinsert(k, node->right, root);
            node->right->par = node;
        }
        else if (k < node->key)
        {
            node->left = helperinsert(k, node->left, root);
            node->left->par = node;
        }
        node->height = max(h(node->left), h(node->right)) + 1;

        int diff = hd(node);

        if (diff > 1 and k < node->left->key)
        {

            return node->LeftLeftRotation();
        }
        if (diff < -1 and k > node->right->key)
        {

            return node->RightRightRotation();
        }
        if (diff > 1 and k > node->left->key)
        {

            return node->LeftRightRotation();
        }
        if (diff < -1 and k < node->right->key)
        {

            return node->RightLeftRotation();
        }
        // cout<<"here";
        return node;
    }
}

void SymbolTable::insert(string k)
{
    size++;
    SymNode *Node = root;
    root = helperinsert(k, Node, root);
}

SymNode *helperremove(SymNode *root, string k, int &size)
{
    if (root == NULL)
    {
        return root;
    }
    if (root->key < k)
    {
        root->right = helperremove(root->right, k, size);
    }
    else if (root->key > k)
    {
        root->left = helperremove(root->left, k, size);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            root = NULL;
            size--;
            // return root;
        }
        else if (root->right == NULL)
        {
            root = root->left;
            size--;
            // return root;
        }
        else if (root->left == NULL)
        {
            root = root->right;
            size--;
            // return root;
        }

        else
        {
            SymNode *Node = root;
            Node = Node->right;
            while (Node->left != NULL)
            {
                Node = Node->left;
            }
            root->key = Node->key;
            root->address = Node->address;
            // root->val = Node->val;
            Node->key = k;

            root->right = helperremove(root->right, k, size);
            // return root;
        }
    }
    if (root == NULL)
    {
        return root;
    }
    root->height = 1 + max(h(root->left), h(root->right));
    int diff = hd(root);
    // cout<<diff<<" "<<node->key<<endl;

    if (diff > 1 and hd(root->left) >= 0)
    {
        // cout<<"case1"<<endl;
        return root->LeftLeftRotation();
    }
    if (diff < -1 and hd(root->right) <= 0)
    {
        return root->RightRightRotation();
    }
    if (diff > 1 and hd(root->left) < 0)
    {
        // cout<<"case3"<<endl;
        return root->LeftRightRotation();
    }
    if (diff < -1 and hd(root->right) > 0)
    {
        // cout<<"case4"<<endl;
        return root->RightLeftRotation();
    }
    // cout<<"here";
    return root;
}

void SymbolTable::remove(string k)
{
    // size--;
    root = helperremove(root, k, size);
}

int SymbolTable::search(string k)
{
    bool found = false;
    // SymNode *p = new SymNode();
    SymNode *Node = root;

    while (!found)
    {
        // cout<<"hi";
        if (Node == NULL)
        {
            found = false;
            break;
        }
        if (Node->key == k)
        {
            found = true;
            // p = Node;
            break;
        }
        else
        {
            if (Node->key > k)
            {
                Node = Node->left;
            }
            else
            {
                Node = Node->right;
            }
        }
    }
    if (found == false)
    {
        return -2;
    }
    // cout<<Node->key<<"      "<<Node->address<<endl;
    return Node->address;
}

void SymbolTable::assign_address(string k, int idx)
{
    // cout<<"string: "<<k<<endl;
    bool found = false;
    SymNode *p = new SymNode();
    SymNode *Node = root;
    while (!found)
    {
        // cout<<"hi";
        if (Node == NULL)
        {
            found = false;
            break;
        }
        if (Node->key == k)
        {
            found = true;
            p = Node;
            break;
        }
        else
        {
            if (Node->key > k)
            {
                Node = Node->left;
            }
            else
            {
                Node = Node->right;
            }
        }
    }
    // cout<<"Node Key: "<< Node->key<<" "<<idx<<endl;
    Node->address = idx;
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}

void deete(SymNode *node)
{
    if (node != NULL)
    {
        if (node->left != NULL)
        {
            deete(node->left);
        }
        if (node->right != NULL)
        {
            deete(node->right);
        }
        delete node;
        node = NULL;
    }
}

SymbolTable::~SymbolTable()
{
    deete(root);
    size = 0;
}
