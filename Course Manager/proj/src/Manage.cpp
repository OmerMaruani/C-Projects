#include "Manage.h"



Manage::Manage() : number_course(0)
{
	this->read_courses();
	this->read_persons();
}
Manage::~Manage()
{
	this->write_courses();
	this->write_persons();
}






void Manage::read_persons()
{
	this->persons = Person::readFromCSV("Students.csv", "Teachers.csv");

}
void Manage::write_persons() const
{
	Person::writeForCSV("Students.csv", "Teachers.csv", this->persons);
}
void Manage::read_courses()
{
	this->courses = Course::readFromCSV("Courses.csv");

}
void Manage::write_courses() const
{
	Course::writeForCSV("Courses.csv", this->courses);

}
void Manage::start()
{

	//this->persons[206944795].get()->use_actions(*this);

	int id = this->join();
	if (id != 0)
		this->persons[id].get()->use_actions(*this);

	//this->persons[207988594].get()->use_actions(*this);

}








void Manage::print_by_courseid(int course_id) const
{


	auto it = this->courses.find(course_id);
	if (it != this->courses.end())
		cout << it->second;
	else
		cout << "Course with ID " << course_id << " not found." << endl << endl;
}
void Manage::print_ten_courses()
{
	//IF MORE ACTIONS ALONE THEN :
	/*
	auto it = this->courses.begin();

	auto endIt = it;
	if (this->courses.size() > 10)
		advance(endIt, 10);
	else
		endIt = this->courses.end();

	while (it != endIt)
	{
		cout << "Number#" << this->number_course << endl;
		cout << it->second;
		it++;
	}

*/


//IF MORE ACTIONS DEPEND ON THIS 

	this->number_course = 0;

	auto it = this->courses.begin();

	auto endIt = it;
	if (this->courses.size() > 10)
		advance(endIt, 10);
	else
		endIt = this->courses.end();

	while (it != endIt)
	{
		cout << "Number#" << this->number_course << endl;
		cout << it->second;
		it++;
		this->number_course++;
	}
	if (this->number_course == 10)
	{
		cout << "for more courses enter \"More\" " << endl;
		string input;
		cin >> input;

		if (input == "More")
			print_more_ten();
	}
	//reset
	this->number_course = 0;


}
void Manage::print_more_ten()
{
	int offset = this->number_course + 10;


	// Check if the number of courses is valid
	if (this->number_course >= this->courses.size()) {
		cout << "No more courses" << endl;
		return;
	}

	// Create iterator and advance to the starting point
	auto it = this->courses.begin();
	advance(it, this->number_course);  // Move iterator to the correct starting position


	// Determine the end iterator
	auto endIt = it;
	if (this->number_course + 10 < this->courses.size())
	{
		advance(endIt, 10);  // Move end iterator 10 positions forward
	}
	else
	{
		endIt = this->courses.end();  // Set end iterator to the end of the container
	}


	// Print "No more courses" if the iterator range is empty
	if (it == endIt)
	{
		cout << "No more courses" << endl;
		return;
	}


	// Print the courses in the specified range
	while (it != endIt) {
		cout << "Number#" << this->number_course << ": ";
		cout << it->second << endl;  // Print the course information
		++it;  // Move to the next course
		++this->number_course;  // Update the course number
	}

	if (this->number_course == offset)
	{
		cout << "for more courses enter \"More\" " << endl;
		string input;
		cin >> input;

		if (input == "More")
			print_more_ten();
	}
	else
		cout << "no more courses" << endl;

	cout << endl;


}
void Manage::print_persons() const
{
	for (const auto& pair : this->persons)
		cout << *pair.second.get();

}











void Manage::print_schedule(Student& student, int schedule_id)
{
	if (student.get_schedule_size() < schedule_id)
	{
		cout << "there is no such : schedule number " << schedule_id << endl;
		return;
	}

	//print days
	print_days();

	//get all the courses 
	unordered_map < int, array<int, 3> > schedule = student.get_schedule(schedule_id - 1);
	//auto schedule = student.get_schedule(schedule_id - 1);

	//creating an array of course from schedual
	vector<Course> s_courses;
	for (const auto& pair : schedule)
		s_courses.push_back(this->courses[pair.first]);

	Lesson lesson;

	int another_check = 1; //if we already print a course, next time check again for parallel course time
	int go_next_day = 1;

	//after i printed a course i can pop him out

	for (int i = FIRST_HOUR; i <= LAST_HOUR; i++)
	{
		//every time we change schedule, we need print course for all hours 
		//so here we redeclare on the schedule, he changed, this allow to print parallel courses

		schedule = student.get_schedule(schedule_id - 1);


		cout << i << "     ";
		if (i < 10) cout << " ";

		another_check = 1;

		while (another_check == 1)
		{
			another_check = 0;


			//here print the course_id
			/*
			for (int day = 1; day <= 7; day++)
			{
				go_next_day = 0;

				for (const auto& val : s_courses )
				{
					course_id = val.get_id();

					//lecture
					group_id = scheudle[course_id][0];
					if (val.get_lecture(group_id, lesson) &&
						time_valid(i, day, lesson))
					{
						cout << course_id;
						go_next_day = 1;
						another_check = 1;
						break;

					}


				}

				for (const auto& val : s_courses)
				{
					if (go_next_day == 1) break;

					course_id = val.get_id();

					//tutorial
					group_id = scheudle[course_id][1];
					if (val.get_tutorial(group_id, lesson) &&
						time_valid(i, day, lesson))
					{
						cout << course_id;
						go_next_day = 1;
						another_check = 1;
						break;

					}
				}

				for (const auto& val : s_courses)
				{

					if (go_next_day == 1) break;
					course_id = val.get_id();

					///lab
					group_id = scheudle[course_id][2];
					if (val.get_lab(group_id, lesson) &&
						time_valid(i, day, lesson))
					{
						cout << course_id;
						another_check = 1;
						go_next_day = 1;
						break;

					}

				}


				//mean we print course id
				if(go_next_day == 1)
					cout << "      |       ";
					//cout<<  "      |"
				else
					cout << "           |       ";





			}
			*/
			check_course_print(another_check, i, 0, lesson, schedule, s_courses);


			//if no lesson , so we can get out here
			if (another_check == 0) break;


			//here print the lesson
			/*
			for (int day = 1; day <= 7; day++)
			{
				go_next_day = 0;

				for (const auto& val : s_courses)
				{
					course_id = val.get_id();

					//lecture
					group_id = scheudle[course_id][0];
					if (val.get_lecture(group_id, lesson) &&
						time_valid(i, day, lesson))
					{
						cout << "Lecture ";
						go_next_day = 1;
						break;

					}


				}

				for (const auto& val : s_courses)
				{
					if (go_next_day == 1) break;

					course_id = val.get_id();

					//tutorial
					group_id = scheudle[course_id][1];
					if (val.get_tutorial(group_id, lesson) &&
						time_valid(i, day, lesson))
					{

						cout << "Tutorial";
						go_next_day = 1;
						break;

					}


				}

				for (const auto& val : s_courses)
				{

					if (go_next_day == 1) break;

					course_id = val.get_id();

					///lab
					group_id = scheudle[course_id][2];
					if (val.get_lab(group_id, lesson) &&
						time_valid(i, day, lesson))
					{

						cout << "  Lab   ";
						go_next_day = 1;
					}


				}



				//mean we print lesson
				if (go_next_day == 1)
					cout << "    |      ";
				else
					cout << "            |      ";

				//if (i > 10) cout << " ";


			}

			*/
			check_course_print(another_check, i, 1, lesson, schedule, s_courses);



			//here print the class
			/*
			for (int day = 1; day <= 7; day++)
			{
				go_next_day = 0;
				for (const auto& val : s_courses)
				{
					course_id = val.get_id();

					//lecture
					group_id = scheudle[course_id][0];
					if (val.get_lecture(group_id, lesson) &&
						time_valid(i, day, lesson))
					{
						cout << lesson.get_class_name();
						go_next_day = 1;

						//delete the course so next time dont print it again
						//print another one thats on the parllel
						scheudle[course_id][0] = 0;
						break;

					}


				}

				for (const auto& val : s_courses)
				{
					if (go_next_day == 1) break;

					course_id = val.get_id();

					//tutorial
					group_id = scheudle[course_id][1];
					if (val.get_tutorial(group_id, lesson) &&
						time_valid(i, day, lesson))
					{
						cout << lesson.get_class_name();
						go_next_day = 1;

						//delete the course so next time dont print it again
						//print another one thats on the parllel
						scheudle[course_id][1] = 0;
						break;

					}

				}

				for (const auto& val : s_courses)
				{
					if (go_next_day == 1) break;

					course_id = val.get_id();

					///lab
					group_id = scheudle[course_id][2];
					if (val.get_lab(group_id, lesson) &&
						time_valid(i, day, lesson))
					{
						cout << lesson.get_class_name();
						go_next_day = 1;

						//delete the course so next time dont print it again
						//print another one thats on the parllel
						scheudle[course_id][2] = 0;
						break;

					}

				}


				//mean we print class
				if (go_next_day == 1)
					cout << "      |       ";
				else
					cout << "           |       ";


			}
			*/
			check_course_print(another_check, i, 2, lesson, schedule, s_courses);


		}

		print_lines();

	}

	cout << "Credits pay: " << this->get_payment(student.get_id(), schedule_id - 1) << endl << endl;
}
void Manage::print_all(Student& student)
{
	for (int schedual_num = 0; schedual_num < student.get_schedule_size(); schedual_num++)
	{
		cout << "Schedule " << schedual_num + 1 << endl << endl;
		this->print_schedule(student, schedual_num + 1);
	}
}
void Manage::add_schedule(Student& student)
{
	vector < unordered_map<int, array<int, 3> > >& schedules = student.get_schedules();
	unordered_map<int, array<int, 3> > map;
	schedules.push_back(map);

}
void Manage::rm_schedule(Student& student, stringstream& ss)
{
	string s_schedule_id, temp;
	ss >> s_schedule_id >> temp;
	if (s_schedule_id.empty())
	{
		cout << "RmSchedule must contain only schedule_id : print <id>" << endl;
		return;
	}
	else if (temp != "")
	{
		cout << "RmSchedule must contain only schedule_id : print <id>" << endl;
	}

	int schedule_id = check_and_convert_str_to_int(s_schedule_id);
	if (schedule_id == 0)//if 0 then id is invalid
		return; // error will be desplayed by  check_and_convert...

	if (schedule_id >= student.get_schedule_size() + 1)
	{
		cout << "Schedule ID: " << schedule_id << " was not founded" << endl;
		return;
	}

	vector < unordered_map<int, array<int, 3> > >& schedules = student.get_schedules();
	auto it = schedules.begin();
	advance(it, schedule_id - 1);
	schedules.erase(it);

}

//function for add_course_schedule
bool Manage::check_valid_id(int course_id, int schedule_id, Student& student) const
{
	auto it = this->courses.find(course_id);
	if (it == this->courses.end())
	{
		cout << "Course ID: " << course_id << " was not founded" << endl;
		return false;
	}

	else if (schedule_id >= student.get_schedule_size() + 1)
	{
		cout << "Schedule ID: " << schedule_id << "was not founded" << endl;
		return false;
	}

	return true;
}

void Manage::add_course_schedule(Student& student, stringstream& ss)
{
	string s_schedule_id, s_course_id, s_group_id, temp;
	ss >> s_schedule_id >> s_course_id >> s_group_id >> temp;
	if (s_schedule_id.empty() || s_course_id.empty() || s_group_id.empty())
	{
		cout << "s_schedule_id or s_course_id or s_group_id is missing : Add <schedule_id> <course_id> <group_id>" << endl;
		return;
	}
	else if (temp != "")
	{
		cout << "too much parameters for : Add <schedule_id> <course_id> <group_id>" << endl;
		return;
	}

	int schedule_id = check_and_convert_str_to_int(s_schedule_id);
	int course_id = check_and_convert_str_to_int(s_course_id);
	int group_id = check_and_convert_str_to_int(s_group_id);

	// check if all id's are numerals
	if (schedule_id == 0 || course_id == 0 || group_id == 0)
		return; // error will be desplayed by check_and_convert func


	//first check if group id and coursid valid
	bool valid = this->check_valid_id(course_id, schedule_id, student);
	if (!valid)
		return;

	//check for group_id 

	else
	{


		//first search if the course id exist in this schedule

		vector <int> courses = student.get_courses_id(schedule_id);
		auto it = find(courses.begin(), courses.end(), course_id);
		if (it == courses.end())
		{
			//add the course
			unordered_map<int, array<int, 3> >& schedule = student.get_schedule(schedule_id - 1);
			//array<int, 3> arr{};
			schedule[course_id] = { 0,0,0 };
		}




		//search if exist , and what lesson is
		vector <Lesson> lessons = this->courses[course_id].get_lectures();
		auto it1 = find(lessons.begin(), lessons.end(), group_id);

		if (it1 != lessons.end())
		{
			student.set_schedule(schedule_id, course_id, 1, group_id);
			return;
		}


		lessons = this->courses[course_id].get_tutorials();
		auto it2 = find(lessons.begin(), lessons.end(), group_id);

		if (it2 != lessons.end())
		{
			student.set_schedule(schedule_id, course_id, 2, group_id);
			return;
		}

		lessons = this->courses[course_id].get_labs();
		auto it3 = find(lessons.begin(), lessons.end(), group_id);

		if (it3 != lessons.end())
		{
			student.set_schedule(schedule_id, course_id, 3, group_id);
			return;
		}



		//add the course and then set schedule group id




	}

	cout << "Team number: " << group_id << " was not founded" << endl;





}
void Manage::rm_course_schedule(Student& student, stringstream& ss)
{

	string s_schedule_id, s_course_id, s_group_id, temp;
	ss >> s_schedule_id >> s_course_id >> s_group_id >> temp;
	if (s_schedule_id.empty() || s_course_id.empty() || s_group_id.empty())
	{
		cout << "s_schedule_id or s_course_id or s_group_id is missing : Rm <schedule_id> <course_id> <group_id>" << endl;
		return;
	}
	else if (temp != "")
	{
		cout << "too much parameters for : Rm <schedule_id> <course_id> <group_id>" << endl;
		return;
	}
	int schedule_id = stoi(s_schedule_id), course_id = stoi(s_course_id), group_id = stoi(s_group_id);

	//first check if group id and coursid valid
	bool valid = this->check_valid_id(course_id, schedule_id, student);
	if (!valid)
		return;


	else
	{


		//first search if the course id exist in this schedule

		vector <int> courses = student.get_courses_id(schedule_id);
		auto it = find(courses.begin(), courses.end(), course_id);
		if (it == courses.end())
		{
			//course does not exist
			cout << "Course ID: " << course_id << "is not in schedule" << endl;
			return;
		}


		unordered_map<int, array<int, 3> >& schedule = student.get_schedule(schedule_id - 1);
		for (int i = 0; i < schedule[course_id].size(); i++)
		{
			if (schedule[course_id][i] == group_id)
			{
				schedule[course_id].at(i) = 0;
				return;
			}
		}

		cout << "group id: " << group_id << "is not in schedule" << endl;
	}

}

void Manage::search_course_id(const string& str)
{

	if (str.size() != COURSE_ID_SIZE || (!all_of(str.begin(), str.end(), isdigit)))
	{
		cout << "Course ID unvalid" << endl;
		return;
	}

	int course_id = stoi(str);

	auto it = this->courses.find(course_id);
	if (it == this->courses.end())
	{
		cout << "Course ID: " << course_id << "was not founded" << endl;
		return;
	}

	cout << it->second;

	cout << "Lessons:" << endl;
	for (int lectur_num = 0; lectur_num < it->second.get_lectures().size(); lectur_num++)
		cout << "Lecture " << lectur_num + 1 << ":" << endl << it->second.get_lectures()[lectur_num] << endl;

	for (int tutorial_num = 0; tutorial_num < it->second.get_tutorials().size(); tutorial_num++)
		cout << "Tutorial " << tutorial_num + 1 << ":" << endl << it->second.get_tutorials()[tutorial_num] << endl;

	for (int lab_num = 0; lab_num < it->second.get_labs().size(); lab_num++)
		cout << "Lab " << lab_num + 1 << ":" << endl << it->second.get_labs()[lab_num] << endl;


}


void Manage::add_course()
{

	int course_id = this->course_id_valid();
	//cout << "Enter ID: ";
	//cin >> course_id;

	string course_name;
	cout << "Enter course name: ";
	cin >> course_name;


	string teacher_name = this->name_valid("teacher");

	//check if credits is numeral only, unless return 0.
	int credits = 0;
	while (credits == 0)
	{
		string string_credits;
		cout << "Enter credits: ";
		cin >> string_credits;
		credits = check_and_convert_str_to_int(string_credits);
	}

	Course course(course_id, course_name, teacher_name, credits);
	this->courses[course_id] = course;



	//get three lessons of the course


	//cout << "Data for lesson will be in this format:" << endl;
	//cout << "group,day,starting,during,teacher,class" << endl;



	this->add_specific_lesson(course_id, "Lecture");
	this->add_specific_lesson(course_id, "Tutorial");
	this->add_specific_lesson(course_id, "Lab");


}
void Manage::add_specific_lesson(int course_id, const string& lesson)
{
	string string_num;
	cout << "How many " << lesson << "s? ";
	cin >> string_num;
	cout << endl;

	int num = 0;
	while (num == 0 && string_num != "0") //repeat until input is a valid numeral
	{
		num = check_and_convert_str_to_int(string_num);
		if (num == 0)
		{
			cout << "How many lectures? ";
			cin >> string_num;
		}
	}

	if (string_num == "0")
		num = 0;

	for (int i = 0; i < num; i++)
	{
		cout << "Enter " << lesson << "#" << i + 1 << " Data:" << endl;
		this->add_lesson(course_id, lesson);
	}
}
void Manage::add_lesson(int course_id, const string& lesson)
{
	//cout << "group,day,starting,during,teacher,class" << endl;


	string string_group, string_day, string_start_time, string_during_time, teacher_name, class_name;
	int  group = 0, day = 0, start_time = 0, during_time = 0;

	cout << "Enter group number:";
	cin >> string_group;
	while (group == 0)
	{
		group = check_and_convert_str_to_int(string_group);
		if (group == 0)
			cin >> string_group;
	}

	cout << "Enter day:";
	cin >> string_day;
	while (day == 0)
	{
		day = check_and_convert_str_to_int(string_day);
		if (day == 0)
			cin >> string_day;
	}

	cout << "Enter starting time:";
	cin >> string_start_time;
	{
		start_time = check_and_convert_str_to_int(string_start_time);
		if (start_time == 0)
			cin >> string_start_time;
	}

	cout << "Enter during time:";
	cin >> string_during_time;
	{
		during_time = check_and_convert_str_to_int(string_during_time);
		if (during_time == 0)
			cin >> string_during_time;
	}


	cout << "Enter teacher name:";
	cin >> teacher_name;

	cout << "Enter class name:";
	cin >> class_name;
	cout << endl;

	Lesson 	l = Lesson(group, day, start_time, during_time, teacher_name, class_name);

	//check class exist
	int n = 0;  //if checked all classes and no avaiable class, get out

	while (this->check_class_available(course_id, l.get_starting_time(), l.get_during_time() + l.get_starting_time(), l.get_day(), class_name) == 0 && n <= TOTAL_CLASSES_SIZE)
	{
		//enter new class
		this->print_all_classes();
		cout << "Enter another class name:";
		cin >> class_name;
		l.set_class_name(class_name);
		cout << endl;
		n++;
	}



	//check teacher exist and avaiable
	n = 0;
	while (this->check_class_available(course_id, l.get_starting_time(), l.get_during_time() + l.get_starting_time(), l.get_day(), teacher_name) == 0 && n <= Teacher::get_total_teachers())
	{
		this->print_all_teachers();
		cout << "Enter Another name:";
		cin >> teacher_name;
		l.set_teacher_name(teacher_name);
		cout << endl;
	}







	if (lesson == "Lecture")
		this->courses[course_id].set_lecture(l);

	else if (lesson == "Tutorial")
		this->courses[course_id].set_tutorial(l);

	else if (lesson == "Lab")
		this->courses[course_id].set_lab(l);


}
int Manage::check_class_available(int course_id, int start_time, int end_time, int day, const string& class_name) const
{

	//to diff between class availabe and teacher available

	//check class
	string str = class_name;

	// Check if the string is only alphabetic
	if (!str.empty() && all_of(str.begin(), str.end(), [](char c) { return isalpha(c); }))
	{
		// If it's a teacher, check if it exists
		if (!this->check_teacher_exist(class_name))
			return 0;

	}
	else
	{
		// If it's a class, check if it exists
		if (!this->check_class_exist(class_name))
			return 0;

	}





	vector<Lesson> l;
	int available = 1;

	//all courses
	for (auto it = this->courses.begin(); it != this->courses.end() && it->second.get_id() != course_id && available == 1; ++it)
	{

		//for every course, check with lectures , tutorials and labs


		//run on all the lectures
		l = it->second.get_lectures();
		this->check_class_lesson(l, available, start_time, end_time, day, class_name);

		//run on all the tutorials
		l = it->second.get_tutorials();
		this->check_class_lesson(l, available, start_time, end_time, day, class_name);

		//run on all the labs
		l = it->second.get_labs();
		this->check_class_lesson(l, available, start_time, end_time, day, class_name);

	}
	return available;
}
int Manage::check_class_exist(const string& s) const
{
	array<string, 9> classes = TOTAL_CLASSES;
	auto it = find(classes.begin(), classes.end(), s);

	if (it != classes.end())
		return 1;
	else
		return 0;

}
void Manage::check_class_lesson(const vector<Lesson>& l, int& available, int start_time, int end_time, int day, const string& class_name) const
{
	for (auto itLesson = l.begin(); itLesson != l.end() && available == 1; itLesson++)
	{
		int start2 = itLesson->get_starting_time();
		int end2 = start2 + itLesson->get_during_time();
		int day2 = itLesson->get_day();
		if (day != day2) return;


		//check both Class and Teacher available

		//first check if class name same, later check the time
		//the double condtions with || on right, ensure the class is empty, so add !=

		//9-11, our is 8-10 ,  
		//if our start time < start2, so we must have aswell that our end < start2, our lesson is end before next one start
		if (!((start_time < start2 && end_time < start2) || (start_time > start2 && start_time > end2)))
		{

			if (itLesson->get_class_name() == class_name)
			{
				cout << "Class:" << class_name << " isn't available in this time,All classes:" << endl;
				available = 0;
			}

			else if (itLesson->get_teacher_name() == class_name)
			{
				cout << "Teacher:" << class_name << " isn't available in this time,All teachers:" << endl;
				available = 0;
			}



		}

		//if our start time ==start2, there is no option for the class avaiable

		//start2,end2, 9-12,   our 13-14
		//if our start time > start2, then we must check the the lesson will be end before we start
		//if(start_time > start2 && start_time > end2 )


	}

}
void Manage::print_all_classes() const
{
	array<string, TOTAL_CLASSES_SIZE> classes = TOTAL_CLASSES;
	for (auto it = classes.begin(); it != classes.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
int Manage::check_teacher_exist(const string& name) const
{
	auto it = this->persons.begin();
	while (it != persons.end())
	{
		//check is teacher
		if (dynamic_cast<Teacher*>(it->second.get()) && it->second->get_name() == name)
			return 1;

		++it;
	}
	cout << "Teacher isnt exist" << endl;
	return 0;
}
void Manage::print_all_teachers() const
{
	for (auto it = this->persons.begin(); it != this->persons.end(); it++)
	{
		if (dynamic_cast<Teacher*>(it->second.get()))
			cout << it->second->get_name() << " ";
	}
	cout << endl;
}



void Manage::rm_course(stringstream& ss)
{
	string string_id, temp;
	ss >> string_id >> temp;
	if (string_id.empty())
	{
		cout << "RmCourse missing an id : RmCourse <course_id>" << endl;
		return;
	}
	else if (temp != "")
	{
		cout << "Command was not found, : RmCourse <course_id> " << endl;
		return;
	}

	int course_id = stoi(string_id);

	auto it = this->courses.find(course_id);
	if (it == this->courses.end())
	{
		cout << "Course was not founded" << endl;
		return;
	}
	else
	{
		//remove lessons
		remove_lessons(string_id, "lectures.csv");
		remove_lessons(string_id, "tutorials.csv");
		remove_lessons(string_id, "labs.csv");

		this->courses.erase(it);
	}
}
void Manage::add_lecturer()
{
	int id = this->id_valid();
	auto person = persons.find(id);
	if (person != persons.end())
	{
		cout << "teacher already exist !" << endl;
		return;
	}
	string name = this->name_valid("teacher");

	this->persons[id] = make_unique<Teacher>(id, name);
}
void Manage::rm_lecturer(stringstream& ss)
{

	int id;
	string n;
	ss >> id >> n;
	if (n != "")
	{
		cout << "Command was not found" << endl;
		return;
	}

	auto it = this->persons.find(id);
	if (it == this->persons.end())
	{
		cout << "Teacher was not founded" << endl;
		return;
	}
	else
	{
		this->persons.erase(it);
	}
}
void Manage::add_student()
{

	int id = this->id_valid();
	auto person = persons.find(id);
	if (person != persons.end())
	{
		cout << "student already exist !" << endl;
		return;
	}
	string name = this->name_valid("student");


	string password;
	cout << "Enter password: ";
	cin >> password;
	//cout << endl;

	this->persons[id] = make_unique<Student>(id, name, password);

}
bool Manage::rm_student(stringstream& ss)
{
	string string_id, temp;
	ss >> string_id >> temp;
	if (string_id.empty())
	{
		cout << "rm_student missinf an id : RmStudent <student_id>" << endl;
		return false;
	}
	else if (temp != "")
	{
		cout << "Command was not found, : RmStudent <student_id> " << endl;
		return false;
	}

	//check if id is numerals only
	int id = check_and_convert_str_to_int(string_id);
	if (id == 0)
		return false;

	auto it = this->persons.find(id);
	if (it == this->persons.end())
	{
		cout << "Student was not founded" << endl;
		return false;
	}
	else
	{
		this->persons.erase(it);
		return true;
	}

}
void Manage::search_text(stringstream& ss)
{

	string text, temp;

	ss >> text >> temp;
	if (text.empty())
	{
		cout << "need to add a text to search for : Search <text>" << endl;
	}
	else if (temp != "")
	{
		cout << "Command was not found or too much parameters" << endl;
		return;
	}

	this->search_course(text);
	this->search_lesson(text);
	this->search_person(text);

}

void Manage::search_course(const string& text) const
{
	//course by course name, teacher name

	//serach course name
	if (text.empty()) return;

	if (!all_of(text.begin(), text.end(), isdigit))
	{
		//course name and teacher name, next 2 data members check if we can cast the string
		auto it = this->courses.begin();
		while (it != courses.end()) {
			if (it->second.get_course_name() == text || it->second.get_teacher_name() == text)
				cout << it->second;
			++it;
		}

	}

	//search by id, credits, try will throw if text isnt a number
	try
	{

		size_t pos;
		stoi(text, &pos);
		// Check if the entire string was used
		if (pos == COURSE_ID_SIZE)
		{
			//serach course id,key

			//cant use [key], const funcition declared, if key doesnot exist, map will modify
			int id = stoi(text);
			auto it = this->courses.find(id);
			if (it != this->courses.end())
			{
				cout << it->second;
			}


			/*
			for (const auto& pair : this->courses)
			{
				if (pair.second.get_id() == stoi(text))
					//cout <<"Course ID: "<< pair.second.get_id() << endl;
					cout << pair.second;
			}
			*/
		}

	}
	catch (const invalid_argument&) {}

	//search by credits
	try
	{

		size_t pos;
		stod(text, &pos);
		// Check if the entire string was used
		if (pos == text.size())
		{
			//serach credit
			for (const auto& pair : this->courses)
			{
				if (pair.second.get_credit_points() == stod(text))
					//cout << "Credits: " << pair.second.get_credit_points() << endl;
					cout << pair.second;

			}
		}

	}
	catch (const invalid_argument&) {}

}
void Manage::search_lesson(const string& text) const
{

	if (text.empty()) return;


	for (const auto& pair : this->courses)
	{
		search_lessons(text, pair.second.get_lectures(), pair.second.get_id(), "Lecture");
		search_lessons(text, pair.second.get_tutorials(), pair.second.get_id(), "Tutorial");
		search_lessons(text, pair.second.get_labs(), pair.second.get_id(), "Lab");
	}


}
void Manage::search_person(const string& text) const
{

	//serach course name
	if (text.empty()) return;

	//search by name
	if (!all_of(text.begin(), text.end(), isdigit))
	{

		//search by name
		for (const auto& pair : this->persons)
		{
			if (pair.second->get_name() == text)
				//cout << "Course name: " <<pair.second.get_course_name() <<endl;
				cout << *pair.second;
		}

	}

	//search by id
	try
	{

		size_t pos;
		stoi(text, &pos);
		// Check if the entire string was used
		if (pos == Person::get_id_size())
		{
			//serach course id
			for (const auto& pair : this->persons)
			{
				if (pair.second->get_id() == stoi(text))
					//cout <<"Course ID: "<< pair.second.get_id() << endl;
					cout << *pair.second;
			}
		}

	}
	catch (const invalid_argument&) {}



}


int Manage::join()
{
	int enter = 0;
	string type;
	int id;
	int person = 0; //student 1, teacher 2

	while (enter == 0)
	{
		cout << "student or admin?" << endl;
		cin >> type;

		if (type.compare("student") == 0)
			person = STUDENT;

		else if (type.compare("admin") == 0)
			person = ADMIN;

		if (person != 0)
		{

			id = this->id_exist();
			if (id != 0)
			{
				bool match = id_type_match(id, type); //check match between id and tpye 
				if (!match)
					enter = 0; //error will get sent from id_type_match 
				else if (person == STUDENT)
					enter = this->password_valid(id);

				else if (person == ADMIN)
					enter = this->password_admin(id);

			}

			person = 0;
		}

	}
	return id;

}
int Manage::id_exist() const
{
	int id = this->id_valid();

	auto it = this->persons.find(id);
	if (it == this->persons.end())
	{
		cout << "ID " << id << " was not founded" << endl;
		return 0;
	}
	return id;


}
//check if id match the type(student/teacher)
bool Manage::id_type_match(const int& id, const string& type)
{

	auto person = this->persons.find(id);
	if (type == "admin")
	{
		if (const Student* student = dynamic_cast<const Student*>((person->second.get())))
		{
			cout << student->get_name() << " is not an admin ! " << endl;
			return false;
		}
		else
			return true;
	}
	else
	{
		if (const Teacher* teacher = dynamic_cast<const Teacher*>((person->second.get())))
		{
			cout << teacher->get_name() << " is not a student ! " << endl;
			return false;
		}
		else
			return true;
	}
}
int Manage::id_valid() const
{

	string string_id;
	cout << "Enter ID: ";
	cin >> string_id;

	int id = 0;
	int valid = 0;
	while (valid == 0)
	{
		id = check_and_convert_str_to_int(string_id); //need to check that input is actual int
		if (id == 0 || string_id.size() != MAX_ID_SIZE)
		{
			cout << "Enter ID:";
			cin >> string_id;

		}
		else
			valid = 1;
	}

	return id;
}
int Manage::course_id_valid() const
{
	int valid = 0;
	string str;

	while (valid == 0)
	{

		cout << "Enter Course ID : ";
		cin >> str;

		if (all_of(str.begin(), str.end(), isdigit) && str.size() == COURSE_ID_SIZE)
			valid = 1;
		else
			cout << "invalid id make sure its numerals only and has " << COURSE_ID_SIZE << " numbers !" << endl;
	}

	return stoi(str);

}
string Manage::name_valid(const string& person) const
{
	string str;
	cout << "Enter " << person << " name:";
	cin >> str;

	while (!all_of(str.begin(), str.end(), [](char c) { return isalpha(static_cast<unsigned char>(c)); }))
	{
		cout << "Enter valid name:";
		cin >> str;
	}

	return str;

}
bool Manage::password_valid(int id)
{
	string password;
	int n = 0;

	while (n <= 3)
	{
		cout << "Enter Password: ";
		cin >> password;
		cout << endl;

		//cant be const
		if (password == this->persons[id]->get_password())
			return 1;
		else
		{
			cout << "Password was not founded" << endl;
			n++;
		}
	}
	return 0;

}
bool Manage::password_admin(int id)
{

	int change_password = 0;
	string password;

	//if admin didnt chnage password yet
	if (this->persons[id]->get_password() == "admin")
	{
		cout << "Your password is admin" << endl;

		cout << "Change password yes = <enter new password>, no = 0" << endl;
		cin >> change_password;
		//if (change_password == 0) 
		if (change_password != 0)
		{
			stringstream ss;
			ss << change_password;  //converting int to string 
			persons[id]->set_password(ss.str());
		}
		return 1;
	}


	//if he has a password
	else
	{
		int n = this->password_valid(id);
		return n;
	}
}

//new non-trivial commands 
void Manage::promote(stringstream& ss_id)
{
	//check is ss_id isnt empty
	string string_id, temp;
	ss_id >> string_id >> temp;
	if (string_id.empty())
	{
		cout << "missing student id in Promote command : Promote <student_id>" << endl;
		return;
	}
	else if (temp != "")
	{
		cout << "unkown command" << endl;
		return;
	}

	int id = check_and_convert_str_to_int(string_id);
	if (id == 0 && string_id != "0")
		return;
	auto person = persons.find(id);

	if (person != persons.end()) // if id exist in map
	{
		//if id belongs to a teacher
		if (const Teacher* teacher = dynamic_cast<const Teacher*>((person->second.get())))
		{
			cout << teacher->get_name() << " is already a teacher" << endl;
			return;
		}

		string student_name = persons[id]->get_name(); //storing student name

		//removing student and promoting him
		ss_id.clear();
		ss_id.str(string_id + " " + temp);
		if (rm_student(ss_id))
		{
			int new_position = string_id.length() * (-1); //negative number to move backwards
			ss_id.seekg(new_position, std::ios::cur); // learned it here : https://cplusplus.com/reference/istream/istream/seekg/
			this->persons[id] = make_unique<Teacher>(id, student_name);
		}
	}
	else
	{
		cout << "you are trying to promote an unkonwn student !" << endl;
		return;
	}
}
void Manage::add_lesson_course(stringstream& ss)
{

	string string_id, lesson;
	ss >> string_id >> lesson;
	int course_id = check_and_convert_str_to_int(string_id);
	if (course_id == 0 || string_id.size() != COURSE_ID_SIZE)
	{
		cout << "Course ID was wrong" << endl;
		return;
	}
	
	auto it = this->courses.find(course_id);
	if (it != this->courses.end())
	{
		if (lesson == "Lecture")
			this->add_lesson(course_id, lesson);

		else if (lesson == "Tutorial")
			this->add_lesson(course_id, lesson);

		else if (lesson == "Lab")
			this->add_lesson(course_id, lesson);
		else
			cout << "Lesson wasnt found" << endl;
	}
	else
		cout << "Course ID not found." << endl;


		
		

	
	


}
void Manage::rm_lesson_course(stringstream& ss)
{
	//cout << "RmLesson <course_id> <lesson_type> <team_number>, ";
	string string_id, lesson, string_number;
	ss >> string_id >> lesson >> string_number;
	int course_id = check_and_convert_str_to_int(string_id);
	if (course_id == 0 && string_id.size() != COURSE_ID_SIZE)
	{
		cout << "Course id was wrong!" << endl;
		return;
	}

	int team_number = check_and_convert_str_to_int(string_number);
	if (team_number == 0 )
	{
		cout << "Team number was wrong!" << endl;
		return;
	}

	//find team number index if exist
	auto it = this->courses.find(course_id);
	if (it != this->courses.end())
	{
		if (lesson == "Lecture")
			this->courses[course_id].pop_lecture_lesson(team_number);
		else if (lesson == "Tutorial")
			this->courses[course_id].pop_tutorial_lesson(team_number);
		else if (lesson == "Lab")
			this->courses[course_id].pop_lab_lesson(team_number);
		else
			cout << "Lesson type wasnt found" << endl;
	}
	else
		cout << "Course ID not found." << endl;



}

const unordered_map<int, Course >& Manage::get_courses() const { return this->courses; }
const unordered_map<int, unique_ptr<Person> >& Manage::get_persons() const { return this->persons; }
int Manage::get_payment(int student_id, int schedule_id)
{
	int sum = 0;
	//	vector < unordered_map < int, array<int, 3> > > Schedule; // array<>
	//cant be const function because get_schedule will not work, when i change student to const student

	//get the student
	Student* student = dynamic_cast<Student*>(this->persons[student_id].get());

	if (student)
	{
		const unordered_map<int, array<int, 3> > schedule = student->get_schedule(schedule_id);
		auto it = schedule.begin();
		auto endIt = schedule.end();

		while (it != endIt)
		{
			sum += this->courses[it->first].get_credit_points() * CREDIT_PAY;
			it++;
		}
		return sum;
	}
	else
		return 0;

}


bool time_valid(int i, int day, const Lesson& lesson)
{
	//the right time
	if (i >= lesson.get_starting_time() &&
		i <= lesson.get_starting_time() + lesson.get_during_time() &&
		lesson.get_day() == day) return 1;
	else
		return 0;
}
void check_course_print(int& another_check, int i, int n, Lesson& lesson,
	unordered_map < int, array<int, 3> >& scheudle, const vector<Course>& s_courses)
{
	int go_next_day = 0;
	int course_id = 0;
	int group_id = 0;

	//here print the course_id
	for (int day = 1; day <= 7; day++)
	{
		go_next_day = 0;

		for (const auto& val : s_courses)
		{
			course_id = val.get_id();

			//lecture
			group_id = scheudle[course_id][0];
			if (val.get_lecture(group_id, lesson) &&
				time_valid(i, day, lesson))
			{
				if (n == 0)
					cout << course_id;
				else if (n == 1)
					cout << "Lecture ";
				else if (n == 2)
				{
					cout << lesson.get_class_name();
					//delete the course so next time dont print it again
					//print another one thats on the parllel
					scheudle[course_id][0] = 0;
				}




				go_next_day = 1;
				another_check = 1;
				break;

			}


		}

		for (const auto& val : s_courses)
		{
			if (go_next_day == 1) break;

			course_id = val.get_id();

			//tutorial
			group_id = scheudle[course_id][1];
			if (val.get_tutorial(group_id, lesson) &&
				time_valid(i, day, lesson))
			{
				if (n == 0)
					cout << course_id;
				else if (n == 1)
					cout << "Tutorial";
				else if (n == 2)
				{
					cout << lesson.get_class_name();
					//delete the course so next time dont print it again
					//print another one thats on the parllel
					scheudle[course_id][1] = 0;
				}




				go_next_day = 1;
				another_check = 1;
				break;

			}
		}

		for (const auto& val : s_courses)
		{

			if (go_next_day == 1) break;
			course_id = val.get_id();

			///lab
			group_id = scheudle[course_id][2];
			if (val.get_lab(group_id, lesson) &&
				time_valid(i, day, lesson))
			{

				if (n == 0)
					cout << course_id;
				else if (n == 1)
					cout << "  Lab   ";
				else if (n == 2)
				{
					cout << lesson.get_class_name();
					//delete the course so next time dont print it again
					//print another one thats on the parllel
					scheudle[course_id][2] = 0;
				}




				go_next_day = 1;
				another_check = 1;
				break;

			}

		}


		//mean we print course id
		if (n == 0)
		{
			if (go_next_day == 1)
				cout << "      |       ";
			else
				cout << "           |       ";
		}
		else if (n == 1)
		{

			//mean we print lesson 
			if (go_next_day == 1)
				cout << "    |      ";
			else
				cout << "            |      ";

		}
		else if (n == 2)
		{

			//mean we print class
			if (go_next_day == 1)
				cout << "      |       ";
			else
				cout << "           |       ";

		}




	}

	if (n == 0)
	{
		cout << endl << "      " << flush;
		if (i < 10) cout << "" << flush;
	}
	else if (n == 1)
	{

		cout << endl << "       " << flush;
		if (i < 10) cout << "";
	}
	else if (n == 2)
	{

		cout << endl;
		cout << "       " << flush;
		if (i < 10) cout << "";
	}


}
void print_lines()
{

	for (int i = 1; i <= 7; i++)
		cout << "------------------";
	cout << "-";
	cout << endl << flush;
	for (int i = 1; i <= 7; i++)
		cout << "           " << "       |";
	cout << endl;
}
void print_days()
{
	cout << endl;
	for (int i = 1; i <= 7; i++)
		cout << "       Day" << i << "       |";

	cout << endl;

	for (int i = 1; i <= 7; i++)
		cout << "           " << "       |";
	cout << endl;




}



void search_lessons(const string& text, const vector<Lesson>& lessons, int id, const string& lesson)
{

	//search by class name,teacher name

	//class name can have alphbet and numbers

	for (const auto& val : lessons)
	{
		if (val.get_class_name() == text)
			cout << "Course ID: " << id << endl << lesson << endl << val;

	}


	//teacher name

	if (!all_of(text.begin(), text.end(), isdigit))
	{
		for (const auto& val : lessons)
		{
			if (val.get_teacher_name() == text)
				cout << "Course ID: " << id << endl << lesson << endl << val;
		}
	}


	try
	{

		size_t pos;
		stoi(text, &pos);
		// Check if the entire string was used
		if (pos == text.size())
		{

			for (const auto& val : lessons)
			{
				//search day
				if (val.get_day() == stoi(text))
					cout << "Course ID: " << id << endl << lesson << endl << val;

				//search during
				else if (val.get_during_time() == stoi(text))
					cout << "Course ID: " << id << endl << lesson << endl << val;

				//search starting
				else if (val.get_starting_time() == stoi(text))
					cout << "Course ID: " << id << endl << lesson << endl << val;

				//search group id
				else if (val.get_team_number() == stoi(text))
					cout << "Course ID: " << id << endl << lesson << endl << val;
			}
		}

	}
	catch (const invalid_argument&) {}

}