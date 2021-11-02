
#include <string>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>

using namespace std;

string ft_cap(string str)
{
	int i = 0;

	while (i < str.length())
	{
		str[i] = toupper(str[i]);
		i++;
	}
	return str;
}

int ft_create_filename(string outfilename, string classname, string infilename)
{
	ifstream cppfile(infilename);
	stringstream buffer;
	string replaced;
	ofstream out(outfilename);

	buffer << cppfile.rdbuf();
	replaced = buffer.str();

	int index;

	while (replaced.find("%s") != -1)
	{
		index = replaced.find("%s");

		replaced.erase(index, 2);
		replaced.insert(index, classname);
	}

	while (replaced.find("%S") != -1)
	{
		index = replaced.find("%S");

		replaced.erase(index, 2);
		replaced.insert(index, ft_cap(classname));
	}
	out << replaced;
	return 0;
}

int main(int ac, char **av)
{
	string classname;
	string cwd = getcwd(NULL, 0);
	string hppfilename;
	string cppfilename;

	string userres;
	string path_to_template("/home/rmechety/Script/exec/");
	int i = 1;

	if (ac < 2)
	{
		cout << "The ClassCreator programme need arguments" << endl;
		cout << "Try ClassCreator -help" << endl;
		return 0;
	}

	if (string(*(av + 1)) == "-help")
	{
		cout << "ClassCreator [ClassName]..." << endl;
		cout << "The program will create the file from the template in ClassCreator Dir" << endl;
		return 0;
	}

	while (i < ac)
	{
		classname = string(*(av + i));
		hppfilename = cwd + "/" + classname + ".hpp";
		cppfilename = cwd + "/" + classname + ".cpp";
		if (access(hppfilename.c_str(), F_OK) == 0)
		{
			cout << "The file " << hppfilename << " already exist" << endl;
			cout << "Do you want to recreate it ? (y/n)" << endl;
			cin >> userres;
			if (userres == "y" || userres == "yes" || userres == "Y" || userres == "YES")
				ft_create_filename(hppfilename, classname, path_to_template + "Template.hpp");
			else
				cout << "You said no" << endl;
		}
		else
			ft_create_filename(hppfilename, classname, path_to_template + "Template.hpp");
		if (access(cppfilename.c_str(), F_OK) == 0)
		{
			cout << "The file " << cppfilename << " already exist" << endl;
			cout << "Do you want to recreate it ? (y/n)" << endl;
			cin >> userres;
			if (userres == "y" || userres == "yes" || userres == "Y" || userres == "YES")
				ft_create_filename(cppfilename, classname, path_to_template + "Template.cpp");
			else
				cout << "You said no" << endl;
		}
		else
			ft_create_filename(cppfilename, classname, path_to_template + "Template.cpp");
		i++;
	}

	return (0);
}
