#include<bits/stdc++.h>
using namespace std;
 #define COUNT 10



class gatorInfo
{
    public:
    int gatorID;
		string gatorName;
    gatorInfo *left;
    gatorInfo *right;
    int height;
};
 

int height(gatorInfo *root)
{
    if (root == NULL){
        return 0;
		}
    return root->height;
}
 

int max(int a, int b)
{
    return (a > b)? a : b;
}
 

gatorInfo* newGatorInfo(string gatorName,int gatorID)
{
    gatorInfo* root = new gatorInfo();
    root->gatorID = gatorID;
    root->left = NULL;
    root->right = NULL;
		root->gatorName = gatorName;
    root->height = 1; 
    return(root);
}
 

gatorInfo *rightRotate(gatorInfo *root)
{
    gatorInfo *newParent = root->left;
    gatorInfo *garndChild = newParent->right;
				/*
			Pre rotation-->
			root->val = 3, newParent->val = 2, grandChild = NULL
								root->	3
										/
			newParent	->	2	
									/		\					
								1			NULL	<- grandChild			
		*/
    newParent->right = root;
    root->left = garndChild;
		/*
				Post rotation
				newParent->val = 2, newParent->right->val = 3
							newParent->	2
												/		\
											1				3 <-root
														/
													NULL <-grandChild
			*/
    root->height = max(height(root->left),height(root->right)) + 1;
    newParent->height = max(height(newParent->left),height(newParent->right)) + 1;

    return newParent;
}
 

gatorInfo *leftRotate(gatorInfo *root)
{
    gatorInfo *newParent = root->right;
    gatorInfo *garndChild = newParent->left;
		/*
			Pre rotation
							root->	1
												\
							newParent->	2			
												/		\					
			grandChild->		NULL	   3				
		*/
  
    newParent->left = root;
    root->right = garndChild;
 
    
    root->height = max(height(root->left), height(root->right)) + 1;
    newParent->height = max(height(newParent->left),height(newParent->right)) + 1;
 
    	/*
		Post rotation
		newParent->		2
								/		\
			root->	1				3
								\
								NULL <- grandChild
		*/
    return newParent;
}
 

int getBalance(gatorInfo *root)
{
    if (root == NULL){
        return 0;
		}
    return height(root->left) - height(root->right);
}

gatorInfo* balanceTree(gatorInfo* root,int gatorID,int balance){
	// Left Left Case
		/*
		-->Left Left case
		--> fix: Rotate right
				-->root->left->val = 2
						3 <-balance =2
					/
				2	<-balance =1			-->				2 <- balance = 1- 1 = 0
			/															/		\
		1															1				3
		*/
	if (balance > 1 && gatorID < root->left->gatorID)
        return rightRotate(root);
 
    // Right Right Case
		/*
		--> Right Right case
		--> fix: Rotate 1 to left
		1 <- balance = -2
			\
				2	<- balance = -1			-->			2 <- balance = 1 - 1 = 0
					\													/		\
						3											1				3
		*/
    if (balance < -1 && gatorID > root->right->gatorID)
        return leftRotate(root);
 
    // Left Right Case
			/*
		-->Left Right case
		--> fix: 1.Rotate left
				-->root->val = 1, root->left->val = 2 
		
			3	<- balance = 2								3 <- balance = 2
		/																/
		1	<- balance = -1		--> 			2 <- balance = 1
		\														/
			2												1
		-->2. rotate righ
			-->root->val = 2
						3 <- balance = 2
					/
				2	<- balance = 1		-->			2 <- balance = 1 - 1 = 0
			/														/		\
		1														1				3
		
		*/
    if (balance > 1 && gatorID > root->left->gatorID)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Left Case
			/*
		-->Right Left case
			--> fix: 1. Rotae right
			-->root->right->val = 3
		
			1	<- balance = -2								1 <- balance = -2
				\																\
					3 <- balance = 1		--> 				2	<- balance = -1
				/																		\				
			2																				3
			-->2. Rotate left	
			-->root->val = 2, root->right->val = 3
			1	<-balance = -2
				\
					2		<- balance = -1			--> 				2 <- balance = 1 - 1 = 0
						\																/		\
							3														1				3
		*/
    if (balance < -1 && gatorID < root->right->gatorID)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 return root;
}
 

gatorInfo* insertGatorInfo(gatorInfo* root, string gatorName,int gatorID)
{
    
    if (root == NULL){
			cout<<"successful😊\n";
        return(newGatorInfo(gatorName,gatorID));
		}
		if(gatorID == root->gatorID){ 
			// Equal gatorIDs are not allowed in BST
			cout<<"successful😊\n";
        return root;
		}
				/*
		insert 1

							10
						/			\
					9					11
				/		\
			3			8



		*/
		
    if (gatorID < root->gatorID){
        root->left = insertGatorInfo(root->left,gatorName, gatorID);
		}
				/*
		insert 12

							10
						/			\
					9					11
				/		\
			1			8



		*/
    if (gatorID > root->gatorID){
        root->right = insertGatorInfo(root->right,gatorName, gatorID);
		}
		
    root->height = 1 + max(height(root->left),height(root->right));

    int balance = getBalance(root);
 
    root = balanceTree(root,gatorID,balance);
   
    return root;
}


void print2DUtil(gatorInfo *root, int space)
{
   
    if (root == NULL)
        return;
 
 
    space += COUNT;
 
 
    print2DUtil(root->right, space);
 
 
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->gatorName<<"\n";
 
   
    print2DUtil(root->left, space);
}
 

void print2D(gatorInfo *root)
{
   
    print2DUtil(root, 0);
}

 int searchGatorName(gatorInfo *root, const string& k) {
    if (root == NULL){
        return 0;
		}
		searchGatorName(root->left,k);
    if (k == root->gatorName){

				cout <<root->gatorID<<"\n";
				
        
		}
		searchGatorName(root->right,k);

		return 1;
		
}

gatorInfo* minValueNode(gatorInfo* node)
{
    gatorInfo* current = node;
 
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}


gatorInfo* deleteGatorID(gatorInfo* root, int gatorID)
{
      if (root == NULL)
        return root;
 
    // If the key to be deleted is
    // smaller than the root's
    // key, then it lies in left subtree
    if (gatorID < root->gatorID)
        root->left = deleteGatorID(root->left, gatorID);
 
    // If the key to be deleted is
    // greater than the root's
    // key, then it lies in right subtree
    else if (gatorID > root->gatorID)
        root->right = deleteGatorID(root->right, gatorID);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else {
        // node has no child
        if (root->left==NULL and root->right==NULL)
            return NULL;
       
        // node with only one child or no child
        else if (root->left == NULL) {
            gatorInfo* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            gatorInfo* temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        gatorInfo* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->gatorID = temp->gatorID;
				root->gatorName = temp->gatorName;
 
        // Delete the inorder successor
        root->right = deleteGatorID(root->right, temp->gatorID);
    }
		cout<<"successful😊\n";
    return root;
}

void searchGatorID(gatorInfo* root, int gatorID, gatorInfo* parent){
	
    if (root == NULL){
        cout << "unsuccessful🙃\n";
        return;
    }
 
    if (root->gatorID == gatorID){
        cout <<root->gatorName<< "\n";
        return;
	}
 /*
			find 10

															8
														/		\
					find this->			7				10 
												/		\			
												4		5				

		*/
    if (gatorID < root->gatorID){
      return searchGatorID(root->left, gatorID, root);
    }
		 /*
			find 10

															8
														/		\
													7				10 <- find this
												/		\			
												4		5				

		*/
    return searchGatorID(root->right, gatorID, root);
}


void printInorder(gatorInfo* root){
	if(root != NULL && root->gatorID != 0){
		printInorder(root->left);
		cout<<root->gatorName << " , ";
		printInorder(root->right);
	}
}

void printPreorder(gatorInfo* root){
	if(root != NULL && root->gatorID != 0){
		cout<<root->gatorName << " , ";
		printPreorder(root->left);
		printPreorder(root->right);
	}
}

void printPostorder(gatorInfo* root){
	if(root != NULL && root->gatorID != 0){
		printPostorder(root->left);
		printPostorder(root->right);
		cout<<root->gatorName << " , ";
	}
}


int findLevel(gatorInfo* root)
{
    if (root->left == NULL && root->right == NULL){
        return 1;
		}
 
    int left = 0;
    if (root->left != NULL){
        left = findLevel(root->left);
		}
 
    int right = 0;
    if (root->right != NULL){
        right = findLevel(root->right);
		}
 
    return (max(left, right) + 1);
}



gatorInfo* removeNthInorder(gatorInfo* root,int n,gatorInfo* temp){
 static int count = 0;
    if (root == NULL)
        return root;
 
    if (count <= n) {
 
        /* first recur on left child */
        
        count++;
 
        // when count = n then print element
        if (count == n){
						cout<<temp->gatorName<<"<--\n";
						root = deleteGatorID(root, temp->gatorID);
            return root;
				}
 
        /* now recur on right child */
        removeNthInorder(root, n,temp->right);removeNthInorder(root, n,temp->left);
    }
		return root;
}
// void removeNthInorder(gatorInfo* root,int n){
// 	gatorInfo *current, *pre;

// 	int count = 0;
 
//     if (root == NULL)
//         return ;
 
//     while (root != NULL && count < n) {
// 				count++;
//         if (current->left == NULL) {
//             cout<<current->gatorName<<"\n";
//             current = current->right;
//         }
//         else {
 
//             /* Find the inorder predecessor of current */
//             pre = current->left;
//             while (pre->right != NULL
//                    && pre->right != current)
//                 pre = pre->right;
 
//             /* Make current as the right child of its
//                inorder predecessor */
//             if (pre->right == NULL) {
//                 pre->right = current;
//                 current = current->left;
//             }
 
//             /* Revert the changes made in the 'if' part to
//                restore the original tree i.e., fix the right
//                child of predecessor */
//             else {
//                 pre->right = NULL;
// 								cout<<current->gatorName<<"\n";
                
//                 current = current->right;
//             } /* End of if condition pre->right == NULL */
//         } /* End of if condition current->left == NULL*/
//     } /* End of while */

	
// }


bool isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}




int main()
{
    // gatorInfo *root = NULL;
     
    // /* Constructing tree given in
    // the above figure */
    // root = insertGatorInfo(root, "Evan", 44985771);
    // root = insertGatorInfo(root,"Earl", 31834874);
    // root = insertGatorInfo(root,"Erica", 21456789);
		// // root = insert(root,"Carla", 56567342);
		// // root = insert(root,"Cody", 83711221);
		// root = insertGatorInfo(root,"Erica", 17449900);
    
    // print2D(root);

		// int val  = 0;
		// val = searchGatorName(root, "Erica");

		// if(val == 0){
		// 	cout<<"unsucseful\n";
		// }

		

		// print2D(root);

		// searchGatorID(root,21456789,NULL);

		// int level = findLevel(root);

		// cout<<level<<"\n";
		
    /* The constructed AVL Tree would be
                30
            / \
            20 40
            / \ \
        10 25 50
    */
    
    //   removeNthInorder(root,2);
		//  print2D(root);

		gatorInfo* root = NULL;

		int iter = 0;

		cin>> iter;


		for(int i = 0; i< iter;i++){

			string comand;

			cin>>comand;
	

			if(comand == "insert"){
				int gatorID =0;
				string gatorName;

				cin>>gatorName;

				cin>>gatorID;
				gatorName.erase(remove(gatorName.begin(),gatorName.end(),'\"'),gatorName.end());

			

				root = insertGatorInfo(root, gatorName, gatorID);
			}
			if(comand == "remove"){
				int gatorID;
				cin>>gatorID;
				
				root = deleteGatorID(root, gatorID);
				
			}

			if(comand == "search"){
				string searchThis;
				cin>>searchThis;

				searchThis.erase(remove(searchThis.begin(),searchThis.end(),'\"'),searchThis.end());

				if(isNumber(searchThis)){

				
    			stringstream convertToInt(searchThis);
 
    			
    			int x = 0;
    			convertToInt >> x;
					searchGatorID(root, x, NULL);
				}

				if(!isNumber(searchThis)){
					int val =0;
					
					val = searchGatorName(root,searchThis);

					if(val == 0){
						cout<<"unsuccessful🙃\n";
					}
					
				}

			}

			if(comand == "printLevelCount"){
			int level =	findLevel(root);

			cout<<level<<"\n";
			}

			if(comand == "removeInorder"){
				int num =0 ;
				cin>>num;
				gatorInfo* temp = new class gatorInfo;
				temp = root;
				root = removeNthInorder(root,num,temp);
			}
			if(comand == "printInorder"){
				printInorder(root);
				cout<<"\n";
			}
			if(comand == "printPreorder"){
				printPreorder(root);
				cout<<"\n";
			}
			if(comand == "printPostorder"){
				printPostorder(root);
				cout<<"\n";
			}
			if(comand == "print2D"){
				print2D(root);
			}
	}
    return 0;
}