#ifndef _PERSON_H_
#define _PERSON_H_




#define MAX_ID_SIZE 9
#define DEFAULT_PASSWORS "123456"
class Manage;

using namespace std;

class Person {



private:

	int id;
	string name;
	string password;



public:

	Person(const int id, const string& name, const string& password);
	Person(const Person&);


	virtual ~Person() = 0;


	friend ostream& operator<<(ostream& os, const Person& person);
	Person* operator=(const Person* b);
	int& operator[](int index);
	int operator[](int index) const;

	string get_name() const;
	int get_id() const;
	string get_password() const;
	static int get_id_size();
	void set_name(const string& name);
	void set_id(const int id);
	void set_password(const string& password);

	virtual void print(ostream& os) const; //to allow use << in poly
	virtual string serialization() const = 0;
	virtual void print_actions_menu() const;
	virtual void join(int& id, int& password) const = 0;
	virtual void use_actions(Manage& manage) = 0;







	//reading from csv , cant return as &
	static unordered_map< int, unique_ptr<Person> > readFromCSV(const string& filename_students, const string& filename_teachers);
	//writing to csv
	static int writeForCSV(const string& filename_students, const string& filename_teachers, const unordered_map<int, unique_ptr<Person> >& persons);



};

ostream& operator<<(ostream& os, const Person& person);









class Student : public Person
{
private:
	//int password;
	static int number_students;


	vector < unordered_map < int, array<int, 3> > > Schedule; // array<>

public:

	Student(const int id, const string& name, const string& password = DEFAULT_PASSWORS);
	Student(const Student& student);
	~Student();

	static int get_total_students();

	void print(ostream& os) const; //to allow use << in poly
	string serialization() const;
	void print_actions_menu() const;
	void join(int& id, int& password) const;
	void use_actions(Manage& manage);

	void set_schedule(int schedule_id, int course_id, int lesson, int group_id);

	int get_schedule_size() const;
	vector<int> get_courses_id(int scheudle_number) const;
	unordered_map<int, array<int, 3> >& get_schedule(int schedule_number);
	vector < unordered_map<int, array<int, 3> > >& get_schedules();




	void read_schedule();
	void write_schedule() const;





};








class Teacher : public Person
{
private:
	static int number_teachers;

public:

	Teacher(const int id, const string& name, const string& password = "admin");
	Teacher(const Teacher& teacher);
	~Teacher();


	static int get_total_teachers();
	void print(ostream& os) const; //to allow use << in poly
	string serialization() const;
	void print_actions_menu() const;
	void join(int& id, int& password) const;
	void use_actions(Manage& manage);




};



ofstream open_person_file(const string& file_name);
void check_person(const Person& person);
void get_command(string& command, stringstream& ss);
int check_and_convert_str_to_int(const string& string_id);



#endif