/*************************************************************************************
 *
 * FILENAME : odb_main.c
 *
 * DESCRIPTION : This file is used as Main menu of the Online Driver Booking  System which 
 *               has all admin, user and driver corners
 *               
 *REVISION HISTORY
 *
 * DATA               NAME                  REASON
 *
 * **********************************************************
 *
 * 26/10/2022        Username                  Menu
 *
 * **********************************************************************************/


#include<stdio.h>    // Including required Header Files
#include<stdlib.h>
#include<termios.h>
#include<string.h>
#include<ctype.h>
#include "odb_header.h"

#define MAXPW 32

char *pt;

int main()   // This is the Main function
{
	int ch=0;
	int user_login=0;
	int driver_login=0;
	int admin_login=0;
	user_to_list();  // Calling file to list function of user corner
	driver_to_list();  // Calling file to list function of driver corner
	report_to_list();  // Calling file to list function of reports
	while(ch!=4)
	{
		printf("\n**************************************************\n");
		printf("\n           ONLINE DRIVER BOOKING SYSTEM           \n");
		printf("\n**************************************************\n");
		printf("1.User Menu\n");
		printf("2.Driver Menu\n");
		printf("3.Admin Menu\n");
		printf("4.Exit\n");
		printf("Enter your choice (1-4):");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: user_login=checkpassword();  // check user's password
				if(user_login==1)
				{
					printf("\nInvalid password\n");
					continue;
				}
				else
				{
					user_menu(); // Calling user_menu function
				}
				break;
			case 2: driver_login=checkpassword();  // check driver's password 	
				if(driver_login==1)
				{
					printf("\nInvalid password\n");
					continue;
				}
				else
				{
					driver_menu();  // Calling driver _menu function
				}
				break;
			case 3: admin_login=checkpassword();  // check admin's password
				if(admin_login==1)
				{
					printf("\nInvalid password\n");
					continue;
				}
				else
				{
					admin_menu();  // Calling admin_menu function
				}
				break;
			case 4: break;
			default: printf("\nInvalid choice\n");
				 continue;
		}
	}
	list_to_user();  // Calling list to user  function of user corner
	list_to_driver();  // Calling list to driver function for driver's corner 
	list_to_report();  // Calling list to report for route details
	return EXIT_SUCCESS;
}

int user_menu()
{
	int ch1=0;
	while(ch1!=4)
	{
		printf("\n------Welcome to user corner------\n");
		printf("1.Add user data\n2.Edit user data\n3.Book driver\n4.Show Top drivers\n5.Cancel ride\n6.Go back to main menu");
		printf("\nEnter your choice(1-6):");
		scanf("%d",&ch1);

		switch(ch1)
		{
			case 1: add_user_data();
				break;
			case 2: edit_user_data();
				break;
			case 3: book_driver();
				break;
			case 4: show_top_drivers();
				break;
			case 5: cancel_ride();
				break;
			case 6: return 1;
			default: printf("\nInvalid choice\n");
				 continue;
		}
	}
	return EXIT_SUCCESS;
}

int driver_menu()
{
	int ch2=0;
	while(ch2!=3)
	{
		printf("\n------Welcome to driver's corner------\n");	
		printf("1.Add driver data\n2.Edit driver data\n3.Go back to main menu");
		printf("\nEnter your choice (1-3):");
		scanf("%d",&ch2);
		switch(ch2)
		{
			case 1: add_driver_data();
				break;
			case 2: edit_driver_data();
				break;
			case 3: return 1;
			default: printf("\nInvalid choice\n");
				 continue;
		}
	}
	return EXIT_SUCCESS;
}

int admin_menu()
{
	int ch3=0;
	while(ch3!=6)
	{
		printf("\n------Welcome to Admin Menu------\n");
		printf("1.User maintainance\n2.Driver maintainance\n3.Ride report\n4.Display cancelled rides\n5.Display records\n6.list of routes\n7.Go back to main menu");
		printf("\nEnter your choice (1-7):");
		scanf("%d",&ch3);
		switch(ch3)
		{
			case 1: user_maintainance();
				break;
			case 2: driver_maintainance();
				break;
			case 3: ride_report();
				break;
			case 4: display_cancelled_rides();
				break;
			case 5: display_records();
				break;
			case 6: list_of_routes();
				break;
			case 7: return 1;
			default: printf("\nInvalid choice\n");
				 continue;
		}
	}
	return EXIT_SUCCESS;
}

/*************************************************************************************
 *
 * FILENAME : odb_main.c
 *
 * DESCRIPTION : This file is used to validate the Admin, User and Driver passwords
 *               to login and do their respective changes
 *
 *               
 *REVISION HISTORY
 *
 * DATA               NAME                  REASON
 *
 * **********************************************************
 *
 * 26/10/2022        Username                  Menu
 *
 * **********************************************************************************/

ssize_t password (char **pw, size_t sz, int mask, FILE *fp)
{
	if(!pw || !sz || !fp)  // Validate Input
		return -1;
#ifdef MAXPW
	if(sz > MAXPW) sz = MAXPW;
#endif
	if(*pw == NULL) // reallocate if no address
	{
		void  *tmp = realloc (*pw, sz * sizeof **pw);
		if(!tmp)
			return -1;
		memset (tmp, 0, sz);  //initialize memory to 0 
		*pw = (char*) tmp;
	}
	size_t idx = 0; //index,number of chars in read
	int c = 0;
	struct termios old_kbd_mode;  // orig keyboard settings
	struct termios new_kbd_mode;
	if (tcgetattr (0, &old_kbd_mode)) // save original settings
	{
		fprintf (stderr , "%s() error: tcgetattr failed.\n", __func__);
		return -1;
	} // copy old to new
	memcpy (&new_kbd_mode, &old_kbd_mode, sizeof(struct termios));
	new_kbd_mode.c_lflag &= ~(ICANON | ECHO); // new kbd flags
	new_kbd_mode.c_cc[VTIME] = 0;
	new_kbd_mode.c_cc[VMIN] = 1;
	if (tcsetattr (0, TCSANOW, &new_kbd_mode))
	{
		fprintf(stderr, "%s() error: tcsetattr failed.\n", __func__);
		return -1;
	}
	// read characters from fp, mask if valid char specified
	while (((c = fgetc(fp)) !='\n' && c != EOF && idx < sz - 1) || (idx == sz - 1 && c == 127))
	{
		if (c != 127)
		{
			if(31 < mask && mask <127) // valid ascii cahr
				fputc (mask, stdout);
			(*pw)[idx++] = c;
		}
		else if (idx > 0) // handle backspace (del)
		{
			if (31 < mask && mask < 127)
			{
				fputc (0x8, stdout);
				fputc (' ', stdout);
				fputc (0x8, stdout);
			}
		}
	}
	(*pw)[idx] = 0; // null- terminate
	// reset original keyboard
	if (tcsetattr (0, TCSANOW ,&old_kbd_mode))
	{
		fprintf (stderr, "(%s() error: truncated failed.\n", __func__);
		return -1;
	}

	if (idx == sz - 1 && c != '\n') //warn if pw truncated
		fprintf (stderr, "%s() warning: truncated at %zu chars.)\n",__func__, sz - 1);
	return idx; // number of chars in passwd
}

int checkpassword()
{
	char pw[MAXPW] = {0};
	char *p = pw;
	FILE *fp = stdin;
	ssize_t nchr = 0;
	nchr = password(&p, MAXPW, '*', fp);

	//Taking input for password
	printf("\n Enter Password:\n");
	nchr = password(&p, MAXPW, '*', fp);
	if (strcmp(p, "abc@123") == 0 || strcmp(p, "xyz@345") == 0) //checking the fixed password
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


char *getpassword()
{
	char pw[MAXPW]={0};
	pt=pw;

	FILE *fp=stdin;
	ssize_t nchr=0;
	nchr=password(&pt,MAXPW,'*',fp);
	//Taking Input Password
	printf("\nEnter password:\n");
	nchr=password(&pt,MAXPW,'*',fp);
	return pt;
}

