/*
	改进的双向循环链表
	2018年8月12日04:35:54
*/

#ifndef _DLINKLIST_H_
#define _DLINKLIST_H_

typedef void DLinkList;
typedef struct _tag_DLinkListNode DLinkListNode;
struct _tag_DLinkListNode
{
    DLinkListNode* next;
    DLinkListNode* pre;
	DLinkListNode* father;
};
typedef struct _tag_DLinkList
{
    DLinkListNode header;
    DLinkListNode* slider;
    int length;
	int nowlength;
} TDLinkList;

DLinkList* DLinkList_Create(void);

void DLinkList_Destroy(DLinkList* list);

void DLinkList_Clear(DLinkList* list);

int DLinkList_Length(DLinkList* list);

int DLinkList_Insert(DLinkList* list, DLinkListNode* node, int pos);

DLinkListNode* DLinkList_Get(DLinkList* list, int pos);

DLinkListNode* DLinkList_Delete(DLinkList* list, int pos);

DLinkListNode* DLinkList_DeleteNode(DLinkList* list, DLinkListNode* node);

DLinkListNode* DLinkList_Reset(DLinkList* list);

DLinkListNode* DLinkList_Current(DLinkList* list);

DLinkListNode* DLinkList_Next(DLinkList* list);

DLinkListNode* DLinkList_Pre(DLinkList* list);
int DLinkList_CurrentLength(DLinkList* list);

#endif
