#include <iostream>

using namespace std;

#define MAX 100

/////////////////////////////////////<------------Queue Function-------------->/////////////////////////////////////////
class Queue{
    private:
        int item[MAX];
        int rear;
        int front;
    public:
        Queue();
        void enqueue(int);
        int dequeue();
        int size();
        void display();
        bool isEmpty();
        bool isFull();
	int isrear();
	int isfront();
};

int Queue::isrear()
{return item[rear];}

int Queue::isfront()
{return item[front];}

Queue::Queue()
	{
	rear = -1;
	front = 0;
	}

void Queue::enqueue(int data)
	{
        item[++rear] = data;
	//cout << data << " enqueue from " << rear << " position" << endl;
	}

int Queue::dequeue()
	{
	//cout << "Dequeue from " << front << " position" << endl;
        return item[front++];
	}

void Queue::display()
	{
	if(!this->isEmpty())
	{
        for(int i=front; i<=rear; i++)
	cout<<item[i]<<endl;
    	}
	else
	{
        cout<<"Queue Underflow"<<endl;
    	}
	}

int Queue::size()
	{
	return (rear - front + 1);
	}

bool Queue::isEmpty()
	{
	if(front>rear)
	{
        return true;
	}
	else
	{
        return false;
	}
	}

bool Queue::isFull()
	{
	if(this->size()>=MAX)
	{
        return true;
	}
	else
	{
        return false;
	}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct tree
{
	int value;
	struct tree *left, *right;
};
typedef struct tree *TREE;

TREE root=NULL;

struct tree* cell_creation(int val)
{
	struct tree *p=(TREE)malloc(sizeof(struct tree));
	p->value=val;
	p->left=NULL;
	p->right=NULL;
	return p;
}

struct tree* BST(int arr[], int start, int end)
{
	if (start > end)
	{
		return NULL;
	}
	
	int mid = (start + end)/2;

	struct tree *root = cell_creation(arr[mid]);
	root->left =  BST(arr, start, mid-1);
	root->right = BST(arr, mid+1, end);

	return root;
}

void preorder(struct tree *root)
{
    if (root != NULL)
    {
	cout << root->value << endl;
        preorder(root->left);        
        preorder(root->right);
    }
}

bool isBST(tree* root, tree* l=NULL, tree* r=NULL)
{
	if (root == NULL)
	{
		return true;
	}
	
	if (l != NULL and root->value < l->value)
	{
		return false;
	}
	
	if (r != NULL and root->value > r->value)
	{
		return false;
	}

	return isBST(root->left, l, root) and isBST(root->right, root, r);
}

int getLevel(tree *root, int node, int level)
{
    if (root == NULL)
        return 0;
    if (root->value == node)
        return level;

    int downlevel = getLevel(root->left, node, level+1);
    if (downlevel != 0)
        return downlevel;
 
    return getLevel(root->right, node, level+1);
}

void printGivenLevel(struct tree* root, int level)
{
	if (root == NULL)
	{return;}

	if (level == 1)
	{
	cout << root->value << " ";
	}

	else if (level > 1)
	{
		printGivenLevel(root->left, level-1);
		printGivenLevel(root->right, level-1);
	}
}
struct Queue sibling;
struct Queue secondcousins;
void RemoveSibingAndSecondCousins(struct tree* root, int node, int GGF, int level)
{
	if (root == NULL)
	{return;}
	
	if (level == 4 && root->value == GGF)
	{
		if (node < root->value)
		{
			if(root->right->left->left)
			{secondcousins.enqueue(root->right->left->left->value);}
			if(root->right->left->right)
			{secondcousins.enqueue(root->right->left->right->value);}
			if(root->right->right->left)
			{secondcousins.enqueue(root->right->right->left->value);}
			if(root->right->right->right)
			{secondcousins.enqueue(root->right->right->right->value);}
			root->right=NULL;
		}
		else
		{
			if(root->left->left->left)
			{secondcousins.enqueue(root->left->left->left->value);}
			if(root->left->left->right)
			{secondcousins.enqueue(root->left->left->right->value);}
			if(root->left->right->left)
			{secondcousins.enqueue(root->left->right->left->value);}
			if(root->left->right->right)
			{secondcousins.enqueue(root->left->right->right->value);}
			root->left=NULL;
		
		}
	}

	if (level == 2)
	{
		if (root->right)
		{
			if(root->right->value == node)
			{sibling.enqueue(root->right->value);
			if(root->left)
			{sibling.enqueue(root->left->value);}
			root->left=NULL;root->right=NULL;}
		}
		if (root->left)
		{
			if(root->left->value == node)
			{sibling.enqueue(root->left->value);
			if(root->right)
			{sibling.enqueue(root->right->value);}
			root->left=NULL;root->right=NULL;}
		}
	
	}

	else if (level > 1)
	{
		RemoveSibingAndSecondCousins(root->left, node, GGF, level-1);
		RemoveSibingAndSecondCousins(root->right, node, GGF, level-1);
	}
}
struct Queue q;
int getgreatGF(struct tree *root, int target)
{
  /* base cases */
  if (root == NULL)
     return false;
 
  if (root->value == target)
     return true;
 
  /* If target is present in either left or right subtree of this node, then print this node */
  if ( getgreatGF(root->left, target) || getgreatGF(root->right, target) )
  {
    q.enqueue(root->value);
  }

}

void inorder(struct tree *root)
{
    if (root != NULL)
    {
	inorder(root->left); 
	cout << root->value << endl;       
        inorder(root->right);
    }
}

int maxDepth(struct tree* node) 
{
   if (node==NULL) 
       return 0;
   else
   {
       int lDepth = maxDepth(node->left);
       int rDepth = maxDepth(node->right);
 
       if (lDepth > rDepth) 
           return(lDepth+1);
       else return(rDepth+1);
   }
} 

int main()
{
int value=1, numbers[5000],GGFnode, node;

for (int i=0;i<5000;i++)
{
	numbers[i]=value;
	value++;
}

root = BST(numbers, 0, 5000-1);

if (isBST(root))
{
	cout << "Tree is a Binary Search Tree" << endl;
}
else
{
	cout << "Tree is not a Binary Search Tree"<< endl;
}
//inorder(root);
int c = maxDepth(root);cout << "Maximum Height of Binary Search Tree created is: " << c << endl;

cout << "Enter the node to print cousins except siblings and second cousins: ";
cin >> node;

if (node > 5000 || node < 1)
{cout << "Wrong Node Number. \nNode Number should be between 1 and 5000"; exit(0);}

int level = getLevel(root, node, 1);
getgreatGF(root, node);
cout << "Level of given Node is: " << level << endl;
for (int i=0;i<3;i++)
{GGFnode= q.dequeue();}

cout << "Level before removal of Siblings and Second Cousins: ";
printGivenLevel(root, level); cout << endl; 
RemoveSibingAndSecondCousins(root, node, GGFnode, level);
cout << "Sibling and Node: ";
while(sibling.isEmpty() != true)
{cout << sibling.dequeue() << " ";}cout << endl;
cout << "Second Cousins: ";
while(secondcousins.isEmpty() != true)
{cout << secondcousins.dequeue() << " ";}cout << endl;
cout << "Resultant level after removal of Siblings and Second Cousins: ";
printGivenLevel(root, level); cout << endl; cout << endl;
return 0;
}
