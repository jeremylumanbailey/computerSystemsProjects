#include<stdio.h>
#include<stdlib.h>

struct node {
	int data;
	struct node *next, *prev;
}*head;


void append(int num) {
	struct node *temp,*right;
	temp= (struct node *)malloc(sizeof(struct node));
	temp->data=num;
	right=(struct node *)head;

	while(right->next != NULL)
		right=right->next;
    temp->prev=right;	
	right->next =temp;
	right=temp;
	right->next=NULL;
}

void add( int num ) {
	struct node *temp;
	temp=(struct node *)malloc(sizeof(struct node));
	temp->data=num;
	
	if (head== NULL) {
		head=temp;
		head->next=NULL;
        head->prev=NULL;
	}
	else {
		temp->next=head;
        temp->prev=NULL;
        head->prev=temp;
        head=temp;
	}
}

void addafter(int num, int loc) {
	int i;
	struct node *temp,*left,*right;
	right=head;

	for(i=1;i<loc;i++) {
	
        
        left=right;
        right->prev=left;
		right=right->next;
	}
	
	temp=(struct node *)malloc(sizeof(struct node));
	temp->data=num;
	left->next=temp;
    temp->prev=left;
	left=temp;
    right->prev=left;
    left->next=right;
	return;
}

void insertNorepeat(int num) {
	int c=0;
    int d = 0;
	struct node *temp;
	temp=head;
	
	if(temp==NULL) {
		add(num);
	}
	else {
		while(temp!=NULL) {

            if(temp->data=num) {
                
              d = 1;  
            }

			if(temp->data<num)
				c++;
			temp=temp->next;
		}
		
		if(c==0 && d==0)
			add(num);
		else if(c<count() && d==0)
			addafter(num,++c);
		else if(d==0)
			append(num);
    }
}

void insert(int num) {
	int c=0;
	struct node *temp;
	temp=head;
	
	if(temp==NULL) {
		add(num);
	}
	else {
		while(temp!=NULL) {
			if(temp->data<num)
				c++;
			temp=temp->next;
		}
		
		if(c==0)
			add(num);
		else if(c<count())
			addafter(num,++c);
		else
			append(num);
    }
}

void sortInsert(int num) {
	int c=0;
	struct node *temp;
	temp=head;
	
	if(temp==NULL) {
		add(num);
	}
	else {
		while(temp!=NULL) 
        {

            if(temp->data==num) {
                printf("Vale already exists");
                    return;
                    }
		
            else if(temp->data<num)
				c++;
			temp=temp->next;
		}
		
		if(c==0)
			add(num);
		else if(c<count())
			addafter(num,++c);
		else
			append(num);
    }
}


int deleteLast(int num) {

    int index=0;
        struct node *temp, *prev,*deleter, *deletelast;
        temp=head;
        while(temp!=NULL) {
            if(temp->data==num){
                deleter=temp;
            deletelast=prev;
            }

            prev=temp;

            temp=temp->next;
               } 
            if(deleter==head) {
                head=deleter->next;
                free(deleter);
                return 1;
            }
            else {
                deletelast->next=deleter->next;
                free(deleter);
                return 1;
            }
            return 0;

}

int delete(int num) {
	struct node *temp;
	temp=head;
	
	while(temp!=NULL) {
		if(temp->data==num) {
			if(temp==head) {
				head=temp->next;
                head->prev=NULL;
				free(temp);
				return 1;
			}
			else {

				temp->prev->next=temp->next;
                temp->next->prev=temp->prev;
				free(temp);
				return 1;
			}
		}
		else {
			temp->prev=temp;
			temp= temp->next;
		}
	}
	return 0;
}


int deleteIndex(int index) {
	struct node *temp;
	temp=head;
	int i;
    for(i = 0; i<index; i++) {  
			temp= temp->next;
	}
			if(temp==head) {
				head=temp->next;
                head->prev=NULL;
				free(temp);
				return 1;
			}
			else {
            
        if(temp->prev != NULL) {
				temp->prev->next=temp->next;
        }

        if(temp->next != NULL) {
                temp->next->prev=temp->prev;
        }

				free(temp);
				return 1;
			}

	return 0;
}

void  display(struct node *r) {
	r=head;

	if(r==NULL) {
		return;
	}
	
	while(r!=NULL) {
		printf("%d ",r->data);
		r=r->next;
	}
	printf("\n");
}

int count() {
	struct node *n;
	int c=0;
	n=head;
	
	while(n!=NULL) {
		n=n->next;
		c++;
	}
	return c;
}

int  main() {
	int i,num;
	struct node *n;
	head=NULL;
	
	while(1) {
		printf("\nList Operations\n");
		printf("===============\n");
		printf("1.Insert\n");
		printf("2.Display\n");
		printf("3.Size\n");
		printf("4.Delete\n");
		printf("5.Exit\n");
		printf("Enter your choice : ");
		if(scanf("%d",&i)<=0) {
			printf("Enter only an Integer\n");
			exit(0);
		} else {
			switch(i) {
				case 1:
					printf("Enter the number to insert (no duplicates) : ");
					scanf("%d",&num);
                   // if(head==NULL) {
                        insert(num);
                  //  }
                  //  else {
				//	append(num);
                 //   }
					break;
				case 2:
					if(head==NULL) {
						printf("List is Empty\n");
					}
					else {
					printf("Element(s) in the list are : ");
					}
					display(n);
					break;
				case 3:
					printf("Size of the list is %d\n",count());
					break;
				case 4:
					if(head==NULL)
						printf("List is Empty\n");
					else {
						printf("Enter the number to delete : ");
						scanf("%d",&num);
						if(deleteIndex(num))
							printf("%d deleted successfully\n",num);
						else
							printf("%d not found in the list\n",num);
					}
					break;
				case 5:
					return 0;
				default:
					printf("Invalid option\n");
			}
		}
	}
	return 0;
}
