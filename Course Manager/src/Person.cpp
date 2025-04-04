#include "Manage.h"


int Student::number_students = 0;
int Teacher::number_teachers = 0;


Person::Person(const int id, const string& name, const string& password) : id(id), name(name), password(password) {};
Person::Person(const Person& person) : id(person.id), name(person.name), password(person.password) {};
Person::~Person() {};


ostream& operator<<(ostream& os, const Person& person)
{
	check_person(person);
	os << "Name:" << person.get_name() << endl;
	os << "Id:" << person.get_id() << endl;
	person.print(os);
	os << endl;
	return os;
}
void Person::print(ostream& os) const
{

}
Person* Person::operator=(const Person* b)
{
	this->id = b->id;
	this->name = b->name;
	return this;
}

string Person::get_name() const { return this->name; }
int Person::get_id() const { return this->id; }
string Person::get_password() const { return this->password; }
int Person::get_id_size()
{
	//id size
	return MAX_ID_SIZE;
}
void Person::set_name(const string& name) { this->name = name; }
void Person::set_id(const int id) { this->id = id; }
void Person::set_password(const string& password) { this->password = password; }


//its making copy of vectors, maybe use &
unordered_map<int, unique_ptr<Person> > Person::readFromCSV(const string& filename_students, const string& filename_teachers)
{


	ifstream file1;
	file1.open(filename_students);
	//if (!file1.is_open()) //try
	try
	{
		if (!file1.is_open())
		{
			cout << "Studnets file didnt open" << endl;
			throw;
		}
	}
	catch (int) {};

	//vector< unique_ptr<Person> > persons;
	unordered_map<int, unique_ptr<Person> > persons;
	string line;
	string para[3]; //convert them , student parameters

	stringstream  ss(line);
	int n = 0; //number token

	//title
	getline(file1, line);


	while (getline(file1, line))
	{
		ss.str(line);
		while (getline(ss, para[n++], ',')) {}
		persons[stoi(para[0])] = make_unique<Student>(stoi(para[0]), para[1], para[2]);

		ss.clear();
		n = 0;
	}
	file1.close();



	ifstream file2;
	file2.open(filename_teachers);

	try
	{
		if (!file2.is_open())
		{
			cout << "Teachers file didnt open" << endl;
			throw;
		}
	}
	catch (int) {};

	getline(file2, line);

	while (getline(file2, line))
	{
		ss.str(line);
		while (getline(ss, para[n++], ',')) {}
		if (para[2].empty() == 1)
			persons[stoi(para[0])] = make_unique<Teacher>(stoi(para[0]), para[1]);
		else
			persons[stoi(para[0])] = make_unique<Teacher>(stoi(para[0]), para[1], para[2]);


		ss.clear();
		para[2] = "";
		n = 0;

	}

	file2.close();

	return persons;

}
int Person::writeForCSV(const string& filename_students, const string& filename_teachers, const unordered_map<int, unique_ptr<Person> >& persons)

{


	ofstream students_file;
	students_file.open(filename_students);

	try
	{
		if (!students_file.is_open())
		{
			cout << "Studnets file didnt open" << endl;
			throw;
		}
	}
	catch (int) {};

	students_file << "id,name,password" << "\n";

	ofstream teachers_file;
	teachers_file.open(filename_teachers);



	try
	{
		if (!teachers_file.is_open())
		{
			cout << "Teachers file didnt open" << endl;
			throw;
		}
	}
	catch (int) {};

	teachers_file << "id,name,password" << "\n";




	for (const auto& pair : persons)
	{


		//Type checking

		//const Student* student = dynamic_cast<const Student*>(obj.get());
		const Student* student = dynamic_cast<const Student*>(pair.second.get());

		if (student)
		{
			students_file << student->serialization();
			student->write_schedule();
		}

		else
		{
			//const Teacher* teacher = dynamic_cast<const Teacher*>(obj.get());
			const Teacher* teacher = dynamic_cast<const Teacher*>(pair.second.get());
			teachers_file << teacher->serialization();
		}

	}

	students_file.close();
	teachers_file.close();

	return 0;
}
void Person::print_actions_menu() const
{
	cout << endl;
	cout << "Options:" << endl;
	cout << "Print <course_id>" << endl;
	cout << "PrintCourses" << endl;
	//cout << "More" << endl;
	//cout << "Back" << endl;

}















Student::Student(const int id, const string& name, const string& password) :Person(id, name, password)
{

	this->read_schedule();
	Student::number_students++;


}
Student::Student(const Student& student) : Person(student.get_id(), student.get_name(), student.get_password())
{
	Student::number_students++;
}
Student::~Student()
{
	Student::number_students--;
}

void Student::print(ostream& os) const { os << "Password:" << this->get_password() << endl; }
string Student::serialization() const
{
	stringstream ss;
	ss << this->get_id() << ','
		<< this->get_name() << ','
		<< this->get_password() << "\n";
	return ss.str();
}
void Student::print_actions_menu() const
{


	//schedule actions
	cout << "Print <schedule_id>" << endl;
	cout << "PrintAll" << endl;
	cout << "AddScheudle" << endl;
	cout << "RmScedule <schedule_id>" << endl;
	cout << "Add <schedule_id> <course_id> <group_id>" << endl;
	cout << "Rm <schedule_id> <course_id> <group_id>" << endl;
	cout << "Search <course_id>" << endl;
	cout << "Back" << endl;

}
void Student::join(int& id, int& password) const
{

	cout << "Enter your id: ";
	cin >> id;
	cout << endl;

	cout << "Enter your password: ";
	cin >> password;
	cout << endl;

}
void Student::use_actions(Manage& manage)
{
	Person::print_actions_menu();
	cout << "Schedule" << endl;
	cout << "Back" << endl;

	//string input;
	//getline(cin, input);
	//cout << endl;
	//input = "Print 15530";
	//input = "Rm 2 13622 32";
	//input = "Add 2 22211 31 ";
	//input = "RmSchedule 2";
	//input = "AddSchedule";
	//input = "Print 1";
	//input = "PrintAll";


	stringstream ss("");
	string command;

	//getline(cin, command);
	get_command(command, ss);


	while (command != "Back")
	{


		if (command == "Schedule")
		{
			this->print_actions_menu();
			get_command(command, ss);

		}

		if (command == "Print")
		{
			//two print, check who is course
			string string_id, temp;
			ss >> string_id >> temp;
			bool isDigit = all_of(string_id.begin(), string_id.end(), isdigit);

			if (string_id.empty() || temp != "" || !isDigit)
				cout << "Print must contain course/schedule id : print <id>" << endl;
			else
			{
				int id = stoi(string_id);
				if (string_id.size() == 5)
					manage.print_by_courseid(id);
				else
					manage.print_schedule(*this, id);
			}


		}

		else if (command == "PrintAll")
			manage.print_all(*this);

		else if (command == "PrintCourses")
			manage.print_ten_courses();

		/*
		else if (command == "More")
			manage.print_more_ten();
		*/

		//else if (command == "Print")
			//manage.print_schedule(*this, ss);

		else if (command == "AddSchedule")
			manage.add_schedule(*this);

		else if (command == "RmSchedule")
			manage.rm_schedule(*this, ss);

		else if (command == "Add")
			manage.add_course_schedule(*this, ss);

		else if (command == "Rm")
			manage.rm_course_schedule(*this, ss);

		else if (command == "Search")
		{
			ss >> command >> command;
			manage.search_course_id(command);
		}

		else cout << "Wrong command" << endl;




		//return;





		//next 
		cout << endl;
		Person::print_actions_menu();
		cout << "Schedule" << endl;
		cout << "Back" << endl; // back the last one
		get_command(command, ss);

	}


}


void Student::set_schedule(int schedule_id, int course_id, int lesson, int group_id)
{
	//key exist
	//lesson=1 lecture, lesson=2 tutorial, lesson=3 lab

	this->Schedule[schedule_id - 1][course_id][lesson - 1] = group_id;

}
int Student::get_schedule_size() const { return this->Schedule.size(); }
int Student::get_total_students() { return Student::number_students; }
vector<int> Student::get_courses_id(int scheudle_number) const
{
	vector <int> courses;

	for (const auto& pair : this->Schedule[scheudle_number - 1])
		courses.push_back(pair.first);

	return courses;
}
unordered_map<int, array<int, 3> >& Student::get_schedule(int schedule_number) { return this->Schedule[schedule_number]; }
vector <unordered_map<int, array<int, 3> > >& Student::get_schedules() { return this->Schedule; }

void Student::read_schedule()
{
	string filename = to_string(this->get_id()) + ".csv";
	ifstream file;
	file.open(filename);



	string line;
	stringstream ss;
	string para[4];
	int n = 0;

	//title
	getline(file, line);
	getline(file, line);

	//int n_schedule = 0;


	while (getline(file, line) && line.size())
	{
		//check if we have only digits, number of schedule
		if (line.find(',') == string::npos)
		{
			//n_schedule = stoi(line);
			this->Schedule.resize(this->Schedule.size() + 1);
		}

		else
		{
			//add courses to the curr schedule
			ss.str(line);
			while (getline(ss, para[n++], ',')) {}
			this->Schedule.back()[stoi(para[0])] = { stoi(para[1]) , stoi(para[2]) ,stoi(para[3]) };

			ss.clear();
			n = 0;
		}

	}



}
void Student::write_schedule() const
{

	//string line;
	//string filename = to_string(student->get_id());
	ofstream file;
	file.open(to_string(this->get_id()) + ".csv");
	stringstream ss;

	file << "Number" << "\n";
	file << "id,lecture_group,tutorial_group,lab_group" << "\n";

	for (int i = 0; i < this->Schedule.size(); i++)
	{

		auto it = this->Schedule[i].begin();
		auto endIt = this->Schedule[i].end();
		file << i + 1 << "\n";
		while (it != endIt)
		{

			ss << it->first << ","
				<< it->second[0] << ","
				<< it->second[1] << ","
				<< it->second[2] << "\n";
			file << ss.str();

			ss.str("");
			ss.clear();
			it++;
		}

	}



}












Teacher::Teacher(const int id, const string& name, const string& password) :Person(id, name, password)
{
	Teacher::number_teachers++;
}
Teacher::Teacher(const Teacher& teacher) : Person(teacher.get_id(), teacher.get_name(), 0)
{
	Teacher::number_teachers++;
}
Teacher::~Teacher()
{
	Teacher::number_teachers--;
}

void Teacher::print(ostream& os) const
{
	if (this->get_password() != "admin")
		cout << "Password: " << this->get_password() << endl;
}
string Teacher::serialization() const
{
	stringstream ss;
	ss << this->get_id() << ','
		<< this->get_name();
	if (this->get_password() != "admin")
		ss << ',' << this->get_password();
	ss << "\n";
	return ss.str();
}
int Teacher::get_total_teachers() { return Teacher::number_teachers; }
void Teacher::print_actions_menu() const
{
	cout << "AddCourse, ";
	cout << "RmCourse <course_id>, ";
	cout << "RmLecturer <lecturer_id>" << endl;
	cout << "AddStudent, ";
	cout << "RmStudent <student_id>, ";
	cout << "Search <search_text>" << endl;
	cout << "Promote <student_id>, ";
	cout << "RmLesson <course_id> <lesson_type> <team_number>, ";
	cout << "AddLesson <course_id> <lesson_type>" << endl;
	cout << "Back" << endl;
}
void Teacher::join(int& id, int& password) const
{

	cout << "Enter your id: ";
	cin >> id;
	cout << endl;

	//search for id in teachers csv.	

	cout << "Enter your password: (admin) ";
	cin >> password;
	cout << endl;
	cout << "Do you want to change password?, 1 or 0" << endl;
	int n;
	cin >> n;
	if (n == 1)
	{
		cout << "Enter new password: ";
		cin >> password;
	}

}
void Teacher::use_actions(Manage& manage)
{
	
	this->print_actions_menu();

	//input = "AddCourse 10030 Computer4 Ner 2.5";
	//input = "RmCourse 13622";
	//input = "AddLecturer 203987444 Oen";
	//input = "AddStudent";
	//input = "RmStudent 207846936";
	//input = "Search 22211";
	//input = "Search Computer3";
	//input = "Search 1";
	stringstream ss;
	string command;

	getline(cin, command);
	get_command(command, ss);

	while (command != "Back")
	{




		if (command == "Print")
		{
			string string_id, temp;
			ss >> string_id >> temp;
			bool isDigit = all_of(string_id.begin(), string_id.end(), isdigit);
			if (string_id.empty() || temp != "" || !isDigit)
				cout << "Print must contain only course_id : print <course_id>" << endl;
			else
			{
				int id = stoi(string_id);
				manage.print_by_courseid(id);
			}
		}

		else if (command == "PrintCourses")
			manage.print_ten_courses();

		else if (command == "More")
			manage.print_more_ten();

		else if (command == "AddCourse")
			manage.add_course();

		else if (command == "RmCourse")
			manage.rm_course(ss);

		else if (command == "AddLecturer")
			manage.add_lecturer();

		else if (command == "RmLecturer")
			manage.rm_lecturer(ss);

		else if (command == "AddStudent")
			manage.add_student();

		else if (command == "RmStudent")
			manage.rm_student(ss);

		else if (command == "Search")
			manage.search_text(ss);

		else if (command == "Promote")
			manage.promote(ss);

		else if (command == "AddLesson")
			manage.add_lesson_course(ss);

		else if (command == "RmLesson")
			manage.rm_lesson_course(ss);

		else
			cout << "wrong command !" << endl;

		cout << endl;
		this->print_actions_menu();
		ss.str("");
		get_command(command, ss);


	}

}


void check_person(const Person& person)
{
	if (const Student* student = dynamic_cast<const Student*>(&person))
		cout << "Student" << endl;

	else if (const Teacher* teacher = dynamic_cast<const Teacher*>(&person))
		cout << "Teacher" << endl;
}
void get_command(string& command, stringstream& ss)
{
	int first_input = 0;
	string input = "";
	ss.clear();
	ss.str("");

	//somtimes the cin has empty stings or new_lines we need to get rid of them
	cout << "Enter command: ";
	while (input == "" || input == "\n")
	{
		getline(cin, input);
		if (first_input > 0 && input == "")
			cout << "Enter command: ";
		first_input++;
	}
	cout << endl;


	ss << input; //ss gets all of input
	ss >> command; //ss give the first word to command
}

int check_and_convert_str_to_int(const string& string_id)
{
	if (!all_of(string_id.begin(), string_id.end(), isdigit))
	{
		cout << "input must contain numerals only !" << endl;
		return 0;
	}
	int id = stoi(string_id);
	return id;
}





