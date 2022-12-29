#include <iostream>
#include "AVLTree.h"

using namespace std;

int main() 
{
    setlocale(LC_ALL, "");
    AVLTree avl;

    int x = 0;
    while (x != -1)
    {
        cout << "\nÂâåäèòå ÷èñëî. (Äëÿ îêîí÷àíèÿ ââîäà, ââåäèòå -1)\n";
        cin >> x;

        if (x == -1) { break; }
        
        if (avl.find(x) == nullptr) { avl.insert(x);}
        else { cout << "\n Ýòîò ýëåìåíò óæå åñòü â äåðåâå"; }
    }

    cout << "\n\nÂûâîä ïîëó÷åííîãî äåðåâà: \n";

    avl.display();

    cout << "\nÏîñëåäîâàòåëüíîñòü ïîëó÷åííîãî ñáàëàíñèðîâàííîãî äåðåâà: \n";
    avl.displayBalancedOrder();
    cout << "\n";

    system("pause");

    return 0;
}
