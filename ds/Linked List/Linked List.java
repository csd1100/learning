class node{
    int data;
    node* next;
};
void mid(node *head){
    node *ptr1 = head;
    node *ptr2 = head;
    if (head!= null){
        while (*ptr1 != null and *ptr2 != null){
            ptr2 = ptr2->next->next;
            ptr1 = ptr1->next;
        }
    }
    cout<<ptr->data;
}