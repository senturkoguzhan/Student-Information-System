/*************************************************************************************/
/*                                     Oguzhan SENTURK                               */
/*                                    				                     */
/*                                   osenturk@gtu.edu.tr                             */
/*************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "administrator.h"

#define MAX 16	//max lecture hour 
#define MIN 9	//min lecture hour

using namespace std;

namespace AdministratorNS
{
	void Administrator::arrangeTimeTable(int number_of_word,Course copy_lecture[], int copy_number_of_lectures, string s) // function arrange timetable
	{
		string delim = " ";	// parse string by whitespace
		int nocourse = 1; 	//nocourse is a flag to check invalid course if value 1 NO COURSE
	    int assignbefore = 0; 	//assignbefore is a flag to check assign course if value 1 course assigned before
		if(number_of_word == 0)
	    {		  		
			for (int j = 0; j <copy_number_of_lectures ; ++j)
			{
				vector<int> date_int_vector;	//holds lecture dates int version 
				int count = 0;
				if(copy_lecture[j].lecture_dates.empty())
				{
					First:
						int date1 = copy_lecture[j].total_hours / 2 ;	//total hours are 5 , date1 is 2 hour, date2 is 3 hour
						int date2 = copy_lecture[j].total_hours - date1;
						int day = rand() % 5 + 1 ;
						int time = rand() % (MAX - MIN) + MIN;
						int sum = 0;
						int overlap = 0;
						string string_time1 = to_string(time);
						string string_time2 = to_string(time+date1);
						string date;

						if(day == 1)
						{
							date = "MON_";
						}
						else if(day == 2)
						{
							date = "TUE_";
						}						//EX: WED_14-16 >> 314,315
						else if(day == 3)
						{						//EX: WED_14-16 >> 314,315
							date = "WED_";
						}
						else if(day == 4)
						{
							date = "THU_";
						}
						else
						{
							date = "FRI_";
						}

						sum = (day * 100) + time;
						for (int i = 0; i < date_int_vector.size(); ++i)
						{
							for (int j = 0; j < date1; ++j)
							{
								if(date_int_vector[i] == sum + j)
								{
									overlap = 1;
									goto First;
								}
							}
						}
						if(overlap == 0)
						{
							for (int i = 0; i < date1; ++i)
							{
								date_int_vector.push_back(sum  + i);
							}
							date += string_time1 + "-" + string_time2;
							copy_lecture[j].lecture_dates += date + ",";
						}
						Second:
						day = rand() % 5 + 1 ;		//random day
						time = rand() % (MAX - MIN) + MIN; //random hour
						sum = 0;
						overlap = 0;
						string_time1 = to_string(time);
						string_time2 = to_string(time+date2);
						date;
						if(day == 1)
						{
							date = "MON_";
						}
						else if(day == 2)
						{
							date = "TUE_";		//EX: MON_11-13 >> 111,112
						}						//EX: WED_14-16 >> 314,315
						else if(day == 3)
						{
							date = "WED_";
						}
						else if(day == 4)
						{
							date = "THU_";
						}
						else
						{
							date = "FRI_";
						}

						sum = (day * 100) + time;
						for (int i = 0; i < date_int_vector.size(); ++i)
						{
							for (int j = 0; j < date2; ++j)
							{
								if(date_int_vector[i] == sum + j)
								{
									overlap = 1;
									goto Second;
								}
							}
						}
						if(overlap == 0)
						{
							for (int i = 0; i < date2; ++i)
							{
								date_int_vector.push_back(sum + i);
							}
							date += string_time1 + "-" + string_time2;
							copy_lecture[j].lecture_dates += date;
						}
				}
			}
			for (int j = 0; j < copy_number_of_lectures; ++j)	//print timetable
			{
				cout << "(" << copy_lecture[j].id << ")" << copy_lecture[j].name << " " << copy_lecture[j].lecture_dates  << endl;		
			}
		}	

		else
		{
			int j;
			vector<int> date_int_vector;		//holds lecture dates int version 
			auto start = 0U;
			auto end = s.find(delim);
	    	int lid = stoi((s.substr(start, end - start))); //lid is lecture id
	    	for ( j = 0; j < copy_number_of_lectures; ++j)
			{
				if (lid == copy_lecture[j].id)
				{
					nocourse= 0;
					if(!copy_lecture[j].lecture_dates.empty())
					{
						assignbefore = 1;
					}
				break;
				}
			}
			if(nocourse == 1 )	//Error Message
			{
				cout << "ERROR: NO COURSE" << endl;	
			}
			else if(assignbefore == 1) //Error Message
			{
				cout << "ASSIGNED BEFORE: " << "(" << copy_lecture[j].id << ")"  <<copy_lecture[j].name << " " << copy_lecture[j].lecture_dates  << endl;	
			}
			else
			{
				Third:
				int date1 = copy_lecture[j].total_hours / 2 ;	//total hours are 5 , date1 is 2 hour, date2 is 3 hour
				int date2 = copy_lecture[j].total_hours - date1;
				int day = rand() % 5 + 1 ;	//random day
				int time = rand() % (MAX- MIN ) + MIN;	//random hour
				int sum = 0;
				int overlap = 0;
				string string_time1 = to_string(time);
				string string_time2 = to_string(time+date1);
				string date;
				if(day == 1)
				{
					date = "MON_";
				}
				else if(day == 2)
				{
					date = "TUE_";
				}
				else if(day == 3)			//EX: MON_11-13 >> 111,112
				{							//EX: WED_14-16 >> 314,315
					date = "WED_";
				}
				else if(day == 4)
				{
					date = "THU_";
				}
				else
				{
					date = "FRI_";
				}

				sum = day * 100 + time;
				for (int i = 0; i < date_int_vector.size(); ++i)
				{
					for (int j = 0; j < date1; ++j)
					{
						if(date_int_vector[i] == sum + j)
						{
							overlap = 1;
							goto Third;
						}
					}
				}
				if(overlap == 0)
				{
					for (int i = 0; i < date1; ++i)
					{
						date_int_vector.push_back(sum + time + i);
					}
					date += string_time1 + "-" + string_time2;
					copy_lecture[j].lecture_dates += date + ",";
				}
				Fourth:
				day = rand() % 5 + 1 ;		//random day
				time = rand() % (MAX- MIN ) + MIN ;		//random hour
				sum = 0;
				overlap = 0;
				string_time1 = to_string(time);
				string_time2 = to_string(time+date2);
				date;

				if(day == 1)
				{
					date = "MON_";
				}
				else if(day == 2)			//EX: MON_11-13 >> 111,112
				{							//EX: WED_14-16 >> 314,315
					date = "TUE_";
				}
				else if(day == 3)
				{
					date = "WED_";
				}
				else if(day == 4)
				{
					date = "THU_";
				}
				else
				{
					date = "FRI_";
				}

				sum = day * 100 + time;
				for (int i = 0; i < date_int_vector.size(); ++i)
				{
					for (int j = 0; j < date2; ++j)
					{
						if(date_int_vector[i] == sum + j)
						{
							overlap = 1;
							goto Fourth;
						}
					}
				}
				if(overlap == 0)
				{
					for (int i = 0; i < date2; ++i)
					{
						date_int_vector.push_back(sum + time + i);
					}
					date += string_time1 + "-" + string_time2;
					copy_lecture[j].lecture_dates += date;
				}
			cout << "DONE: "<< "(" << copy_lecture[j].id << ")" << copy_lecture[j].name  << " " << copy_lecture[j].lecture_dates  << endl;		
			}	
		}			
	}

	void Administrator::arrangeClassroom(Course copy_lecture[], Classroom class_room[], string id_class1,int  id_course,int index_of_lecture,int index_of_class, string lecture_time) //function to arrangeclassrom
	{
		 	vector<string> comparision_vector;	//holds lecture dates to be checked (MON_11-13,THURS_12-10 etc)	
		 	vector<int> int_comparision_vector;	////holds lecture dates int version				
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
		    for (int i = 0; i < int_comparision_vector.size(); ++i)
		    {
		    	class_room[index_of_class].int_date.push_back(int_comparision_vector[i]);
		    }
		   
		    copy_lecture[index_of_lecture].class_name.push_back(id_class1);
	}

	Administrator& Administrator::operator = (const Administrator& rightside)
	{
		if(this == &rightside)
		{
			return *this;
		}
		else
		{
			pid = rightside.pid;
			password = rightside.password;
		}
	}
	Administrator::~Administrator()
	{

	}
	Administrator::Administrator(const Administrator& administrator_object)
	{
		pid = administrator_object.pid;
		password = administrator_object.password;
	}
	Administrator::Administrator()
	{

	}
}
