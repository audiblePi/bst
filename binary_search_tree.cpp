//Binary Search Tree Program
#include <iostream>
#include <cstdlib>

using namespace std;

class Node {
    public:
        int data;
        Node* leftChild;
        Node* rightChild;
};

class Tree{
    private:
        Node* root;
    
    public:
        Tree(){
           root = NULL;
        }
        
        void display(int);
        void inOrder(Node*);
        void preOrder(Node*);
        void postOrder(Node*);
        void insert(int);
        void remove(int);
        bool isEmpty() const { return root==NULL; }
};

void Tree::display(int type){
    switch (type){
        case 1:
            inOrder(root);
            break;
        case 2:
            preOrder(root);
            break;
        case 3:
            postOrder(root);
            break;
    }
}

void Tree::inOrder(Node* node){
    if(node != NULL) {
        if(node->leftChild) inOrder(node->leftChild);
        cout<<" "<<node->data <<" ";
        if(node->rightChild) inOrder(node->rightChild);
        
    }
    else return;
}

void Tree::preOrder(Node* node){
    if(node != NULL) {
        cout<<" "<<node->data <<" ";
        if(node->leftChild) preOrder(node->leftChild);
        if(node->rightChild) preOrder(node->rightChild);
        
    }
    else return;
}

void Tree::postOrder(Node* node){
    if(node != NULL) {
        if(node->leftChild) postOrder(node->leftChild);
        if(node->rightChild) postOrder(node->rightChild);
        cout<<" "<<node->data <<" ";
    }
    else return;
}

// Smaller elements go left, larger elements go right
void Tree::insert(int d){
    Node* newNode = new Node;
    Node* parentNode;

    newNode->data = d;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    parentNode = NULL;
    
    // If Tree is empty, make the newNode the root
    if(isEmpty()){
        root = newNode;
    }
    else{
        Node* currentNode;
        currentNode = root;

        // Find the Node's parent
        while(currentNode){
            parentNode = currentNode;

            if(newNode->data > currentNode->data) 
                currentNode = currentNode->rightChild;
            else 
                currentNode = currentNode->leftChild;
        }

        //test and append newNode to its parentNode
        if(newNode->data < parentNode->data)
           parentNode->leftChild = newNode;
        else
           parentNode->rightChild = newNode;
    }
}

void Tree::remove(int key){
    bool found = false;

    if(isEmpty()){
        cout<<" This Tree is empty! "<<endl;
        return;
    }
    
    Node* currrentNode;
    Node* parentNode;
    currrentNode = root;
    
    while(currrentNode != NULL){
        if(currrentNode->data == key){
            found = true;
            break;
        }
        else{
            parentNode = currrentNode;
            if(key > currrentNode->data) 
                currrentNode = currrentNode->rightChild;
            else 
                currrentNode = currrentNode->leftChild;
        }
    }

    if(!found){
        cout<<" Data not found! "<<endl;
        return;
    }

    // 3 cases :
    // 1. We're removing a leaf node
    // 2. We're removing a node with a single child
    // 3. we're removing a node with 2 children

    // Node with single child
    if( (currrentNode->leftChild == NULL && currrentNode->rightChild != NULL) || (currrentNode->leftChild != NULL && currrentNode->rightChild == NULL)){
        if(currrentNode->leftChild == NULL && currrentNode->rightChild != NULL){
           if(parentNode->leftChild == currrentNode){
                parentNode->leftChild = currrentNode->rightChild;
                delete currrentNode;
           }
           else{
                parentNode->rightChild = currrentNode->rightChild;
                delete currrentNode;
           }
        }
        else{// left child present, no right child
            if(parentNode->leftChild == currrentNode){
                parentNode->leftChild = currrentNode->leftChild;
                delete currrentNode;
            }
            else{
                parentNode->rightChild = currrentNode->leftChild;
                delete currrentNode;
            }
        }

        return;
    }

    //We're looking at a leaf node
	if( currrentNode->leftChild == NULL && currrentNode->rightChild == NULL){
        if(parentNode->leftChild == currrentNode) 
            parentNode->leftChild = NULL;
        else 
            parentNode->rightChild = NULL;
        delete currrentNode;
        return;
    }

    //Node with 2 children
    // replace node with smallest value in right subtree
    if (currrentNode->leftChild != NULL && currrentNode->rightChild != NULL){
        Node* chkr;
        chkr = currrentNode->rightChild;

        if((chkr->leftChild == NULL) && (chkr->rightChild == NULL)){
            currrentNode = chkr;
            delete chkr;
            currrentNode->rightChild = NULL;
        }
        else{ 
            // right child has children
            //if the node's right child has a left child
            // Move all the way down left to locate smallest element
            if((currrentNode->rightChild)->leftChild != NULL){
                Node* lcurr;
                Node* lcurrp;
                lcurrp = currrentNode->rightChild;
                lcurr = (currrentNode->rightChild)->leftChild;

                while(lcurr->leftChild != NULL){
                   lcurrp = lcurr;
                   lcurr = lcurr->leftChild;
                }
                currrentNode->data = lcurr->data;
                delete lcurr;
                lcurrp->leftChild = NULL;
           }
           else{
               Node* tmp;
               tmp = currrentNode->rightChild;
               currrentNode->data = tmp->data;
	           currrentNode->rightChild = tmp->rightChild;
               delete tmp;
           }
        }
		return;
    }
}


//-------------------------------
void loadDefault(Tree* tree){
    tree->insert(8);
    tree->insert(12);
    tree->insert(4);
    tree->insert(7);
    tree->insert(5);
    tree->insert(2);
    tree->insert(6);
    tree->insert(8);
}

int main(){
    int ch,tmp,tmp1;
    Tree myTree;

    while(1){
       cout<<endl<<endl;
       cout<<" Binary Search Tree Operations "<<endl;
       cout<<" ----------------------------- "<<endl;
       cout<<" 1. Load Default Tree "<<endl;
       cout<<" 2. Insertion/Creation "<<endl;
       cout<<" 3. In-Order Traversal "<<endl;
       cout<<" 4. Pre-Order Traversal "<<endl;
       cout<<" 5. Post-Order Traversal "<<endl;
       cout<<" 6. Removal "<<endl;
       cout<<" 7. Exit \n"<<endl;
       cout<<" Enter your choice : ";
       cin>>ch;

       switch(ch){
            case 1 :
                loadDefault(&myTree);
                break;
            case 2 : 
                cout<<" Enter Number to be inserted : ";
                cin>>tmp;
                myTree.insert(tmp);
                break;
            case 3 : 
                cout<<endl;
                cout<<" In-Order Traversal "<<endl;
                cout<<" -------------------"<<endl;
                myTree.display(1);
                break;
            case 4 : 
                cout<<endl;
                cout<<" Pre-Order Traversal "<<endl;
                cout<<" -------------------"<<endl;
                myTree.display(2);
                break;
            case 5 : 
                cout<<endl;
                cout<<" Post-Order Traversal "<<endl;
                cout<<" --------------------"<<endl;
                myTree.display(3);
                break;
            case 6 : cout<<" Enter data to be deleted : ";
                cin>>tmp1;
                myTree.remove(tmp1);
                    break;
            case 7 : 
                return 0;
                    
       }
    }
}