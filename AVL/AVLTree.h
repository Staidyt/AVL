#pragma once

#include "Tree.h"
#include "AVLNode.h"

class AVLTree : public Tree<AVLNode> 
{
public:
	AVLTree();
	~AVLTree();

	AVLNode* find(int value) const override;							//поиск элемента
	void insert(int value) override;									//добавление элемента
	void erase(int value) override;										//удаление элемента
	void clear() override;												//удаление дерева

	int getSize() const;												//получить размер дерева
	bool isEmpty() const;												//проверка на наличие элементов

	void balance(std::vector<AVLNode**> disbalancedNodesPtrs);			//балансировка дерева

	void display() override;											//вывод дерева
	void display(AVLNode* node, int depth = 0, int state = 0);			//(для функции вывода с помощью рекурсии)

	void displayBalancedOrder();										//отобразить последовательность
};