#include "ProjectHeader.h"

TreeNode* createNewTreeNode(char* instrument, unsigned short insId, TreeNode* left, TreeNode* right)
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    CheckMem(node);

    int len = strlen(instrument);

    node->instrument = (char*)malloc(sizeof(char) * len);
    CheckMem(node->instrument);

    node->insId = insId;
    node->left = left;
    node->right = right;
}

InstrumentTree BuildTreeFromArray(char** instrumentArr, int size)
{
    int i = 0;
    return RecBuildTreeFromArray(instrumentArr + size / 2, size, &i);
}

InstrumentTree RecBuildTreeFromArray(char** instrumentArr, int size, int* insId)
{
    InstrumentTree output;

    if (size == 0)
    {
        output.root = NULL;
        return output;
    }

    else if (size == 1)
    {
        TreeNode* root = NULL, * leftNode = NULL, * rightNode = NULL;

        leftNode = createNewTreeNode(*(instrumentArr - 1), (*insId) + 1, NULL, NULL);
        rightNode = createNewTreeNode(*(instrumentArr + 1), (*insId) + 2, NULL, NULL);
        root = createNewTreeNode(*instrumentArr, *insId, leftNode, rightNode);

        *insId = *insId + 3;

        output.root = root;
        return output;
    }

    else
    {
        InstrumentTree leftTree, rightTree, output;
        int i = 0;
    }
}