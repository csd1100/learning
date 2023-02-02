#include <iostream>

using namespace std;
struct node
{
    int data;
    node *next;
};
class linkedList
{
    node *head;
    int count;

public:
    linkedList()
    {
        head = NULL;
        count = 0;
    }
    node *newNode()
    {
        int d;
        node *temp;
        temp = new node();
        cout << "\nEnter Data:\n";
        cin >> d;
        temp->data = d;
        temp->next = NULL;
        return temp;
    }
    void prependNode()
    {
        count++;
        node *temp = newNode();
        if (head != NULL)
        {
            temp->next = head;
            head = temp;
        }
        else
        {
            head = temp;
        }
    }
    void appendNode()
    {
        int d;
        count++;
        node *ptr;
        node *temp = newNode();
        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            cout << "\n";
            ptr = head;
            while (ptr->next != NULL)
            {
                cout << ptr->data << "->";
                ptr = ptr->next;
            }
            ptr->next = temp;
            ptr = ptr->next;
            ptr->next = NULL;
        }
    }
    void insertNode()
    {
        //
        int loc;

        if (head != NULL)
        {
            cout << "\nEnter Location";
            cin >> loc;
            if (loc > count)
            {
                cout << "\nLocation Greater than Length Appending Node.";
                appendNode();
            }
            else
            {
                node *temp = newNode();
                node *ptr;
                ptr = head;
                int i = 1;
                while (i < loc)
                {
                    ptr = ptr->next;
                    i++;
                }
                temp->next = ptr->next;
                ptr->next = temp;
            }
        }
        else
        {
            node *temp = newNode();
            cout << "\nLinkedList is empty inserting in 1st node";
            head = temp;
        }
    }
    void deleteAll()
    {
        node *dptr;
        node *nptr;
        if (head != NULL)
        {
            dptr = head;
            nptr = head->next;
            while (nptr != NULL)
            {
                delete dptr;
                dptr = nptr;
                nptr = dptr->next;
            }
        }
    }
    void midOfLl()
    {
        node *ptr1;
        node *ptr2;
        if (head != NULL)
        {
            ptr1 = head;
            ptr2 = head;
            while (ptr2->next->next != NULL)
            {
                ptr1 = ptr1->next;
                ptr2 = ptr2->next->next;
            }
            cout << "\nMid:" << ptr1->data;
        }
    }
    void displayLl()
    {
        node *temp;
        if (head != NULL)
        {
            temp = head;
            while (temp != NULL)
            {
                cout << temp->data << "->";
                temp = temp->next;
            }
        }
        else
        {
            cout << "\nLinked List is Empty.";
        }
    }
};

int main()
{
    linkedList ll;
    int c = 1;
    while (c == 1)
    {
        ll.appendNode();
        cout << "\nChoice:";
        cin >> c;
    }
    ll.displayLl();
    // ll.midOfLl();
    ll.prependNode();
    ll.displayLl();
    // ll.midOfLl();
    ll.insertNode();
    ll.displayLl();
    ll.deleteAll();
    return 0;
}