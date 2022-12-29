#include "AVLTree.h"

AVLTree::AVLTree() {}

AVLTree::~AVLTree() { clear(); }

AVLNode* AVLTree::find(int value) const 
{
    auto desiredNode = root;

    while (desiredNode != nullptr && desiredNode->value != value) 
    {
        if (desiredNode->value > value) { desiredNode = desiredNode->left;}
        else { desiredNode = desiredNode->right;}
    }

    return desiredNode;
}

void AVLTree::insert(int value) 
{
    auto newNodePtr = &root;
    std::vector<AVLNode**> disbalancedNodesPtrs;

    while (*newNodePtr != nullptr) 
    {
        disbalancedNodesPtrs.push_back(newNodePtr);

        if (value > (*newNodePtr)->value) { newNodePtr = &((*newNodePtr)->right);}
        else { newNodePtr = &((*newNodePtr)->left);}
    }

    *newNodePtr = new AVLNode(value);
    disbalancedNodesPtrs.push_back(newNodePtr);

    balance(disbalancedNodesPtrs);
    size++;
}

void AVLTree::erase(int value) 
{
    auto erasingNodePtr = &root;
    std::vector<AVLNode**> disbalancedNodesPtrs;

    while (*erasingNodePtr != nullptr && (*erasingNodePtr)->value != value) 
    {
        disbalancedNodesPtrs.push_back(erasingNodePtr);

        if ((*erasingNodePtr)->value > value) {erasingNodePtr = &((*erasingNodePtr)->left);}
        else {erasingNodePtr = &((*erasingNodePtr)->right);}
    }

    if (*erasingNodePtr == nullptr) {return;}

    // Удаление листа
    if ((*erasingNodePtr)->left == nullptr && (*erasingNodePtr)->right == nullptr) 
    {
        delete* erasingNodePtr;
        *erasingNodePtr = nullptr;
    }
    // Удаление узла с левым элементом
    else if ((*erasingNodePtr)->right == nullptr) 
    {
        auto trashPtr = *erasingNodePtr;

        (*erasingNodePtr) = (*erasingNodePtr)->left;
        delete trashPtr;
    }
    // Удаление узла с правым элементом
    else {
        disbalancedNodesPtrs.push_back(erasingNodePtr);
        auto erasingNodePtrIndex = disbalancedNodesPtrs.size();

        auto erasingNodeRightChildWithoutLeftNodePtr = &((*erasingNodePtr)->right);

        while ((*erasingNodeRightChildWithoutLeftNodePtr)->left != nullptr) 
        {
            disbalancedNodesPtrs.push_back(erasingNodeRightChildWithoutLeftNodePtr);
            erasingNodeRightChildWithoutLeftNodePtr = &((*erasingNodeRightChildWithoutLeftNodePtr)->left);
        }

        if (*erasingNodeRightChildWithoutLeftNodePtr == (*erasingNodePtr)->right) 
        {
            (*erasingNodeRightChildWithoutLeftNodePtr)->left = (*erasingNodePtr)->left;

            auto toRemove = *erasingNodePtr;
            *erasingNodePtr = *erasingNodeRightChildWithoutLeftNodePtr;
            delete toRemove;
        }
        else {
            auto erasingNodeRightChildBeforeWithoutLeftNode = *disbalancedNodesPtrs.back(), erasingNodeRightChildWithoutLeftNode = *erasingNodeRightChildWithoutLeftNodePtr;

            erasingNodeRightChildBeforeWithoutLeftNode->left = (*erasingNodeRightChildWithoutLeftNodePtr)->right;
            erasingNodeRightChildWithoutLeftNode->left = (*erasingNodePtr)->left;
            erasingNodeRightChildWithoutLeftNode->right = (*erasingNodePtr)->right;

            delete* erasingNodePtr;
            *erasingNodePtr = erasingNodeRightChildWithoutLeftNode;
            disbalancedNodesPtrs[erasingNodePtrIndex] = &(erasingNodeRightChildWithoutLeftNode->right);
        }
    }

    balance(disbalancedNodesPtrs);
    size--;
}

void AVLTree::clear() 
{
    std::vector<Node*> stack;

    if (root != nullptr) {stack.push_back(root);}

    while (!stack.empty()) 
    {
        Node* node = stack.back();
        stack.pop_back();

        if (node->left != nullptr) {
            stack.push_back(node->left);
        }

        if (node->right != nullptr) {
            stack.push_back(node->right);
        }

        size--;
        delete node;
    }

    root = nullptr;
}

int AVLTree::getSize() const {return size;}

bool AVLTree::isEmpty() const {return size == 0;}

void AVLTree::balance(std::vector<AVLNode**> path) 
{
    reverse(path.begin(), path.end());

    for (auto node : path) 
    {
        (*node)->updateValues();

        // ll
        if ((*node)->balanceFactor() >= 2 && (*node)->left->balanceFactor() >= 1) {*node = (*node)->rightRotate();}
        // lr
        else if ((*node)->balanceFactor() >= 2) 
        {
            (*node)->left = (*node)->left->leftRotate();
            *node = (*node)->rightRotate();
        }
        // rr
        else if ((*node)->balanceFactor() <= -2 && (*node)->right->balanceFactor() <= -1) {*node = (*node)->leftRotate();}
        // rl
        else if ((*node)->balanceFactor() <= -2) 
        {
            (*node)->right = ((*node)->right)->rightRotate();
            *node = (*node)->leftRotate();
        }
    }
}

void AVLTree::display() 
{
    std::cout << std::endl;

    if (root != nullptr) {display(root);}
    else {std::cout << "Пусто\n";}
}

void AVLTree::display(AVLNode* node, int depth, int state) 
{
    if (node->right) {display(node->right, depth + 1, 2);}

    for (int i = 0; i < depth; i++) {std::cout << "     ";}

    std::cout << "|----";
    std::cout << "[" << node->value << "]" << std::endl;

    if (node->left) {display(node->left, depth + 1, 1);}
}

void AVLTree::displayBalancedOrder() 
{
    std::vector<AVLNode*> order;

    order.push_back(root);

    for (int i = 0; i < size; i++) 
    {
        if (order[i]->left != nullptr) {order.push_back(order[i]->left);}
        if (order[i]->right != nullptr) {order.push_back(order[i]->right);}
    }

    for (auto node : order) {std::cout << node->value << " ";}
}