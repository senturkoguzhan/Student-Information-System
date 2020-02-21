/*************************************************************************************/
/*                                     Oguzhan SENTURK                               */
/*                                        			                     */
/*                                   osenturk@gtu.edu.tr                             */
/*************************************************************************************/

#include <iostream>
#include <string>
#include <vector>

#include "student.h"

#define MAX 16	//max lecture hour 
#define MIN 9	//min lecture hour
#define LEVEL_4 23 //credit
#define LEVEL_3 22 //credit
#define LEVEL_2 21 //credit
#define LEVEL_1 20 //credit

using namespace std;

namespace StudentNS
{
	string Student::getter_student_surname()
	{
		return surname;
	}

	string Student::getter_student_name()
	{
		return name;
	}

	int Student::getter_student_level()
	{
		return level;
	}

	int Student::getter_student_credit()
	{
		return stu_credit;
	}

	int Student::getter_student_no()
	{
		return student_no;
	}

	int Student::getter_student_busy()
	{
		return busy;
	}

	int Student::getter_student_class_id()
	{
		return class_id;
	}

	void Student::enter_classroom(Classroom& class_room,int student_id,int date_of_week)
	{
		int course_id;
		if(class_room.capacity >= class_room.student_inroom)
		{
			class_room.student_inroom ++;
			busy = 1;	//student is busy
			cout<<"Student inroom: " << class_room.student_inroom <<endl;
			class_id = class_room.id; // class_id holds information of class which student in classroom
			course_id = find_course_id(class_room,date_of_week); // if no lecture at that moment course_id = 0

			if(course_id != 0)
			{
				class_room.attendance(course_id,student_id);
			}
		}
		else
		{
			cout << "ERROR: CLASSROOM FULL" << endl;
		}	
	}

	int Student::find_course_id(Classroom class_room,int date_of_week) // function to find course id given by classroom at that moment
	{
	
		for (int course_index = 0; course_index < class_room.course_name.size(); ++course_index)
		{
			vector<string> comparision_vector;	//holds lecture dates to be checked (MON_11-13,THURS_12-10 etc)	
		 	vector<int> int_comparision_vector;	////holds lecture dates int version				
			int lecture_int;
			string s = class_room.course_name[course_index]->lecture_dates;
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
		    for (int i = 0; i < int_comparision_vector.size(); ++i)
		    {
		    	if(int_comparision_vector[i] == date_of_week)
		    	{
		    		return class_room.course_name[course_index]->id; 
		    	}
		    }
		}
		return 0;
	}

	void Student::quit_classroom(Classroom& class_room)
	{
		class_room.student_inroom --;
		cout<<"Student inroom: " << class_room.student_inroom <<endl;
		busy = 0;	//student is not busy
	}

	string Student::extract_schedule()
	{
		string student_course = "[";
		for (int i = 0; i < schedule.size(); ++i)
		{
			if(i + 1 == schedule.size())
			{
				student_course += schedule[i].name + " " + to_string(schedule[i].credit);
			}
			else
			{
				student_course += schedule[i].name + " " + to_string(schedule[i].credit) + " " ;
			}
		}
		student_course += "]";
		return student_course;
	}

	int Student::disenroll_course(Course lecture)
	{
		int i = 0;
		int no_enrolled_course = 1; // check enrolled course
		for (; i < schedule.size(); ++i)
		{
			if(schedule[i].code ==lecture.code)
			{
				no_enrolled_course = 0;
				break;
			}
		}
		if(no_enrolled_course == 1)
		{
			cout<< "ERROR: YOU ARE NOT REGISTERED FOR THIS COURSE"<< endl;
		}
		else
		{
			cout << "DONE!"<< endl;
			schedule.erase(schedule.begin() + i);
			stu_credit += lecture.credit;
		}
		return stu_credit;
	}

	int Student::enroll_course(Course lecture)
	{
		if(stu_credit -lecture.credit < 0)
		{
			cout << "BLOCK! Because of credits"<< endl;
		}
		if(overlap(lecture) == 0)
		{
			cout << "DONE!"<< endl;
			schedule.push_back(lecture);
			stu_credit -= lecture.credit;
		}
		else
		{
			cout << "BLOCK! Because of overlap"<< endl;
		}
		return stu_credit;
	}

	bool Student::overlap(Course lecture) // function to calculate overlap if function returns false, it meaans no overlap
	{
		if(schedule.size() == 0) // if student' schedule is empty
		{
			return false;
		}
		vector<Course> temp;
		for (int i = 0; i < schedule.size(); ++i) // new lecture and student's schedule copy temp vector
		{
			temp.push_back(schedule[i]);
		}
	 	temp.push_back(lecture);
	 	int count = 0;
	 	int overlap_control = 0;	//variable to hold count of overlap hour
	 	while(count < temp.size())
	 	{
	 		// overlap algorithm :
	 		// My algorithm contol each lecture with other lecture
	 		// Example student's schedule is 1 and 2 , new lecture is 3
	 		// (2,3) - 1 , (1,3) - 2 , (1,2) - 3
	 		vector<string> comparision_vector;	//holds lecture dates to be checked (MON_11-13,THURS_12-10 etc)							/*TO BE 	*/
	 		vector<string> other_vector;		//holds other's lecture dates (MON_11-13,THURS_12-10 etc)								/*EXPLANIED	*/
	 		vector<int> int_comparision_vector;	//holds int version lecture dates to be checked (MON_11-13,THURS_12-10 etc)				/*BELOW 	*/
			vector<int> int_other_vector;		//holds other's int version lecture dates (MON_11-13,THURS_12-10 etc)					
			int lecture_int;
			Course temp_lecture = temp[count]; //holds lecture struct to be checked
			string s = temp[count].lecture_dates;
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
			   	else if(a == "TUES" )
			   	{
			   		lecture_int = 200;
			   	}
			   	else if(a == "WEDNES")
			   	{
			   		lecture_int = 300;
			   	}
			   	else if(a == "THURS")
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

		    temp.erase(temp.begin() + count);	// erase struct lecture to be checked from vector, after this process vector holds others

			for (int i = 0; i < temp.size(); ++i)
	   		{
				string s = temp[i].lecture_dates;
			    string delim = ",";		//parse string by comma
			    auto start = 0U;
			    auto end = s.find(delim);
			    while (end != string::npos)
			    {
			       	other_vector.push_back (s.substr(start, end - start)) ;
			        start = end + delim.length();					//EX: MON_11-13,THURS_12-10
			        end = s.find(delim, start);						//inside vector : { (MON_11-13) , (THURS_12-10) }
			    }													
			    other_vector.push_back(s.substr(start, end)) ;
			}
		    for (int j = 0; j < other_vector.size(); ++j)
			{
				s = other_vector[j];
			  	delim = "_";		//parse string by underscroe
				start = 0U;									//EX : MON_11-13
				end = s.find(delim);
			    string a =s.substr(start, end - start);		//variable a holds MON
			    start = end + delim.length();
			    end = s.find(delim, start);
			    string b = s.substr(start, end);			//variable b holds 11-13
			 	delim = "-";		//parse string by hyphen
				start = 0U;
				end = b.find(delim);
			    string c =b.substr(start, end - start);		//variable c holds 11
			    start = end + delim.length();
			    end = b.find(delim, start);
			   	string d = b.substr(start, end);			//variable d holds 13
			   	if(a == "MON")
			   	{
			   		lecture_int = 100;
			   	}
			   	else if(a == "TUES" )
			   	{
			   		lecture_int = 200;
			   	}
			   	else if(a == "WEDNES")
			   	{
			   		lecture_int = 300;
			   	}
			   	else if(a == "THURS")
			   	{
			   		lecture_int = 400;
			   	}
			   	else if(a == "FRI")
			   	{
			   		lecture_int = 500;
			   	}
			   	for (int i = stoi(c); i < stoi(d); ++i)
			   	{
			   		int_other_vector.push_back(lecture_int + i);	//vector inside :{ 110, 111 } for MON_11-13
			   	}
		    }
	    	int  total_overlap = 0;		//for every comparision variable initialize 0. holds count of overlap hours
	    	for (int i = 0; i < int_other_vector.size(); ++i)
	    	{
	    		for (int j = 0; j < int_comparision_vector.size(); ++j)
	    		{
	    			if(int_other_vector[i] == int_comparision_vector[j])
	    			{
	    			total_overlap ++ ;
	    			}
	    		}
	    	}
	    	//Students mustn’t enrol courses whose most hours are overlapped
	    	if(temp_lecture.total_hours - total_overlap < (double)temp_lecture.total_hours / 2)	
			{
				overlap_control ++;
			}

			temp.insert(temp.begin() + count , temp_lecture); //lecture which to be checked add again to same index
			count ++;
		}

		if(overlap_control == 0)	// no overlap
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void Student::setter(string name1, string surname1, int student_no1, int level1) // function to set student object
	{
			name = name1;
			surname = surname1;
			student_no = student_no1;
			level = level1;
			busy = 0;
			if(level == 4)
			{
				stu_credit = LEVEL_4;
			}
			else if(level == 3)
			{
				stu_credit = LEVEL_3;
			}
			else if(level == 2)
			{
				stu_credit = LEVEL_2;
			}
			else
			{
				stu_credit = LEVEL_1;
			}
	}

	Student& Student::operator = (const Student& rightside)
	{
		if(this == &rightside)
		{
			return *this;
		}
		else
		{
			class_id = rightside.class_id;
			name = rightside.name;
			surname = rightside.surname;
			student_no = rightside.student_no;
			level = rightside.level;
			stu_credit = rightside.stu_credit;
			busy = rightside.busy;
			schedule = rightside.schedule;
		}
	}
	Student::~Student()
	{

	}
	Student::Student(const Student& student_object)
	{
		class_id = student_object.class_id;
		name = student_object.name;
		surname = student_object.surname;
		student_no = student_object.student_no;
		level = student_object.level;
		stu_credit = student_object.stu_credit;
		busy = student_object.busy;
		schedule = student_object.schedule;
	}
	Student::Student()
	{
		
	}
}
