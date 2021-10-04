#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <fstream>

const int N = 5;



struct birthday {
	int day;
	int m;
	int year;
};

struct student {
	std::string name;
	std::string surname;
	birthday b{ 0,0,0 };
	student* next{ nullptr };
	student* prev{ nullptr };
};
void RW(std::string fileName, std::string* str);

void RW(std::string fileName, student* head);

void RW(std::string fileName, std::string* str)
{
	std::ofstream outf(fileName, std::ios::app);
	outf << *str << std::endl;
	outf.close();
}

void RW(std::string fileName, student* head)
{
	student* current = head;
	std::ofstream outf(fileName, std::ios::binary);
	while (current->next)
	{
		///outf << current->surname << '\t' << current->name << '\t' << current->b.day << "\t" << current->b.m << "\t" << current->b.year << std::endl;
		outf.write((char*)current, sizeof(student));
		current = current->next;
	}
	outf.close();
}

void RD(std::string fileName);
student* RD(std::string fileName, birthday bb);

void RD(std::string fileName)
{
	std::ifstream inf{ fileName };
	while (!inf.eof())
	{
		std::string str;
		std::getline(inf, str);
		std::cout << str << std::endl;
	}
}

student* RD()
{
	student* head{ new student };
	student* current = head;
	std::ifstream inf{ "info.dat" };
	while (!inf.eof())
	{
		inf.read((char*)current, sizeof(student));
		if (!inf.eof())
		{
			current->next = new student;
			if (current->b.m == 6)
			{
				if (current->b.day >= 22)
				{
					student* temp = current;
					current = current->next;
					current->prev = temp;
				}
			}
			else if (current->b.m == 7)
			{
				if (current->b.day <= 21)
				{
					student* temp = current;
					current = current->next;
					current->prev = temp;
				}
			}
		}
	}
	return head;
}



int main()
{
	student* stud{ new student };
	student* head = stud;
	student* current = head;
	if (stud)
	{
		for (int i{ 0 }; i < N; i++)
		{
			std::cout << "Enter name: ";
			std::cin >> current->name;
			std::cout << "Enter surname: ";
			std::cin >> current->surname;
			std::cout << "Enter birth year: ";
			std::cin >> current->b.year;
			std::cout << "Enter birth month: ";
			std::cin >> current->b.m;
			std::cout << "Enter birth day: ";
			std::cin >> current->b.day;
			student* temp = current;
			current->next = new student;
			current = current->next;
			current->prev = temp;
			current->next = NULL;
			//std::cout << stud->surname << '\t' << stud->name << '\t' << stud->b.day << "." << stud->b.m << "." << stud->b.year << std::endl;
		}
	}
	current = head;
	/*while (current->next)
	{
		std::cout << current->surname << '\t' << current->name << '\t' << current->b.day << "." << current->b.m << "." << current->b.year << std::endl;
		current = current->next;

	}*/
	//std::cout << head->surname << '\t' << head->name << '\t' << head->b.day << "." << head->b.m << "." << head->b.year << std::endl;
	std::string str{};
	std::stringstream strss;
	while (current->next)
	{

		strss << current->name << '\t' << current->surname << '\t' << current->b.day << "." << current->b.m << "." << current->b.year << std::endl;

		std::getline(strss, str);
		RW("info.txt", &str);
		current = current->next;
	}

	RD("info.txt");
	RW("info.dat", head);
	head = NULL;
	head = RD();
	current = head;
	while (current->next)
	{
		std::cout << current->surname << '\t' << current->name << '\t' << current->b.day << "." << current->b.m << "." << current->b.year << std::endl;
		current = current->next;
	}
	return 0;
}