struct ListNode{
    int m_nValue;
    ListNode *m_pNext;
};
void delete_node(ListNode **pListHead, ListNode *pToBeDeleted){
   if(!pListHead or !pToBeDeleted) return; 

   // 找得到且不为尾结点
   if(pToBeDeleted->m_pNext != NULL){
       ListNode *pNext = pToBeDeleted->m_pNext;
       pToBeDeleted->m_nValue = pNext->m_nValue;
       pToBeDeleted->m_pNext = pNext->m_pNext;

       delete pNext;
       pNext = NULL;
   }

   // 找得到且为尾结点同时为头结点, pListHead需置为空
   else if(*pListHead == pToBeDeleted){
       delete pToBeDeleted;
       pToBeDeleted = NULL;
       *pListHead = NULL;
   }

   // 找得到且为尾结点(非头结点)
   else{
       ListNode *pNode = *pListHead;
       while(pNode->m_pNext != pToBeDeleted){
           pNode = pNode->m_pNext;
       }
       
       pNode->m_pNext = NULL;
       deelte pToBeDeleted;
       pToBeDeleted = NULL;
    }
}
       
          


