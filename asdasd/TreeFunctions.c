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
    int i = 0, direction = LEFT;
    return RecBuildTreeFromArray(instrumentArr + size / 2, size, &i, &direction);
}

InstrumentTree RecBuildTreeFromArray(char** instrumentArr, int size, int* insId, int* dir)
{
    InstrumentTree output;

    if (size == 0)
    {
        output.root = NULL;
        return output;
    }

    else if (size <= 3)
    {
        TreeNode* root = NULL, * leftNode = NULL, * rightNode = NULL;
        root = createNewTreeNode(*instrumentArr, *insId, NULL, NULL);
        *insId = (*insId) + 1;

        output.root = root;
        
        if (size == 2)
        {
            if (!(*dir))
            {
                leftNode = createNewTreeNode(*(instrumentArr - 1), *insId, NULL, NULL);
                output.root->left = leftNode;
            }

            else if (*dir)
            {
                rightNode = createNewTreeNode(*(instrumentArr + 1), *insId, NULL, NULL);
                output.root->right = rightNode;
            }

            *insId = (*insId) + 1;
        }

        else if (size == 3)
        {
            leftNode = createNewTreeNode(*(instrumentArr - 1), *insId, NULL, NULL);
            rightNode = createNewTreeNode(*(instrumentArr + 1), *insId, NULL, NULL);

            output.root->left = leftNode;
            output.root->right = rightNode;

            *insId = (*insId) + 2;
        }

        return output;
    }

    else
    {
        InstrumentTree leftTree, rightTree, output;
        output.root = createNewTreeNode(*instrumentArr, *insId, NULL, NULL);

        *insId = *insId + 1;

        *dir = LEFT;
        leftTree = RecBuildTreeFromArray(instrumentArr - size / 3, size / 2, insId, dir);

        *dir = RIGHT;
        rightTree = RecBuildTreeFromArray(instrumentArr + size / 3, (size - 1) / 2, insId, dir);

        output.root->left = leftTree.root;
        output.root->right = rightTree.root;

        return output;
    }
}