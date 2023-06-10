struct ListNode *reverse(struct ListNode *head)
{
    typedef struct ListNode node;
    node *temp = NULL, *head_new = NULL;
    while (head)
    {
        temp = head;
        head = temp->next;
        temp->next = head_new;
        head_new = temp;
    }
    return head_new;
}