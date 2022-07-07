#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>
struct node{
    int data;
    struct node *left;
    struct node *right;
};
struct node *tree;
void createTree(struct node *);
struct node *insertNodes(struct node *, int);
void preOrderTraversal(struct node *);
void inOrderTraversal(struct node *);
void postOrderTraversal(struct node *);
struct node *findSmallestNode(struct node *);
struct node *findLargestNode(struct node *);
bool ifNodeExistsInBST(struct node *, int);
int getMinValueOfRightSubTree(struct node *);
struct node *deleteNodeFromBST(struct node *, int);
int  totalNodeOfTheBST(struct node *);
int totalExternalNodeOfBST(struct node *);
int totalInternalNodeOfBST(struct node *);
int heightOfTeBST(struct node *);
struct node *deleteBST(struct node *);
void createTree(struct node *tree)
{
    tree =NULL;
}
struct node *insertNodes(struct node *tree, int Value)
{
    struct node *ptr, *nodePtr, *parentPtr;
    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = Value;
    ptr->left = NULL;
    ptr->right = NULL;
    if(tree==NULL)
    {
        tree = ptr;
        tree->data=Value;
        tree->left=NULL;
        tree->right=NULL;
    }
    else{
        parentPtr=NULL;
        nodePtr=tree;
        while(nodePtr!=NULL)
        {
            parentPtr=nodePtr;
            if(Value<nodePtr->data)
                nodePtr=nodePtr->left;
            else   
                nodePtr=nodePtr->right;
        }
        if(Value<parentPtr->data)
            parentPtr->left=ptr;
        else    
            parentPtr->right=ptr;
    }
    return tree;
}
void preOrderTraversal(struct node *tree)
{
    if(tree!=NULL)
    {
        printf("%d\t",tree->data);
        preOrderTraversal(tree->left);
        preOrderTraversal(tree->right);
    }
}
void inOrderTraversal(struct node *tree)
{
    if(tree!=NULL)
    {
        inOrderTraversal(tree->left);
        printf("%d\t",tree->data);
        inOrderTraversal(tree->right);
    }
}
void postOrderTraversal(struct node *tree)
{
    if(tree!=NULL)
    {
        postOrderTraversal(tree->left);
        postOrderTraversal(tree->right);
        printf("%d\t",tree->data);
    }
}
struct node *findSmallestNode(struct node *tree)
{
    if((tree==NULL) || (tree->left==NULL))
        return tree;
    else
        return findSmallestNode(tree->left);
}
struct node *findLargestNode(struct node *tree)
{
    if((tree==NULL) || (tree->right==NULL))
        return tree;
    else
        return findLargestNode(tree->right);
}
int totalNodesOfTheBST(struct node *tree)
{
    if(tree==NULL)
        return 0;
    else    
        return (totalNodesOfTheBST(tree->left))+(totalNodesOfTheBST(tree->right)+1);
}
int totalExternalNodesInTheBST(struct node *tree)
{
    if(tree==NULL)
        return 0;
    else if((tree->left==NULL)&&(tree->right==NULL))
        return 1;
    else
        return ((totalExternalNodesInTheBST(tree->left)+(totalExternalNodesInTheBST(tree->right))));
}
int totalInternalNodesInTheBST(struct node *tree)
{
    if((tree==NULL)||((tree->left==NULL)&&(tree->right==NULL)))
        return 0;
    else
        return ((totalInternalNodesInTheBST(tree->left)+(totalInternalNodesInTheBST(tree->right)+1)));
}
int heightOfTheBST(struct node *tree)
{
    int leftHeightOfTheBST, rightHeightOfTheBST;
    if(tree==NULL)
        return 0;
    else{
        leftHeightOfTheBST = heightOfTheBST(tree->left);
        rightHeightOfTheBST = heightOfTheBST(tree->right);
        if(leftHeightOfTheBST > rightHeightOfTheBST)
            return(leftHeightOfTheBST+1);
        else
            return(rightHeightOfTheBST+1);
    }
}
int getMinValueOfRightSubTree(struct node *tree)
{
    struct node *storeMinValue;
    storeMinValue = tree;
    while(storeMinValue->left != NULL)
    {
        storeMinValue = storeMinValue->left;
    }
    return storeMinValue->data;
}
bool ifNodeExistsInBST(struct node *tree, int Value)
{
    if(tree ==NULL)
        return false;
    if(tree->data==Value)
        return true;
    bool checkOnLeftSubTree =ifNodeExistsInBST(tree->left, Value);
    if(checkOnLeftSubTree)
        return true;
    bool checkOnTheRightSubtree = ifNodeExistsInBST(tree->right, Value);
        return checkOnTheRightSubtree;
}
struct node *deleteNodeFromBST(struct node *tree, int Value)
{
    if(tree == NULL)
        return tree;
    /*
     * If tree->data < Value. Value must be present in the right subtree
     * So, call the above remove function with tree->right
     */
    if(tree->data < Value)
        tree->right = deleteNodeFromBST(tree->right,Value);
    /*
     * if tree->data > Value. Value must be present in the left subtree
     * So, call the above function with tree->left
     */
    else if(tree->data > Value)
        tree->left = deleteNodeFromBST(tree->left,Value);
    /*
     * This part will be executed only if the tree->data == Value
     * The actual remoValue starts from here
     */
    else
    {
        /*
         * Case 1: Leaf node. Both left and right reference is NULL
         * replace the node with NULL by returning NULL to the calling pointer.
         * free the node
         */
        if(tree->left == NULL && tree->right == NULL)
        {
            free(tree);
            return NULL;
        }
        /*
         * Case 2: Node has right child.
         * replace the tree node with tree->right and free the right node
         */
        else if(tree->left == NULL)
        {
            struct node *temp = tree->right;
            free(tree);
            return temp;
        }
        /*
         * Case 3: Node has left child.
         * replace the node with tree->left and free the left node
         */
        else if(tree->right == NULL)
        {
            struct node *temp = tree->left;
            free(tree);
            return temp;
        }
        /*
         * Case 4: Node has both left and right children.
         * Find the min Value in the right subtree
         * replace node Value with min.
         * And again call the remove function to delete the node which has the min Value.
         * Since we find the min Value from the right subtree call the remove function with tree->right.
         */
        else
        {
            int rightMin = getMinValueOfRightSubTree(tree->right);
            tree->data = rightMin;
            tree->right = deleteNodeFromBST(tree->right,rightMin);
        }
    }
    //return the actual tree's address
    return tree;
}
struct node *deleteBST(struct node *tree)
{
    if(tree!= NULL)
    {
        deleteBST(tree->left);
        deleteBST(tree->right);
        free(tree);
    }
}
int main()
{
    int choice, Value;
    struct node *ptr;
    createTree(tree);
    do{
        printf("\n-----------Binary Search Tree Operations-----------\n");
        printf("1. Insert Element In The BST.\n");
        printf("2. Display Pre Order Traversal Of BST.\n");
        printf("3. Display In Ordet Traversal Of BST.\n");
        printf("4. Display Post Order Traversal Of BST.\n");
        printf("5. Display The Smallest Element In BST.\n");
        printf("6. Display The Largest Element In BST.\n");
        printf("7. Display The Total Nodes Of BST.\n");
        printf("8. Display The Total External Nodes Of BST.\n");
        printf("9. Display The Total Internal Nodes Of BST.\n");
        printf("10. Display The Height Of The BST.\n");
        printf("11. Check The Node Present In The BST or NOT.\n");
        printf("12. Delete A Node From BST.\n");
        printf("13. Delete The Binary Search Tree.\n");
        printf("14. Exit The Program.\n\n");
        printf("Enter Your Choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            printf("\nEnter The New Element To Insert : ");
            scanf("%d",&Value);
            tree=insertNodes(tree, Value);
            break;
            case 2:
            printf("\nDisplaying Pre Order Traversal Of BST : ");
            preOrderTraversal(tree);
            break;
            case 3:
            printf("\nDisplaying In Order Traversal Of BST : ");
            inOrderTraversal(tree);
            break;
            case 4:
            printf("\nDisplaying Post Order Traversal Of BST  : ");
            postOrderTraversal(tree);
            break;
            case 5:
            ptr = findSmallestNode(tree);
            printf("\nThe Smallest Element In BST : %d\n",ptr->data);
            break;
            case 6:
            ptr = findLargestNode(tree);
            printf("\nThe Largest Element In BST : %d\n",ptr->data);
            break;
            case 7:
            printf("\nThe Total Nodes In BST are : %d\n",totalNodesOfTheBST(tree));
            break;
            case 8:
            printf("\nThe Total External Nodes In The BST are : %d\n",totalExternalNodesInTheBST(tree));
            break;
            case 9:
            printf("\nThe Total Internal Nodes In The BST are %d\n",totalInternalNodesInTheBST(tree));
            break;
            case 10:
            printf("\nThe Height Of The BST is : %d\n",heightOfTheBST(tree));
            break;
            case 11:
            printf("\nEnter The Node Value To Check The Existence : ");
            scanf("%d",&Value);
            if(ifNodeExistsInBST(tree, Value))
                printf("\nYes %d Is Present In BST.\n");
            else
                printf("\nNo, It Is Not Present.\n");
            break;
            case 12:
            printf("\nEnter The Node Value To Delete : ");
            scanf("%d",&Value);
            if(ifNodeExistsInBST(tree,Value)){
                tree=deleteNodeFromBST(tree, Value);
                printf("%d Deleted Successfully..\n",Value);
            }
            else
                printf("\nThis Node Is Not Present In The BST.\n");
            break;
            case 13:
            tree=deleteBST(tree);
            break;
        }
    }while(choice!=14);
        getch();
        return 0;
}