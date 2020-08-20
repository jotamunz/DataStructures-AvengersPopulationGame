#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <DoubleList.h>
#include <QDebug>

struct TreeNode
{
    TreeNode *leftSon, *rightSon;
    Node* personNode;
    int marks;

    TreeNode(Node* personNode)
    {
        this->rightSon = this->leftSon = nullptr;
        this->personNode = personNode;
        this->marks = 0;
    }

    bool isLeaf()
    {
        return (this->leftSon == nullptr && this->rightSon == nullptr);
    }
};

struct BinaryTree
{
    TreeNode *root;
    int nodeAmount;

    BinaryTree()
    {
        this->root = nullptr;
    }

    void insert(Node* personNode)
    {
        this->root = insert(personNode, root);
        nodeAmount++;
    }

    TreeNode* insert(Node* personNode, TreeNode* node)
    {
        if (node == nullptr)
            node = new TreeNode(personNode);
        else if (node->personNode->person->id < personNode->person->id)
            node->rightSon = insert(personNode, node->rightSon);
        else if (node->personNode->person->id >= personNode->person->id)
            node->leftSon = insert(personNode, node->leftSon);
        return node;
    }

    int height()
    {
        return height(this->root);
    }

    int height(TreeNode* node)
    {
        if (node != nullptr)
            return (1 + std::max(height(node->leftSon), height(node->rightSon)));
        return 0;
    }

    QString print()
    {
        QString tree = "";
        for (int i = 1; i <= height(); i++)
        {
            QString str;
            printLevel(this->root, i, &str);
            tree += "Level " + QVariant(i).toString() + ": " + str + "\n";
        }
        return tree;
    }

    void printLevel(TreeNode* node, int level, QString* str)
    {
        if (node == nullptr)
            return;
        if (level == 1)
             (*str) += QVariant(node->personNode->person->id).toString() + " ";
        else if (level > 1)
        {
            printLevel(node->leftSon, level-1, str);
            printLevel(node->rightSon, level-1, str);
        }
    }

    void resetMarks()
    {
        return this->resetMarks(this->root);
    }

    void resetMarks(TreeNode* node)
    {
        if (node != nullptr)
        {
            resetMarks(node->leftSon);
            node->marks = 0;
            resetMarks(node->rightSon);
        }
    }
};

#endif // BINARYTREE_H
