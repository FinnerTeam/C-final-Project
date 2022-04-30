#include "ProjectHeader.h"

TreeNode* createNewTreeNode(char* instrument, unsigned short insId, TreeNode* left, TreeNode* right)
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
        TreeNode* root = NULL;
        root = createNewTreeNode(*instrumentArr, *insId, NULL, NULL);

        *insId = (*insId) + 1;

        output.root = root;
        return output;
    }

    else
    {
        InstrumentTree leftTree, rightTree, output;
        output.root = createNewTreeNode(*instrumentArr, *insId, NULL, NULL);

        *insId = *insId + 1;

        leftTree = RecBuildTreeFromArray(instrumentArr - (size + 1) / 4, size / 2, insId);
        rightTree = RecBuildTreeFromArray(instrumentArr + (size + 1) / 4, size / 2, insId);

        output.root->left = leftTree.root;
        output.root->right = rightTree.root;

        return output;
    }
}