/*************************************************************************************/
/*                                     Oguzhan SENTURK                               */
/*                                            		                             */
/*                                   osenturk@gtu.edu.tr                             */
/*************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "lecturer.h"

#define MAX 16	//max lecture hour 
#define MIN 9	//min lecture hour

using namespace std;

namespace LecturerNS
{

	void Lecturer::assignCourse(Course course1, Course lecture[], int& number_of_lectures) //function to assign course
	{

		int mismatch = 1; 	//mismatch is a flag to check invalid course if value 1 MISMATCH
	    int assign_before = 0; 	//assign_before is a flag to check invalid course if value 1 ASSIGN BEFORE
	    int overlap_course = 0; //if current lecture is must taken course, value 1

		if (courses.size() == 3)
		{
			cout << "ERROR: LECTURER GIVES 3 LESSONS ALREADY" << endl; //ERROR MESSAGE
		}
		else
		{
			for (int k = 0; k < professions.size(); ++k)
			{
				if(professions[k] == course1.field)
				{
					mismatch = 0;
					break;
				}
			}
			if(mismatch == 1)
			{
				cout << "BLOCK: FIELD AND PROFESSION MISMATCH" << endl; //ERROR MESSAGE
			}
			else
			{
				for (int k = 0; k < courses.size(); ++k)
				{
					if(courses[k].id == course1.id)
					{
						assign_before = 1;
						break;
					}
				}
				if(assign_before == 1)
				{
					cout << "ERROR: COURSE ASSIGNED BEFORE TO LECTURER" << endl; //ERROR MESSAGE
				}
				else
				{
					int k ;
					for ( k= 0; k < must_take_course.size(); ++k)
					{
						if(must_take_course[k].id == course1.id)
						{
							overlap_course = 1;
							break;
						}
					}
					if( ( must_take_course.size() + courses.size() ) == 3 && overlap_course == 0)
					{
						cout << "ERROR: THERE ARE OTHER LESSONS THAT THE LECTURER HAS TO GIVE" << endl;	//ERROR MESSAGE
					}
					else if(must_take_course.size() != 3 && overlap_course == 0)
					{
						cout << "DONE!" << endl;
						courses.push_back(course1);
						for(int i = 0; i < number_of_lectures; i++)
						{	
							if(lecture[i].id == course1.id)			//lecture has been assigned and lecture delete from array to prevent to another assign
							{
								for(int j = i; j < (number_of_lectures - 1); j++)
								{
									lecture[j] = lecture[j + 1];
								}
								number_of_lectures --;
								break;
							}
						}
					}
					else
					{
						must_take_course.erase(must_take_course.begin() + k);
						cout << "DONE!" << endl;
						courses.push_back(course1);
						for(int i = 0; i < number_of_lectures; i++)
						{
							if(lecture[i].id == course1.id)
							{
								for(int j = i; j < (number_of_lectures - 1); j++)	//lecture has been assigned and lecture delete from array to prevent to another assign
								{
									lecture[j] = lecture[j + 1];
								}
								number_of_lectures --;
								break;
							}
						}
					}
				}
			}
		}
		if(courses.size() < 3 && (propose_courses.size() == 0) )	//lecturer hasnt propose an elevtive course yet
		{
			cout << name<<" "<< surname
			<< " HAS NOT PROPOSED AN ELECTIVE COURSE YET, PROPOSE AN ELECTIVE COURSE" << endl;
		}
	}

	void Lecturer::proposeCourse(string course_data) //function to propose course
	{
		string name1, field1;
		int code1, credit1, total_hours1;
		int blockfield = 1;		//blockfield is a flag to check mismatch field and profession if value 1 MISMATCH
	    string delim = " ";		//parse string by whitespace
	    auto start = 0U;
	    auto end = course_data.find(delim);
	    //propse setting DeepLearning 521 3 3 AI
	    name1 = (course_data.substr(start, end - start));
	    start = end + delim.length();
	    end = course_data.find(delim, start);
	    code1 = stoi((course_data.substr(start, end - start)));
	    start = end + delim.length();
	    end = course_data.find(delim, start);
	    credit1 = stoi((course_data.substr(start, end - start)));	
	    start = end + delim.length();
	    end = course_data.find(delim, start);
	    total_hours1 = stoi((course_data.substr(start, end - start)));	
	    start = end + delim.length();
	    end = course_data.find(delim, start);
	    field1 = (course_data.substr(start, end - start));	
	   
	    for (int i = 0; i < professions.size(); ++i)
	    {
	    	if(professions[i] == field1)
	    	{
	    		blockfield = 0;
	    		break;
	    	}
	    }

		if (blockfield == 1)
		{
			cout << "BLOCK: FIELD AND PROFESSION MISMATCH" << endl;		//Error Message
		}
		else
		{
			Course temp;			//propose course are adding to vector of propose
			temp.name = name1;
			temp.code = code1;
			temp.credit = credit1;
			temp.total_hours = total_hours1;
			temp.field = field1;
			temp.isMandotary = 0;
			cout << "DONE!" << endl;
			propose_courses.push_back(temp);
		} 
	}

	int Lecturer::assignCourse_automatic(Course course1, Course lecture[], int& number_of_lectures) //function to assign course automatic
	{
		int mismatch = 1; 	//mismatch is a flag to check invalid course if value 1 MISMATCH
	    int assign_before = 0; 	//assign_before is a flag to check invalid course if value 1 ASSIGN BEFORE
	    int overlap_course = 0; 	

		if (courses.size() == 3)
		{
			//cout << "ERROR: LECTURER GIVES 3 LESSONS ALREADY" << endl;
		}
		else
		{
			for (int k = 0; k < professions.size(); ++k)
			{
				if(professions[k] == course1.field)
				{
					mismatch = 0;
					break;
				}
			}
			if(mismatch == 1)
			{
				//cout << "BLOCK: FIELD AND PROFESSION MISMATCH" << endl;
			}
			else
			{
				for (int k = 0; k < courses.size(); ++k)
				{
					if(courses[k].id == course1.id)
					{
						assign_before = 1;
						break;
					}
				}
				if(assign_before == 1)
				{
					//cout << "ERROR: COURSE ASSIGNED BEFORE TO LECTURER" << endl;
				}
				else
				{
					int k ;
					for ( k= 0; k < must_take_course.size(); ++k)
					{
						if(must_take_course[k].id == course1.id)
						{
							overlap_course = 1;
							break;
						}
					}
					if( ( must_take_course.size() + courses.size() ) == 3 && overlap_course == 0)
					{
						//cout << "ERROR: THERE ARE OTHER LESSONS THAT THE LECTURER HAS TO GIVE" << endl;
					}
					else if(must_take_course.size() != 3 && overlap_course == 0)
					{
						//cout << "DONE!" << endl;
						courses.push_back(course1);
						for(int i = 0; i < number_of_lectures; i++)
						{
							if(lecture[i].id == course1.id)
							{
								for(int j = i; j < (number_of_lectures - 1); j++)
								{
									lecture[j] = lecture[j + 1];
								}
								number_of_lectures --;
								return 1;
								break;
							}
						}
					}
					else
					{
						must_take_course.erase(must_take_course.begin() + k);
						//cout << "DONE!" << endl;
						courses.push_back(course1);
						for(int i = 0; i < number_of_lectures; i++)
						{
							if(lecture[i].id == course1.id)
							{
								for(int j = i; j < (number_of_lectures - 1); j++)
								{
									lecture[j] = lecture[j + 1];
								}
								number_of_lectures --;
								return 1;
								break;
							}
						}
					}
				}
			}
		}
		return 0;
	}

	string Lecturer::getter_lecturer_name()
	{
		return name;
	}

	string Lecturer::getter_lecturer_surname()
	{
		return surname;
	}

	int Lecturer::getter_lecturer_personal_id()
	{
		return personal_id;
	}

	string Lecturer::getter_lecturer_title()
	{
		return title;
	}

	void Lecturer::setter_lecturer_name(string name1)
	{
		name = name1;
	}

	void Lecturer::setter_lecturer_surname(string surname1)
	{
		surname = surname1;
	}

	void Lecturer::setter_lecturer_personal_id(int personal_id1)
	{
		personal_id = personal_id1;	
	}

	void Lecturer::setter_lecturer_title(string title1)
	{
		title = title1;
	}

	void Lecturer::setter_lecturer_professions(string professions1)
	{
		string s = professions1;
		    string delim = ",";		//parse string by comma
		    auto start = 0U;
		    auto end = s.find(delim);
		    while (end != string::npos)
		    {
		       	professions.push_back (s.substr(start, end - start)) ;
		        start = end + delim.length();					//EX: MACH,PROG
		        end = s.find(delim, start);						//inside vector : { (MACH) , (PROG) }
		    }													
		professions.push_back(s.substr(start, end)) ;		
	}

	Lecturer& Lecturer::operator = (const Lecturer& rightside)
	{
		if(this == &rightside)
		{
			return *this;
		}
		else
		{
			name = rightside.name; 
			surname = rightside.surname; 
			personal_id = rightside.personal_id; 
			title = rightside.title; 
			professions = rightside.professions; 
			courses = rightside.courses;
			propose_courses = rightside.propose_courses;
			must_take_course = rightside.must_take_course ;
		}
	}
	Lecturer::~Lecturer()
	{

	}
	Lecturer::Lecturer(const Lecturer& lecturer_object)
	{
		name = lecturer_object.name; 
		surname = lecturer_object.surname; 
		personal_id = lecturer_object.personal_id; 
		title = lecturer_object.title; 
		professions = lecturer_object.professions; 
		courses = lecturer_object.courses;
		propose_courses = lecturer_object.propose_courses;
		must_take_course = lecturer_object.must_take_course ;
	}
	Lecturer::Lecturer()
	{
		
	}

}
