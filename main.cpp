#include <iostream>
using namespace std;
template <class T, int Order>
class Node
{
    T *keys;
    int numberOfKeysNode;
    Node **children;
    int currentNumberOfkeys;
    bool leaf;

public:
    Node(int numberOfKeys, bool stateLeaf)
    {
        numberOfKeysNode = numberOfKeys;
        leaf = stateLeaf;
        keys = new T[2 * numberOfKeysNode - 1];
        children = new Node *[2 * numberOfKeysNode];
        currentNumberOfkeys = 0;

        for (int i = 0; i < 2 * numberOfKeysNode - 1; i++)
            keys[i] = -1;

        for (int i = 0; i < 2 * numberOfKeysNode - 1; i++)
            children[i] = nullptr;
    }
    void insertKey(T key)
    {
        int location = currentNumberOfkeys - 1;
        if (leaf == true)
        {
            while (location >= 0 && keys[location] > key)
            {
                keys[location + 1] = keys[location];
                location--;
            }
            keys[location + 1] = key;
            currentNumberOfkeys = currentNumberOfkeys + 1;
        }
        else
        {
            while (location >= 0 && keys[location] > key)
                location--;
            if (children[location + 1]->currentNumberOfkeys == 2 * numberOfKeysNode - 1)
            {
                split(location + 1, children[location + 1]);
                if (keys[location + 1] < key)
                    location++;
            }
            children[location + 1]->insertKey(key);
            if (Order % 2 == 1)
            {
                if (children[location + 1]->currentNumberOfkeys == 2 * numberOfKeysNode - 1)
                {
                    split(location + 1, children[location + 1]);
                }
            }
        }
    }
    void split(int index, Node *splitNode)
    {
        Node *temp = new Node(splitNode->numberOfKeysNode, splitNode->leaf);
        temp->currentNumberOfkeys = numberOfKeysNode - 1;

        for (int j = 0; j < numberOfKeysNode - 1; j++)
            temp->keys[j] = splitNode->keys[j + numberOfKeysNode];

        if (splitNode->leaf == false)
        {
            for (int j = 0; j < numberOfKeysNode; j++)
                temp->children[j] = splitNode->children[j + numberOfKeysNode];
        }

        splitNode->currentNumberOfkeys = numberOfKeysNode - 1;

        for (int j = currentNumberOfkeys; j >= index + 1; j--)
            children[j + 1] = children[j];
        children[index + 1] = temp;

        for (int j = currentNumberOfkeys - 1; j >= index; j--)
            keys[j + 1] = keys[j];

        keys[index] = splitNode->keys[numberOfKeysNode - 1];
        currentNumberOfkeys = currentNumberOfkeys + 1;
    }
    void PrintKeys(int space)
    {
        int j;
        for (j = 1; j <= space; j++)
            cout << " ";
        for (int i = 0; i < currentNumberOfkeys; i++)
            cout << " " << keys[i];
        cout << "\n ";
        for (int i = 0; i <= currentNumberOfkeys; i++)
        {
            if (leaf == false)
                children[i]->PrintKeys(space + 1);
        }
    }

    template <class, int>
    friend class BTree;
};
template <class T, int Order>
class BTree
{
public:
    Node<T, Order> *root;
    int numberOfKeys;

public:
    BTree()
    {
        numberOfKeys = (Order % 2 == 0) ? (Order / 2) : (Order / 2) + 1;
        root = NULL;
    }
    void Print()
    {
        if (root != NULL)
            root->PrintKeys(0);
    }
    void Insert(int key)
    {
        if (root == NULL)
        {
            root = new Node<T, Order>(numberOfKeys, true);
            root->keys[0] = key;
            root->currentNumberOfkeys = 1;
        }
        else
        {
            if (root->currentNumberOfkeys == 2 * numberOfKeys - 1)
            {
                Node<T, Order> *temp = new Node<T, Order>(numberOfKeys, false);
                temp->children[0] = root;
                temp->split(0, root);
                int i = 0;
                if (temp->keys[0] < key)
                    i++;
                temp->children[i]->insertKey(key);
                root = temp;
            }
            else
                root->insertKey(key);
        }
        if (Order % 2 == 1)
        {
            if (root->currentNumberOfkeys == 2 * numberOfKeys - 1)
            {
                Node<T, Order> *temp = new Node<T, Order>(numberOfKeys, false);
                temp->children[0] = root;
                temp->split(0, root);
                root = temp;
            }
        }
    }
};
int main()
{

    BTree<int, 3> t1;
    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);
    t1.Print();

    BTree<char, 5> t;
    // Look at the example in our lecture:
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');
    t.Print();

    return 0;
}
