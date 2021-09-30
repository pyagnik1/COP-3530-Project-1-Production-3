#include<bits/stdc++.h>
using namespace std;
 #define COUNT 10


// An AVL tree root
class gatorInfo
{
    public:
    int gatorID;
		string gatorName;
    gatorInfo *left;
    gatorInfo *right;
    int height;
};
 
// A utility function to get maximum
// of two integers
int max(int a, int b);
 
// A utility function to get the
// height of the tree
int height(gatorInfo *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum
// of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a
   new root with the given gatorID and
   NULL left and right pointers. */
gatorInfo* newGatorInfo(string gatorName,int gatorID)
{
    gatorInfo* root = new gatorInfo();
    root->gatorID = gatorID;
    root->left = NULL;
    root->right = NULL;
		root->gatorName = gatorName;
    root->height = 1; // new root is initially
                      // added at leaf
    return(root);
}
 
// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
gatorInfo *rightRotate(gatorInfo *y)
{
    gatorInfo *x = y->left;
    gatorInfo *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
    // Return new root
    return x;
}
 
// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
gatorInfo *leftRotate(gatorInfo *x)
{
    gatorInfo *y = x->right;
    gatorInfo *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = max(height(x->left),   
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of root N
int getBalance(gatorInfo *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

gatorInfo* balanceTree(gatorInfo* root,int gatorID,int balance){
	// Left Left Case
	if (balance > 1 && gatorID < root->left->gatorID)
        return rightRotate(root);
 
    // Right Right Case
    if (balance < -1 && gatorID > root->right->gatorID)
        return leftRotate(root);
 
    // Left Right Case
    if (balance > 1 && gatorID > root->left->gatorID)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Left Case
    if (balance < -1 && gatorID < root->right->gatorID)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 return root;
}
 
// Recursive function to insert a gatorID
// in the subtree rooted with root and
// returns the new root of the subtree.
gatorInfo* insert(gatorInfo* root, string gatorName,int gatorID)
{
    /* 1. Perform the normal BST insertion */
    if (root == NULL)
        return(newGatorInfo(gatorName,gatorID));
 
    if (gatorID < root->gatorID)
        root->left = insert(root->left,gatorName, gatorID);
    else if (gatorID > root->gatorID)
        root->right = insert(root->right,gatorName, gatorID);
    else // Equal gatorIDs are not allowed in BST
        return root;
 
    /* 2. Update height of this ancestor root */
    root->height = 1 + max(height(root->left),
                        height(root->right));
 
    /* 3. Get the balance factor of this ancestor
        root to check whether this root became
        unbalanced */
    int balance = getBalance(root);
 
    // If this root becomes unbalanced, then
    // there are 4 cases
 
    
    root = balanceTree(root,gatorID,balance);
    /* return the (unchanged) root pointer */
    return root;
}


void print2DUtil(gatorInfo *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current root after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->gatorName<<"\n";
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(gatorInfo *root)
{
    // Pass initial space count as 0
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
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}
 
/* Given a binary search tree and a key, this function
deletes the key and returns the new root */
gatorInfo* deleteGatorID(gatorInfo* root, int key)
{
    // base case
    if (root == NULL)
        return root;
 
    // If the key to be deleted is
    // smaller than the root's
    // key, then it lies in left subtree
    if (key < root->gatorID)
        root->left = deleteGatorID(root->left, key);
 
    // If the key to be deleted is
    // greater than the root's
    // key, then it lies in right subtree
    else if (key > root->gatorID)
        root->right = deleteGatorID(root->right, key);
 
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
        root = temp;
 
        // Delete the inorder successor
        root->right = deleteGatorID(root->right, temp->gatorID);
    }
    return root;
}

void searchGatorID(gatorInfo* root, int gatorID, gatorInfo* parent){
	
    if (root == NULL){
        cout << "unsuccessful\n";
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
    if (root->left == NULL && root->right == NULL)
        return 1;
 
    int left = 0;
    if (root->left != NULL)
        left = findLevel(root->left);
 
    int right = 0;
    if (root->right != NULL)
        right = findLevel(root->right);
 
    return (max(left, right) + 1);
}
void removeNthInorder(gatorInfo* root, int target){
    static int count = 0;
    if (root == NULL)
        return;

    if (count <= target) {
        /* first recur on left child */
        removeNthInorder(root->right, target);
		
        count++;
        // when count = n then print element
        if (count == target){
            deleteGatorID(root, root->gatorID);
						return; 
				}
        /* now recur on right child */
        removeNthInorder(root->right, target);
    }

}
/*

all the function call prototypes 



*/
// Driver Code
int main()
{
    gatorInfo *root = NULL;
     
    /* Constructing tree given in
    the above figure */
    root = insert(root, "Evan", 44985771);
    root = insert(root,"Earl", 31834874);
    root = insert(root,"Erica", 21456789);
		// root = insert(root,"Carla", 56567342);
		// root = insert(root,"Cody", 83711221);
		root = insert(root,"Erica", 17449900);
    
    print2D(root);

		int val  = 0;
		val = searchGatorName(root, "Erica");

		if(val == 0){
			cout<<"unsucseful\n";
		}

		

		print2D(root);

		searchGatorID(root,21456789,NULL);

		int level = findLevel(root);

		cout<<level<<"\n";
		
    /* The constructed AVL Tree would be
                30
            / \
            20 40
            / \ \
        10 25 50
    */
    
     
    return 0;
}