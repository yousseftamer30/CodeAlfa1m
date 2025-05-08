#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;


class user 
{

public :

	string username;
	string password;

	user() : username("\0") , password("\0")
	{

	}
	//friend class AuthSystem;
	bool login()
	{
		//bool vaild;
		string uname, psword;
		cout << "login \n enter your username :";
		cin >> uname;
		if (uname == username)
		{
			cout << "enter your password :";
			cin >> psword;
			if (psword == password)
				return	true;
			return false;
		}
		else
		{
			return false;
		}

	}

	void registeration()
	{

		cout << "registeration \n username :";
		cin >> username;
		cout << "password :";
		cin >> password;

	}

};


class AuthSystem //: private user 
{
private:
	static int membernumber;
	void ReadMumberNumber()
	{
		string fileMemberNumber , line;
		ifstream outfile("H:\\membernumber.txt");
		if (!(outfile.is_open()))
			cout << "not open membernumber.txt in read" << endl;
		getline(outfile, line);
		fileMemberNumber = line.substr(line.find(":") + 1);
		membernumber= stoi(fileMemberNumber) ;
		outfile.close();
	}
	void WriteMumberNumber()
	{
		string fileMemberNumber, line;
		ofstream outfile("H:\\membernumber.txt");
		outfile << "MemberNumber:" << membernumber;
		outfile.close();
	}

public :
	AuthSystem()
	{

	}
	
	bool verifyLogin(string uname, string pword)
	{
		string fileUsername, filePassword, line , fileMemberNumber;

		ReadMumberNumber();
		for (int i = 0; i < membernumber; i++) 
			{
				ifstream file("H:\\users0" + to_string(i) + ".txt");
				if (!(file.is_open()))
					cout << "not open in verifyLogin" << endl;

				getline(file, line);
				fileUsername = line.substr(line.find(":") + 1);
				getline(file, line);
				filePassword = line.substr(line.find(":") + 1);
				file.close();

				if (uname == fileUsername && pword == filePassword)
					return true;
			}
			return false;
		
	}

	
	void safefile(string username , string password)
	{
		ofstream file("H:\\users0" + to_string(membernumber) + ".txt");
		if (!(file.is_open()))
			cout << "not open in safefile" << endl;
		file << "username:" << username << endl;
		file << "password:" << password << endl;
		membernumber++;
		WriteMumberNumber();
		file.close();
	}

	bool isUsernameUnique(string usname)
	{
		string fileUsername, line;

		 ReadMumberNumber();
		for (int i = 0; i < membernumber; i++)
		{
			ifstream file("H:\\users0" + to_string(i) + ".txt");
			if (!(file.is_open()) )
				cout << "not open in useruniqe" << endl;

			getline(file, line);
			fileUsername = line.substr(line.find(":") + 1);
			file.close();

			if (usname == fileUsername )
				return false;
		}
		return true;
	}

};

int AuthSystem::membernumber = 0;

int main()
{
	int choose , tries=0;
	user USER;
	AuthSystem AUTH;
	string uname, psword;
	while (tries < 3)
	{

		cout << "choose your state \n 1-Registration \n 2-login \n 3-Exit" << endl;
		cin >> choose;
		switch (choose)
		{
		case 1:
			USER.registeration();
			if (AUTH.isUsernameUnique(USER.username))
			{
				AUTH.safefile(USER.username, USER.password);
				cout << "registeration is vaild" << endl;
			}
			else
			{
				cout << "registeration isn't vaild" << endl;
			}

			break;
		case 2:
			
			cout << "login \n enter your username :";
			cin >> uname;
			cout << "enter your password :";
			cin >> psword;
			//USER.login();
			if (AUTH.verifyLogin(uname, psword))
			{
				cout << "login is vaild" << endl;
			}
			else
			{
				cout << "login isn't vaild" << endl;
			}

			break;
		case 3:
			tries = 3;
			break;
		default:
			cout << "invaild choice" << endl;
			tries++;
			break;
		}
	}

}
















/*
	while (tries < 3)
	{

		cout << "choose your state \n 1-login \n 2-Registration \N 3-Exit" << endl;
		cin >> choose;
		if (choose == 1)
		{
			cout << "please enter your username" << endl;
			cin >> usname;
			userflag = findusername(usname);
			if (userflag == true)
			{
				cout << "please enter your password" << endl;
				cin >> pasword;
				passwordflag = findpassword(pasword);
				if (passwordflag == true)
				{
					cout << "Login is Succesful" << endl;
				}
				else
				{
					cout << "inaild password" << endl;
					tries++;
				}
			}
			else
			{
				cout << "inaild username" << endl;
				tries++;
			}
		}
		else if (choose == 2)
		{
			cout << "please enter your username" << endl;
			cin >> usname;
			userflag = findusername(usname);
			if (userflag == true  )
			{
				cout << "username is already used !!" << endl;
					tries++;

			}
			else
			{
				cout << "please enter your password" << endl;
				cin >> pasword;
				Add_Node(usname, pasword);
				printusername();

			}

		}
		else
		{
			cout << "invaild choice" << endl;
			tries++;
		}
	}*/

	/*
	struct user
	{
		user* New_Node;
		//string state;
		string user_name;
		string password;

	};

	 user* head = NULL;



	void Add_Node( string usname , string pass)
	{
		//user* link = ( user*)malloc(sizeof( user));
		struct user* link = (struct user*)malloc(sizeof(struct user));

		link->password = pass;
		//link->state = state;
		link->user_name = usname;

		//point the next pointer to the old head node
		link->New_Node = head;

		//point the head to the new first node
		head = link;

	}

	bool findusername(string usernam)
	{
		user* ptr = head;

		if (head == NULL)
		{
			//if (head->user_name == usernam)
				return false;
			/*else
			{
				return false;
			}*/
			/*}
			else
			{
				do
				{
					if (ptr->user_name == usernam)
						return true;
					else
					{
						ptr = ptr->New_Node;

					}
				} while (ptr->New_Node != NULL);

			}
			return false;

		}

		bool findpassword(string  pass)
		{
			user* ptr = head;

			if (head == NULL)
			{
				//if (head->password == pass)
				return false;
				/*else
				{
					return false;
				}*/
				/*}
				else
				{
					do
					{
						if (ptr->password == pass)
							return true;
						else
						{
							ptr = ptr->New_Node;
						}
					} while (ptr->New_Node != NULL);

				}
				return false;

			}

			void printusername(void)
			{
				user* ptr = head;

				if (head->New_Node == NULL)
				{
					cout << "no user found" << endl;
				}
				else
				{
					while (ptr->New_Node != NULL)
					{
						cout << ptr->user_name << "\n";
						ptr = ptr->New_Node;
					}

				}

			}


			*/




			/*
			* void set_state(string s)
			{
				state = s;

			}
			void print_state()
			{
				cout << "The State Is " << state << endl;

			}
			void set_password()
			{
				cout << "enter your set password ";
				cin >> password;

			}
			int login()
			{
				char* pass;
				string us;
				cout << "enter your  username ";
				cin >> us;
				if (us == user_name)
				{
					cout << "enter your  password ";
					cin >> pass;
					if (*pass == *password)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			*/



