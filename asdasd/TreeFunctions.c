#include "ProjectHeader.h"


TreeNode* createNewTreeNode(char* instrument, unsigned short insId, int numOfMusicians, TreeNode* left, TreeNode* right) //Creates a new TreeNode.
{
    TreeNode* node = NULL;
    node = (TreeNode*)DynamicAllocation(node, sizeof(TreeNode), 1, MALLOC);

    size_t len = strlen(instrument);

    node->instrument = NULL;
    node->instrument = DynamicAllocation(node->instrument,sizeof(char), len + 1, MALLOC);

    if (instrument != '\0')
        strcpy(node->instrument, instrument);

    node->insId = insId;
    node->left = left;
    node->right = right;
    node->numOfMusicians = 0;

    return node;
}

InstrumentTree buildBinaryTreeFromArray(char** arrOfInstruments, int size) //Build a binary search tree from arrOfInstruments.
{
    InstrumentTree output;
    int i, insId = 1;
    output.root = createNewTreeNode(*arrOfInstruments, 0, 0, NULL, NULL);

    for (i = 1; i < size; i++, insId++)
    {
        TreeNode* node = createNewTreeNode(arrOfInstruments[i], insId, 0, NULL, NULL);
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

int findNumOfMusicians(InstrumentTree tree, int insId) //Finds numbers of instrument #insId's musicians.
{
    return recFindNumOfMusicians(tree.root, insId);
}

int recFindNumOfMusicians(TreeNode* root, int insId) //Recursively finds numbers of instrument #insId's musicians.
{
    if (root == NULL)
        return 0;

    else if (root->insId == insId)
        return root->numOfMusicians;

    else
    {
        int left = recFindNumOfMusicians(root->left, insId);
        int right = recFindNumOfMusicians(root->right, insId);
        return (left != 0) ? left : right;
    }

}

void updateNumOfMusicians(InstrumentTree tree, int numOfMusicians, int insId) //Updates num of musicians to instrument #insId.
{
    recUpdateNumOfMusicians(tree.root, numOfMusicians, insId);
}

void recUpdateNumOfMusicians(TreeNode* root, int numOfMusicians, int insId) //Recursively updates num of musicians to instrument #insId.
{
    if (root == NULL)
        return;

    else if (root->insId == insId)
        root->numOfMusicians = numOfMusicians;

    else
    {
        recUpdateNumOfMusicians(root->left, numOfMusicians, insId);
        recUpdateNumOfMusicians(root->right, numOfMusicians, insId);
    }
}

char* findInstrumentName(InstrumentTree insTree, int insID) //Finds instrument's name by insID.
{
    char* output = NULL;
    output = recFindInstrumentName(insTree.root, insID);
    return output;
}

char* recFindInstrumentName(TreeNode* root, int insID) //Recursively finds instrument's name by insID.
{
    if (root == NULL)
        return NULL;

    else if (root->insId == insID)
        return root->instrument;

    else
    {
        char* leftTree = recFindInstrumentName(root->left, insID);
        char* rightTree = recFindInstrumentName(root->right, insID);

        if (leftTree != NULL)
            return leftTree;

        else
            return rightTree;
    }
}