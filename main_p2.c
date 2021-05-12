#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<limits.h>

/************************************* Addition and Multiplication of 2 bivariate polynomial  ********************************************/


// a structure, which include 3 data values and 2 pointers.
struct node{
int pow_x;
int pow_y;
float coe;
struct node* prev;
struct node* next;

};
void add_node(struct node*);
struct node* head=NULL;  //using global head.
struct node* temp;

/**************** Multiplication ************************/

struct node* mul_poly(struct node* pt3,struct node* pt4)
{


    struct node *newnode;
    struct node* start;
    start=pt3;

  while(pt4!=NULL)
  {
    pt3=start;
     while(pt3!=NULL)                             //for pt4, i am looping to whole pt3 and then calling add node .
    {
        newnode = (struct node*) malloc(sizeof(struct node));
        newnode->pow_x= (pt3->pow_x + pt4->pow_x);
        newnode->pow_y= (pt3->pow_y + pt4->pow_y);
        newnode->coe= (pt3->coe * pt4->coe);
        newnode->next=NULL;
        newnode->prev=NULL;
        pt3=pt3->next;
        add_node(newnode);

    }
    pt4=pt4->next;                               //incrementing pt4
  }

 return head;                                   //returning the head of final multiplied polynomial.
};


/********************** Addition *************************///

struct node* add_poly(struct node* pt1,struct node* pt2)
{
    struct node* poly;
    struct node *temp;
    poly = (struct node*)malloc(sizeof(struct node)); //allocating new memory to the node , so that we can later add this node to linked list

   head=poly;                                         //making the node as head ,that is adding our node to linked list

                                                      //NOTE; here i could have used add_node function directly as i did in multiplication .

  while(pt1!=NULL && pt2 !=NULL ) //checking if both of the linked list(polynomial) is non empty.
  {

      if((pt1->pow_x +pt1->pow_y)>(pt2->pow_x +pt2->pow_y))
      {

             poly->pow_x = pt1->pow_x;  //storing data in our newly created variable i.e poly
             poly->pow_y = pt1->pow_y;
             poly->coe = pt1->coe;
             pt1 = pt1->next;

      }
       else if((pt1->pow_x +pt1->pow_y)<(pt2->pow_x +pt2->pow_y))
       {
            poly->pow_x = pt2->pow_x;
             poly->pow_y = pt2->pow_y;
             poly->coe = pt2->coe;
             pt2 = pt2->next;

       }
       else
       {
           if(pt1->pow_x > pt2->pow_x)
           {
               poly->pow_x = pt1->pow_x;
               poly->pow_y = pt1->pow_y;
               poly->coe = pt1->coe;
               pt1 = pt1->next;

           }
           else if(pt1->pow_x < pt2->pow_x)
           {
               poly->pow_x = pt2->pow_x;
               poly->pow_y = pt2->pow_y;
               poly->coe = pt2->coe;
               pt2 = pt2->next;

           }
           else
           {
               poly->pow_x = pt2->pow_x;
               poly->pow_y = pt2->pow_y;
               poly->coe = (pt1->coe + pt2->coe);
               pt1=pt1->next;
               pt2 = pt2->next;

           }

       }



       // Dynamically create new node ,creating next node of poly and then incrementing poly to next (linked list)
        poly->next= (struct node*)malloc(sizeof(struct node));
        temp=poly;
        poly = poly->next;
        poly->next = NULL;

   }



   while (pt1!=NULL || pt2!=NULL) //checking if any one of the polynomial become empty , so that we can directly copy the other polynomial in the final linked list
        {
        if (pt1!=NULL) {
             poly->pow_x = pt1->pow_x;
             poly->pow_y = pt1->pow_y;
             poly->coe = pt1->coe;
             pt1 = pt1->next;

        }
        if (pt2!=NULL) {
              poly->pow_x = pt2->pow_x;
               poly->pow_y = pt2->pow_y;
               poly->coe = pt2->coe;
               pt2 = pt2->next;

        }

        // Dynamically create new node
        poly->next = (struct node*)malloc(sizeof(struct node));
        temp=poly;
        poly = poly->next;
        poly->next = NULL;

    }
    temp->next=NULL;

return head; //returning head of final polynomial(addition)

}

//For Traversing a linked list
void Traverse(struct node* x)
{
    struct node *temp;

    if(x== NULL)
    {
        printf("List is empty.");
        return;
    }

    temp = x;
    while(temp!= NULL)
    {

        printf("(%d, ", temp->pow_x); // Print data of current node
        printf("%d, ", temp->pow_y);
        printf("%.2f) -> ", temp->coe);
        temp = temp->next;
    }
}

/***************** The below function performs Addition of newnode in linked list + sorting at the same time *************************////

//this add function do 2 things , it adds the node in the linked list in sorted order.so everytime  i get a whole node , i call add_node function.


void add_node(struct node* newnode)
{
    if(head==NULL)  //if we don't have any node in linked list ,then we will make our new node as head.
    {
        head=newnode;

    }
    else if(head->next==NULL)  // if linkedlist is not empty and its next points to null, then i am updating the newnode position either on left or right(whichever is sorted position).
    {
        if((head->pow_x+head->pow_y) > (newnode->pow_x+newnode->pow_y) || ((head->pow_x+head->pow_y==newnode->pow_x+newnode->pow_y)&&(head->pow_x >newnode->pow_x)))
        {
           head->next=newnode;
           newnode->prev=head;
        }
        else if(((newnode->pow_x+newnode->pow_y== head->pow_x+head->pow_y) &&(head->pow_x ==newnode->pow_x))) // this is when both nodes have same values but different coefficient, then simply adding the coefficient.
        {
               head->coe+=newnode->coe;

        }
        else
        {
            newnode->next=head;
            head->prev=newnode;
            head=newnode;
        }

    }
    else if(head->next!=NULL && ((head->pow_x+head->pow_y < newnode->pow_x+newnode->pow_y) || ((head->pow_x+head->pow_y==newnode->pow_x+newnode->pow_y)&&(head->pow_x <newnode->pow_x))) )
    {
        newnode->next=head;
        head->prev=newnode;
        head=newnode;

    }

    else
    {
       temp=head;

       while (temp->next != NULL && ((newnode->pow_x + newnode->pow_y < temp->pow_x+temp->pow_y) || ((newnode->pow_x + newnode->pow_y == temp->pow_x+temp->pow_y) && (newnode->pow_x<temp->pow_x) ) ))
       {
           temp=temp->next;
       }

       if(temp->next==NULL)
       {

           if((newnode->pow_x+newnode->pow_y < temp->pow_x+temp->pow_y) || ((newnode->pow_x+newnode->pow_y== temp->pow_x+temp->pow_y) &&(temp->pow_x>newnode->pow_x)))
           {
               temp->next=newnode;
               newnode->prev=temp;
           }

           else if(((newnode->pow_x+newnode->pow_y== temp->pow_x+temp->pow_y) &&(temp->pow_x ==newnode->pow_x)))
           {
               temp->coe+=newnode->coe;

           }
           else
           {
                struct node *prevnode = temp -> prev;
                struct node *nextnode = temp;
                newnode->next = nextnode;
                newnode->prev = prevnode;
                nextnode->prev = newnode;
                prevnode->next = newnode;

           }
       }
       else if(((newnode->pow_x+newnode->pow_y== temp->pow_x+temp->pow_y) &&(temp->pow_x ==newnode->pow_x)))
        {
               temp->coe+=newnode->coe;
        }

        else
        {
            struct node *prevnode = temp -> prev;
            struct node *nextnode = temp;
            newnode->next = nextnode;
            newnode->prev = prevnode;
            nextnode->prev = newnode;
            prevnode->next = newnode;
        }
    }

}

/***************Fetch function to fetch elements and return ****************************/

//This fetch function will read the characters one by one and will return to the poly input function.

float fetch()
{
    float sign=1;
    char ch=getchar();
    float num=0;

    if(ch=='-') //to handle the condition for negative input
    {
         sign=-1 ;
         ch=getchar();
    }
    else{ sign=1;}


    float x;
    int count=1;
    while(ch!=',' && ch!=')')
    {

       if(ch=='.')            //this ise done so that whenever '.' occurs, then we will find the decimal value
       {

          x=fetch();          //recursive call of fetch, so that we will get the value after decimal.
          int y=(int)x;

          while(y!=0)         //implemented power function, to calculate the decimal position
          {

              y=y/10;
              count*=10;        // incrementing the count , so that later we will get to know, the number of digits after decimal.

          }
           x=x/count;

           num=num+x;

           num*=sign;         // at last updating the num value with the sign, so that if negative number will be handled.

           return num;

       }
       else
      {
        num=num*10+((int)ch-'0');      //here updating the value of num
        ch=getchar();


       }

    }
    num=num*sign;




 return num;
}

/*********************Poly_input function for fetching the values and then adding it to node****************************************/


struct node* poly_input()
{
    while(1)
    {
       char ch=getchar();

       if(ch=='(') //if first character is '(' then we will start reading a particular node.(a node consist of 3 values and 2 pointers.
       {
           int a=(int)fetch();
           int b=(int)fetch();
           float c=fetch();


          //Creating the node to store all 3 fetched value ,so now we will add this node to linked list
           struct node* newnode;
           newnode = (struct node*) malloc(sizeof(struct node)); //memory allocated to node
           newnode->pow_x=a;
           newnode->pow_y=b;
           newnode->coe=c;
           newnode->prev=NULL;
           newnode->next=NULL;

           add_node(newnode);   //This function is used to add the node in linked list with a head ,and also it sorts the node in descending order.

       }
       if(ch==',') continue; //if we get comma ,then we will continue to our loop.
       if(ch=='\n') break; //This condition is used so that whenever user hit enter ,and after reading enter we will break.


    }
    return head;

}


/******************************* Main function **************************************/

int main()
{
   char op;
   char t ='y';

do
{

   head=NULL;
   printf("\nEnter first polynomial A:\n");
   poly_input();

   struct node* ptr1=head;

   head=NULL; //Making Head NULL after storing head in ptr1, as i am using a global head so using it again and again for other purpose

   printf("\nEnter second polynomial B:\n");
   poly_input();
   struct node* ptr2=head;

   head=NULL; //Making Head NULL after storing head in ptr1, as i am using a global head so using it again and again for other purpose

   //Traversing both polynomial input by user ,and checking if sorting works correctly or not .
   // Note: sorting is done on every node insertion

   printf("\n\n");

   //pointers to store the final head of multiplication and addition linked list.
   struct node* ptr4;
   struct node* ptr3;

   printf("\nPlease enter the operator(+/*): ");
   op=getchar();

   if(op=='+')
   {
       head=NULL;
       ptr3=add_poly(ptr1,ptr2); //add poly will return the head,which is stored in ptr3 and later the head is updated to NULL.(as i am using global head).

       printf("\n\nA+B:  ");

       Traverse(ptr3);


   }
   else if(op=='*')
   {
       head=NULL;
       ptr4=mul_poly(ptr1,ptr2);

       printf("\n\nA*B:  ");
       Traverse(ptr4);

    }

    printf("\n\nDo you want to continue? (y/n):\n");
    scanf(" %c",&t);
    getchar();
    ptr1=NULL;
    ptr2=NULL;
}while(t!='n');


  return 0;
}



