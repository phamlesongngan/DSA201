/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : Student code for Assignment 2 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */
#include "requestLib.h"
#include "dbLib.h"

/// Initialize and Finalize any global data that you use in the program
string *List;
char requestID[16];
double Ry, Rx, x, y;
char *ID;
size_t requestNum = 0;
AVLTree <char*> *AVLTreeID = nullptr;

L1List <VRecord*> *result = new L1List <VRecord*>();

bool isAVLTree_Created = false;

bool initVGlobalData(void** pGData) {
    // TODO: allocate global data if you think it is necessary.
    /// pGData contains the address of a pointer. You should allocate data for the global data
    /// and then assign its address to *pGData
    return true;
}
void releaseVGlobalData(void* pGData) {
    // TODO: release the data if you finish using it
}

bool processRequest(VRequest& request, L1List<VRecord>& recList, void* pGData) {
	stringstream ss;
	List = (string*)pGData;
	ss << request.code;
	while (!isAVLTree_Created) {
		isAVLTree_Created = true; 
		AVLTreeID = new AVLTree<char*>();
		size_t i;
	
	}
    return true;
}

