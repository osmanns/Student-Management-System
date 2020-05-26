#include <iostream>
#include <fstream>
#include <string>
#include <stdbool.h>
#include <iomanip>

using namespace std;

class Student{
	private :

		class Node{
			public:
				string id, year, prefix, fname, lname, major, gen, adviser, status, date;
				string gpa;
				Node *link;

				Node(string id, string year, string prefix, string fname, string lname, string gpa, 
				     string major, string gen, string adviser, string status, string date){
					this->id = id;
					this->year = year;
					this->prefix = prefix;
					this->fname = fname;
					this->lname = lname;
					this->gpa = gpa;
					this->major = major;
					this->gen = gen;
					this->adviser = adviser;
					this->status = status;
					this->date = date;
					link = NULL;
				}
		};	
		
		Node *head;
		Node *tail;
		int count;	
		int mr, miss, mr2, miss2;
		string userlogin;
	public :
		Student();
		void add(string id, string year, string prefix, string fname, string lname, string gpa, 
			 string major, string gen, string adviser, string status, string date);
		void remove(string search);
		void readFile();
		void writeFile();
		void search(string id);
		void showStudentList();
		bool isEmpty();	
		bool checkAdd(string id);	
		bool checkRem(string id);
		bool checkId(string id);
		void checkStu();
		string login();
		void add2(string id2, string password, string stat);
		int sortMaxMin();
		int sortMinMax();
		int sortAZ();
		int sortZA();
		void edit(string id);
};

Student::Student(){
	this->head = NULL;
	this->tail = NULL;
	this->count = 0;
	this->readFile();
	this->mr = 0;
	this->miss = 0;
	this->mr2 = 0;
	this->miss2 = 0;
	this->userlogin = " ";
}

void Student::add(string id, string year, string prefix, string fname, string lname, string gpa, 
		  string major, string gen, string adviser, string status, string date){
	Node *n = new Node(id, year, prefix, fname, lname, gpa, major, gen, adviser, status, date);	
		if(isEmpty()){
			head = n;
			tail = n;
		}
		else{
			tail->link = n;
			tail = tail->link;
		} 
		count++;
		
			if(status == "Studying"){
				if(prefix == "Mr.")	
					mr=mr+1;
				else
					miss=miss+1;
			}
			else if(status == "Graduated"){
				if(prefix == "Mr.")	
					mr2++;
				else
					miss2++;
			}
}

void Student::remove(string search){
	Node *ptemp, *temp;
	int round = 1;
	string status, prefix;				
			for(Node *temp = head;temp != NULL;temp = temp->link){			
				if(temp->id != search && count == round){
					cout << "The item to be delete is not in the list.\n\n";
				}			
				if(round == 1){
					ptemp = temp;
					if(temp->id == search){
						if(temp->status == "Studying"){
							mr--;
						}
						
						if(temp == head && temp == tail){
							delete temp;
							head = NULL;
							tail = NULL;
						}else if(temp == head){
							head = head->link;
							delete temp;
						}	
						cout << "Remove Complete\n\n";
						count--;
					}
				}
				else{
					if(temp->id == search){	
						if(temp->status == "Studying"){
							mr--;
						}
										
						if(temp == tail){
							tail = ptemp;
							tail->link = NULL;
							delete temp;
						}
						else{
							ptemp->link = temp->link;
							delete temp;
						}
						cout << "Remove Complete\n\n";
						count--;											
					}
					else
					{
						ptemp = temp;
					}
				}			
				round++;	
			}
}

void Student::readFile(){
	ifstream file;
	string id, year, prefix, fname, lname, major, gen, adviser, status, date;
	string gpa;
	
	file.open("myfile.txt");
		while(file >> id >> year >> prefix >> fname >> lname >> gpa >> major >> gen >> adviser >> status){
			if(status == "Studying"){	
				add(id, year, prefix, fname, lname, gpa, major, gen, adviser, status, " ");
			}
			else if(status == "Graduated"){
				file >> date;
				add(id, year, prefix, fname, lname, gpa, major, gen, adviser, status, date);
			}
		}
	file.close();
}

void Student::writeFile(){
	ofstream file;
		
		file.open("myfile.txt",ios::out);
		for(Node *temp = head;temp != NULL;temp = temp->link){
			file << temp->id << "\t" 
				 << temp->year << "\t"
				 << temp->prefix << "\t" 
				 << temp->fname << "\t"
				 << temp->lname << "\t" 
				 << temp->gpa << "\t" 
				 << temp->major << "\t" 
				 << temp->gen << "\t"
				 << temp->adviser << "\t"
				 << temp->status << "\t"
				 << temp->date << "\n";
		}
		file.close();
}

void Student::search(string id){
	cout << "                                       Show Student " << endl; 
	cout << "===================================================================================================================================" << endl;
	cout << "No	Student Id.     Year    Prefix  Student Name            GPA     Major   Generation      Adviser     Status                      " << endl;
	cout << "===================================================================================================================================" << endl;
	for(Node *temp=head; temp!=NULL; temp=temp->link){
		if(temp->id==id){
			cout << setw(8) << left << temp->id << "\t" 
				<< setw(4) << left << temp->year << "\t"
				<< setw(5) << left << temp->prefix << "\t"
		 		<< setw(1) << left << temp->fname[0] << ". " 
		 		<< setw(11) << left << temp->lname << "\t\t" 
				<< setw(4) << left << temp->gpa << "\t" 
		 		<< setw(4) << left << temp->major << "\t" 
				<< setw(4) << left << temp->gen << "\t\t"
		 		<< setw(6) << left << temp->adviser << "\t    "
			 	<< setw(10) << left << temp->status << "  "
		 		<< setw(10) << left << temp->date << "\n";
		}
	}
}

void Student::showStudentList(){
	cout << "                                       Show Student " << endl; 
	cout << "===================================================================================================================================" << endl;
	cout << "No	Student Id.     Year    Prefix  Student Name            GPA     Major   Generation      Adviser     Status                      " << endl;
	cout << "===================================================================================================================================" << endl;
	
	if(this->isEmpty()){
		cout << "No Data" << endl;
	}
	else{
		Node *temp;
		temp = head;

		cout << "Studying Student : " << mr+miss << "  (Mr. = " << mr << " Miss = " << miss << " )"<< endl;	
		cout << "===================================================================================================================================" << endl;
		int n=1;
		//for(int i=0; i<count; i++){
			for(Node*temp=head;temp!=NULL;temp=temp->link){	
				if(temp->status == "Studying"){
			//	if(temp->status == "Studying" && temp->adviser == userlogin){
					cout << n << "\t"; 
					cout << setw(8) << left << temp->id << "\t" 
						 << setw(4) << left << temp->year << "\t"
				 		<< setw(5) << left << temp->prefix << "\t"
				 		<< setw(1) << left << temp->fname <<". " 
				 		<< setw(11) << left << temp->lname << "\t\t" 
					 	<< setw(4) << left << temp->gpa << "\t" 
				 		<< setw(4) << left << temp->major << "\t" 
				 		<< setw(4) << left << temp->gen << "\t\t"
				 		<< setw(6) << left << temp->adviser << "\t    "
				 		<< setw(10) << left << temp->status << "  "
				 		<< setw(10) << left << temp->date << "\n";
				//temp = temp->link;
				n++;
				}
			
			}
			
		cout << "===================================================================================================================================" << endl;
		cout << "Graduated Student : " << mr2+miss2 << "  (Mr. = " << mr2 << " Miss = " << miss2 << " )"<< endl;
		cout << "===================================================================================================================================" << endl;
		n = 1;
		//for(int i=0; i<count; i++){
		    for(Node*temp=head;temp!=NULL;temp=temp->link){
				if(temp->status == "Graduated"){
					cout << n << "\t"; 
					cout << setw(8) << left << temp->id << "\t" 
						<< setw(4) << left << temp->year << "\t"
				 		<< setw(5) << left << temp->prefix << "\t"
				 		<< setw(1) << left << temp->fname << ". " 
				 		<< setw(11) << left << temp->lname << "\t\t" 
						<< setw(4) << left << temp->gpa << "\t" 
				 		<< setw(4) << left << temp->major << "\t" 
				 		<< setw(4) << left << temp->gen << "\t\t"
				 		<< setw(6) << left << temp->adviser << "\t    "
					 	<< setw(10) << left << temp->status << "  "
				 		<< setw(10) << left << temp->date << "\n";
				//temp = temp->link;
				n++;
				} 			
			}
	} // else
	cout << "===================================================================================================================================" << endl;
	cout << endl;
}

bool Student::isEmpty(){
	if(count == 0){
		return true;
	}else{
		return false;
	}
}

bool Student::checkAdd(string id){		
		for(Node *temp = head;temp != NULL;temp = temp->link){
			if(temp->id == id){
				cout <<  "Duplicate ID ! ! ! ! !\n\n";
				return true;
			}	
		}
		return false;
}

bool Student::checkRem(string id){		
		for(Node *temp = head;temp != NULL;temp = temp->link){
			if(temp->id == id && temp->status == "Graduated"){
				return true;
			}	
		}
		return false;
}

void Student::checkStu(){
		for(Node*temp=head;temp!=NULL;temp=temp->link){
			if(temp->status == "Studying"){
				if(temp->prefix == "Mr.")	
					mr++;
				else
					miss++;
			}
			else if(temp->status == "Graduated"){
				if(temp->prefix == "Mr.")	
					mr2++;
				else
					miss2++;
				}
		}	
}


bool Student::checkId(string id){
	for(Node *temp = head;temp != NULL;temp = temp->link){
		if(temp->id == id){
			return true;
		}	
	}
		return false;
}

string Student::login(){
	string id2, pass2, user, password, stat;

	cout << "======= Login =======" << endl;
	cout << "User : ";
		cin >> id2;
	cout << "Password : ";
		cin >> pass2;
		
	ifstream file;
		file.open("login.txt");
		while(file >> user >> password >> stat){	
			if(id2==user && pass2==password){
				if(stat=="staff" || stat=="teacher"){			
					cout << endl << "Welcome " << id2 << endl;
					userlogin = id2;
				return "1";
				}	
			}
		}
		cout << "Sorry you don't have premission to access " << endl;
		file.close();
}

int Student::sortMaxMin(){
	string id, year, prefix, fname, lname, gpa, major, gen, adviser, status, date;
	Node *temp, *ptemp, *itemp;
	itemp = new Node(id, year, prefix, fname, lname, gpa, major, gen, adviser, status, date);
	temp = head;
	temp = temp->link;
	ptemp = NULL;
		for(temp=head; temp!=NULL; temp=temp->link){	
			for(ptemp=temp->link; ptemp!=NULL; ptemp=ptemp->link){	
				if(temp->id < ptemp->id){
					id = temp->id;
					year = temp->year;
					prefix = temp->prefix;
					fname = temp->fname;
					lname = temp->lname;
					gpa = temp->gpa;
					major = temp->major;
					gen = temp->gen;
					adviser = temp->adviser;
					status = temp->status;
					date = temp->date;
										
					temp->id = ptemp->id;
					temp->year = ptemp->year;
					temp->prefix = ptemp->prefix;
					temp->fname = ptemp->fname;
					temp->lname = ptemp->lname;
					temp->gpa = ptemp->gpa;
					temp->major = ptemp->major;
					temp->gen = ptemp->gen;
					temp->adviser = ptemp->adviser;
					temp->status = ptemp->status;
					temp->date = ptemp->date;
					
					ptemp->id = id;
					ptemp->year = year;
					ptemp->prefix = prefix;
					ptemp->fname = fname;
					ptemp->lname = lname;
					ptemp->gpa = gpa;
					ptemp->major = major;
					ptemp->gen = gen;
					ptemp->adviser = adviser;
					ptemp->status = status;
					ptemp->date = date;
				}
			}
	}
 	cout << "Sort ! ! !" << endl;
}

int Student::sortMinMax(){
		string id, year, prefix, fname, lname, gpa, major, gen, adviser, status, date;
	Node *temp, *ptemp, *itemp;
	itemp = new Node(id, year, prefix, fname, lname, gpa, major, gen, adviser, status, date);
	temp = head;
	temp = temp->link;
	ptemp = NULL;
		for(temp=head; temp!=NULL; temp=temp->link){	
			for(ptemp=temp->link; ptemp!=NULL; ptemp=ptemp->link){	
				if(temp->id > ptemp->id){
					id = temp->id;
					year = temp->year;
					prefix = temp->prefix;
					fname = temp->fname;
					lname = temp->lname;
					gpa = temp->gpa;
					major = temp->major;
					gen = temp->gen;
					adviser = temp->adviser;
					status = temp->status;
					date = temp->date;
										
					temp->id = ptemp->id;
					temp->year = ptemp->year;
					temp->prefix = ptemp->prefix;
					temp->fname = ptemp->fname;
					temp->lname = ptemp->lname;
					temp->gpa = ptemp->gpa;
					temp->major = ptemp->major;
					temp->gen = ptemp->gen;
					temp->adviser = ptemp->adviser;
					temp->status = ptemp->status;
					temp->date = ptemp->date;
					
					ptemp->id = id;
					ptemp->year = year;
					ptemp->prefix = prefix;
					ptemp->fname = fname;
					ptemp->lname = lname;
					ptemp->gpa = gpa;
					ptemp->major = major;
					ptemp->gen = gen;
					ptemp->adviser = adviser;
					ptemp->status = status;
					ptemp->date = date;
				}
			}
	}
 	cout << "Sort ! ! !" << endl;
}

int Student::sortAZ(){
	string id, year, prefix, fname, lname, gpa, major, gen, adviser, status, date;
	Node *temp, *ptemp;
	temp = head;
	temp = temp->link;
	ptemp = NULL;
		for(temp=head; temp!=NULL; temp=temp->link){	
			for(ptemp=temp->link; ptemp!=NULL; ptemp=ptemp->link){	
				if(temp->fname > ptemp->fname){
					id = temp->id;
					year = temp->year;
					prefix = temp->prefix;
					fname = temp->fname;
					lname = temp->lname;
					gpa = temp->gpa;
					major = temp->major;
					gen = temp->gen;
					adviser = temp->adviser;
					status = temp->status;
					date = temp->date;
										
					temp->id = ptemp->id;
					temp->year = ptemp->year;
					temp->prefix = ptemp->prefix;
					temp->fname = ptemp->fname;
					temp->lname = ptemp->lname;
					temp->gpa = ptemp->gpa;
					temp->major = ptemp->major;
					temp->gen = ptemp->gen;
					temp->adviser = ptemp->adviser;
					temp->status = ptemp->status;
					temp->date = ptemp->date;
					
					ptemp->id = id;
					ptemp->year = year;
					ptemp->prefix = prefix;
					ptemp->fname = fname;
					ptemp->lname = lname;
					ptemp->gpa = gpa;
					ptemp->major = major;
					ptemp->gen = gen;
					ptemp->adviser = adviser;
					ptemp->status = status;
					ptemp->date = date;
				}
			}
	}
 	cout << "Sort ! ! !" << endl;
}

int Student::sortZA(){
	string id, year, prefix, fname, lname, gpa, major, gen, adviser, status, date;
	Node *temp, *ptemp;
	temp = head;
	temp = temp->link;
	ptemp = NULL;
		for(temp=head; temp!=NULL; temp=temp->link){	
			for(ptemp=temp->link; ptemp!=NULL; ptemp=ptemp->link){	
				if(temp->fname < ptemp->fname){
					id = temp->id;
					year = temp->year;
					prefix = temp->prefix;
					fname = temp->fname;
					lname = temp->lname;
					gpa = temp->gpa;
					major = temp->major;
					gen = temp->gen;
					adviser = temp->adviser;
					status = temp->status;
					date = temp->date;
										
					temp->id = ptemp->id;
					temp->year = ptemp->year;
					temp->prefix = ptemp->prefix;
					temp->fname = ptemp->fname;
					temp->lname = ptemp->lname;
					temp->gpa = ptemp->gpa;
					temp->major = ptemp->major;
					temp->gen = ptemp->gen;
					temp->adviser = ptemp->adviser;
					temp->status = ptemp->status;
					temp->date = ptemp->date;
					
					ptemp->id = id;
					ptemp->year = year;
					ptemp->prefix = prefix;
					ptemp->fname = fname;
					ptemp->lname = lname;
					ptemp->gpa = gpa;
					ptemp->major = major;
					ptemp->gen = gen;
					ptemp->adviser = adviser;
					ptemp->status = status;
					ptemp->date = date;
				}
			}
	}
 	cout << "Sort ! ! !" << endl;
}

void Student::edit(string id){
	string id2, fname2, lname2;
	
	for(Node* temp=head; temp!=NULL; temp=temp->link){
		if(temp->id==id){
			cout << "Enter First Name : ";
			cin >> fname2;
			cout << "Enter Last Name : ";
			cin >> lname2;
			temp->fname = fname2;
			temp->lname =lname2;
		}
	}
}

int main(){

	Student s;
	string id, year, prefix, fname, lname, major, gen, adviser, status, gra, date;
	string gpa;
	string number;
	
	if(s.login()=="1"){

	s.checkStu();
	do{
		cout << " ------------------------" << endl;
		cout << " 1. Show Student"          << endl;
		cout << " 2. Add Student"           << endl;
		cout << " 3. Delete Student"        << endl;
		cout << " 4. Save Student"          << endl;
		cout << " 5. Student Search"        << endl;
		cout << " 6. Edit Student Name"     << endl;
		cout << " 0. Logout"               << endl;
		cout << " ------------------------" << endl;
		cout << " Enter Number(0-6) : ";
		cin >> number;
		
		if(number == "1"){
			s.showStudentList();
			cout << "What kind of sort do you want" << endl;
			cout << "1. Student ID : Max - Min" << endl;
			cout << "2. Student ID : Min - Max" << endl;
			cout << "3. Student Name : A - Z" << endl;
			cout << "4. Student Name : Z - A" << endl;
				string num;
				cout << " : ";
				cin >> num;
				if(num=="1"){
					s.sortMaxMin();
				}
				if(num=="2"){
					s.sortMinMax();
				}
				if(num=="3"){
					s.sortAZ();
				}
				if(num=="4"){
					s.sortZA();
				}
			s.showStudentList();
		}
		if(number == "2"){
			cout << "Input Student ID : ";
			cin >> id;
				if(!s.checkAdd(id)){
					cout << "Input Student Year : ";
					cin >> year;
					cout << "Input Prefix 1 = Mr. 2 = Miss : ";
					cin >> prefix;
						if(prefix == "1"){
							prefix = "Mr.";
							cout << "Input Student Frist Name : Mr. ";
							cin >> fname;
							cout << "Input Student Last Name : ";
							cin >> lname;
						}
						else if(prefix == "2"){
							prefix = "Miss.";
							cout << "Input Student Frist Name : Miss. ";
							cin >> fname;
							cout << "Input Student Last Name : ";
							cin >> lname;
						}
					
					cout << "Input Student GPA : ";
					cin >> gpa;
					cout << "Input Student Major : ";
					cin >> major;
					cout << "Input Student Generation : ";
					cin >> gen;
					cout << "Input Student Adviser : ";
					cin >> adviser;
					cout << "Input Status 1 = Studying. 2 = Graduated : ";
					cin >> status;
						if(status == "1"){
							status = "Studying";
						}
						else if(status == "2"){
							status = "Graduated";
							cout << "Input Date of Graduated. Ex. 12/04/2536 : ";
							cin >> date;
						}
					s.add(id, year, prefix, fname, lname, gpa, major, gen, adviser, status, date);
				}
		}
		if(number == "3"){
			string search;
			s.showStudentList();
				cout << "Enter The Student ID To Delete : ";
				cin >> search;
			if(s.checkRem(search)){
				cout << "In case of graduated, can not delete student.\n\n";
			}
			else{
				s.remove(search);
			}
		}
		if(number == "4"){
			s.writeFile();
			cout << "\n Save complete !!!!!!!!!!!! \n";
		}
		if(number == "5"){
			string id;
			cout << "Enter student ID : ";
			cin >> id;
			if(s.checkId(id)){
				s.search(id);
			}
			else{
				cout << "No Information ! ! !" << endl;
			}
		}  
		if(number == "6"){
				string id;
				s.showStudentList();
				cout << "Enter  Student ID : ";
				cin >> id;
					if(s.checkId(id)){
						s.edit(id);
					}
					else{
						cout << "Not Found ! ! !" << endl;
					}
		}
		}while(number != "0");
		
	}
	else{
		return 0;
	}
}


