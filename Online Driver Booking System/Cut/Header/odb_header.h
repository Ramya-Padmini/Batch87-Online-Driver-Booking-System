#ifndef ODB_HEADER_H
#define ODB_HEADER_H
#define pragma pack(1)

typedef struct user      //User Structure
{
	int uad;
	char uname[20];
	char uaddress[20];
	int uage; 
	struct user *next;
}u;

typedef struct temp   
{

	int uad;
	char uname[20];
	char uaddress[20];
	int uage;
}t;


typedef struct driver  //Driver Structure
{
	int dlno;
	char nam[20];
	int da;
	char adrs[20];
	char dphno[10];
	int lor;
	int uid;
	int status;
	//int ctc;
	struct driver *next1;
}d;

typedef struct store
{
	int dlno;
	char nam[20];
	int da;
	char adrs[20];
	char dphno[10];
	int uid;
	int lor;
	int status;
	//int ctc;
}s;

typedef struct route_details   //Route Details Structure
{
	int rno;
	char sp[10];
	char ep[10];
	int d;
	//char status_driver[3];
	struct route_details *next2;
}rd;

typedef struct root
{
	int rno;
	char sp[10];
	char ep[10];
	int d;
	//char status_driver[3];
}r;

//Function Declaration of menus and submenus
int user_menu();
int add_user_data();
int edit_user_data();
int delete_user_data();
int view_user_data();
int book_driver();
int show_top_drivers();
int cancel_ride();

int user_to_list();//file to list
int list_to_user();//list to file

int display_records();//view user/driver details

int driver_menu();
int add_driver_data();
int edit_driver_data();
int view_driver_data();
int delete_driver_data();

int driver_to_list();//file to list
int list_to_driver();//list to file

int admin_menu();
int user_maintainance();
int driver_maintainance();
int ride_report();
int display_cancelled_rides();

int list_of_routes();
int add_list_data();
int view_list_data();

int report_to_list();//file to list
int list_to_report();//list to file

ssize_t password(char **pw,size_t sz,int mask,FILE *fp);
//Fucntion Declaration of password
int checkpassword();
char *getpassword();
#endif
