#include<bits/stdc++.h>
using namespace std;

#define InMinHeap false
#define InMaxHeap true

class IntervalHeapNode{



    int leftEndPoint;
    int rightEndPoint;

    IntervalHeapNode * parent;
    IntervalHeapNode * leftChild;
    IntervalHeapNode * rightChild;

public:

    IntervalHeapNode( int l = INT_MIN  , int r = INT_MIN ){
        this->leftEndPoint = l;
        this->rightEndPoint = r;

        this->parent=NULL;
        this->leftChild=NULL;
        this->rightChild=NULL;


    }

    void NodeDisplay(){
    cout<<"\nNode's own address " << this;

    cout<< "\nLeft Endpoint  - "<< this->leftEndPoint;
    cout<< "\nRight Endpoint  - "<< this->rightEndPoint;
    cout<< "\nParent  - "<< this->parent;
    cout<< "\nLeft Child  - "<< this->leftChild;
    cout<< "\nLeft Right  - "<< this->rightChild;


    }



    IntervalHeapNode * getLeftChild( ){
        return this->leftChild;
    }


    IntervalHeapNode * getRightChild( ){
        return this->rightChild;
    }


     void setLeftChild(  IntervalHeapNode * t ){
         this->leftChild = t;
    }


    void setRightChild(IntervalHeapNode *  t ){
         this->rightChild = t;
    }


    IntervalHeapNode * getParent( ){
        return this->parent;
    }

     void setParent( IntervalHeapNode * P){
      this->parent =P;
    }

    int  getLeftEndPoint( ){
        return this->leftEndPoint;
    }

    int  getRightEndPoint( ){
        return this->rightEndPoint;
    }

    void  setLeftEndPoint(  int x ){
        this->leftEndPoint = x;
    }


    void  setRightEndPoint(  int x ){
        this->rightEndPoint = x;
    }






};

class IntervalHeap{

public:
IntervalHeapNode *root;
IntervalHeapNode *lastNode;

deque<IntervalHeapNode *> q;

deque<IntervalHeapNode *> deleteTrackQ;


IntervalHeap( IntervalHeapNode * t){

this->root = t;
this->lastNode = t;

}



void InorderDisplay(IntervalHeapNode * T){

if(T!=NULL)
    {

        InorderDisplay(T->getLeftChild());

        cout<< endl<<endl;
        T->NodeDisplay();

        InorderDisplay( T->getRightChild());


    }
}


void printLevelOrder(IntervalHeapNode *root)
{

    cout<<"[Displaying Interval Heap in Level Order]\n";

    if (root == NULL) return;


    queue<IntervalHeapNode *> printQ;

    // Enqueue Root and initialize height
    printQ.push(root);

    while (printQ.empty() == false)
    {
        // nodeCount (queue size) indicates number
        // of nodes at current level.
        int nodeCount = printQ.size();

        // Dequeue all nodes of current level and
        // Enqueue all nodes of next level
        while (nodeCount > 0)
        {
            IntervalHeapNode *node = printQ.front();

            int Lep = node->getLeftEndPoint();
            int Rep = node->getRightEndPoint();

            if(Lep==INT_MIN){
                cout <<  "( XXX "  << ",  " << Rep<<" )      ";

            }else if(Rep==INT_MIN){
                cout << "( "<<Lep << ",  "<< " XXX "<<" )      ";

            }else{
                cout << "( "<<Lep << ",  "<< Rep<<" )      ";
            }





            printQ.pop();
            if (node->getLeftChild() != NULL)
                printQ.push(node->getLeftChild());
            if (node->getRightChild() != NULL)
                printQ.push(node->getRightChild());
            nodeCount--;
        }
        cout << endl;
    }
}



void BubbleUp(IntervalHeapNode * N, bool &f){

    if(!N->getParent()){
        return ;

    }

    if(f==InMinHeap){

        if(N->getLeftEndPoint() > N->getParent()->getLeftEndPoint()){
            return;
        }
        else{
            //1. perform swap -  leftEndPoint of N's parent with leftEndPoint of N
            //2. And after swap at each level up if leftEndPoint becomes greater than rightEndPoint
            //3. Swap leftEP with rightEP and then start moving is MAX - heap

            //1.
            int ele = N->getParent()->getLeftEndPoint();
            N->getParent()->setLeftEndPoint(N->getLeftEndPoint());
            N->setLeftEndPoint(ele);

            //2.
            if(N->getParent()->getLeftEndPoint() > N->getParent()->getRightEndPoint()  ){
                int ele1 = N->getParent()->getLeftEndPoint();
                N->getParent()->setLeftEndPoint(N->getParent()->getRightEndPoint());
                N->getParent()->setRightEndPoint(ele1);

                f=InMaxHeap;

            }

            //3. Move up
            BubbleUp(N->getParent(), f);



        }



    }else{

        //Moving in MAX-HEAP

        if(N->getRightEndPoint() < N->getParent()->getRightEndPoint()){
            return;
        }
        else{
            //1. perform swap -  rightEndPoint of N's parent with rightEndPoint of N
            //2. And after swap at each level up if rightEndPoint becomes less than leftEndPoint
            //3. Swap leftEP with rightEP and then start moving is MAX - heap

            //1.
            int ele = N->getParent()->getRightEndPoint();
            N->getParent()->setRightEndPoint(N->getRightEndPoint());
            N->setRightEndPoint(ele);

            //2.
            if( N->getParent()->getRightEndPoint()  < N->getParent()->getLeftEndPoint()  ){
                int ele1 = N->getParent()->getLeftEndPoint();
                N->getParent()->setLeftEndPoint(N->getParent()->getRightEndPoint());
                N->getParent()->setRightEndPoint(ele1);

                f=InMinHeap;

            }

            //3. Move up
            BubbleUp(N->getParent(), f);



        }




    }



}

void DisplayQueue()
{

for(auto it=q.begin(); it!=q.end();++it)
       {
           cout<<*it <<" " ; /*(*it)->NodeDisplay();*/


       }
}

void DisplayQueueDelTrckQ()
{

for(auto it=deleteTrackQ.begin(); it!=deleteTrackQ.end();++it)
       {
           cout<<*it <<" " ; /*(*it)->NodeDisplay();*/


       }
}



void moveDown(IntervalHeapNode * N, bool &f){

    if(N->getLeftEndPoint() > N->getRightEndPoint()  && N->getRightEndPoint() != INT_MIN){

            int X = N->getLeftEndPoint();
            N->setLeftEndPoint(N->getRightEndPoint());
            N->setRightEndPoint(X);

    }

    //Also check for last level where no left or right child present
    // directly return
    if(!N->getLeftChild() && !N->getRightChild()){
        return;
    }


    if(f==InMinHeap){

        //Only left child case and no right child
         if(N->getLeftChild() && !N->getRightChild()){

                //-> this left child will if has INT_MIN as leftEP return
              if(N->getLeftChild()->getLeftEndPoint()==INT_MIN){
                return;
              }

            if(N->getLeftEndPoint() < N->getLeftChild()->getLeftEndPoint() && N->getLeftChild()->getLeftEndPoint() !=INT_MIN )
                {  return;  }
            else{
                int X = N->getLeftEndPoint();
                N->setLeftEndPoint(N->getLeftChild()->getLeftEndPoint());
                N->getLeftChild()->setLeftEndPoint(X);

                return;

            }

        }

        //If we control reaches here that means both left and right child are present

        if(N->getLeftEndPoint() < N->getLeftChild()->getLeftEndPoint() &&
            (N->getLeftEndPoint() < N->getRightChild()->getLeftEndPoint()  ||  N->getRightChild()->getLeftEndPoint()==INT_MIN )){
             //Recursion terminating condition - Min heap property established

                return;


        }else if (N->getLeftEndPoint() < N->getLeftChild()->getLeftEndPoint() &&  N->getLeftEndPoint() > N->getRightChild()->getLeftEndPoint()
                  &&  N->getRightChild()->getLeftEndPoint()!=INT_MIN){
            //Move down from right child
            // swap first rightchild's leftEP with N's leftEP

            int X = N->getLeftEndPoint();
            N->setLeftEndPoint(N->getRightChild()->getLeftEndPoint());
            N->getRightChild()->setLeftEndPoint(X);

            moveDown(N->getRightChild(), f);



        }
        else if (N->getLeftEndPoint() > N->getLeftChild()->getLeftEndPoint() && N->getLeftChild()->getLeftEndPoint()!=INT_MIN
                  &&  (N->getLeftEndPoint() < N->getRightChild()->getLeftEndPoint()  ||  N->getRightChild()->getLeftEndPoint()  ==INT_MIN)  ){

            //Move down from left child


            int X = N->getLeftEndPoint();
            N->setLeftEndPoint(N->getLeftChild()->getLeftEndPoint());
            N->getLeftChild()->setLeftEndPoint(X);

            moveDown(N->getLeftChild(), f);


        }else{
        // when N-leftEndpoint greater than both leftchild and rightchilds leftEP's

        //Choose min of leftchild and rightchilds leftEP's and go in that direction
            if(N->getLeftChild()->getLeftEndPoint() <  N->getRightChild()->getLeftEndPoint() && N->getLeftChild()->getLeftEndPoint()!=INT_MIN){

                    int X = N->getLeftEndPoint();
                    N->setLeftEndPoint(N->getLeftChild()->getLeftEndPoint());
                    N->getLeftChild()->setLeftEndPoint(X);

                    moveDown(N->getLeftChild(), f);


            }else{

                int X = N->getLeftEndPoint();
                N->setLeftEndPoint(N->getRightChild()->getLeftEndPoint());
                N->getRightChild()->setLeftEndPoint(X);

                moveDown(N->getRightChild(), f);



            }

        }

    }
    else
    {

        //Moving in MAX-HEAP


        //Only left child case and no right child
         if(N->getLeftChild() && !N->getRightChild()){


              if(N->getLeftChild()->getRightEndPoint()==INT_MIN){
                return;
              }

            if(N->getRightEndPoint() > N->getLeftChild()->getRightEndPoint() && N->getLeftChild()->getRightEndPoint() !=INT_MIN )
                {  return;  }
            else{
                int X = N->getRightEndPoint();
                N->setRightEndPoint(N->getLeftChild()->getRightEndPoint());
                N->getLeftChild()->setRightEndPoint(X);

                return;

            }

        }


        //If we control reaches here that means both left and right child are present

        if(N->getRightEndPoint() > N->getLeftChild()->getRightEndPoint() &&
            (N->getRightEndPoint() > N->getRightChild()->getRightEndPoint()  ||  N->getRightChild()->getRightEndPoint()==INT_MIN )){
             //Recursion terminating condition - MaxHeap established
                return;


        }else if (N->getRightEndPoint() > N->getLeftChild()->getRightEndPoint()
                  &&  N->getRightEndPoint() < N->getRightChild()->getRightEndPoint()
                  &&  N->getRightChild()->getRightEndPoint()!=INT_MIN){
            //Move down from right child
            // swap first rightchild's rightend point with N's rightEP


            int X = N->getRightEndPoint();
            N->setRightEndPoint(N->getRightChild()->getRightEndPoint());
            N->getRightChild()->setRightEndPoint(X);

            moveDown(N->getRightChild(), f);


        }
        else if (N->getRightEndPoint() < N->getLeftChild()->getRightEndPoint()
                 && N->getLeftChild()->getRightEndPoint()!=INT_MIN
                  &&  (N->getRightEndPoint() > N->getRightChild()->getRightEndPoint()
                        ||  N->getRightChild()->getRightEndPoint()  ==INT_MIN)  ){




            int X = N->getRightEndPoint();
            N->setRightEndPoint(N->getLeftChild()->getRightEndPoint());
            N->getLeftChild()->setRightEndPoint(X);

            moveDown(N->getLeftChild(), f);


        }else{
        // when N-rightEndpoint less than both leftchild and rightchilds leftEP's

        //Choose max of leftchild and rightchilds leftEP's and go in that direction
            if(N->getLeftChild()->getRightEndPoint() >  N->getRightChild()->getRightEndPoint()
               && N->getLeftChild()->getRightEndPoint()!=INT_MIN){

                    int X = N->getRightEndPoint();
                    N->setRightEndPoint(N->getLeftChild()->getRightEndPoint());
                    N->getLeftChild()->setRightEndPoint(X);

                    moveDown(N->getLeftChild(), f);


            }else{


                int X = N->getRightEndPoint();
                N->setRightEndPoint(N->getRightChild()->getRightEndPoint());
                N->getRightChild()->setRightEndPoint(X);

                moveDown(N->getRightChild(), f);



            }

        }

    }

}


int removeMin(){

     bool f= InMinHeap;
    //CASE - 1 : 0 elements in interval heap - Empty Interval heap
    if(this->root==NULL){
        cout<<"\nDeletion Failed - Heap Empty\n";
        return INT_MIN;
    }

    //CASE - 2 When only root node present
    if(root->getLeftChild()==NULL && root->getRightChild()==NULL){

         //cout<<"\nDelete CASE -2 When only root node present \n";

        //If only root node present -> min element will always at leftEndpoint
        //there may be right endpoint without a leftEndpoint - when we performed  remove min twice on interval heap when root is the only node

        //CASE : when both leftEP and rightEP are present
        //Just return leftEP and No change in deque and root deletion is not required
        if(root->getLeftEndPoint()!=INT_MIN && root->getRightEndPoint()!=INT_MIN){
            int del_ele = root->getLeftEndPoint();
            root->setLeftEndPoint(INT_MIN);
            return del_ele;

        }
        //CASE : when only rightEP is present
        //return rightEP
        //set root to null and lastnode to null
        //also remove root from deque
        else if(root->getLeftEndPoint()==INT_MIN && root->getRightEndPoint()!=INT_MIN){
            int del_ele = root->getRightEndPoint();
            root->setRightEndPoint(INT_MIN);
            q.pop_back();
            delete root;
            root =NULL;
            //delete lastNode; -> not reuired as deleted this node while calling delete root
            lastNode =NULL;

            return del_ele;
        }
        else{
            //CASE : when only leftEP is present
            //return leftEP
            //set root to null and lastnode to null
            //also remove root from deque

            int del_ele = root->getLeftEndPoint();
            root->setLeftEndPoint(INT_MIN);
            q.pop_back();
            delete root;
            root =NULL;
            //delete lastNode; -> not reuired as deleted this node while calling delete root
            lastNode =NULL;

            return del_ele;




        }

        //Also there won't be any case where both leftEP and rightEP are not there..and root node exist

    }


    //--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
    // CASE - 3 When  we have more nodes apart from root node
    //--------------------------------------------------------------------------------
    //SUB - CASE - A : When last node has both rightEP and leftEP - and NO Changes are required in lastNODE pointer and queue and root pointer
    //1. Save root->LeftEP in var
    //2. Change lastNode leftEP with root->leftEP
    //3. Move down in heap until parent-> leftEP < leftChild->leftEP and  parent-> leftEP < rightChild->leftEP ..i.e. min-heap prop statisfied
    //4. Also at any point currentnode->leftEP > currentnode->rightEP  ..then swap these
    //--------------------------------------------------------------------------------

    //SUB - CASE - B: When last node has either rightEP and leftEP - and  Changes are required in lastNODE pointer and queue
    //bcoz lastNode will become empty after moving leftEP or rightEP to root node

        //Sub-sub case - a. lastNode it the only present in our deque (This situation will arise with repeated deletion)
        //In this case deletion of lastNode will make deque empty
        // But more elements are still present in our interval
        // so our deque should be loaded again with previous level elements..so that next delete or insert should work properly.....
        //after loading deque back....new lastNode will be present as last node present in deque


        //Sub- sub case b. there are other nodes in deque -> so we will just move to 2nd last element ...delete previous last element ..
        //.and mark 2nd last element of deque as our new last element

    //Following  steps will be common in both of the sub-sub cases
    //1. Save root->LeftEP in var
    //2. Swap lastNode leftEP or rightEP (whichever present)  with root->leftEP ...take care it might be possible we have to swap it with root's rightEP
    //3. Move down in heap until currentnode-> leftEP < leftChild->leftEP and  currentnode-> leftEP < rightChild->leftEP ..i.e. min-heap prop statisfied
    //4. Also at any point currentnode->leftEP > currentnode->rightEP  ..then swap these

    //--------------------------------------------------------------------------------

    //NOTE - In entire case 3 parent pointer of deleted node need to re-adjusted

    //cout<<"\nDelete CASE -3  When  we have more nodes apart from root node \n";
    if(this->lastNode->getLeftEndPoint()!=INT_MIN && this->lastNode->getRightEndPoint()!=INT_MIN){


        //SUB - CASE - A : When last node has both rightEP and leftEP - and NO Changes are required in lastNODE pointer and queue and root pointer
        // 1. Save root->LeftEP in var
        //2. Swap lastNode leftEP with root->leftEP
        //3. Move down in heap until root-> leftEP < leftChild->leftEP and  root-> leftEP < rightChild->leftEP ..i.e. min-heap prop statisfied
        //4. Also at any point currentroot->leftEP > currentroot->rightEP  ..then swap these
        //In this - parent's pointer are not required to be adjusted


        int del_ele = root->getLeftEndPoint();
        this->root->setLeftEndPoint(this->lastNode->getLeftEndPoint());
        this->lastNode->setLeftEndPoint(INT_MIN);

        moveDown(root, f);

        return del_ele;


    }
    else{

        //SUB - CASE - B: When last node has either rightEP and leftEP - and  Changes are required in lastNODE pointer and queue
        //bcoz lastNode will become empty after moving leftEP or rightEP to root node

        //Sub-sub case - a. lastNode is the only present in our deque (This situation will arise with repeated deletion)
        //In this case deletion of lastNode will make deque empty
        // But more elements are still present in our interval
        // so our deque should be loaded again with previous level elements..so that next delete or insert should work properly.....
        //after loading deque back....new lastNode will be present as last node present in deque


        //Sub- sub case b. there are other nodes in deque -> so we will just move to 2nd last element ...delete previous last element ..
        //.and mark 2nd last element of deque as our new lastNode




        //a. lastNode only present in queue (Repeated Deletion Case)
        //b. More nodes are present in queue

        //1. Save lastNode in temporary node
        //2. Remove this node from queue
        //3. Reset lastNode  to new lastElement of queue
        //4. Parent pointer reset (Check whether it is leftChild or rightChild)
        //5. Get min from root and replace it with element from previous lastNode
        //6. Delete temp node as it is no longer required
        //7. Percolate down from root
        //8. Save Parent pointer from step 4 in del_track_q
        //9. return del_ele



        IntervalHeapNode* temp = q.back(); // or this->lastNode //save lastNode or last element in deque

        //4.
        IntervalHeapNode* P = temp->getParent();
        //Check left and right of P
        if(P->getLeftChild()==temp){
            P->setLeftChild(NULL);
        }else{
             P->setRightChild(NULL);
        }


        //8. This will help us in sub-sub space a



        if(deleteTrackQ.empty() || deleteTrackQ.front()!=P)
            deleteTrackQ.push_front(P);

        if(deleteTrackQ.size()>=1 && deleteTrackQ.back()==temp){
            deleteTrackQ.pop_back();
        }


        q.pop_back();




        //SubSubCase-  a handled here
        if(q.size()==0){
           swap(q , deleteTrackQ );

        }

        this->lastNode= q.back();

        //5.
        //check whether leftEP or rightEP is present in previous lastNode ..i.e. temp
        //replace root->leftEP with it

        //save root->leftEP ..and then replace
        int del_ele = root->getLeftEndPoint();

        if(temp->getLeftEndPoint()!=INT_MIN){
           root->setLeftEndPoint(temp->getLeftEndPoint());

        }else{
            root->setLeftEndPoint(temp->getRightEndPoint());

        }

        //6.
        delete temp;
        temp=NULL;


        //7.
        moveDown(root, f);


        //Step** (updated on 22-10-2021)
        //Last Node leftEP and rightEP should be at right order
        if(lastNode->getLeftEndPoint() > lastNode->getRightEndPoint()
           && lastNode->getRightEndPoint() != INT_MIN
           && lastNode->getLeftEndPoint() != INT_MIN ){

            int X = lastNode->getLeftEndPoint();
            lastNode->setLeftEndPoint(lastNode->getRightEndPoint());
            lastNode->setRightEndPoint(X);

        }



        //9.
        return del_ele;

    }

}



int removeMax(){

    bool f= InMaxHeap;
    //CASE - 1 : 0 elements in interval heap - Empty Interval heap
    if(this->root==NULL){
        cout<<"\nDeletion Failed - Heap Empty\n";
        return INT_MIN;
    }

    //CASE - 2 When only root node present
    if(root->getLeftChild()==NULL && root->getRightChild()==NULL){

        //CASE : when both leftEP and rightEP are present
        //Just return rightEP and No change in deque and root deletion is not required
        if(root->getLeftEndPoint()!=INT_MIN && root->getRightEndPoint()!=INT_MIN){
            int del_ele = root->getRightEndPoint();
            root->setRightEndPoint(INT_MIN);
            return del_ele;

        }
        //CASE : when only rightEP is present
        //return rightEP
        //set root to null and lastnode to null
        //also remove root from deque
        else if(root->getLeftEndPoint()==INT_MIN && root->getRightEndPoint()!=INT_MIN){
            int del_ele = root->getRightEndPoint();
            root->setRightEndPoint(INT_MIN);
            q.pop_back();
            delete root;
            root =NULL;
            //delete lastNode; -> not reuired as deleted this node while calling delete root
            lastNode =NULL;

            return del_ele;
        }
        else{
            //CASE : when only leftEP is present
            //return leftEP
            //set root to null and lastnode to null
            //also remove root from deque

            int del_ele = root->getLeftEndPoint();
            root->setLeftEndPoint(INT_MIN);
            q.pop_back();
            delete root;
            root =NULL;
            //delete lastNode; -> not reuired as deleted this node while calling delete root
            lastNode =NULL;

            return del_ele;


        }

        //Also there won't be any case where both leftEP and rightEP are not there..and root node exist

    }


    //--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
    // CASE - 3 When  we have more nodes apart from root node
    //--------------------------------------------------------------------------------

    //NOTE - In entire case 3 parent pointer of deleted node need to re-adjusted

    if(this->lastNode->getLeftEndPoint()!=INT_MIN && this->lastNode->getRightEndPoint()!=INT_MIN){

        //SUB - CASE - A : When last node has both rightEP and leftEP -
        //and NO Changes are required in lastNODE pointer and queue and root pointer
        // 1. Save root->rightEP in var
        //2. Swap lastNode rightEP with root->rightEP
        //3. Move down in heap until root-> rightEP > leftChild->rightEP and  root-> rightEP > rightChild->rightEP
        // ..i.e. max-heap prop statisfied
        //4. Also at any point currentroot->leftEP > currentroot->rightEP  ..then swap these
        //In this - parent's pointer are not required to be adjusted


        int del_ele = root->getRightEndPoint();
        this->root->setRightEndPoint(this->lastNode->getRightEndPoint());
        this->lastNode->setRightEndPoint(INT_MIN);

        moveDown(root, f);

        return del_ele;


    }
    else{


        IntervalHeapNode* temp = q.back(); // or this->lastNode //save lastNode or last element in deque

        //4.
        IntervalHeapNode* P = temp->getParent();
        //Check left and right of P
        if(P->getLeftChild()==temp){
            P->setLeftChild(NULL);
        }else{
             P->setRightChild(NULL);
        }


        //8. This will help us in [sub-sub case a]

        if(deleteTrackQ.empty() || deleteTrackQ.front()!=P)
            deleteTrackQ.push_front(P);

        if(deleteTrackQ.size()>=1 && deleteTrackQ.back()==temp){
            deleteTrackQ.pop_back();
        }

        q.pop_back();


        //subsub case a handled here
        if(q.size()==0){
            swap(q , deleteTrackQ );
        }


        this->lastNode= q.back();


        //5.
        //check whether leftEP or rightEP is present in previous lastNode ..i.e. temp
        //replace root->RightEP with it

        //save root->leftRP ..and then replace
        int del_ele = root->getRightEndPoint();

        //On priority replace with temp's rightEP ..if present..otherwise leftEP

        if(temp->getRightEndPoint()!=INT_MIN){
           root->setRightEndPoint(temp->getRightEndPoint());

        }else{
            root->setRightEndPoint(temp->getLeftEndPoint());

        }

        //6.
        delete temp;
        temp=NULL;


        //7.
        moveDown(root, f);


        //Step** (updated on 23-10-2021)
        //Last Node leftEP and rightEP should be at right order
        if(lastNode->getLeftEndPoint() > lastNode->getRightEndPoint()
           && lastNode->getRightEndPoint() != INT_MIN
           && lastNode->getLeftEndPoint() != INT_MIN ){

            int X = lastNode->getLeftEndPoint();
            lastNode->setLeftEndPoint(lastNode->getRightEndPoint());
            lastNode->setRightEndPoint(X);

        }



        //9.
        return del_ele;

    }

}



IntervalHeapNode * insertHeap( int X){

    if (root == NULL)
    {

        IntervalHeapNode* node = new IntervalHeapNode(X);

        root = node;
        lastNode=node;
        q.push_back(node);
    }
    else
    {
         bool f; //Decide in which heap we will percolate values

        //[CASE 1]  : Insert in lastNode if it has  space - Do not disturb queue
        //otherwise [CASE -2]  create new node and add it to queue

        if(this->lastNode->getLeftEndPoint()!=INT_MIN &&  this->lastNode->getRightEndPoint()==INT_MIN) {



                //Step 1. Compare new element X and leftEndPoint to decide which one of them will go in min heap and max heap
                if(this->lastNode->getLeftEndPoint() < X){
                    this->lastNode->setRightEndPoint(X);
                    f=InMaxHeap;
                }
                else
                {
                    int l = this->lastNode->getLeftEndPoint();
                    this->lastNode->setLeftEndPoint(X);
                    this->lastNode->setRightEndPoint(l);
                    f=InMinHeap;


                }
        }
        else if(this->lastNode->getLeftEndPoint()==INT_MIN &&  this->lastNode->getRightEndPoint()!=INT_MIN) {


                //Step 1. Compare new element X and leftEndPoint to decide which one of them will go in min heap and max heap
                if(this->lastNode->getRightEndPoint() > X){
                    this->lastNode->setLeftEndPoint(X);
                    f=InMinHeap;

                }
                else
                {
                    int r = this->lastNode->getRightEndPoint();
                    this->lastNode->setRightEndPoint(X);
                    this->lastNode->setLeftEndPoint(r);
                    f=InMaxHeap;
                }
        }
        else
        {


            lastNode =new  IntervalHeapNode(X);

            //CORNER CASE
            //Decide whether X should be stay in MIN-HEAP or MAX-HEAP based on parent-node (i.e Q.front ) left -endpint and right-endpoint

            if(X>q.front()->getRightEndPoint()){
                lastNode =new  IntervalHeapNode(INT_MIN, X);  //insert X as right-endpoint
                 f=InMaxHeap;
            }else{
                lastNode =new  IntervalHeapNode(X);  //insert X as left end point
                 f=InMinHeap;
            }



            // The left child of the current Node is
            // used if it is available.
            if (q.front()->getLeftChild() == NULL)
                {
                q.front()->setLeftChild(lastNode);
                lastNode->setParent(q.front());


                }
            // The right child of the current Node is used
            // if it is available. Since the left child of this
            // node has already been used, the Node is popped
            // from the queue after using its right child.
            else {
                q.front()->setRightChild(lastNode);
                 lastNode->setParent(q.front());
                q.pop_front();
            }

            // Whenever a new Node is added to the tree, its
            // address is pushed into the queue.
            // So that its children Nodes can be used later.
            q.push_back(lastNode);


        }

        BubbleUp(lastNode, f);


    }


    return root;
}



void createHeap(int arr[], int n){
    for(int i=0; i<n; i++){
            cout<<"\nProcessing element - "<<arr[i]<<"\n";
            this->root = this->insertHeap(arr[i]);

            cout<<"Interval Heap:\n";
            this->printLevelOrder(this->root);


        }

}


};

//Basic utility function for array display
void displayArray(int arr[], int n)
{
    cout<<endl;
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

}

int main(){

    IntervalHeapNode * R = NULL;
    IntervalHeap* H = new IntervalHeap (R);

    cout<<"\nInterval Heaps\n";

    cout<<"\nHow do you want to proceed?\n";
    cout<<"\n1. Pre-stored static list of elements\n";
    cout<<"\n2. User Interactive Console\n";
    cout<<"\n\nEnter your choice(1|2)\n";
    int ch;
    cin>>ch;

    if(ch==1){

        int arr []= {1, 2 , 2955, 6565, 256, 454, 945, 5454, 92955, 96565, 9256, 9454,  95453, 9545499, 2, 0, 89};

        int n = sizeof(arr)/sizeof(arr[0]);
        cout<<"\n\nStatic list of elements\n";
        displayArray(arr, n);


        cout<<"\n\nCreating Heap\n";
        H->createHeap(arr,n);

        cout<<"\n----------------------------------------------------------------------------------------------------------------------------------\n";


        cout<<"\n\nRemoving Min";
        int X_min = H->removeMin();
        cout<<"\nElement Removed - "<< X_min;
        cout<<"\nInterval Heap after removing min element\n";
        H->printLevelOrder(H->root);

        cout<<"\n----------------------------------------------------------------------------------------------------------------------------------\n";


        cout<<"\n\nRemoving Max";
        int X_max = H->removeMax();
        cout<<"\nElement Removed - "<< X_max;
        cout<<"\nInterval Heap after removing max element\n";
        H->printLevelOrder(H->root);


        cout<<"\n----------------------------------------------------------------------------------------------------------------------------------\n";

        cout<<"\n\nInserting Element : ";
        int ele = 50;
        cout<<ele;
        H->insertHeap(ele);
        cout<<"\nInterval Heap after insertion\n";
        H->printLevelOrder(H->root);



    }
    else if(ch ==2){

        int n;
        cout<<"\nEnter no. of elements to be inserted\n";
        cin>>n;

        int *arr = new int[n];
        cout<<"\nEnter elements\n";
        for(int i=0;i<n;i++){
            cout<<"\nEnter element "<<i+1<<"\n";
            cin>>arr[i];
        }

        cout<<"\n\nList of elements entered\n";
        displayArray(arr, n);

        cout<<"\n----------------------------------------------------------------------------------------------------------------------------------\n";

        cout<<"\n\nCreating Heap\n";
        H->createHeap(arr,n);

        cout<<"\n----------------------------------------------------------------------------------------------------------------------------------\n";

        cout<<"\nEnter no. of times removeMin is to be performed\n";
        int cnt_r_min;
        cin>>cnt_r_min;
        for(int i =1; i<=cnt_r_min; i++){
        cout<<"\n\n["<<i<<"] Removing Min";
        int X_min = H->removeMin();

        if(X_min==INT_MIN){
            cout<<"No Element can be removed";
        } else{
            cout<<"\nElement Removed - "<< X_min;
            cout<<"\nInterval Heap after removing min element\n";
            H->printLevelOrder(H->root);
        }

        }

        cout<<"\n----------------------------------------------------------------------------------------------------------------------------------\n";

        cout<<"\nEnter no. of times removeMax is to be performed\n";
        int cnt_r_max;
        cin>>cnt_r_max;
        for(int i =1; i<=cnt_r_max; i++){
        cout<<"\n\n["<<i<<"] Removing Max";
        int X_max = H->removeMax();

        if(X_max==INT_MIN){

            cout<<"No Element can be removed";
        }else{
            cout<<"\nElement Removed - "<< X_max;
            cout<<"\nInterval Heap after removing max element\n";
            H->printLevelOrder(H->root);
        }


        }

        cout<<"\n----------------------------------------------------------------------------------------------------------------------------------\n";


        cout<<"\n\nEnter Element to be Inserted\n";
        int ele;
        cin>>ele;
        H->insertHeap(ele);
        cout<<"\nInterval Heap after insertion\n";
        H->printLevelOrder(H->root);


        cout<<"\n----------------------------------------------------------------------------------------------------------------------------------\n";




    }else{

    cout<<"\nInvalid Choice - Execution Terminated\n";

    }


    return 0;

}


