#pragma once

class Node abstract 
{
public:
	const int value = -1;

	Node* left = nullptr;
	Node* right = nullptr;

	Node(int value);

	virtual void display() = 0;
};