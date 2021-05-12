#include <stdio.h>
#include <stdlib.h>
#include<limits.h>


struct node{
    int a[8];
    struct node* next;

};


struct link
{
    int value;
    struct link* next;
};

void add_n(struct link*);

struct node* head=NULL;
struct link* head1=NULL;

/*int count(struct node* ptr2)
{
    int i=0;
    int c=0;
    while(ptr2!=NULL && ptr2->a[i]!=INT_MIN)
    {
        c++;

        if((i+1)%8==0)
        {
            ptr2=ptr2->next;
            i=0;
        }
        else i++;

    }
    return c;
}*/


//this replace function will replace the pattern from the text from the required indexes.

struct node* Replace(struct node* ptr1,struct link* ptr3,struct link* ptr4,int pattern_size)
{
   struct node* head3=NULL;
   struct node * temp=(struct node*) malloc(sizeof(struct node));
   head3=temp;
   struct link* text;
   text=ptr3;



  int i=0,j=0;
  int m,s;
  int chunk2=0;
  while(ptr4!=NULL)
  {

      text=ptr3;


      m=chunk2*8+j;
      s=ptr4->value;

      while(m<s)
      {
        temp->a[i]=ptr1->a[j];
        i++;
        j++;
        m++;
        if(i%8==0)
        {
            temp->next=(struct node*) malloc(sizeof(struct node));
            temp=temp->next;
            temp->next=NULL;

            i=0;
        }
        if(j%8==0)
        {
            ptr1=ptr1->next;
            j=0;
            chunk2++;
        }

      }
      while(text!=NULL)
      {
          temp->a[i]=text->value;
          text=text->next;
          i++;
         if(i%8==0)
        {
            temp->next=(struct node*) malloc(sizeof(struct node));
            temp=temp->next;
            temp->next=NULL;
            i=0;

        }

      }
      ptr4=ptr4->next;

      j=j+pattern_size;
       if(j>=8)
            {
                int div = j/8;
                for(int f=0;f<div;f++)
                   {
                    ptr1 = ptr1->next;
                    chunk2++;

                    }
                j = (j%8);
            }

      temp->a[i]=INT_MIN;

  }
  if(ptr4==NULL)
  {
      while(ptr1->a[j]!=INT_MIN && ptr1!=NULL)
      {
         temp->a[i]=ptr1->a[j];
        i++;
        j++;
        if(i%8==0)
        {
            temp->next=(struct node*) malloc(sizeof(struct node));
            temp=temp->next;
            temp->next=NULL;
           // chunk1++;
            i=0;
        }
        if(j%8==0)
        {
            ptr1=ptr1->next;
            j=0;
            chunk2++;
        }


      }
      temp->a[i]=INT_MIN;
  }

  return head3;

}


//this function will return the total elements in linked list of type struct link*

int count(struct link* ptr2)
{
    int c=0;
    while(ptr2!=NULL && ptr2->value!=INT_MIN)
    {
        c++;
        ptr2=ptr2->next;

    }
    return c;
}


//here get index function is taking sequence and pattern address and patter size as arguemnet. later it will return a head of linked list.
//that linked  list will contain the values of index, from where pattern is matching .
// like if our seq is: 1,23,4,5,6,7,1,23  and pattern : 1,23
//then get_index function will return head of linked list containing node with value 0->6.  as one matching is from 0th index, and other matching is from 6th index.

struct link* get_index(struct node* ptr1, struct link* ptr2,int count_ele)
{
    int c = 0;
    int l = 0;
    struct node *temp1;
    struct link *temp2;

     temp1 = ptr1;
     temp2 = ptr2;

    int i=0,j,count1=0,var=0;
    int k;

    if(count_ele==0)
    {
         struct link* newnode;
         newnode = (struct link*) malloc(sizeof(struct link));
         newnode->value=0;
         newnode->next=NULL;

         add_n(newnode);
         return head1;

    }


  else{
    while(ptr1!=NULL)              //looping till my sequence becomes null
    {
       for(i=0;i<8;i++)            //for 8 elements per node.
        {
            if(ptr1->a[i]==ptr2->value)   //comparing value of pattern and sequence value.if they are equal then we will enter in f;
            {
                temp1 = ptr1;
                k = i;
                temp2 = ptr2;

                for(j=1;j<count_ele;j++)
                {
                    k=k+1;
                    temp2 = temp2->next;
                    if(k==8)
                    {
                        temp1 =temp1->next;
                        k=0;
                        if(temp1==NULL)
                            break;
                        l++;
                        var++;
                    }

                    if(temp2->value==temp1->a[k])
                    {
                        continue;
                    }

                    else
                        break;
                }
                if(ptr1!=temp1&&j!=count_ele)
                    {l=l-var;
                    count1++;}
                if(j==count_ele)
                {
                    //note i am using linked list to store the indexes.

                    int val=i+8*(c+l-var);   //this val variable contains the index of pattern ,later we will store that index in a node and will add it to linked list.
                    ptr1 = temp1;
                    i = k;
                    struct link* newnode;
                    newnode = (struct link*) malloc(sizeof(struct link));
                    newnode->value=val;
                    newnode->next=NULL;
                    //printf("%d",newnode->value);
                    add_n(newnode);    //this add node function will add the node to linked list.

                }
                var=0;
            }

        }
        c++;
        ptr1 =ptr1->next;

    }
  }
    return head1;

}


//traverse function to traverse the singly linked list of type node * . that is it contains size 8 chunks.
void Traverse(struct node* x)
{
    struct node* temp;

    if(x== NULL)
    {
        printf("List is empty.");
        return;
    }


    temp = x;
    int i=0;
    while(temp!= NULL && temp->a[i]!=INT_MIN)
    {
        i++;

           for(int k=0;k<=7;k++)
           {
               if(temp->a[k]==INT_MIN )
                 return;
               printf("%d ",temp->a[k]) ;

           }
           printf(" -> ");
           temp=temp->next;
    }

}

//traverse function to traverse the singly linked list, which of type struct *link
void Traversee(struct link* x)
{
    struct link* tem;

    if(x== NULL)
    {
        printf("List is empty.");
        return;
    }



    tem = x;
    while(tem!= NULL)
    {

           printf("%d- > ",tem->value);
           tem=tem->next;
    }
}

//this add function will add node to singly linked list of type node*. here it is inserting 8-8 chunked node in list.

  void add_node(struct node* newnode)
{
    struct node* temp;


   if(head==NULL)    //if head is null, then we will make our newnode as head.  i.e making a linked list.
   {
       head=newnode;

   }
   else
   {

       temp=head;
       while(temp->next!=NULL)
       {
           temp=temp->next;
       }

       temp->next=newnode;
   }

}
 void add_n(struct link* newnode)  //this add node function is used to add node to singly linked list. here my list if of type link.(to store only 1 element)
{
    struct link* temp;
   if(head1==NULL)
   {
       head1=newnode;

   }
   else
   {

       temp=head1;
       while(temp->next!=NULL)
       {
           temp=temp->next;
       }

       temp->next=newnode;
   }

}

char ch;

//this fetch function is used to fetch the digits (like 23 , 45 etc) and it will return the value to poly input function.
int fetch()
{

    int sign=1;
    int a=INT_MIN;
    int num=0;
    ch=getchar();
    if(ch=='-') //to handle the condition for negative input
    {
         sign=-1 ;
         ch=getchar();
    }
    else{ sign=1;}


    if(ch=='$')
    {

        return INT_MIN;
    }
    else
    {
    do
    {
        num=num*10+((int)ch-'0');
        ch=getchar();

    }while(ch!=',' &&ch!='$');

    num=num*sign;
    a=num;
    return a;
    }
}

struct link* poly_input1() //this poly input function is used to create a linked list with only 1 element in node.
 {

   while(ch!='$')         // loop till we get dollar.
   {
       int k=fetch();
       if(k==INT_MIN)
            {
                break;
            }
       struct link* newnode;                //here i created link type node.
       newnode = (struct link*) malloc(sizeof(struct link));
       newnode->value=k;
       newnode->next=NULL;
       add_n(newnode);

    }
    return head1;

}

struct node* poly_input()  //this input is used for 8 chunked linked list.(like every node will have 8 elements +2 pointers)
 {

   while(ch!='$')          //we will loop till we get '$'
   {
       int j=0;
       int b[8];
       for(int i=0;i<=7;i++)   //initializing the array b by INT_MIN
       {
           b[i]=INT_MIN;
       }
       while(j<=7)                  //this while loop will exit when either the input read is INT_MIN or untill the whole node is read.(i.e till 8 elements)
       {
            b[j]=fetch();
            if(b[j]==INT_MIN)
            {

                break;
            }

           else  j++;
       }


       if(j==0)  break;         //if there is no element to be ineserted next (i.e j=0),so we don't need to create the next node. hence break.
       else{

        //Creating the node to store all  fetched value ,so now we will add this node to linked list
           struct node* newnode;
           newnode = (struct node*) malloc(sizeof(struct node)); //memory allocated to node

           for(int k=0;k<=7;k++)  //storing value of array b into newnode's element.
           {
                newnode->a[k]=b[k];
           }

           newnode->next=NULL;
          /*  for(int k=0;k<=7;k++)
           {
               printf("%d\n",newnode->a[k]) ;
           }*/

           add_node(newnode);  //this add node function will add the newnode to the linked list(every node of linked list consists of 8 elements+2 pointers
       }

    }
    return head;     //returning head of linked list

}



int main()
{

  printf("Please enter the sequence S:");
  poly_input();                          //poly input function will read the input character by character entered by user.and later will add it to linkedlist
  struct node* ptr1=head;

  //making the  head null, as i am using global head.
  head=NULL;
  //Traverse(ptr1);
  ch=getchar();   //this getchar is used to store "enter",whenever user input sequence and then click enter, then that enter will be handled by getchar()
  char c='y';
  do
 {

  printf("\nPlease enter the pattern to be replaced:");

  poly_input1();
  struct link* ptr2=head1;
  head1=NULL;
  //Traversee(ptr2);
  ch=getchar();


  int count_ele=count(ptr2);  // this will count the number of element in pattern .
  //printf("%d",count_ele);


  printf("\nPlease enter the replacement text:");
  poly_input1();
  struct link* ptr3=head1;
  head1=NULL;
  //Traverse(ptr3);
  ch=getchar();

   struct link* ptr4;
   ptr4=get_index(ptr1,ptr2,count_ele);
  //struct link* ptr4=head1;
  //Traversee(ptr4);
  head1=NULL;

  //note: ptr1 shows sequence head, ptr2 contain pattern address, ptr3 contain the text addresss,
 //ptr4 contains the index information(matching index)


  struct node* fin;
  fin=Replace(ptr1,ptr3,ptr4,count_ele);
  Traverse(fin);   //traversing the final linked list.


  head=NULL;
  printf("\n\n Do you want to continue y/n: \n");
  c=getchar();
  getchar();   //getchar is used to handle error
  ptr1=fin;

 }
  while(c=='y');
  //Traverse(ptr1);
  //Traverse(ptr2);
  //Traverse(ptr3);
  //printf("\nAfter replacement, S:");

  return 0;

}
