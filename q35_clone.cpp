
// 面试题35：复杂链表的复制
// 题目：请实现函数ComplexListNode* Clone(ComplexListNode* pHead)，复
// 制一个复杂链表。在复杂链表中，每个结点除了有一个m_pNext指针指向下一个
// 结点外，还有一个m_pSibling 指向链表中的任意结点或者nullptr。

#include <cstdio>

struct ComplexListNode
{
    int                 m_nValue;
    ComplexListNode*    m_pNext;
    ComplexListNode*    m_pSibling;

    ComplexListNode(int val=0):m_nValue(val),m_pNext(nullptr),m_pSibling(nullptr){};
};

ComplexListNode* CreateNode(int nValue)
{
    ComplexListNode* pNode = new ComplexListNode();

    pNode->m_nValue = nValue;
    pNode->m_pNext = nullptr;
    pNode->m_pSibling = nullptr;

    return pNode;
}

void BuildNodes(ComplexListNode* pNode, ComplexListNode* pNext, ComplexListNode* pSibling)
{
    if(pNode != nullptr)
    {
        pNode->m_pNext = pNext;
        pNode->m_pSibling = pSibling;
    }
}

void PrintList(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode != nullptr)
    {
        printf("The value of this node is: %d.\n", pNode->m_nValue);

        if(pNode->m_pSibling != nullptr)
            printf("The value of its sibling is: %d.\n", pNode->m_pSibling->m_nValue);
        else
            printf("This node does not have a sibling.\n");

        printf("\n");

        pNode = pNode->m_pNext;
    }
}
//=============func=========

ComplexListNode *CloneNodes(ComplexListNode *p_head){
    if(!p_head) return nullptr;

    ComplexListNode *p_node_new = new ComplexListNode(p_head->m_nValue);
    CloneNodes(p_head->m_pNext);

    ComplexListNode *p_head_next = p_head->m_pNext;
    p_head->m_pNext = p_node_new;
    p_node_new->m_pNext = p_head_next;

    return p_head;
}

ComplexListNode *ConnectSiblings(ComplexListNode *p_head){
    if(!p_head) return nullptr;

    ComplexListNode *p_head_next = p_head->m_pNext;

    if(!p_head->m_pSibling) p_head_next->m_pSibling = nullptr;
    else p_head_next->m_pSibling = p_head->m_pSibling->m_pNext;

    ConnectSiblings(p_head_next->m_pNext);
    return p_head;
}

ComplexListNode *getCloneList(ComplexListNode *p_head){
    if(!p_head) return nullptr;

    ComplexListNode *p_head_next = p_head->m_pNext;

    p_head->m_pNext = p_head_next->m_pNext;
    p_head_next->m_pNext = getCloneList(p_head_next->m_pNext);

    return p_head_next;
}

void print_list_test(ComplexListNode *p_head){
    ComplexListNode *node = p_head;
    while(node){
        printf("%d",node->m_nValue );
        if(node->m_pSibling){
            printf("->%d ",node->m_pSibling->m_nValue);
        }
        else printf(" ");
        node = node->m_pNext;
    }

    printf("\n");
}
ComplexListNode *Clone(ComplexListNode *p_head){
    CloneNodes(p_head);
    printf("CloneNodes() result:\n");
    print_list_test(p_head);
    ConnectSiblings(p_head);
    printf("ConnectSiblings() result:\n");
    print_list_test(p_head);
    ComplexListNode *res = getCloneList(p_head);
    printf("ComplexListNode() result:\n");
    print_list_test(p_head);
    return res;
}

// ====================测试代码====================
void Test(const char* testName, ComplexListNode* pHead)
{
    if(testName != nullptr)
        printf("%s begins:\n", testName);

    printf("The original list is:\n");
    PrintList(pHead);

    ComplexListNode* pClonedHead = Clone(pHead);

    printf("The cloned list is:\n");
    PrintList(pClonedHead);
}

//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//  |       |      /|\             /|\
//  --------+--------               |
//          -------------------------
void Test1()
{
    ComplexListNode* pNode1 = CreateNode(1);
    ComplexListNode* pNode2 = CreateNode(2);
    ComplexListNode* pNode3 = CreateNode(3);
    ComplexListNode* pNode4 = CreateNode(4);
    ComplexListNode* pNode5 = CreateNode(5);

    BuildNodes(pNode1, pNode2, pNode3);
    BuildNodes(pNode2, pNode3, pNode5);
    BuildNodes(pNode3, pNode4, nullptr);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test1", pNode1);
}

// m_pSibling指向结点自身
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//         |       | /|\           /|\
//         |       | --             |
//         |------------------------|
void Test2()
{
    ComplexListNode* pNode1 = CreateNode(1);
    ComplexListNode* pNode2 = CreateNode(2);
    ComplexListNode* pNode3 = CreateNode(3);
    ComplexListNode* pNode4 = CreateNode(4);
    ComplexListNode* pNode5 = CreateNode(5);

    BuildNodes(pNode1, pNode2, nullptr);
    BuildNodes(pNode2, pNode3, pNode5);
    BuildNodes(pNode3, pNode4, pNode3);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test2", pNode1);
}

// m_pSibling形成环
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//          |              /|\
//          |               |
//          |---------------|
void Test3()
{
    ComplexListNode* pNode1 = CreateNode(1);
    ComplexListNode* pNode2 = CreateNode(2);
    ComplexListNode* pNode3 = CreateNode(3);
    ComplexListNode* pNode4 = CreateNode(4);
    ComplexListNode* pNode5 = CreateNode(5);

    BuildNodes(pNode1, pNode2, nullptr);
    BuildNodes(pNode2, pNode3, pNode4);
    BuildNodes(pNode3, pNode4, nullptr);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test3", pNode1);
}

// 只有一个结点
void Test4()
{
    ComplexListNode* pNode1 = CreateNode(1);
    BuildNodes(pNode1, nullptr, pNode1);

    Test("Test4", pNode1);
}

// 鲁棒性测试
void Test5()
{
    Test("Test5", nullptr);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();

    return 0;
}


