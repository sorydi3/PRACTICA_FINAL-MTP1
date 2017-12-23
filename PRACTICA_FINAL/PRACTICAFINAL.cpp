// PRACTICAFINAL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<vector>

using namespace std;
const unsigned CAPACITY = 1000;
//struct that store information about an app
struct Date {
	unsigned day;
	unsigned month;
	unsigned year;
};
struct App {
	unsigned Id_app;
	string name_app;
	string type;
	Date date;
	unsigned downloads;
};
//declared an vector os type App
typedef App infoApps[CAPACITY];

//struct info about an vector
struct Vector_apps {
	infoApps apps;
	unsigned curren_size;
};
////////////////////////////////////------------SHOW INFO APP  METHODE AND READ APP FROM FILE METHODE----------///////////////////////////////////
App read_app(ifstream& in_file) {
	//pre: file open
	//post:
	App app;
	in_file >> app.Id_app >> app.name_app >> app.type >> app.date.day >> app.date.month >> app.date.year >> app.downloads;
	return app;
}
void show_info_app(const Vector_apps vector_apps, unsigned pos_element) {
	//pre:cert
	//post:
	cout << vector_apps.apps[pos_element].Id_app << "  " << vector_apps.apps[pos_element].name_app << "  " << vector_apps.apps[pos_element].type
		<< "  " << vector_apps.apps[pos_element].date.day << "  " << vector_apps.apps[pos_element].date.month << "  " << vector_apps.apps[pos_element].date.year
		<< "  " << vector_apps.apps[pos_element].downloads << endl;
}
////////////////////////////////////////-------------BINARY SERACH METHODE---------------////////////////////////////////////////////////////////////////
void search_element(Vector_apps& vector, App app, bool& is_there, unsigned & pos_element) {
	//pre:cert
	//post:
	int low = 0;
	int hight = vector.curren_size - 1;
	int pos = 0;
	while (low <= hight && !is_there) {
		pos = (low + hight) / 2;
		if (vector.apps[pos].Id_app == app.Id_app) is_there = true;
		else if (vector.apps[pos].Id_app < app.Id_app)low = pos + 1;
		else hight = pos - 1;
	}
	if (is_there)pos_element = pos;
	else pos_element = low;
	//incert_to_position(vector, pos, app);
}
/////////////////////////////////////-------------INSERT METHODE IN ORDERED ARRAY-----------------////////////////////////////////////////////////////////
void fill_vector_sorting(Vector_apps &vector, App app) {
	//pre:cert
	//post:
	int i = vector.curren_size;
	while (i > 0 && app.Id_app < vector.apps[i - 1].Id_app) {
		vector.apps[i] = vector.apps[i - 1];
		i--;
	}
	vector.apps[i] = app;
	vector.curren_size++;
}

////////////////////////////////////////-----------METHODE THAT READ THE FILE---------------///////////////////////////////////////////////////
void read_file(ifstream &in_file, Vector_apps &vector_apps) {
	//pre:
	//post:
	App app;
	app = read_app(in_file);
	while (!in_file.eof()) {
		fill_vector_sorting(vector_apps, app);
		app = read_app(in_file);
	}
}
void print_vector(Vector_apps &vector) {
	for (int i = 0; i < vector.curren_size; i++)cout << "id app:  " << "[" << i << "] = " << vector.apps[i].Id_app << endl;
}
////////////////////////////////////-----------REGISTER AN APP-------------//////////////////////////////////////////////////////////////////

void incert_element(Vector_apps &vector, App app, unsigned pos) {
	//pre:
	//post:
	for (int i = vector.curren_size - 1; i > pos; i--) {
		vector.apps[i] = vector.apps[i - 1];
	}
	cout << " receved to incert: " << app.Id_app << app.name_app << app.type << app.date.day << app.date.month << app.date.year << app.downloads;
	vector.apps[pos] = app;
	vector.curren_size++;
	cout << "succeful insercion  size !: pos " << vector.curren_size << " : " << pos << endl;
}

void register_app(Vector_apps& vector_apps) {
	//pre:
	//post:
	cout << "estoy en register " << endl;
	App app;
	bool is_there = false;
	unsigned pos_insersion;
	cout << "insert details of the apps " << endl;
	cin >> app.Id_app >> app.name_app >> app.type >> app.date.day >> app.date.month >> app.date.year >> app.downloads;
	search_element(vector_apps, app, is_there, pos_insersion);
	if (is_there) cout << "CODI EXISTENT" << endl;
	else incert_element(vector_apps, app, pos_insersion);
}

//////////////////////////////////---------QUERRY INFO VECTOR--------///////////////////////////////////////////////////////////////

void querry_info_app(Vector_apps &vector_apps) {
	//pre:
	//post:
	App app;
	cin >> app.Id_app;
	bool is_there = false;
	unsigned pos_app = 0;
	search_element(vector_apps, app, is_there, pos_app);
	if (is_there) show_info_app(vector_apps, pos_app);
	else cout << "CODI INEXISTENT" << endl;

}
////////////////////////////////////////////--------------UPDATE AND DELETE METHODE-------------///////////////////////////////////////////////////

void delete_app_vector(Vector_apps &vector_app, App app, unsigned pos_element) {
	//pre:
	//post:
	for (unsigned i = pos_element; i <= vector_app.curren_size - 2; i++)
		vector_app.apps[i] = vector_app.apps[i + 1];
	vector_app.curren_size--;
	cout << "succeful deletion : " << endl;
}

void modifier_vector(Vector_apps &vector_apps, char option) {
	//pre:
	//post:
	App app;
	bool is_there = false;
	unsigned pos_element = 0, n_downloads;
	cin >> app.Id_app;
	search_element(vector_apps, app, is_there, pos_element);
	if (option == 'd' && is_there) {
		cout << "ENTER NUMBER DOWLOADS: ";
		cin >> n_downloads;//ask user to enter the number of the new dowloads
		vector_apps.apps[pos_element].downloads += n_downloads; //update downloads
		cout << "succeful downloads " << endl;
		show_info_app(vector_apps, pos_element);
	}
	else if (option == 'b' && is_there) delete_app_vector(vector_apps, app, pos_element);//delete an app
	else {
		if (!is_there)cout << "CODI INEXISTEN " << endl;
		else cout << "CODI EXISTENT " << endl;
	}
}
///////////////////////////////////////////////////////------------MANAGER METHODS---------//////////////////////////////////////////////////////////
void showMenu(char &option) {
	cout << "CHOOSE ACTION " << endl;
	cout << "L:llista apps" << endl;
	cout << "A:Alta" << endl;
	cout << "B:Baixa app" << endl;
	cout << "C:Codi_app info" << endl;
	cout << "T:raonament" << endl;
	cout << "X:--" << endl;
	cin >> option;
}
void compute_option(char option, Vector_apps& vector_apps) {
	option = tolower(option);
	cout << "estoy aquii compute : " << option << endl;
	switch (option)
	{
	case 'l':
		//sort_apps_by_dowloads(vector_apps);
		break;
	case 'a':

		register_app(vector_apps);
		break;
	case 'b':
		//delete_app(vector_apps);
		modifier_vector(vector_apps, option);
		break;
	case 'c':
		querry_info_app(vector_apps);
		break;
	case 'd':
		//update_downloads(vector_apps);
		modifier_vector(vector_apps, option);
		break;
	case 't':
		//sort_apps_by_type(vector_apps);
		break;
	case 'x':
		//sort_app_by_id();
		print_vector(vector_apps);
		break;
	default:
		cout << "CODI INESISTENT" << endl;
		break;
	}
}
//aded a come
////////////////////////////////////////-------------MAIN-------------//////////////////////////////////////////////////////////////////////////////////
int main()
{
	//added aome changes
	Vector_apps vector_apps;
	vector_apps.curren_size = 0;
	cout << "enter the name of the file" << endl;
	string name_file;
	cin >> name_file;
	ifstream in_file(name_file.c_str());
	if (in_file.is_open()) {
		read_file(in_file, vector_apps);
		print_vector(vector_apps);
		cout << "enter id elemrnts to delete" << endl;
		App app;
		app.Id_app = 1300;
		unsigned pos = 0;
		bool hi_es = false;
		search_element(vector_apps, app, hi_es, pos);
		if (hi_es) {
			cout << "hi_es: " << pos << endl;
		}
		else {
			cout << "no_hi es: " << pos << endl;
		}
		char option;
		showMenu(option);
		while (option != 'e') {
			compute_option(option, vector_apps);
			print_vector(vector_apps);
			showMenu(option);
		}
		print_vector(vector_apps);
	}
	else {
		cout << "somthing when opening the file" << endl;
	}
	return 0;
}
