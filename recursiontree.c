#include<stdio.h>
#include<stdlib.h>


struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
};
struct node *deleteNode (struct node *root, int key);
struct node* successor( struct node *root);
struct node * search(int value, struct node *root);
struct node * lowest(struct node *root);


int max(int a, int b);


int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}


int max(int a, int b)
{
    return (a > b)? a : b;
}


struct node* newNode(int key)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    
    x->right = y;
    y->left = T2;

    
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;


    return x;
}

struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    
    y->left = x;
    x->right = T2;

    
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    
    return y;
}


int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, int key)
{
    
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    
    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);

    
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }


    return node;
}

 


void preOrder(struct node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
void postOrder(struct node *root)
{
    if(root==NULL){
        return;
    }
   
    postOrder(root->left);
    postOrder(root->right);
     printf("%d ",root->key);

}
void inOrder(struct node *root)
{
    if(root==NULL){
        return;
    }
   
    inOrder(root->left);
    printf("%d ",root->key);
    inOrder(root->right);
     
}


int main()
{
  struct node *root = NULL;

  
    root = insert(root, 8);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 9);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);



    printf("Pre order traversal of the constructed AVL tree is \n");
    preOrder(root);
     printf("\nPost order traversal of the constructed AVL tree is \n");
    postOrder(root);
     printf("\nIn order traversal of the constructed AVL tree is \n");
    inOrder(root);

    root = deleteNode(root, 10);

    

    printf("\nPre order traversal after deletion of 10 \n");
    preOrder(root);
    printf("\nPost order traversal after deletion of 10 \n");
    postOrder(root);

printf("\nIn order traversal after deletion of 10 \n");
    inOrder(root);


    return 0;
}

struct node *deleteNode (struct node *root, int key)
{  

    struct node *remove_node;
    if (root == NULL){
        return root;
    }

    if ( key < root->key) {
        root->left = deleteNode(root->left, key);

    } else if ( key > root->key) {
        root->right = deleteNode(root->right,key);

    } else {

        if ((root->left == NULL) && (root->right != NULL)){
            remove_node = root->right;
            *root = *remove_node;
            free(remove_node); // this is for free-ing the memory

        } else if ((root->right == NULL)  && (root->left != NULL)){
            remove_node = root->left;
            *root = *remove_node;
            free(remove_node);

        } else if ((root->right == NULL)  && (root->left == NULL)){
            remove_node = root;
            root = NULL;

        } else {

            remove_node = successor(root);
            root->key = remove_node->key;
            root->right = deleteNode(root->right, remove_node->key);
        }
    }

    if (root == NULL) {
        return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    
    int balance = getBalance(root);

    
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
}
struct node* successor( struct node *root) {
	struct node* vij = search(root->key ,root);
	
	if(vij == NULL) {
		return NULL;
	}
	
	return lowest(vij->right);
	
}
struct node * search(int value, struct node *root) {
	if (root == NULL) {
		return NULL;
	}
	
	if(root->key == value) {
		return root;
	} else if (root->key > value) {
		return search(value, root->left); 
	} else {
		return search(value, root->right);
	}
}

struct node * lowest(struct node *root) {
	if (root == NULL) {
		return NULL;
	}
	
	
	if (root->left == NULL) {
		return root;
	}
	
	return lowest(root->left);
}


