/*************************************************************************************/
/*                                     Oguzhan SENTURK                               */
/*                                      			                     */
/*                                   osenturk@gtu.edu.tr                             */
/*************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include "administrator.h"
#include "lecturer.h"
#include "student.h"
#include "classroom.h"

#define MAX 16	//max lecture hour 
#define MIN 9	//min lecture hour
#define LEVEL_4 23 //credit
#define LEVEL_3 22 //credit
#define LEVEL_2 21 //credit
#define LEVEL_1 20 //credit

using namespace std;
using namespace AdministratorNS;
using namespace LecturerNS;
using namespace StudentNS;
using namespace ClasroomNS;

int word_count(string s);	//function to calculate count of word in string
void set_class(Lecturer lecturer_array[], int number_of_lecturer);	//function to set class
void read_lecturers_file(int& number_of_lecturer);	//function to calculate count of lecturer
void set_struct_class(Course lecture[], int number_of_lectures, Classroom class_room[], int number_of_classrooms); //function to set structs
void read_courses_classrooms_file(int& number_of_lectures, int& number_of_classrooms);	//function to calculate count of lectures and classrooms
void set_must_take_course(Lecturer lecturer_array[],int number_of_lecturer, Course lecture[], int number_of_lectures);	//function to calculate overlap classroom
bool overlap(Course copy_lecture[], Classroom class_room[], string id_class1,int  id_course, int index_of_lecture, int index_of_class, string lecture_time); // function to calculate overlap 
void parse_string(string s,vector<Student>& stu); 	//function to parse string (Murat Boz 111 3)
void show_lecture(Course lecture[],int number_of_lectures); // function to show lecture
void classroom_course(Classroom class_room,int number_of_classrooms,Course copy_lecture,int number_of_lectures); // function to set course which the class assigned

void read_courses_classrooms_file(int& number_of_lectures, int& number_of_classrooms)	//function to calculate count of lectures and classrooms
{
	string control;
	number_of_lectures = 0, number_of_classrooms = 0;
	ifstream inp("courses_classrooms.txt");		//open txt to reading

	while (control != "CLASSROOMS")
	{
		getline(inp,control);
		number_of_lectures++;
	}
	number_of_lectures = number_of_lectures -2;

	while (!inp.eof())	//end of file check
	{	
		getline(inp,control);	
		number_of_classrooms++;
	}
	inp.close();
}

void set_struct_class(Course lecture[], int number_of_lectures, Classroom class_room[], int number_of_classrooms) //function to set structs
{
	string data;
	ifstream inp("courses_classrooms.txt");	//open txt to reading
	inp >> data;
	// 	lecture setting (4 OOP 241 4 6 PROG)
	for (int i = 0; i < number_of_lectures; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			inp >> data;
			if(j == 0 )
			{
				lecture[i].id = stoi(data);
			}
			else if(j == 1)
			{
				lecture[i].name = data;
			}
			else if(j == 2)
			{
				lecture[i].code = stoi(data);
					
			}
			else if(j == 3)
			{
				lecture[i].credit = stoi(data);
			}
			else if(j == 4)
			{
				lecture[i].total_hours = stoi(data);
			}
			else if(j == 5)
			{
				lecture[i].field = data;
				lecture[i].isMandotary = 1;
			}
		}
	}
	inp >> data;
	//classroom setting 1 Z23 60
	for (int i = 0; i < number_of_classrooms; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			inp >> data;
			if(j == 0 )
			{
				class_room[i].id = stoi(data);
			}
			else if(j == 1)
			{
				class_room[i].c_no = data;
			}
			else if(j == 2)
			{
				class_room[i].capacity = stoi(data);
				class_room[i].student_inroom = 0;
			}
		}
	}
	inp.close();
}

void read_lecturers_file(int& number_of_lecturer)	//function to calculate count of lecturer
{
	string control;
	number_of_lecturer = 0;
	ifstream inp("lecturers.txt");		//open txt to reading

	while (!inp.eof())	//end of file check
	{	
		getline(inp,control);	
		number_of_lecturer++;
	}
	inp.close();
}

void set_class(Lecturer lecturer_array[], int number_of_lecturer)	//function to set class
{
	string data;
	ifstream inp("lecturers.txt");	//open txt to reading
	// 	lecturer setting (1 IBRAHIM SOGUK PROF CYBER,MATH,NET)
	for (int i = 0; i < number_of_lecturer; ++i)
	{	
		for (int j = 0; j < 5; ++j)
		{
			inp >> data;
			if(j == 0 ) 
			{
				lecturer_array[i].setter_lecturer_personal_id(stoi(data));
			}
			else if(j == 1) 
			{
				lecturer_array[i].setter_lecturer_name(data);
			}
			else if(j == 2)
			{
				lecturer_array[i].setter_lecturer_surname(data);		
			}
			else if(j == 3)
			{
				lecturer_array[i].setter_lecturer_title(data);
			}
			else if(j == 4)
			{
				lecturer_array[i].setter_lecturer_professions(data);
			}
		}
	}
}

int word_count(string s)	//function to calculate count of word in string
{
	string delim = " ";		//parse string by whitespace
	int count = 0;		//count of word in string
    auto start = 0U;
    auto end = s.find(delim);
    while (end != string::npos)	//parse to string till the end
    {
        (s.substr(start, end - start)) ;
        start = end + delim.length();
        end = s.find(delim, start);
        count ++;
    }
    (s.substr(start, end)) ;
	return count;
}

int has_coma(string s)	//function to calculate count of word in string
{
	string delim = ",";		//parse string by whitespace
	int count = 0;		//count of word in string
    auto start = 0U;
    auto end = s.find(delim);
    while (end != string::npos)	//parse to string till the ende
    {
        (s.substr(start, end - start)) ;
        start = end + delim.length();
        end = s.find(delim, start);
        count ++;
    }
    (s.substr(start, end)) ;
	return count;
}

void set_must_take_course(Lecturer lecturer_array[],int number_of_lecturer, Course lecture[], int number_of_lectures) //funciton to hold lecuteres which lecturer must take
{
	int a;
	for (int k = 0; k < number_of_lectures; ++k)
	{
		int count = 0;
		for (int i = 0; i < number_of_lecturer; ++i)
		{
			for (int j = 0; j < lecturer_array[i].professions.size(); ++j)
			{
				if(lecturer_array[i].professions[j] == lecture[k].field)
				{
					count ++;
					a = i;
					break;
				}
			}
		}
		if(count == 1)
		{
			lecturer_array[a].must_take_course.push_back(lecture[k]);
		}
	}
}

bool overlap(Course copy_lecture[], Classroom class_room[], string id_class1,int  id_course,int index_of_lecture,int index_of_class, string lecture_time) //function to calculate overlap classroom
{
	if(copy_lecture[index_of_lecture].class_name.size() == 0 && class_room[index_of_class].int_date.size() == 0) // if student' schedule is empty
	{
		return true;
	}
 		// overlap algorithm :
 		// My algorithm contol each lecture with other lecture
 		// Example student's schedule is 1 and 2 , new lecture is 3
 		// (2,3) - 1 , (1,3) - 2 , (1,2) - 3
 		vector<string> comparision_vector;	//holds lecture dates to be checked (MON_11-13,THURS_12-10 etc)							
 		vector<int> int_comparision_vector;	//holds int version lecture dates to be checked (MON_11-13,THURS_12-10 etc)			
		int lecture_int;

		string s = lecture_time;
	    string delim = ",";		//parse string by comma
	    auto start = 0U;
	    auto end = s.find(delim);
	    while (end != string::npos)
	    {																	//EX: MON_11-13,THURS_12-10
	        comparision_vector.push_back(s.substr(start, end - start)) ;	//inside vector : { (MON_11-13) , (THURS_12-10) }
	        start = end + delim.length();
	        end = s.find(delim, start);
	    }
	    comparision_vector.push_back(s.substr(start, end)) ;

	    for (int i = 0; i < comparision_vector.size(); ++i)
		{
			s = comparision_vector[i];
		  	delim = "_";	//parse string by underscroe
			start = 0U;									//EX : MON_11-13
			end = s.find(delim);
		    string a =s.substr(start, end - start);		//variable a holds MON
		    start = end + delim.length();
		    end = s.find(delim, start);
		    string b = s.substr(start, end);			//variable b holds 11-13
		 	delim = "-";	//parse string by hyphen
			start = 0U;
			end = b.find(delim);
		    string c =b.substr(start, end - start);		// variable c holds 11
		    start = end + delim.length();
		    end = b.find(delim, start);			
		   	string d = b.substr(start, end);			//variable d holds 13
		   	if(a == "MON")
		   	{
		   		lecture_int = 100;
		   	}
		   	else if(a == "TUE" )
		   	{
		   		lecture_int = 200;
		   	}
		   	else if(a == "WED")
		   	{
		   		lecture_int = 300;
		   	}
		   	else if(a == "THU")
		   	{
		   		lecture_int = 400;
		   	}
		   	else if(a == "FRI")
		   	{
		   		lecture_int = 500;
		   	}
		   	for (int j = stoi(c); j < stoi(d); j++)
		   	{																
		   		int_comparision_vector.push_back(lecture_int + j);	//vector inside :{ 110, 111 } for MON_11-13
		   	}
	    }

    	int  total_overlap = 0;		//for every comparision variable initialize 0. holds count of overlap hours
    	for (int i = 0; i <  class_room[index_of_class].int_date.size(); ++i)
    	{
    		for (int j = 0; j < int_comparision_vector.size(); ++j)
    		{
    			if( class_room[index_of_class].int_date[i] == int_comparision_vector[j])
    			{
    			total_overlap ++ ;
    			}
    		}
    	}

	if(total_overlap == 0)	// no overlap
	{
		return true;
	}
	else
	{
		return false;
	}
}

void show_lecture(Course lecture[],int number_of_lectures) // function to show lecture
{
	for (int i = 0; i < number_of_lectures; ++i)
	{
		cout << "(" << lecture[i].id << ") " << lecture[i].name << " ";
	}
	cout << endl;
}

void parse_string(string s,vector<Student>& stu)	//function to parse string (Murat Boz 111 3)
{
	static int i = 0;		//i is variable to count of student object
	int no_unique = 0;		// variable to check is it student number is unique
	string name, surname;
	int student_no, level;
    string delim = " ";		//parse string by whitespace
    auto start = 0U;
    auto end = s.find(delim);
    name = (s.substr(start, end - start));
    start = end + delim.length();
    end = s.find(delim, start);
    surname = (s.substr(start, end - start));
    start = end + delim.length();
    end = s.find(delim, start);
    student_no = stoi((s.substr(start, end - start)));	
    start = end + delim.length();
    end = s.find(delim, start);
    level = stoi((s.substr(start, end - start)));	
    start = end + delim.length();
    end = s.find(delim, start);
    for (int j = 0; j < stu.size(); ++j)
    {
    	if(stu[j].getter_student_no() == student_no)
    	{
    		no_unique = 1;
    	}
    }
    if(no_unique == 1)
    {
    	cout << "ERROR: STUDENT NUMBER HAS BEEN PREVİOUSLY TAKEN"<< endl;
    }
    else{
    	stu.resize(i + 1);		// vector size +1
    	cout<< "DONE!"<< endl;
    	stu[i].setter(name, surname ,student_no, level); 	//set student object
    	i++;
    }
}

void classroom_course(Classroom class_room[],int number_of_classrooms,Course copy_lecture[],int number_of_lectures) // function to set course which the class is assigned
{
	for (int i = 0; i < number_of_lectures; ++i)
	{
		for (int j = 0; j < copy_lecture[i].class_name.size(); ++j)
		{
			for (int k = 0; k < number_of_classrooms; ++k)
			{
				if(class_room[k].c_no == copy_lecture[i].class_name[j])
				{
					class_room[k].course_name.push_back(&copy_lecture[i]);
				}
			}
		}
	}
}

int main()
{
	srand(time(NULL));	// RANDOM NUMBER
	int number_of_lectures, number_of_classrooms, number_of_lecturer;
	read_courses_classrooms_file(number_of_lectures,number_of_classrooms);		// calculate count of lecture and classrooms in courses_classrooms.txt
	read_lecturers_file(number_of_lecturer);	// calculate count of lecturer in lecturers.txt
	Course lecture[number_of_lectures];		// array of course struct
	Course copy_lecture[number_of_lectures];	// array of course struct
	vector<Student> stu;
	Administrator admin;
	int copy_number_of_lectures = number_of_lectures;
	Classroom class_room[number_of_classrooms];		// array of classrom struct
	Lecturer lecturer_array[number_of_lecturer];	// array of lecturer class
	set_struct_class(lecture, number_of_lectures, class_room, number_of_classrooms); // initialize struct
	set_class(lecturer_array, number_of_lecturer);	// initialize class
	set_must_take_course(lecturer_array, number_of_lecturer, lecture, number_of_lectures);
	string full_command; 	// variable holds whole user's command
	string hyphen_command;		// variable holds user's hyphen command (-propose, -assign, -timetable etc);
	string s;	// variable holds command after -propose, -assign, -timetable etc

	for (int i = 0; i < number_of_lectures; ++i)
	{
		copy_lecture[i]=lecture[i];
	}

	Label:	// INTERFACE START 
	getline(cin, full_command);	// get input from user
	s = full_command;
	string delim = " ";	// parse string by whitespace
    auto start = 0U;
    auto end = s.find(delim);
    hyphen_command = (s.substr(start, end - start));
   	start = end + delim.length();
    s = (s.substr(start, end - start));

	if (hyphen_command == "-propose")
	{
		int nolecturer = 1; 	//nolecturer is a flag to check invalid lecturer if value 1 NO LECTURER
		auto start = 0U;
	    auto end = s.find(delim);
	    int pid = stoi((s.substr(start, end - start))); // PERSONAL ID
		start = end + delim.length();
		s = (s.substr(start, end - start));

		for (int i = 0; i < number_of_lecturer; ++i)
		{
			if (pid == lecturer_array[i].getter_lecturer_personal_id())
			{
				lecturer_array[i].proposeCourse(s);
				nolecturer = 0;
				break;
			}
		}
		if(nolecturer == 1)
		{
			cout << "ERROR: NO LECTURER" << endl;		//Error Message
			goto Label;		// go to User interface
		}
		else
		{
			goto Label;		// go to User interface
		}
	}

    else if(hyphen_command == "-assign")
    {
    	int number_of_word = word_count(full_command);

    	if(number_of_word == 0)
    	{
    		int control;
    		int index_of_lecture;
    		int count = 1;	// id of lectures
			while(number_of_lectures > 0)
			{
				for (int i = 0; i < number_of_lecturer; ++i)
				{
					for (index_of_lecture  = 0; index_of_lecture < number_of_lectures; ++index_of_lecture)
					{
						if(lecture[index_of_lecture].id == count)
						{
							break;
						}
						else
						{
							continue;
						}
					}
					control = lecturer_array[i].assignCourse_automatic(lecture[index_of_lecture], lecture, number_of_lectures);
					if(control == 1)
					{
						break;
					}
					else
					{
						continue;
					}
				}
				count ++;
			}
			for (int i = 0; i < number_of_lecturer; ++i)
			{
				if(lecturer_array[i].courses.size() <3 )	//lecturer given less than 3 lessons
				{
					while(lecturer_array[i].courses.size() < 3)
					{
						if(lecturer_array[i].propose_courses.size() != 0)
						{
							lecturer_array[i].courses.push_back(lecturer_array[i].propose_courses[0]);
							lecturer_array[i].propose_courses.erase(lecturer_array[i].propose_courses.begin() + 0);
						}
						else	//lecturer hasnt propose an elctive course yet
						{
							cout << lecturer_array[i].getter_lecturer_name() <<" "<< lecturer_array[i].getter_lecturer_surname()
							<< " PLEASE PROPOSE AN ELECTIVE COURSE" << endl;
							goto Label;
						}
					}
				}
			}
    	}

    	else
    	{
    		int nolecturer = 1; 	//nolecturer is a flag to check invalid course if value 1 NO LECTURER
    		int nocourse = 1; 	//nocourse is a flag to check invalid course if value 1 NO COURSE

    		int i,j;
    		auto start = 0U;
	    	auto end = s.find(delim);
	    	int pid = stoi((s.substr(start, end - start)));
			start = end + delim.length();
			end = s.find(delim, start);
			int course_id =stoi((s.substr(start, end - start)));

			for ( i = 0; i < number_of_lecturer; ++i)
			{
				if (pid == lecturer_array[i].getter_lecturer_personal_id())
				{
				nolecturer = 0;
				break;
				}
			}

			for (j = 0; j < number_of_lectures; ++j)
			{
				if (course_id == lecture[j].id)
				{
				nocourse= 0;
				break;
				}
			}

			if(nocourse == 1 || nolecturer == 1)	//Error Message
			{
				cout << "ERROR: NO LECTURER OR NO COURSE OR ASSIGNED BEFORE" << endl;
			}
			else
			{
				lecturer_array[i].assignCourse(lecture[j],lecture, number_of_lectures);				
			}
    	}
   		goto Label;		// go to User interface
    }

    else if(hyphen_command == "-timetable")
    {
    	int number_of_word = word_count(full_command);
    	admin.arrangeTimeTable(number_of_word,copy_lecture,copy_number_of_lectures,s);
    	goto Label;
	}	

    else if (hyphen_command == "-arrangeC")
    {
    	int number_of_word = word_count(full_command);

    	if(number_of_word == 0)	//-arrangeC without parameter
    	{
    		int nodates = 1;		//nodates is a flag to check invalid course if value 1 timetable is empty
    		for (int i = 0; i < copy_number_of_lectures; ++i)
    		{
				if(!copy_lecture[i].lecture_dates.empty())
				{
					nodates = 0;
					break;
				}
    		}
    		if(nodates == 1)
			{
				cout << "ERROR: NO CLASS OR NO COURSE OR TIMETABLE NOT ARRANGED YET" << endl;		//ERROR MESSAGE
			}
			else
			{
				for (int i = 0; i < copy_number_of_lectures; ++i)
				{
					if(copy_lecture[i].class_name.size() == 0)
					{
						for (int j = 0; j < number_of_classrooms; ++j)
						{
							int control = overlap(copy_lecture, class_room, class_room[j].c_no, copy_lecture[i].id ,i,j,copy_lecture[i].lecture_dates)	;
							if(control == 1)
							{
								admin.arrangeClassroom(copy_lecture, class_room, class_room[j].c_no, copy_lecture[i].id ,i,j,copy_lecture[i].lecture_dates);
								break;
							
							}
							else
							{	
								continue;
							}
						}
					}
					else
					{
						continue;
					}
				}
			
				for (int i = 0; i < copy_number_of_lectures; ++i)
    			{
    			string delim = ",";
    			auto start = 0U;
		    	auto end = copy_lecture[i].lecture_dates.find(delim);
		    	string  date1 = (copy_lecture[i].lecture_dates.substr(start, end - start));
		   	    start = end + delim.length();
				end = copy_lecture[i].lecture_dates.find(delim, start);
				string date2 = (copy_lecture[i].lecture_dates.substr(start, end - start));
    			if(copy_lecture[i].class_name.size() == 1)	// lecture has one class
    			{
    				cout <<"(" << copy_lecture[i].id << ")" << copy_lecture[i].name << " in "<<copy_lecture[i].class_name[0]  << " at "<< copy_lecture[i].lecture_dates  << endl;
    			}
    			else	//lecture has two class
    			{
					cout <<"(" << copy_lecture[i].id << ")" << copy_lecture[i].name << " in " << copy_lecture[i].class_name[0] << " at "<< date1<< ", in " 
					<< copy_lecture[i].class_name[1] << " at "<< date2 << endl;	
    			}	
    			}		
    		}
    	}
    	else
    	{
    		int nocourse = 1;	//nocourse is a flag to check invalid course if value 1 NO course
    		int noclass = 1;	//noclass is a flag to check invalid class if value 1 NO Class
    		int nodates = 1;	//nodates is a flag to check invalid dates if value 1 timetable is empty
    		auto start = 0U;
	    	auto end = s.find(delim);
	    	int id_course= stoi((s.substr(start, end - start)));
	    	start = end + delim.length();
			end = s.find(delim, start);
			string id_class1= (s.substr(start, end - start));
			int comma = has_coma(s);
			int index_of_lecture;
			for (index_of_lecture = 0; index_of_lecture < copy_number_of_lectures; ++index_of_lecture)
			{
				if(copy_lecture[index_of_lecture].id == id_course )
				{
					nocourse= 0;
					break;	
				}
			}
			if(comma == 0)	//-arrangeC 4 301
			{
				int index_of_class;		
				for (index_of_class = 0; index_of_class < number_of_classrooms; ++index_of_class)
				{
					if(class_room[index_of_class].c_no == id_class1 )
					{
						noclass= 0;
						break;	
					}
				}
				for (int i = 0; i < copy_number_of_lectures; ++i)
				{
					if(!copy_lecture[i].lecture_dates.empty())
					{
						nodates = 0;
						break;
					}
				}
				if(nocourse == 1|| noclass == 1 ||nodates == 1)
				{
					cout << "ERROR: NO CLASS OR NO COURSE OR TIMETABLE NOT ARRANGED YET" << endl;	//ERROR MESSAGE
				}
				else
				{	
					if(copy_lecture[index_of_lecture].class_name.size() !=0)
					{
						cout << "BLOCK: CLASS IS NOT AVAILABLE, THERE IS ANOTHER CLASS ASSIGNED" << endl;	//ERROR MESSAGE
					}
					else
					{
						int control = overlap(copy_lecture, class_room,  id_class1, id_course,index_of_lecture,index_of_class,copy_lecture[index_of_lecture].lecture_dates);
						if(control == 1)
						{
							admin.arrangeClassroom(copy_lecture,  class_room, id_class1, id_course, index_of_lecture, index_of_class,copy_lecture[index_of_lecture].lecture_dates);
							cout <<"DONE: (" << copy_lecture[index_of_lecture].id << ")" << copy_lecture[index_of_lecture].name << " in " <<copy_lecture[index_of_lecture].class_name[0]
							 << " at "<< copy_lecture[index_of_lecture].lecture_dates  << endl;	

						}
						else
						{
							cout << "BLOCK: CLASS IS NOT AVAILABLE" << endl; //ERROR MESSAGE
						}
					}
				}
			}
			else	//-arrangeC 4 301,302
			{
				noclass = 0;	//noclass is a flag to check invalid course 
				nodates = 1;	//nodates is a flag to check invalid dates if value 1 TIMETABLE IS EMPTY
				delim = " ";
				auto start = 0U;
	    		auto end = s.find(delim);
	    		(s.substr(start, end - start));
	    		delim = ",";
				start = end + delim.length();
	    		end = s.find(delim, start);
	    		string  id_class1 = (s.substr(start, end - start));
	   	    	start = end + delim.length();
				end = s.find(delim, start);
				string id_class2 = (s.substr(start, end - start));

				for (int i = 0; i < number_of_classrooms; ++i) // NO CLASS CHECKING FOR FIRST CLASS
				{
					if(class_room[i].c_no == id_class1  )
					{
						noclass++;	
					}
				}
				for (int i = 0; i < number_of_classrooms; ++i)	// NO CLASS CHECKING FOR SECOND CLASS
				{
					if(class_room[i].c_no == id_class2 )
					{
						noclass++;	
					}
				}

				for (int i = 0; i < copy_number_of_lectures; ++i)	//Timetable is empty
				{
					if(!copy_lecture[i].lecture_dates.empty())
					{
						nodates = 0;
						break;
					}
				}
				if(nocourse == 1|| noclass != 2 ||nodates == 1)
				{
					cout << "ERROR: NO CLASS OR NO COURSE OR TIMETABLE NOT ARRANGED YET" << endl;	//ERROR MESSAGE
				}
				else
				{
					if(copy_lecture[index_of_lecture].class_name.size() !=0)
					{
						cout << "BLOCK: CLASS IS NOT AVAILABLE, THERE IS ANOTHER CLASS ASSIGNED" << endl;	//ERROR MESSAGE
					}
					else
					{
						auto start = 0U;
		    			auto end = copy_lecture[index_of_lecture].lecture_dates.find(delim);	
		    			string  date1 = (copy_lecture[index_of_lecture].lecture_dates.substr(start, end - start));	// WED_15-17
		   	    		start = end + delim.length();
						end = copy_lecture[index_of_lecture].lecture_dates.find(delim, start);
						string date2 = (copy_lecture[index_of_lecture].lecture_dates.substr(start, end - start));	// TUE_15-17
						int index_of_class, index_of_class2; 
						for (index_of_class = 0; index_of_class < number_of_classrooms; ++index_of_class)
						{
							if(class_room[index_of_class].c_no == id_class1 )
							{
							break;	
							}
						}
						int control = overlap(copy_lecture, class_room,  id_class1, id_course,index_of_lecture,index_of_class,date1)	;
						for (index_of_class2 = 0; index_of_class2 < number_of_classrooms; ++index_of_class2)
						{
							if(class_room[index_of_class2].c_no == id_class2 )
							{
							break;	
							}
						}
						int control2 = overlap(copy_lecture, class_room,  id_class2, id_course,index_of_lecture,index_of_class2,date2);

						if(control == 1 && control2 == 1)
						{
							admin.arrangeClassroom(copy_lecture,  class_room, id_class1, id_course, index_of_lecture, index_of_class, date1);
							admin.arrangeClassroom(copy_lecture,  class_room, id_class2, id_course, index_of_lecture, index_of_class2, date2);
							cout <<"DONE: (" << copy_lecture[index_of_lecture].id << ")" << copy_lecture[index_of_lecture].name << " in " << copy_lecture[index_of_lecture].class_name[0] 
							<< " at "<< date1<< ", in " << copy_lecture[index_of_lecture].class_name[1] << " at "<< date2 << endl;	
						}
						else
						{
							cout << "BLOCK: CLASS IS NOT AVAILABLE" << endl; 	//ERROR MESSAGE
						}
					}
				}
			}
    	}
    	goto Label;
    }

    else if(hyphen_command == "-ns")
	{
		parse_string(s,stu);
		goto Label;		
	}	

	else if (hyphen_command == "-list")
	{
		show_lecture(lecture, number_of_lectures);
		goto Label;
	}

	else if (hyphen_command == "-enter")
	{
		string delim = " ";		//parse string by whitespace
	    auto start = 0U;
	    auto end = s.find(delim);
	    int student_id = stoi((s.substr(start, end - start)));
	    start = end + delim.length();
	    end = s.find(delim, start);
	    string classroom_id = (s.substr(start, end - start));
	    start = end + delim.length();
	    end = s.find(delim, start);
	   	int hour_of_week = stoi((s.substr(start, end - start)));	
	   	int day_of_hour_of_week =ceil( (double)hour_of_week / 8 );	// 1=monday, 2=tuesday, 3=wednesday, 4=thursday, 5=friday
	   	int date_of_hour_of_week = hour_of_week % 8;				// 1=09.00, 2=10.00..., 8=16.00
	   	int date_of_week;
	   	int course_id;
	   	if(date_of_hour_of_week == 0)
	   	{
	   		date_of_week = (day_of_hour_of_week * 100) + 16;
	   	}
	   	else
	   	{
	   		date_of_week = (day_of_hour_of_week * 100) + date_of_hour_of_week + 8;
	   	}
		int nostudent = 1;	//nostudent is a flag to check invalid student if value 1 NO Student
    	int noclass = 1;	//noclass is a flag to check invalid class if value 1 NO Class
   		int nodates = 1;	//nodates is a flag to check invalid dates if value 1 no lecture at this time
   		int classroom_index ;
   		int student_index ;
   		for (classroom_index= 0; classroom_index < number_of_classrooms; ++classroom_index)
   		{
   			if (class_room[classroom_index].c_no == classroom_id )
   			{
   				noclass = 0;
   				break;
   			}
   		}
   		for (student_index  = 0; student_index  < stu.size(); ++student_index )
   		{
   			if(stu[student_index ].getter_student_no() == student_id)
   			{
   				nostudent = 0;
   				break;
   			}
   		}

   		if(noclass == 1 || nostudent == 1)
   		{
   			cout << "ERROR: NO CLASS OR NO STUDENT "<< endl;
   		}
   		else
   		{
   			if(class_room[classroom_index].int_date.size() == 0)
   			{
   				cout <<"ERROR: TIMETABLE OR CLASSROOM NOT ARRANGED YET" << endl;
   			}
   			else
   			{
   			 	if (stu[student_index].getter_student_busy() == 1)
   			 	{
   			 		cout<<"BLOCK: S/HE IS AT ANOTHER CLASSROOM" << endl;
   			 	}
   			 	else 
   			 	{
   					classroom_course(class_room,number_of_classrooms,copy_lecture,number_of_lectures);
   					stu[student_index].enter_classroom(class_room[classroom_index],student_id,date_of_week);
   				}
   			}
   		}
   		goto Label;
	}

	else if (hyphen_command == "-quit")
	{
		int nostudent = 1;	//nostudent is a flag to check invalid student if value 1 NO Student
		int student_index;
		int classroom_index;
		string delim = " ";	
		auto start = 0U;
	    auto end = s.find(delim);
	   	int student_id= stoi((s.substr(start, end - start)));
	   	for (student_index  = 0; student_index  < stu.size(); ++student_index )
   		{
   			if(stu[student_index ].getter_student_no() == student_id)
   			{
   				nostudent = 0;
   				break;
   			}
   		}
   		if(nostudent == 1)
   		{
   			cout << "ERROR: NO STUDENT "<< endl;
   		}
   		else
   		{
   			if (stu[student_index].getter_student_busy() == 0)
   			{
   				cout<<"BLOCK: S/HE IS NOT IN ANY CLASSROOM" << endl;
   			}
   			else
   			{
   				for (classroom_index = 0; classroom_index < number_of_classrooms; ++classroom_index)
   				{
   					if(class_room[classroom_index].id == stu[student_index].getter_student_class_id() )
   					{
   						break;
   					}
   				}
				stu[student_index].quit_classroom(class_room[classroom_index]);
   			}
   		}
   		goto Label;
	}

	else if (hyphen_command == "-attendance")
	{
		string delim = " ";	
		auto start = 0U;
	    auto end = s.find(delim);
	   	int course_id= stoi((s.substr(start, end - start)));
	   	int classroom_index;
	   	int course_index;
		for (course_index = 0;course_index < number_of_lectures; ++course_index)
		{
			if(copy_lecture[course_index].id == course_id)
			{
				for (int i = 0; i < copy_lecture[course_index].student_count; ++i)
				{
					for (int j = 0; j < stu.size(); ++j)
					{
						if(stu[j].getter_student_no() == copy_lecture[course_index].attendance_rec[i][0])
						{
							if(i + 1 == copy_lecture[course_index].student_count)
							{
								cout << stu[j].getter_student_name() << " " << stu[j].getter_student_surname() << " " << copy_lecture[course_index].attendance_rec[i][1] ;
							}
							else
							{
								cout << stu[j].getter_student_name() << " " << stu[j].getter_student_surname() << " " << copy_lecture[course_index].attendance_rec[i][1] << " -- ";
							}	
							break;
						}
					}
				}
			}
		}
		cout << endl;
		goto Label;
	}

	else if(hyphen_command == "exit")
    {
    	return 0;	// terminate program
    }

    else
    {
    	goto Label;		// go to User interface
    }

	return 0;
}
