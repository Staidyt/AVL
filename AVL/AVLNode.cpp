#include "AVLNode.h"

AVLNode::AVLNode(int value) : Node(value), height(1) {}

void AVLNode::display() 
{
    if (right != nullptr) {std::cout << "     |---- " << "[" << right->value << "]" << std::endl;}

    std::cout << "|----[" << value << "]" << std::endl;

    if (left != nullptr) {std::cout << "     |---- " << "[" << left->value << "]" << std::endl;}
}

void AVLNode::updateValues() 
{
    auto leftCount = 0;
    auto leftHeight = 0;

    if (left != nullptr) {leftHeight = left->height;}

    auto rightCount = 0;
    auto rightHeight = 0;

    if (right != nullptr) {rightHeight = right->height;}

    height = std::max(leftHeight, rightHeight) + 1;
}

int AVLNode::balanceFactor() 
{
    auto leftHeight = left != nullptr ? left->height : 0;
    auto rightHeight = right != nullptr ? right->height : 0;

    return leftHeight - rightHeight;
}

AVLNode* AVLNode::leftRotate() 
{
    AVLNode* rightTmp = right;

    right = right->left;
    rightTmp->left = this;

    this->updateValues();
    rightTmp->updateValues();

    return rightTmp;
}

AVLNode* AVLNode::rightRotate() 
{
    AVLNode* leftTmp = left;
    left = left->right;
    leftTmp->right = this;

    this->updateValues();
    leftTmp->updateValues();

    return leftTmp;
}