#include "ProjectHeader.h"

TreeNode* createNewTreeNode(char* instrument, unsigned short insId, TreeNode* left, TreeNode* right) //Creates a new TreeNode.
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    CheckMem(node);

    int len = strlen(instrument);

    node->instrument = (char*)malloc(sizeof(char) * len);
    CheckMem(node->instrument);

    strcpy(node->instrument, instrument);

    node->insId = insId;
    node->left = left;
    node->right = right;
}

InstrumentTree buildBinaryTreeFromArray(char** arrOfInstruments, int size) //Build a binary search tree from arrOfInstruments.
{
    InstrumentTree output;
    int i, insId = 1;
    output.root = createNewTreeNode(*arrOfInstruments, 0, NULL, NULL);
    TreeNode* currNode = output.root;

    for (i = 1; i < size; i++, insId++)
    {
        TreeNode* node = createNewTreeNode(arrOfInstruments[i], insId, NULL, NULL);
        insertNodeToTree(output.root, node);
    }

    return output;
}

void insertNodeToTree(TreeNode* root, TreeNode* node) //Inserts a node to a tree lexicographically.
{
    if (root == NULL)
    {
        root = node;
        return;
    }

    else if (strcmp(root->instrument, node->instrument) < 0)
    {
        if (root->right == NULL)
            root->right = node;

        else
            insertNodeToTree(root->right, node);
    }

    else if (strcmp(root->instrument, node->instrument) > 0)
    {
        if (root->left == NULL)
            root->left = node;

        else
            insertNodeToTree(root->left, node);
    }

    return;
}

int findInsId(InstrumentTree tree, char* instrument) //Finds instrument's insId.
{
    int res = -1;
    
    recFindInsId(tree.root, instrument, &res);

    return res;
}

void recFindInsId(TreeNode* root, char* instrument, int* res) //Recursively finds instrument's insId.
{
    if (root == NULL)
        return;

    else if (strcmp(root->instrument, instrument) == 0)
    {
        *res = root->insId;
        return;
    }

    else if (strcmp(root->instrument, instrument) < 0)
        recFindInsId(root->right, instrument, res);

    else
        recFindInsId(root->left, instrument, res);

    return;
}