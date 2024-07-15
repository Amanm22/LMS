#include <bits/stdc++.h>
using namespace std;



struct Date {
    int d, m, y;
};

const int monthDays[12]
    = { 31, 28, 31, 30, 31, 30,
       31, 31, 30, 31, 30, 31 };

int countLeapYears(Date d)
{
    int years = d.y;
 
    if (d.m <= 2)
        years--;
    return years / 4
           - years / 100
           + years / 400;
}

int getDifference(Date dt1, Date dt2)
{
    long int n1 = dt1.y * 365 + dt1.d;
 
    for (int i = 0; i < dt1.m - 1; i++)
        n1 += monthDays[i];
    n1 += countLeapYears(dt1);
 
    long int n2 = dt2.y * 365 + dt2.d;
    for (int i = 0; i < dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);
    return (n2 - n1);
}

bool isLeap(int y)
{
    if (y%100 != 0 && y%4 == 0 || y %400 == 0)
        return true;
 
    return false;
}

int offsetDays(int d, int m, int y)
{
    int offset = d;
 
    switch (m - 1)
    {
    case 11:
        offset += 30;
    case 10:
        offset += 31;
    case 9:
        offset += 30;
    case 8:
        offset += 31;
    case 7:
        offset += 31;
    case 6:
        offset += 30;
    case 5:
        offset += 31;
    case 4:
        offset += 30;
    case 3:
        offset += 31;
    case 2:
        offset += 28;
    case 1:
        offset += 31;
    }
 
    if (isLeap(y) && m > 2)
        offset += 1;
 
    return offset;
}


void revoffsetDays(int offset, int y, int *d, int *m)
{
    int month[13] = { 0, 31, 28, 31, 30, 31, 30,
                      31, 31, 30, 31, 30, 31 };
 
    if (isLeap(y))
        month[2] = 29;
 
    int i;
    for (i = 1; i <= 12; i++)
    {
        if (offset <= month[i])
            break;
        offset = offset - month[i];
    }
 
    *d = offset;
    *m = i;
}

//Code for addDate and getDifference are taken from GFG

void addDays(int d1, int m1, int y1, int x)
{
    int offset1 = offsetDays(d1, m1, y1);
    int remDays = isLeap(y1)?(366-offset1):(365-offset1);
    int y2, offset2;
    if (x <= remDays)
    {
        y2 = y1;
        offset2 = offset1 + x;
    }
    else
    {
        x -= remDays;
        y2 = y1 + 1;
        int y2days = isLeap(y2)?366:365;
        while (x >= y2days)
        {
            x -= y2days;
            y2++;
            y2days = isLeap(y2)?366:365;
        }
        offset2 = x;
    }
    int m2, d2;
    revoffsetDays(offset2, y2, &d2, &m2);
    cout<<"The due date for returning the book is "<<d2<<' '<<m2<<' '<<y2;
    return;
}

 

class Book{
public:
	string title ;
	string author ;
	string isbn ;
	string publication ;
    int avail = 1;
    string issued = "Available";
};

class user{

public:
	string name ;
	string userid ;
	string password ;
};

class Student: public user {
public:
	int fine ;
	vector<Book> issued ;
    vector<Date> date;
    void clear_fine_amt(){
        fine=0;
        cout<<"Transaction Successful\n";
    }
};

class Professor: public user {
public:
	int fine ;
	vector<Book> issued ;
    vector<Date> date;
    void clear_fine_amt(){
        fine=0;
        cout<<"Transaction Successful\n";
    }
};

vector<Student> Stud;
vector<Professor>Prof;
vector<Book> book;

class UserDatabase{
public:
    
	void add_user();
    void del_user();
    void update_user();
    void list_users();
    void search_user();
    void calculate_fine(int pos, int type);
};

class BookDatabase : public Book{
public:
    
	void add_book();
    void del_book();
    void update_book();
    void search_book();
    void list_books();
    void Book_Request(int pos, int type);
    void check_book();
    void Book_Return(int pos,int type);
    void show_due_date();

};

void BookDatabase :: search_book(){
   string isbn;
   cout<<"Enter the title of the book: ";
   cin>>isbn;
   for(int i=0;i<book.size();++i){
       if(book[i].title==isbn){
           cout<<"Title: "<<book[i].title<<"\n";
           cout<<"Author: "<<book[i].author<<"\n";
           cout<<"ISBN : "<<book[i].isbn<<"\n";
           cout<<"Publication: "<<book[i].publication<<"\n";
           if(book[i].avail==1){
               cout<<"Status: Available"<<"\n";
               cout<<"Issued by user with userid: "<<book[i].issued<<'\n';
           }
           else{
               cout<<"Status: Not Available"<<"\n";
           }
       }
   }

}

void BookDatabase:: show_due_date(){
    cout<<"Please enter the isbn of the book whose due date is to be viewed: ";
    string isbn;
    cin>>isbn;
    int bn=-1;
    for(int i=0;i<book.size();++i){
       if(book[i].isbn==isbn){
           bn=i;
           break;
       }
    }
    if(bn==-1){
        cout<<"Book Not Found\n";
    }
    else{
        for(int i=0;i<Stud.size();++i){
           if(Stud[i].userid==book[bn].issued){
               for(int j=0;j<Stud[i].issued.size();++j){
                   if(isbn==Stud[i].issued[j].isbn){
                       addDays(Stud[i].date[j].d,Stud[i].date[j].m,Stud[i].date[j].y,30);
                       return;
                   }
               }
           }
        }

        for(int i=0;i<Prof.size();++i){
           if(Prof[i].userid==book[bn].issued){
               for(int j=0;j<Prof[i].issued.size();++j){
                   if(isbn==Prof[i].issued[j].isbn){
                       addDays(Prof[i].date[j].d,Prof[i].date[j].m,Prof[i].date[j].y,60);
                       return;
                   }
               }
           }
        }

        cout<<"Book has not been issued\n";
        return;

    }
}


void UserDatabase :: add_user(){
      string name,userid,pswd;
      cout<<"Please enter the name";
      cin>>name;
      cout<<'\n';
      cout<<"Please enter the userid";
      cin>>userid;
      cout<<'\n';
      cout<<"Please enter the password";
      cin>>pswd;
      cout<<'\n';
      cout<<"Press 1 if this user is a Student and 0 otherwise";
      int m;
      cin>>m;
      if(m==1){
        Student s1;
        s1.name = name;
        s1.userid = userid;
        s1.password = pswd;
        Stud.push_back(s1);
      }
      else{
        Professor s1;
        s1.name = name;
        s1.userid = userid;
        s1.password = pswd;
        Prof.push_back(s1);
      }

}

void BookDatabase :: add_book(){
    string title, author, isbn, publication;
    cout<<"Please enter the title of the book to be added";
    cin>>title;
    cout<<'\n';
    cout<<"Please enter the author of the book to be added";
    cin>>author;
    cout<<'\n';
    cout<<"Please enter the isbn of the book to be added";
    cin>>isbn;
    cout<<'\n';
    cout<<"Please enter the publication of the book to be added";
    cin>>publication;
    cout<<'\n';
    
    Book b;
    b.title=title;
    b.author=author;
    b.isbn=isbn;
    b.publication=publication;

    book.push_back(b);
}

void BookDatabase :: del_book(){
    string isbn;
    cout<<"Please enter the isbn of the book to be deleted";
    cin>>isbn;
    cout<<'\n';
    auto v=book.begin();
    for(auto it:book){
        if(it.isbn==isbn){
            book.erase(v);
        }
        v++;
    }
    if(v==book.end()){
        cout<<"Sorry, book not found\n";
    }
    else{
        cout<<"Book deleted successfully\n";
    }
}

void BookDatabase :: update_book(){
    string title, author, isbn, publication;
    cout<<"Please enter the isbn of the book to be updated";
    cin>>isbn;
    cout<<'\n';

    for(auto it:book){
        if(it.isbn==isbn){
           int temp;
           cout<<"Is the title of the book to be updated? Press 1 for Yes and 0 for No";
           cin>>temp;
           cout<<'\n';
           if(temp){
               cout<<"Please enter the title of the book to be updated";
               cin>>title;
               it.title=title;
           }
           cout<<"Is the author of the book to be updated? Press 1 for Yes and 0 for No";
           cin>>temp;
           cout<<'\n';
           if(temp){
               cout<<"Please enter the author of the book to be updated";
               cin>>author;
               it.author=author;
           }
           cout<<"Is the isbn of the book to be updated? Press 1 for Yes and 0 for No";
           cin>>temp;
           cout<<'\n';
           if(temp){
               cout<<"Please enter the isbn of the book to be updated";
               cin>>isbn;
               it.isbn=isbn;
           }
           cout<<"Is the publication of the book to be updated? Press 1 for Yes and 0 for No";
           cin>>temp;
           cout<<'\n';
           if(temp){
               cout<<"Please enter the publication of the book to be updated";
               cin>>publication;
               it.publication=publication;
           }

        }
    }
}



void UserDatabase :: del_user(){
    string id;
    int type;
    cout<<"Enter the userid of the user to be deleted";
    cin>>id;
    cout<<'\n';
    cout<<"Enter 1 if the user is a Student and 2 otherwise";
    cin>>type;
    cout<<'\n';
    if(type==1){
       auto s = Stud.begin();
       for(auto it: Stud){
           if(it.userid==id){
              Stud.erase(s);
           }
           s++;
       }
    }
    else{
       auto s = Prof.begin();
       for(auto it: Prof){
           if(it.userid==id){
              Prof.erase(s);
           }
           s++;
       }
    }
    
}

void UserDatabase :: update_user(){
    string userid,name;
    string id;
    int type;
    cout<<"Enter the userid of the user to be updated";
    cin>>id;
    cout<<"Enter 1 if the user is a Student and 2 otherwise";
    cin>>type;
    if(type==1){
       auto s = Stud.begin();
       for(auto it: Stud){
           int temp;
           cout<<"Is the name of the user to be updated? Press 1 for Yes and 0 for No";
           cin>>temp;
           if(temp){
               cout<<"Please enter the name of the user to be updated";
               cin>>name;
               it.name=name;
           }
           cout<<"Is the userid of the user to be updated? Press 1 for Yes and 0 for No";
           cin>>temp;
           if(temp){
               cout<<"Please enter the userid of the user to be updated";
               cin>>userid;
               it.userid=userid;
           }
           s++;
       }
    }
    else{
       auto s = Prof.begin();
       for(auto it: Prof){
           int temp;
           cout<<"Is the name of the user to be updated? Press 1 for Yes and 0 for No";
           cin>>temp;
           if(temp){
               cout<<"Please enter the name of the user to be updated";
               cin>>name;
               it.name=name;
           }
           cout<<"Is the userid of the user to be updated? Press 1 for Yes and 0 for No";
           cin>>temp;
           if(temp){
               cout<<"Please enter the userid of the user to be updated";
               cin>>userid;
               it.userid=userid;
           }
           s++;
       }
    }
}

void BookDatabase :: list_books(){
    int count=0;
    for(auto it: book){
        if(it.avail){
            cout<<it.title<<' ';
            count++;
        }
    }
    if(count==0){
        cout<<"No Books Available\n";
    }
    return;
    
}

void BookDatabase :: Book_Request(int pos, int type){
    string isbn;
    cout<<"Enter the ISBN of the book to be issued: ";
    cin>>isbn;
    int c=0;
    for(auto it: book){
        if(it.isbn==isbn){
            if(it.avail==1){
               if(type==1){
                   if(Stud[pos].issued.size()<5){
                     Stud[pos].issued.push_back(it);
                     cout<<"Please enter today's date in dd mm yyyy format";
                     int d,m,y;
                     cin>>d>>m>>y;
                     Stud[pos].date.push_back({d,m,y});
                     book[c].issued=Stud[pos].userid;
                     book[c].avail=0;
                     cout<<"Book Issued Successfully\n";
                   }
                   else{
                       cout<<"Maximum Capacity reached";
                   }
               }
               else{
                     Prof[pos].issued.push_back(it);
                     cout<<"Please enter today's date in dd mm yyyy format";
                     int d,m,y;
                     cin>>d>>m>>y;
                     Prof[pos].date.push_back({d,m,y});
                     book[c].issued=Prof[pos].userid;
                     book[c].avail=0;
                     cout<<"Book Issued Successfully\n";
               }
            }
            else{
              cout<<"Sorry, the book is currently unavailable\n";
            }
        }
        c++;
    }
}


void BookDatabase :: Book_Return(int pos, int type){
    
    int bookno=0;
    int q=0;
    cout<<"Enter the isbn of the book to be returned: ";
    string isbn;
    cin>>isbn;
    for(auto it: book){
       if(it.isbn==isbn){
           q=1;
           break;
       }
       bookno++;
    }
    if(q=0){
        cout<<"Book not found\n";
        return;
    }
    int fine=0;
    if(type==1){
    for(int i=0;i<Stud[pos].issued.size();++i){
       if(Stud[pos].issued[i].isbn==isbn){
           cout<<"Please enter today's date in dd mm yyyy format";
            int d,m,y;
            cin>>d>>m>>y;
            int g= getDifference(Stud[pos].date[i],{d,m,y});
            if(g>30){
                fine=(2*(g-30));
            }
            cout<<"Your fine for this transaction is Rs."<<fine<<'\n';
            Stud[pos].issued.erase(Stud[pos].issued.begin()+i);
            Stud[pos].date.erase(Stud[pos].date.begin()+i);
            book[bookno].avail=1;
            book[bookno].issued="Available";
            return;
       }
    }
    }  
    else{
    for(int i=0;i<Prof[pos].issued.size();++i){
       if(Prof[pos].issued[i].isbn==isbn){
           cout<<"Please enter today's date in dd mm yyyy format";
            int d,m,y;
            cin>>d>>m>>y;
            int g= getDifference(Prof[pos].date[i],{d,m,y});
            if(g>60){
                fine=(5*(g-60));
            }
            cout<<"Your fine for this transaction is Rs."<<fine<<'\n';
            Prof[pos].issued.erase(Prof[pos].issued.begin()+i);
            Prof[pos].date.erase(Prof[pos].date.begin()+i);
            book[bookno].avail=1;
            book[bookno].issued="Available";
            return;
       }
    }
    }
            

    //cout<<"User not found\n";
    return;

}

void UserDatabase :: calculate_fine(int pos, int type){
   int fine=0;
   int d,m,y;
   cout<<"Please enter today's date in dd mm yyyy format";
   cin>>d>>m>>y;
   Date ret = {d,m,y};
   int g;
   if(type==1){
   for(int i=0;i<Stud[pos].issued.size();++i){
      g = getDifference(Stud[pos].date[i],ret);
      if(g>30){
          fine+=2*(g-30);
      }
   }
   cout<<"Your total fine is Rs."<<fine<<'\n';
   Stud[pos].fine=fine;
   }
   else{
     for(int i=0;i<Prof[pos].issued.size();++i){
      g = getDifference(Prof[pos].date[i],ret);
      if(g>60){
          fine+=5*(g-60);
      }
   }
     cout<<"Your total fine is Rs."<<fine<<'\n';
     Prof[pos].fine=fine;
   }
}

void BookDatabase :: check_book(){
   cout<<"Please enter the isbn number of the book to be checked: ";
   string isbn;
   cin>>isbn;
   for(int i=0;i<book.size();++i){
       if(book[i].avail==0){
           cout<<"The book has been issued by user "<<book[i].issued;
           return;
       }
   }
   cout<<"The book has not been issued by any user\n";
   return;
}

void UserDatabase :: search_user(){
   cout<<"Please enter the userid of the user: ";
   string id;
   cin>>id;
   for(int i=0;i<Stud.size();++i){
       if(Stud[i].userid==id){
           cout<<"Name: "<<Stud[i].name<<'\n';
           cout<<"Userid: "<<Stud[i].userid<<'\n';
           cout<<"Type: Student \n";
           cout<<"Books issued: ";
           for(int j=0;j<Stud[i].issued.size();++j){
               cout<<Stud[i].issued[j].title<<"\n";
           }
       }
   }
   for(int i=0;i<Prof.size();++i){
       if(Prof[i].userid==id){
           cout<<"Name: "<<Prof[i].name<<'\n';
           cout<<"Userid: "<<Prof[i].userid<<'\n';
           cout<<"Type: Professor \n";
           cout<<"Books issued: ";
           for(int j=0;j<Prof[i].issued.size();++j){
               cout<<Prof[i].issued[j].title<<"\n";
           }
       }
   }
   return;
}

int main(){
    UserDatabase u;
    BookDatabase b;
   
    string id_lib="library",pswd_lib="abcd@1234";

    
    //Test Data Small

     Student q;
     q.name='Shrey'; q.userid='Shrey'; q.password='Shrey_Mehta';
     Stud.push_back(q);

     q.name='Kartik'; q.userid='Kartik'; q.password='Kartik_Mehta';
     Stud.push_back(q);

     Book w;
     w.title='Harry Potter'; w.author='J K Rowling'; w.isbn='123456'; w.publication='Scholastic Press';
     book.push_back(w);

     w.title='Alice in the Wonderland'; w.author='Lewis Caroll'; w.isbn='654321'; w.publication='MacMillan';
     book.push_back(w);
     

    //



    cout<<"Hello\n";
    int type;
    int count=0;
while(1){
    int test=0;
    cout<<"Please enter 1 if you are a student, 2 if you are a Professor or 3 if you are the Librarian: ";
    cin>>type;

    string id,pass;

    cout<<"Please enter your userid";
    cin>>id;
    cout<<"Please enter the password";
    cin>>pass;
    int pos = 0;
    if(type==3){
        if(id==id_lib&&pass==pswd_lib){
          cout<<"Welcome to your account, librarian\n";
          test=1;
        }
        else{
          cout<<"Something's wrong\n";
          count++;
          if(count==3){
              exit(0);
          }
        }
    }
    else if(type==2){
        for(auto it:Prof){
           if(it.userid==id&&it.password==pass){
               cout<<"Welcome to your account\n";
               test=1;
               break;
           }
           pos++;
        }
        if(test==0){
            cout<<"Something's wrong\n";
            count++;
            if(count==3){
                exit(0);
            }
        }
    }
    else{
         for(auto it:Stud){
           if(it.userid==id&&it.password==pass){
               cout<<"Welcome to your account\n";
               test=1;
               break;
           }
           pos++;
        }
        if(test==0){
            cout<<"Something's wrong\n";
            count++;
            if(count==3){
                exit(0);
            }
        }
    }
     if(test==0){
        continue;
    }


    int option;

    ////////////////////////////////////////////////////////////////////


while(type==3){
    cout << "Select the task you want to perform: \n1. Add a user\n";
    cout << "2. Add a book\n";
    cout << "3. Update a book \n";
    cout << "4. Delete a book\n";
    cout << "5. Update a user\n";
    cout << "6. Delete a user\n";
    cout << "7. List all the books\n";
    cout << "8. List all the users\n";
    cout << "9. Check the user having a particular book\n";
    cout << "10. See the list of all available books\n" ;
    cout << "11. Get all the details of the user\n" ;
    cout << "12. Clear fine of a student\n" ;
    cout << "13. Search for a book" ;    


    cin>>option;
    string id1;
    switch(option){
					case 1:
						u.add_user() ;
                        break ;
					case 2:
						b.add_book() ;
                        break ;
					case 3:
						b.update_book(); 
                        break ;
					case 4:
						b.del_book() ;
                        break ;
					case 5:
						u.update_user() ;
                        break ;
					case 6:
						u.del_user() ;
                        break ;
					case 7:
						for(auto it: book) cout << it.title << '\n' ;
                        break ;
					case 8:
						for(auto it: Stud) cout << it.name << '\n' ;
						for(auto it: Prof) cout << it.name << '\n' ;
                        break ;
					case 9:
						b.check_book() ;
                        break ;
                    case 10:
                        b.list_books();
                        break;
                    case 11:
                        u.search_user();
                        break;
                    case 12:
                        cout<<"Please enter the userid of the user: ";
                        cin>>id1;
                        for(int k=0;k<Stud.size();++k){
                            if(Stud[k].userid==id){
                                Stud[k].clear_fine_amt();
                                cout<<"Transaction Successful\n";
                            }
                        }
                        for(int k=0;k<Prof.size();++k){
                            if(Prof[k].userid==id){
                                Prof[k].clear_fine_amt();
                                cout<<"Transaction Successful\n";
                            }
                        }
                        break;
                    case 13:
                        b.search_book();
                        break;
                    default:
                        cout<<"Sorry, try again";		
				}
        cout<<"If you want to make more changes, press 1 else press 0";
        int p;
        cin>>p;
        if(p==0){
            break;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////
   

   while(type==1||type==2){
    cout << "Select the task you want to perform:\n";
    cout << "1. List all the books available\n";
    cout << "2. Calculate your fine amount\n";
    cout << "3. Issue a Book\n" ;
    cout << "4. Return a Book\n" ;
    cout << "5. List of books issued by you\n" ;
    cout << "6. Show due date for a book" ;
    //cout<<type<<'\n';
    cin>>option;
    cout<<'\n';
    switch(option){
					case 1:
						for(auto it: book){
                            if(it.avail==1){
                                cout<<it.title<<" ";
                            }
                        }
                        break ;
                    case 2:
                       u.calculate_fine(pos,type);
                        break;
                    case 3:
                        if(type==1){ 
                                   if(Stud[pos].issued.size()<5){
                                      b.Book_Request(pos,1);
                                   }
                                   else{
                                       cout<<"Max capacity of books reached\n";
                                   }
                        }
                        else{
                                      b.Book_Request(pos,2);
                            }
                        break;
                    case 4:
                         if(type==1){
                            b.Book_Return(pos,1);
                         }
                         else{
                            b.Book_Return(pos,2); 
                         }  
                        break;
                    case 5:
                        if(type==1){
                           for(auto it: Stud[pos].issued){
                               cout<<it.title<<' ';
                           }
                        }
                        else{
                           for(auto it: Prof[pos].issued){
                               cout<<it.title<<' ';
                           }
                        }
                        break;
                    case 6:
                        b.show_due_date();
                        break;
                    default:
                        cout<<"Sorry, try again";		
				}
        cout<<"If you want to make more changes, press 1 else press 0";
        int p;
        cin>>p;
        if(p==0){
            break;
        }
    }
        

    //////////////////////////////////////////////////////////////////////////////////////


    cout<<"Press 0 if you want to exit and 1 otherwise: ";
        int e;
        cin>>e;
        if(e==0){
            exit(0);
        }
}
}