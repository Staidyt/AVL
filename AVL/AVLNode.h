#pragma once

#include <iostream>

#include "Node.h"

class AVLNode : public Node 
{
public:
	int height = 0;

	AVLNode* left = nullptr;
	AVLNode* right = nullptr;

	AVLNode(int value);

	void updateValues();
	int balanceFactor();

	AVLNode* leftRotate();
	AVLNode* rightRotate();

	void display() override;
};