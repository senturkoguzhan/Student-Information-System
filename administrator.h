/*************************************************************************************/
/*                                     Oguzhan SENTURK                               */
/*                                       			                     */
/*                                   osenturk@gtu.edu.tr                             */
/*************************************************************************************/

#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <iostream>
#include <string>
#include "classroom.h"

using namespace std;

namespace AdministratorNS
{
using namespace ClasroomNS;
	class Administrator
	{
	public:
		void arrangeClassroom(Course copy_lecture[], Classroom class_room[], string id_class1,int  id_course,int index_of_lecture,int index_of_class,string lecture_time);
		void arrangeTimeTable(int number_of_word,Course copy_lecture[], int copy_number_of_lectures, string s);
		Administrator& operator = (const Administrator& rightside);
		~Administrator();
		Administrator(const Administrator& administrator_object);
		Administrator();
	private:
		int pid; 
		string password;
	};
}
#endif
