#include "Manage.h"




Lesson::Lesson(const int t, const int d, const int s, const int during_time, const string& name, const string& class_name) :
	teacher_name(name), class_name(class_name)
{
	this->team_number = t;
	this->day = d;
	this->starting_time = s;
	this->during_time = during_time;

}
Lesson::Lesson() {}
Lesson::Lesson(const Lesson& lesson) :
	teacher_name(lesson.get_teacher_name()), class_name(lesson.get_class_name())
{
	this->team_number = lesson.get_team_number();
	this->day = lesson.get_day();
	this->starting_time = lesson.get_starting_time();
	this->during_time = lesson.get_during_time();

}
Lesson::~Lesson() {}


int Lesson::get_team_number() const { return this->team_number; }
int Lesson::get_day() const { return this->day; }
int Lesson::get_starting_time() const { return this->starting_time; }
int Lesson::get_during_time() const { return this->during_time; }
string Lesson::get_teacher_name() const { return this->teacher_name; }
string Lesson::get_class_name() const { return this->class_name; }


void Lesson::set_team_number(const int n) { this->team_number = n; }
void Lesson::set_day(const int n) { this->day = n; }
void Lesson::set_starting_time(const int n) { this->starting_time = n; }
void Lesson::set_during_time(const int n) { this->during_time = n; }
void Lesson::set_teacher_name(const string& name) { this->teacher_name = name; }
void Lesson::set_class_name(const string& name) { this->class_name = name; }

ostream& operator<<(ostream& os, const Lesson& lesson)
{
	os << "Team number:" << lesson.get_team_number() << endl;
	os << "Day:" << lesson.get_day() << endl;
	os << "Start:" << lesson.get_starting_time() << endl;
	os << "End:" << lesson.get_starting_time() + lesson.get_during_time() << endl;
	os << "Teacher:" << lesson.get_teacher_name() << endl;
	os << "Class:" << lesson.get_class_name() << endl << endl;
	return os;
}
bool Lesson::operator==(int id) const { return this->team_number == id; }

string Lesson::serialization() const
{
	stringstream ss;

	ss << this->get_team_number() << ','
		<< this->get_day() << ','
		<< this->get_starting_time() << ','
		<< this->get_during_time() << ','
		<< this->get_teacher_name() << ','
		<< this->get_class_name() << '\n';


	return ss.str();

}

Lesson& Lesson::operator=(const Lesson& lesson)
{
	this->team_number = lesson.get_team_number();
	this->day = lesson.get_day();
	this->starting_time = lesson.get_starting_time();
	this->during_time = lesson.get_during_time();
	this->teacher_name = lesson.get_teacher_name();
	this->class_name = lesson.get_class_name();

	return *this;
}






Course::Course(const int id, const string& name, const string& teacher, const int c_points)
{
	this->id = id;
	this->course_name = name;
	this->teacher_name = teacher;
	this->credit_points = c_points;

}
Course::Course(const Course& course) :
	lectures(course.get_lectures()), tutorials(course.get_tutorials()), labs(course.get_labs())
{
	this->id = course.get_id();
	this->course_name = course.get_course_name();
	this->teacher_name = course.get_teacher_name();
	this->credit_points = course.get_credit_points();

}
Course::Course() {}
Course::~Course()
{

}


ostream& operator<<(ostream& os, const Course& course)
{
	os << "Course id:" << course.get_id() << endl;

	os << "Course name:" << course.get_course_name() << endl;
	os << "Course teacher:" << course.get_teacher_name() << endl;
	os << "Credit points:" << course.get_credit_points() << endl << endl;


	return os;
}



int Course::get_id() const { return this->id; }
string Course::get_course_name() const { return this->course_name; }
string Course::get_teacher_name() const { return this->teacher_name; }
double Course::get_credit_points() const { return this->credit_points; }
vector<Lesson> Course::get_lectures() const { return this->lectures; }
vector<Lesson> Course::get_tutorials() const { return this->tutorials; }
vector<Lesson>Course::get_labs() const { return this->labs; }

//this loop will be used for get_lectures/tutorials/labs
bool const get_lesson(int group_id, Lesson& lesson, const vector<Lesson>& lesson_vector)
{
	for (auto it = lesson_vector.begin(); it != lesson_vector.end(); ++it)
	{
		if (it->get_team_number() == group_id)
		{
			lesson = *it;
			return true;
		}
	}
	return false;
}


bool Course::get_lecture(int group_id, Lesson& lesson)	const { return get_lesson(group_id, lesson, this->lectures); }
bool Course::get_tutorial(int group_id, Lesson& lesson) const { return get_lesson(group_id, lesson, this->tutorials); }
bool Course::get_lab(int group_id, Lesson& lesson)		const { return get_lesson(group_id, lesson, this->labs); }



void Course::set_id(const int id) { this->id = id; }
void Course::set_course_name(const string& name) { this->course_name = name; }
void Course::set_teacher_name(const string& name) { this->teacher_name = name; }
void Course::set_credit_points(const double c_points) { this->credit_points = c_points; }
void Course::set_lecture(const Lesson& l) { this->lectures.push_back(l); }
void Course::set_tutorial(const Lesson& l) { this->tutorials.push_back(l); }
void Course::set_lab(const Lesson& l) { this->labs.push_back(l); }
void Course::pop_lecture_lesson(int i)
{
	auto it = lectures.begin();
	while (it != lectures.end())
	{
		if (i == it->get_team_number())
		{
			lectures.erase(it); // Erase returns the next iterator
			return;
		}
		it++;
	}
	cout << "Team number wasnt found" << endl;
}
void Course::pop_tutorial_lesson(int i)
{
	auto it = tutorials.begin();
	while (it != tutorials.end())
	{
		if (i == it->get_team_number())
		{
			tutorials.erase(it); // Erase returns the next iterator
			return;
		}
		it++;
	}
	cout << "Team number wasnt found" << endl;
}
void Course::pop_lab_lesson(int i)
{
	auto it = labs.begin();
	while (it != labs.end())
	{
		if (i == it->get_team_number())
		{
			labs.erase(it);
			return;
		}
		it++;
	}
	cout << "Team number wasnt found" << endl;
}



Course& Course::operator=(const Course& course)
{
	this->id = course.get_id();
	this->course_name = course.get_course_name();
	this->teacher_name = course.get_teacher_name();
	this->credit_points = course.get_credit_points();
	this->lectures = course.get_lectures();
	this->tutorials = course.get_tutorials();
	this->labs = course.get_labs();
	return *this;
}
int Course::writeForCSV(const string& filename, const unordered_map<int, Course >& courses)
{
	//int n_courses = courses.size();

	ofstream file = open_course_file(filename);

	for (auto& pair : courses)
		file << pair.second.serialization();

	file.close();

	//itirate over courses, and save its lessons(lecture/tutorial/lab) to the right file
	for (auto& pair : courses)
	{

		ofstream file_lectures = open_lesson_file("lectures.csv", pair.second);
		ofstream file_tutorials = open_lesson_file("tutorials.csv", pair.second);
		ofstream file_labs = open_lesson_file("labs.csv", pair.second);


		write_lesson_to_csv(file_lectures, pair.second, &Course::get_lectures);
		write_lesson_to_csv(file_tutorials, pair.second, &Course::get_tutorials);
		write_lesson_to_csv(file_labs, pair.second, &Course::get_labs);

		file_lectures.close();
		file_tutorials.close();
		file_labs.close();


	}
	return 0;
}
unordered_map<int, Course > Course::readFromCSV(const string& filename)
{
	ifstream file;
	file.open(filename);

	try
	{
		if (!file.is_open())
		{
			cout << "Courses file didnt open" << endl;
			throw;
		}
	}
	catch (int) {};

	unordered_map <int, Course > courses;
	//vector< Course> courses;
	string line;

	//get title
	getline(file, line);

	//first read line of the course, then read 3 lessons and add them

	//4 tokens for course
	string para[4]; //parameters 
	Course course;

	int n = 0; //number token
	while (getline(file, line))
	{
		stringstream  ss(line);
		while (getline(ss, para[n++], ',')) {}

		//get course first 4 parameters
		course = Course(stoi(para[0]), para[1], para[2], stoi(para[3]));


		fileSetLesson("lectures.csv", &Course::set_lecture, course);
		fileSetLesson("tutorials.csv", &Course::set_tutorial, course);
		fileSetLesson("labs.csv", &Course::set_lab, course);

		//fileSetLesson("lectures.csv", set_lecture_wrapper, course);
		//fileSetLesson("tutorials.csv", set_tutorial_wrapper, course);
		//fileSetLesson("labs.csv", set_lab_wrapper, course);


		courses[stoi(para[0])] = course;
		//courses.push_back(course);
		n = 0;
	}

	file.close();
	return courses;

}
string Course::serialization() const
{
	stringstream ss;

	ss << this->get_id() << ','
		<< this->get_course_name() << ','
		<< this->get_teacher_name() << ','
		<< this->get_credit_points() << '\n';

	return ss.str();
}



void fileSetLesson(const string& lesson_name, set_method set_lesson, Course& course)
{

	string lesson_filename = to_string(course.get_id()) + "_" + lesson_name; //lesson_filename = "xxxx_lessonName"
	ifstream file;
	file.open(lesson_filename);
	//if (!file.is_open()) cout << "Course ID:"<< course.get_id() <<", lesson didnt open" <<endl;

	try
	{
		if (!file.is_open())
		{
			cout << "Course ID:" << course.get_id() << ", lesson didnt open" << endl;
			throw;
		}
	}
	catch (int) {};


	//else
	//{
	string line;
	string para[6];
	int n = 0;

	getline(file, line);


	while (getline(file, line) && line.size())
	{

		stringstream  ss(line);
		while (getline(ss, para[n++], ',')) {}
		Lesson 	lesson = Lesson(stoi(para[0]), stoi(para[1]), stoi(para[2]), stoi(para[3]), para[4], para[5]);
		(course.*set_lesson)(lesson); //set_lesson will become address to the correct method

		ss.str("");
		ss.clear();
		n = 0;
	}
	file.close();
	//}

}
ofstream open_course_file(const string& file_name)
{
	ofstream file;
	file.open(file_name);

	try
	{
		if (!file.is_open())
		{
			cout << file_name + " didnt open" << endl;
			throw;
		}
	}
	catch (int) {};

	file << "id,name,teacher,credits" << "\n";

	return file;
}
ofstream open_lesson_file(const string& file_name, const Course& course)
{
	ofstream file;
	string lesson_filename;
	lesson_filename = to_string(course.get_id()) + "_" + file_name;
	file.open(lesson_filename);

	try
	{
		if (!file.is_open())
		{
			cout << lesson_filename + " didnt open" << endl;
			throw;
		}
	}
	catch (int) {};
	file << "group,day,starting,during,teacher,class" << "\n";

	return file;
}

//i used pointer to function and defined a type, learned it here : https://isocpp.org/wiki/faq/pointers-to-members 
void write_lesson_to_csv(ofstream& file, const Course& course, get_method get_lessons)
{
	const vector<Lesson> lessons = (course.*get_lessons)();
	vector<Lesson>::iterator it;

	for (auto it = lessons.begin(); it != lessons.end(); ++it)
		file << it->serialization();
}
void remove_lessons(const string& string_id, const string& lesson)
{
	string filename = string_id + "_" + lesson;
	remove(filename.c_str());
}






//no need for this wrapper anymore because i used typedef for pointer to function 
/*
void set_lecture_wrapper(Course& course, const Lesson& lesson) {
	course.set_lecture(lesson);
}

void set_tutorial_wrapper(Course& course, const Lesson& lesson) {
	course.set_tutorial(lesson);
}

void set_lab_wrapper(Course& course, const Lesson& lesson) {
	course.set_lab(lesson);
}
*/












