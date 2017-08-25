 #pragma once
//virtual class Node and it's attribute/operation, in C, operation implement in .c file so,
// not put in the structure,but keep the unit together for good reading
/*
 * virtual interface-only virtual operation
 *
 */
 typedef struct _NodeVTable NodeVTable;
 typedef struct _Node{
 const NodeVTable * vtable;
 }Node;
 typedef Node* pNodeType;
extern double node_calc(Node *pThis);
extern void node_cleanup(Node *pThis);
/*
 * Reality NumNode class
 * "_"means private attribute
 */
 typedef struct _NumNode{
 Node isa;
 double _num;
 }NumNode;
typedef NumNode* pNumNodeType;
extern NumNode * newNumNode(double num);
//AddNode class
 typedef struct _AddNode{
 Node isa;
 Node *_pLeft;
 Node *_pRight;
 }AddNode;
typedef AddNode* pAddNodeType;
extern AddNode * newAddNode(Node *pLeft, Node *pRight);
/*
 * Reality MultNode class
 */
 typedef struct _MultNode{
 Node isa;
 Node *_pLeft;
 Node *_pRight;
 }MultNode;
typedef MultNode* pMultNodeType;
extern MultNode * newMultNode(Node *pLeft, Node *pRight);
/*
 * Virtual BinNode Class
 * virtual operation and virtual attributes
 */
typedef struct _BinNode{
Node isa;
Node *_pLeft;
Node *_pRight;
}BinNode;
typedef BinNode* pBinNodeType;
//virtual class no external operation required.
//new BinNode and Node is not available since virtual


