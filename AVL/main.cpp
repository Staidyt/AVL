#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

#include "AVLTree.h"

using namespace std;

int main() 
{
    setlocale(LC_ALL, "");
    AVLTree avl;

    int x = 0;
    while (x != -1)
    {
        cout << "\n������� �����. (��� ��������� �����, ������� -1)\n";
        cin >> x;

        if (x == -1) { break; }
        
        if (avl.find(x) == nullptr) { avl.insert(x);}
        else { cout << "\n ���� ������� ��� ���� � ������"; }
    }

    cout << "\n\n����� ����������� ������: \n";

    avl.display();

    cout << "\n������������������ ����������� ����������������� ������: \n";
    avl.displayBalancedOrder();
    cout << "\n";

    system("pause");

    return 0;
}