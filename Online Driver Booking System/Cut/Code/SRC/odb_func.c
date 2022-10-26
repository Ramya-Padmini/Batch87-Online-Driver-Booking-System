/****************************************************************
 *
 * FILENAME : odb_func.c
 *
 *
 * DESCRIPTION : This file uses as functions file which contains
 *               all the functions and performs all designated
 *               tasks.
 *
 *
 * **************************************************************/


#include<stdio.h>  // Include required header files
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<ctype.h>
#include "odb_header.h"


u *start,*new,*ptr,*prev,*last;  //Declaring pointers for user structure

d *start1,*new1,*ptr1,*prev1,*last1;  //Declaring pointers for driver structure

rd *start2,*new2,*ptr2,*prev2,*last2;  //Declaring pointers for route details structure

int ctc;
int did;

/***************************************************************
 *
 * FUNCTION-NAME : user_to_list
 *
 * DESCRIPTION : This function will inesert records from user 
 *               file to user's linked list.
 *
 *
 * ************************************************************/

int user_to_list()  // Inserting records from user file to list
{
	FILE *p;  // File Pointer
	t a;
	if((p=fopen("user","rb"))==NULL) // Opening a binary file for reading
	{
		printf("\nFile is not present to read\n");
		return EXIT_FAILURE;
	}
	fread(&a,sizeof(t),1,p);//Reading file 
	while(!feof(p))
	{
		if((new=(u*)calloc(1,sizeof(u)))==NULL)  // Allocating Dynamic Memory
		{
			printf("\nMemory allocation failed\n");
			return EXIT_FAILURE;
		}
		new->uad=a.uad;
		strcpy(new->uname,a.uname);
		strcpy(new->uaddress,a.uaddress);
		new->uage=a.uage;
		// after reading data from user file, insert into the linked list
		if(!start)
		{
			start=last=new;
			new->next=NULL;
		}
		else
		{
			last->next=new;
			last=new;
			new->next=NULL;
		}
		fread(&a,sizeof(t),1,p);  // Reading file
	}
	fclose(p);  // Closing the file
	return EXIT_SUCCESS;
}


/***************************************************************
 *
 * FUNCTION-NAME : list_to_user
 *
 * DESCRIPTION : This function will ineserting the user's linked 
 *               list records to the user's file.
 *
 *
 * ************************************************************/

int list_to_user()
{
	t b;
	if(!start)//Checking if list is empty
	{
		printf("\nList is empty\n");
		return EXIT_FAILURE;
	}
	FILE *p1;//File pointer
	if((p1=fopen("user","wb"))==NULL)//Opening user file for writing
	{
		// printf("\nFile is no there to read from\n");
		return EXIT_FAILURE;
	}
	for(ptr=start;(ptr);ptr=ptr->next)
	{
		b.uad=ptr->uad;
		strcpy(b.uname,ptr->uname);
		strcpy(b.uaddress,ptr->uaddress);
		b.uage=ptr->uage;
		fwrite(&b,sizeof(t),1,p1);  // Writing in file
	}
	fclose(p1);  // Closing the file
	return EXIT_SUCCESS;
}

/***************************************************************
 *
 * FUNCTION-NAME : driver_to_list
 *
 * DESCRIPTION : This function will ineserting the driver file 
 *               records into a driver linked list
 *
 *
 * ************************************************************/

int driver_to_list()//Storing from drive's file to list
{
	FILE *q;//File pointer
	s i;
	if((q=fopen("driver","rb"))==NULL)//Opening the driver's file
	{
		//printf("\nFile is not present to read\n");
		return EXIT_FAILURE;
	}
	fread(&i,sizeof(s),1,q);//Reading file
	while(!feof(q))
	{
		if((new1=(d*)calloc(1,sizeof(d)))==NULL) // Dynamic Memory Allocation
		{
			printf("\nMemory allocation failed\n");
			return EXIT_FAILURE;
		}
		new1->dlno=i.dlno;
		strcpy(new1->nam,i.nam);
		strcpy(new1->adrs,i.adrs);
		new1->da=i.da;
		strcpy(new1->dphno,i.dphno);
		new1->uid=i.uid;
		new1->lor=i.lor;
		new1->status=i.status;	
		// after reading data from driver file, insert into the linked list
		if(!start1)
		{
			start1=last1=new1;
			new1->next1=NULL;
		}
		else
		{
			last1->next1=new1;
			last1=new1;
			new1->next1=NULL;
		}
		fread(&i,sizeof(s),1,q); // Reading file 
	}
	fclose(q); // Closing the file
	return EXIT_SUCCESS;
}

/***************************************************************
 *
 * FUNCTION-NAME : list_to_driver
 *
 * DESCRIPTION : This function will ineserting the drivers linked 
 *               list records to the driver's file.
 *
 *
 * ************************************************************/

int list_to_driver() // For inserting records from list to  driver's file
{
	s j;
	if(!start1) // Checking if the list is empty
	{
		printf("\nList is empty\n");
		return EXIT_FAILURE;
	}
	FILE *q1;   // File Pointer
	if((q1=fopen("driver","wb"))==NULL)  // Opening the binary file in write mode
	{
		// printf("\nFile is no there to read from\n");
		return EXIT_FAILURE;
	}
	for(ptr1=start1;(ptr1);ptr1=ptr1->next1)
	{
		j.dlno=ptr1->dlno;
		strcpy(j.nam,ptr1->nam);
		strcpy(j.adrs,ptr1->adrs);
		j.da=ptr1->da;
		strcpy(j.dphno,ptr1->dphno);
		j.uid=ptr1->uid;
		j.lor=ptr1->lor;
		j.status=ptr1->status;
		fwrite(&j,sizeof(s),1,q1);   // Writing in file
	}
	fclose(q1);  // Closing the file
	return EXIT_SUCCESS;	
}

/***************************************************************
 *
 * FUNCTION-NAME : report_to_list
 *
 * DESCRIPTION : This function will ineserting the report file 
 *               records into a report linked list
 *
 *
 * ************************************************************/

int report_to_list()  // For inserting records in list from report file
{
	FILE *l;  // File Pointer
	r u;
	if((l=fopen("report","rb"))==NULL)  // Opening the binary file in read mode
	{
		return EXIT_FAILURE;
	}
	fread(&u,sizeof(r),1,l);  // Reading file
	while(!feof(l))
	{
		if((new2=(rd *)calloc(1,sizeof(rd)))==NULL) // Dynamically allocating memory for new2 for list of routes
		{
			printf("\nMemory Allocation Failed\n");
			return EXIT_FAILURE;
		}
		new2->rno=u.rno;
		strcpy(new2->sp,u.sp);
		strcpy(new2->ep,u.ep);
		new2->d=u.d;
		// After reading data from file inserting into linked list
		if(!start2)
		{
			start2=last2=new2;
			new2->next2=NULL;
		}
		else
		{
			last2->next2=new2;
			last2=new2;
			new2->next2=NULL;
		}
		fread(&u,sizeof(r),1,l); //Reading file
	}
	fclose(l);   // Closing the file
	return EXIT_SUCCESS;
}

/***************************************************************
 *
 * FUNCTION-NAME : list_to_report
 *
 * DESCRIPTION : This function will inserting the report linked 
 *               list records to the report file.
 *
 *
 * ************************************************************/

int list_to_report()
{
	r v;
	if(!start2) // Checking if the list is empty
	{
		printf("\nList is empty\n");
		return EXIT_FAILURE;
	}
	FILE *m;  // File Pointer
	if((m=fopen("report","wb"))==NULL) // Opening the binary file in write mode
	{
		return EXIT_FAILURE;
	}
	for(ptr2=start2;(ptr2);ptr2=ptr2->next2) // Appending data at the end
	{
		v.rno=ptr2->rno;
		strcpy(v.sp,ptr2->sp);
		strcpy(v.ep,ptr2->ep);
		v.d=ptr2->d;
		fwrite(&v,sizeof(r),1,m); // Writing in a file
	}
	fclose(m);  // Closing the file
	return EXIT_SUCCESS;
}

/***************************************************************
 *
 * FUNCTION-NAME : user_maintainance
 *
 * DESCRIPTION : This function will be performed by the admin
 *               to make changes in the user details 
 *
 *
 * ************************************************************/

int user_maintainance()
{
	int ch7;
	while(ch7!=5)
	{
		printf("\n----------WELCOME TO USER CORNER----------\n");
		printf("\n1. Add User Data \n2.Edit User Data \n3.Delete User Data \n4. View User Data\n5.Go back to admin menu");
		printf("\nEnter your choice(1-5):");
		scanf("%d",&ch7);
		switch(ch7)
		{
			case 1:add_user_data();
			       break;
			case 2:edit_user_data();
			       break;
			case 3:delete_user_data();
			       break;
			case 4:view_user_data();
			       break;
			case 5: break;
			default:printf("\nInvalid choice\n");
		}
	}
}

/********************* This function is used to add user data by admin **************************/

int add_user_data() 
{
	if((new=(u*)calloc(1,sizeof(u)))==NULL)  // Dynamic memory allocation for user structure
	{
		printf("\nMemory allocation failed\n");
		return EXIT_FAILURE;
	}
	while(1)
	{
		// Taking Input of user aadhar number
		printf("Enter user's aadhar number:");
		scanf("%d",&new->uad);
		if(start)
		{
			for(ptr=start;(ptr) && ptr->uad!=new->uad;ptr=ptr->next);
			if(ptr)
			{
				printf("User's aadhar number is duplicate\n");
				continue;
			}	
		}
		if(new->uad<1111 || new->uad>9999)//checking if the length of the aadhar number should be 4 digits only else it will print invalid message
		{
			printf("Invalid length, length should only of 4 digits \n");
			continue;
		}
		else
		{
			break;
		}
	}
	while(1)
	{
		// Taking input of user name
		printf("Enter user name:");
		fflush(stdin);
		scanf("%s",new->uname);
		int flag=0;
		for(int i=0;new->uname[i];i++)
		{
			if(!isalpha(new->uname[i]))//isalpha() function check whether the name is corret or has special chqaracters or numbers in it
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			printf("\nInavlid name should contains only alphabets\n");
			continue;
		}
		int max_len=strlen(new->uname);;
		if(max_len==0 || max_len>15)//Checking that length of the name should not be less than 5 and graeter than 15
		{
			printf("\nThe length of name should be in the size");
			continue;
		}
		else
		{
			break;
		}
	}
	while(1)
	{
		// Taking input of user address
		printf("Enter user address:");
		scanf("%s",new->uaddress);
		int max_len=20;
		if(strlen(new->uaddress)>max_len)
		{
			printf("\nThe length should be in size");
			continue;
		}
		else
			break;
	}
	while(1)
	{
		// Taking input of user age
		printf("Enter user age:");
		scanf("%d",&new->uage);
		if(new->uage<18)
		{
			printf("\nInavlid age of user\n");
			continue;
		}
		else
			break;
	}
	char *pr=getpassword();  // Storing password in pointer
	//Storing in the user's linked list
	if(!start)
	{
		start=new;
		new->next=NULL;
	}
	else if(new->uad<start->uad)
	{
		new->next=start;
		start=new;
	}
	else
	{
		for(ptr=start;(ptr) && ptr->uad<new->uad;prev=ptr,ptr=ptr->next);
		prev->next=new;
		new->next=ptr;
	}
	printf("\n------Registerated Successfully------\n");
	return EXIT_SUCCESS;
}

/********************* This function is used to edit user details by admin **************************/

int edit_user_data() 
{
	if(!start) // Checking if list is empty
	{
		printf("\nEmpty list\n");
		return EXIT_FAILURE;
	}
	int uad1;
	printf("\nEnter aadhar number for editing:");
	scanf("%d",&uad1);
	for(ptr=start;(ptr) && ptr->uad!=uad1;ptr=ptr->next);
	if(!ptr) // if pointer id is NULL then user is not found
	{

		printf("\nUser's aadhar %d is not found\n",uad1);
		return EXIT_FAILURE;
	}
	printf("Old name %s \nAddress %s  \nAge %d",ptr->uname,ptr->uaddress,ptr->uage);
	printf("\nEnter new name new address new age:");
	scanf("%s %s %d",ptr->uname,ptr->uaddress,&ptr->uage);
	printf("\n------Edited Successfully------\n");
	return EXIT_SUCCESS;
}

/********************* This function is used to delete user details by admin **************************/

int delete_user_data()
{
	if(!start)
	{
		printf("\nEmpty list\n");
		return EXIT_FAILURE;
	}
	int uad1;
	printf("\nEnter user aadhar number fot deleting:");
	scanf("%d",&uad1);
	if(uad1==start->uad)// We are reading aadhar no from admin and comparing with exsting aadhar no to delete
	{
		ptr=start;
		start=start->next;
		free(ptr);
	}
	else
	{
		for(ptr=start;(ptr) && ptr->uad!=uad1;prev=ptr,ptr=ptr->next);//Going to the usr linked list
		if(!ptr)
		{
			printf("\nUser's aadhar number %d not found for deletion\n",uad1);
			return EXIT_FAILURE;
		}
		prev->next=ptr->next;
		free(ptr);
	}
	printf("\n------Deleted Successfully------\n");
	return EXIT_SUCCESS;
}

/***************************************************************
 *
 * FUNCTION-NAME : driver_maintainance
 *
 * DESCRIPTION : This function will be performed by the admin
 *               to make changes in the driver details 
 *
 *
 * ************************************************************/

int driver_maintainance()
{
	int ch8=0;
	while(ch8!=5)
	{
		printf("\n----------WELCOME TO DRIVER CORNER----------\n");
		printf("\n1.Add Driver Data\n2. Edit Driver Data\n3. View Driver Data\n4. Delete Driver Data\n5. Go back to admin menu");
		printf("\nEnter your choice(1-5):");
		scanf("%d",&ch8);
		switch(ch8)
		{
			case 1:add_driver_data();
			       break;
			case 2:edit_driver_data();
			       break;
			case 3:view_driver_data();
			       break;
			case 4:delete_driver_data();
			       break;
			case 5:break;
			default:printf("\nInvalid Choice\n");
		}
	}
}

/********************* This function creates the driver account  by admin  **************************/

int add_driver_data()  
{
	if((new1=(d*)calloc(1,sizeof(d)))==NULL)//dynamic memory allocation
	{
		printf("\nMemory allocation failed\n");
		return EXIT_FAILURE;
	}
	while(1)
	{
		//Taking input of driver dlno
		printf("Enter dlno:");
		scanf("%d",&new1->dlno);
		if(start)
		{
			for(ptr1=start1;(ptr1) && ptr1->dlno!=new1->dlno;ptr1=ptr1->next1);
			if(ptr)
			{
				printf("\nDlno %d is  duplicate\n",new1->dlno);
				continue;
			}
			else
				break;
		}
		if(new1->dlno<=1111 || new1->dlno>9999)//Checking the lenght of dlno should be in limit 
		{
			printf("\nInvalid driver licence number");
			continue;
		}
		break;
	}
	while(1)
	{
		//Taking input of driver's name
		printf("Enter driver's name:");
		scanf("%s",new1->nam);
		int flag=0;
		for(int i=0;new1->nam[i];i++)
		{
			if(!isalpha(new1->nam[i]))//isalpha() function check whether the name is corret or has special chqaracters or numbers in it
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			printf("\nInavlid name should contains only alphabets\n");
			continue;
		}
		int max_len=strlen(new1->nam);
		if(max_len == 0|| max_len >15)//Checking length of name should be in limit
		{
			printf("\nThe name should be in the size\n");
			continue;
		}
		else
			break;
	}
	while(1)
	{
		//Taking input of driver's address 
		printf("Enter driver's address:");
		scanf("%s",new1->adrs);
		int max_len=strlen(new1->adrs);
		if(max_len > 20 || max_len == 0)//Checking the length of the address should be in limit
		{
			printf("\nInvalid Address\n");
			continue;
		}
		else
			break;
	}
	while(1)
	{
		//Taking input of driver's age
		printf("Enter driver's age:");
		scanf("%d",&new1->da);
		if(new1->da<18 || new1->da>65)//Checking the age 
		{
			printf("\nThe age is invalid\n");
			continue;
		}
		else
			break;
	}
	while(1)
	{
		//Taking input of driver's phone number
		printf("Enter driver's phone number:");
		scanf("%s",&new1->dphno);
		int flag=0;
		for(int i=0;i<strlen(new1->dphno);i++)
		{
			if(isdigit(new1->dphno[i]))//Checking whether the phone number is a digit or not
				flag++;
		}
		if(flag>10 || flag < 10)
		{
			printf("Invalid Phone Number\n");
			continue;
		}

		else
			break;
	}
	while(1)
	{
		//Creating a unique serial id number for driver
		int big=0;
		if(!start1)
		{
			new1->uid=101;
		}
		else 
		{
			for(ptr1=start1;(ptr1);ptr1=ptr1->next1)
			{
				if(ptr1->uid>big)
					big=ptr1->uid;
			}
			new1->uid=big+1;
		}
		break;
	} 	
	while(1)
	{
		//Driver selecting the routes from the given list of routes
		printf("\nList of Routes\n");
		printf("1.HYD-KKD \n2.TRP_NLR \n3.BANG-CHENNAI \n4.DELHI-BOMBAY\n5.CHITTOR-ANANTAPUR\n6.Go to driver menu"); 
		printf("\nSelect the route from the list:");
		scanf("%d",&new1->lor);
		if(new1->lor==1)
		{	
			printf("HYD-KKD");
		}
		if(new1->lor==2)
		{
			printf("TRP-NLR");
		}
		if(new1->lor==3)
		{
			printf("BANG-CHENNAI");
		}
		if(new1->lor==4)
		{
			printf("DELHI-BOMBAY");
		}
		if(new1->lor==5)
		{
			printf("CHITTOR-ANANTAPUR");
		}

		break;
	}

	char *pr1=getpassword();//Storing the driver's password
	//Stroing in the driver's linked list
	if(!start1)
	{
		start1=new1;
		new1->next1=NULL;
	}
	else if(new1->dlno<start1->dlno)
	{
		new1->next1=start1;
		start1=new1;
	}
	else
	{
		for(ptr1=start1;(ptr1) && ptr1->dlno< new1->dlno;prev1=ptr1,ptr1=ptr1->next1);
		prev1->next1=new1;
		new1->next1=ptr1;
	}
	printf("\n------Registerated Successfully------\n");
	return EXIT_SUCCESS;
}

/********************* This function is used to edit driver details by admin **************************/

int edit_driver_data()  
{

	if(!start1)
	{
		printf("\nEmpty list\n");
		return EXIT_FAILURE;
	}
	int dlno1;
	printf("\nEnter new dl number for editing:");//Taking the dlno from the driver and changing the details
	scanf("%d",&dlno1);
	for(ptr1=start1;(ptr1) && ptr1->dlno!=dlno1;ptr1=ptr1->next1);
	if(!ptr1)
	{

		printf("\nDriver's dlno %d is not found\n",dlno1);
		return EXIT_FAILURE;
	}
	printf("Old name %s \nAddress %s \nAge %d  \nPhone Number %s",ptr1->nam,ptr1->adrs,ptr1->da,ptr1->dphno);
	printf("\nEnter new name new address new age new phone number:");
	scanf("%s %s %d %s",ptr1->nam,ptr1->adrs,&ptr1->da,ptr1->dphno);
	printf("\n------Edited Successfully------\n");
}

/********************* This function is used to delete driver details by admin **************************/

int delete_driver_data()  
{
	if(!start)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	int dlno1;
	printf("\nEnter Driver license number for deleting:");//Checking the dlno from the admin to delete the driver's data
	scanf("%d",&dlno1);
	if(dlno1==start1->dlno)
	{
		ptr1=start1;
		start1=start1->next1;
		free(ptr);
	}
	else
	{
		for(ptr1=start1;(ptr1) && ptr1->dlno!=dlno1;prev1=ptr1,ptr1=ptr1->next1);
		if(!ptr1)
		{
			printf("\nDriver dlno %d is not found for deletion\n",dlno1);
			return EXIT_FAILURE;
		}
		prev1->next1=ptr1->next1;
		free(ptr1);
	}
	printf("\n------Deleted Successfully------\n");
	return EXIT_SUCCESS;
}

/***************************************************************
 *
 * FUNCTION-NAME : display_records
 *
 * DESCRIPTION : This function will be performed by admin to
 *               view the user details and driver details
 *
 *
 * ************************************************************/

int display_records() 
{
	int ch=0;
	while(ch!=3)
	{
		printf("\n----------DISPLAYING USER AND DRIVER RECORDS----------\n");
		printf("1.View user data \n2.View driver data  \n3.Goto admin menu");
		printf("\nEnter your choice (1-3):");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: view_user_data();
				break;
			case 2: view_driver_data();
				break;
			case 3: return 1;
			default: printf("\nInavlid choice\n");
				 continue;
		}
	}
}

/********************* View_user_data  **************************/
int view_user_data()  
{
	if(!start)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	printf("\nUser aadhar no       User name     User address     User age\n");
	for(ptr=start;(ptr);ptr=ptr->next)//go to linked list
	{
		printf("\n %3d             %10s        %10s       %3d\n",ptr->uad,ptr->uname,ptr->uaddress,ptr->uage);
	}
	printf("\n");
	return EXIT_SUCCESS;
}

/********************* View driver data  **************************/
int view_driver_data()  
{
	if(!start1)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	printf("\nDriver dlno     Driver name     Driver address      Diver age      Driver phone number   Drivers Unique Id  List of routes");
	for(ptr1=start1;(ptr1);ptr1=ptr1->next1)
	{   
		printf("\n %3d            %10s          %10s          %3d          %10s           %3d            %3d\n",ptr1->dlno,ptr1->nam,ptr1->adrs,ptr1->da,ptr1->dphno,ptr1->uid,ptr1->lor);
	}
	printf("\n");
	return EXIT_SUCCESS;
}


/***************************************************************
 *
 * FUNCTION-NAME : list_of_routes
 *
 * DESCRIPTION : This function will be performed by the admin 
 *               to add list of routes
 *
 *
 * ************************************************************/

int list_of_routes()//This function will have the list of routes  
{
	int ch11=0;
	while(ch11!=3)
	{
		printf("\n----------LIST OF ROUTES----------\n");
		printf("1.Add list data \n2.View list data \n3.Go to admin menu");
		printf("\nEnter your choice(1-3):");
		scanf("%d",&ch11);
		switch(ch11)
		{
			case 1: add_list_data();
				break;
			case 2: view_list_data();
				break;
			case 3: return 1;
			default: printf("\nInvalid choice");
				 continue;
		}
		break;
	}
}

/********************* add_list_data  **************************/

int add_list_data()//This function will add the list of routes by the admin
{
	if((new2=(rd*)calloc(1,sizeof(rd)))==NULL)//Allocating the memory
	{
		printf("\nMemory allocation failed\n");
		return EXIT_FAILURE;
	}
	while(1)
	{
		//Taking the input from the admin to add route number
		printf("Enter route number:");
		scanf("%d",&new2->rno);
		if(isdigit(new2->rno)>5)
		{
			printf("Invalid route number:");
			return EXIT_FAILURE;
		}
		else
			break;
	}
	while(1)
	{
		//Taking the source point and destination from admin
		printf("Enter Source:");
		scanf("%s",new2->sp);
		printf("Enter destination:");
		scanf("%s",new2->ep);
		break;
	}
	while(1)
	{
		//Taking the distance of the specified routes from the admin
		printf("Enter distance:");
		scanf("%d",&new2->d);
		if(isdigit(new2->d))
		{
			printf("\nInvalid Distance\n");
			continue;
		}
		else
			break;
	}
	//Storing in the linked list 
	if(!start2)
	{
		start2=new2;
		new2->next2=NULL;
	}
	else if(new2->rno<start2->rno)
	{
		new2->next2=start2;
		start2=new2;
	}
	else
	{
		for(ptr2=start2;(ptr2)&&ptr2->rno!=new2->rno;ptr2=ptr2->next2);
		prev2->next2=new2;
		new2->next2=ptr2;
	}
	printf("\n------Added Succesfully------\n");
	return EXIT_SUCCESS;
}

/********************* view_list_data **************************/

int view_list_data() 
{
	if(!start2)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	printf("\n Route no        Starting point       Ending point      Distance");
	for(ptr2=start2;(ptr2);ptr2=ptr2->next2)
	{
		printf("\n%3d          %10s            %10s             %3d\n",ptr2->rno,ptr2->sp,ptr2->ep,ptr2->d);
	}
	printf("\n");
	return EXIT_SUCCESS;
}

/***************************************************************
 *
 * FUNCTION-NAME : book_driver
 *
 * DESCRIPTION : This function will be used to book a driver
 *
 *
 * ************************************************************/

int book_driver()//This function is to book the driver
{
	printf("\n----------BOOKING DRIVER----------\n");
	printf("List of routes:\n");
	int lor1;
	while(1)
	{       
		//Selecting the routes to book driver
		while(lor1!=6)
		{
			printf("\n1.HYD-KKD\n2.TRP-NLR\n3.BANG-CHENNAI\n4.DELHI-BOMBAY\n5.CHITTOR-ANANTHAPUR\n");
			printf("Select your route: \n");
			scanf("%d",&lor1);
			switch(lor1)
			{
				case 1: printf("HYD-KKD");
					break;
				case 2: printf("TRP-NLR");
					break;
				case 3: printf("BANG-CHENNAI");
					break;
				case 4: printf("DELHI-BOMBAY");
					break;
				case 5: printf("CHITTOR-ANANTHAPUR");
					break;
				case 6: return 1;
				default:printf("Invalid Choice\n");
					continue;
			}			
			break;
		}
		int flag=0;
		while(1)
		{
			printf("\nList of drivers are:\n");//Showing the list of driver's for the specified route
			for(ptr1=start1;(ptr1);ptr1=ptr1->next1)//Driver linked list
			{
				if(lor1==ptr1->lor)
				{
					printf("Driver dlno         Driver name         Driver age        Driver address        Driver phone number        Driver uid\n");
					printf("%3ld             %10s              %3d              %10s               %10s               %3d\n",ptr1->dlno,ptr1->nam,ptr1->da,ptr1->adrs,ptr1->dphno,ptr1->uid);
					flag=1;
				}
			}
			if(flag==0)
			{
				printf("\nDriver are not found for the route\n");
				return EXIT_FAILURE;
			}
			int id;
			printf("\nTo book a driver enter the uid of the driver:");
			scanf("%d",&id);
			//To book driver the uid should match with the user entered id
			//int status_driver=0;
			for(ptr1=start1;(ptr1)&& ptr1->uid!=id;ptr1=ptr1->next1);
			if(!ptr1)
			{
				printf("\nDriver is not found\n");
				continue;
			}
			ptr1->status=0;
			if(id==ptr1->uid)
			{
				if(ptr1->status==0)
				{
					printf("Driver is free\n");
				}
				else
				{
					printf("Oops! Driver is not free\n");
					//continue;
				}
				break;
			}
			break;
		}
		//Asking for  no of days 
		int nod;
		printf("\nEnter no of days for ride:");
		scanf("%d",&nod);
		if(isdigit(nod))//Checking whether the no of days is a digit or not
		{
			printf("\nInvalid number\n");
			continue;
		}
		if(nod<=0 || nod>10)
		{
			printf("\nDriver is not available those many days\n");
			continue;
		}
		if(ptr1->status==0)//Checking for the driver's status
		{
			printf("Booking Confirmed and charge is 300 per km\n");
			ctc+=1;
			did=ptr1->uid;
			ptr1->status=1;
		}
		break;
	}
	printf("\n------Booking Completed Successfully------\n");
	return EXIT_SUCCESS;
}

/***************************************************************
 *
 * FUNCTION-NAME : show_top_drivers
 *
 * DESCRIPTION : This function will be used to show top drivers 
 *
 *
 * ************************************************************/

int show_top_drivers()//This function hows the top driver's in the list fo driver's
{
	printf("\n----------SHOWING TOP DRIVERS----------\n");
	if(!start1)
	{
		printf("\nNo records present in the driver's list\n");
		return EXIT_FAILURE;
	}
	int max=0;
	int c;
	char dnam[40];
	for(ptr1=start1;(ptr1);ptr1=ptr1->next1)
	{
		if(ctc > max)
		{
			max=ctc;
			strcpy(dnam,ptr1->nam);
			c=ptr1->dlno;
			//	ctc+=1;
		}
		else
			break;
	}
	printf("Driver dlno     Driver name\n");
	printf(" %3d      %10s\n",c,dnam);	
}

/***************************************************************
 *
 * FUNCTION-NAME : ride_report
 *
 * DESCRIPTION : This function will be used to view the 
 *               successfully completed rides
 *
 *
 * ************************************************************/

int ride_report()
{
	printf("\n----------RIDE REPORTS----------\n");
	if(!start2)
	{
		printf("Empty List\n");
		return EXIT_FAILURE;
	}
	for(ptr1=start1;(ptr1)&& ptr1->uid!=did;ptr1=ptr1->next1);
	if(!ptr1)
	{
		printf("\nDriver not found\n");
		return EXIT_FAILURE;
		//continue;
	}
	if(ptr1->uid==did)
	{
		printf("Driver dlno    Driver name\n");
		printf(" %3d       %10s\n",ptr1->dlno,ptr1->nam);
	}
	return EXIT_SUCCESS;
}

/***************************************************************
 *
 * FUNCTION-NAME : cancel_ride
 *
 * DESCRIPTION : This function will be used to cancel a ride 
 *
 *
 * ************************************************************/

int cancel_ride() 
{
	printf("\n----------CANCEL  RIDE----------\n");
	int id1;
	printf("\nUser needs to pay 2 percent of the total amount\n");
	printf("Enter uid of driver:\n");
	scanf("%d",&id1);
	if(!start1)
	{
		printf("\nList is empty\n");
		return EXIT_FAILURE;
	}
	//for(ptr1=start1;(ptr1);ptr1=ptr1->next1)
	//{
		if(did==id1)//Checking the given id with the uid in the driver's list
		{
			printf("Driver dlno    Driver name\n");
			printf(" %3d   %20s",ptr1->dlno,ptr1->nam);
			printf("\n------The Ride Got Cancelled------\n");
			ctc--;
		}
		else
		{
			printf("\nDriver's uid is incorrect");
		}
		//break;
	//}
	return EXIT_SUCCESS;
}

/***************************************************************
 *
 * FUNCTION-NAME : dispaly_cancelled_rides
 *
 * DESCRIPTION : This function will be performed by admin to
 * view the cancelled rides
 *
 *
 * ************************************************************/

int display_cancelled_rides()
{
	printf("\n----------DISPLAYING CANCELLED RIDES----------\n");
	if(!start1)
	{
		printf("\nNo records about cancelled rides\n");
		return EXIT_FAILURE;
	}
	for(ptr1=start1;(ptr1);ptr1=ptr1->next1)
	{
		if(ptr1->uid==did)
		{
			printf("\nDriver dlno     Driver name\n");
			printf("\n%3d   %10s\n",ptr1->dlno,ptr1->nam);
		}
	}
	printf("\n");
	return EXIT_SUCCESS;
}


