
#include <stdio.h>
#include <malloc.h>
#include "CalcTree.h"

 typedef double (*node_calc_t)(Node *pThis);
 typedef void (*node_cleanup_t)(Node *pThis);
 struct _NodeVTable{
 const node_calc_t node_calc;
 const node_cleanup_t node_cleanup;
 };

 static double _numnode_calc(Node *pThis)
 {
 printf("numeric node %lf\n", ((NumNode *)pThis)->_num);
 return ((NumNode *)pThis) ->_num;
 }

 static void _numnode_cleanup(Node *pThis)
 {
 printf("NumNode cleanup\n");
 free(pThis);
 }

 const NodeVTable _numnode_vtable = {_numnode_calc, _numnode_cleanup};

 static void _binnode_cleanup(Node *pThis)
 {
 printf("BinNode cleanup\n");
 BinNode * pBinNode = (BinNode*)pThis;
 node_cleanup(pBinNode ->_pLeft);
 node_cleanup(pBinNode ->_pRight);
 free(pThis);
 }

 static double _addnode_calc(Node *pThis)
 {
 printf("Adding...\n");
 AddNode * pAddNode = (AddNode*)pThis;
 BinNode * pBinNode = (BinNode *)&(pAddNode ->isa);
 return node_calc(pBinNode->_pLeft) + node_calc(pBinNode->_pRight);
 }

 const NodeVTable _addnode_vtable = { _addnode_calc, _binnode_cleanup };

 static double _multnode_calc(Node *pThis)
 {
 printf("Multiplying...\n");
 MultNode * pMultNode = (MultNode*)pThis;
 BinNode * pBinNode = (BinNode *)&(pMultNode ->isa);
 return node_calc(pBinNode->_pLeft) * node_calc(pBinNode->_pRight);
 }

 const NodeVTable _multnode_vtable = { _multnode_calc, _binnode_cleanup };

 NumNode * newNumNode(double num)
 {
 NumNode *pNumNode = malloc(sizeof(NumNode));
 if(pNumNode != NULL){
	 pNumNode -> isa.vtable = &_numnode_vtable;
	 pNumNode -> _num = num;
	 }
 return pNumNode;
 }

 AddNode * newAddNode(Node *pLeft, Node *pRight)//apply the obj
 {
 AddNode *pAddNode = malloc(sizeof(AddNode));

 if(pAddNode != NULL){
	 BinNode * pBinNode = (BinNode *)&(pAddNode ->isa);
	 pBinNode->isa.vtable = &_addnode_vtable;
	 pBinNode->_pLeft = pLeft;
	 pBinNode->_pRight = pRight;
	 }
 return pAddNode;
 }

 MultNode * newMultNode(Node *pLeft, Node *pRight)
 {
 MultNode *pMultNode = malloc(sizeof(MultNode));
 if(pMultNode != NULL){
	 BinNode * pBinNode = (BinNode *)&(pMultNode ->isa);
	 pBinNode->isa.vtable = &_multnode_vtable;
	 pBinNode->_pLeft = pLeft;
	 pBinNode->_pRight = pRight;
	 }
 return pMultNode;
 }

 double node_calc(Node *pThis)
 {
 return pThis -> vtable -> node_calc(pThis);
 }

 void node_cleanup(Node *pThis)
 {
 pThis -> vtable -> node_cleanup(pThis);
 }
 /*
  * AppMain() calculate the result of polynomial [2*3+(3+6)]*3
  *
  */
static pMultNodeType buildCalcTree(void){
	pNumNodeType pnum[5];
	pnum[0] = newNumNode(5);
	pnum[1] = newNumNode(3);
	pMultNodeType pmult1;
	pmult1 = newMultNode(pnum[0],pnum[1]);
	pnum[2] = newNumNode(3);
	pnum[3] = newNumNode(6);
	pAddNodeType padd1;
	padd1 = newAddNode(pnum[2],pnum[3]);
	pAddNodeType padd2;
	padd2 = newAddNode(pmult1,padd1);
	pnum[4] = newNumNode(15);
	pMultNodeType pmult2;
	pmult2 = newMultNode(padd2,pnum[4]);
	return pmult2;
}
int main(int arc, char* argv[]){
	pMultNodeType pmult = buildCalcTree();
	printf("result is %lf\n",node_calc(pmult));
	node_cleanup(pmult);


}
