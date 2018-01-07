// PRACTICAFINAL.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>

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
void print_vector(Vector_apps &vector) {
	//pre:cert
	//post:mostra en la consola els apps guardat en un vector
	for (unsigned i = 0; i < vector.curren_size; i++)
		cout << vector.apps[i].Id_app << "  " << vector.apps[i].name_app << "  " <<
		vector.apps[i].type << "  " << vector.apps[i].downloads << "  " << vector.apps[i].date.day << "  " <<
		vector.apps[i].date.month << "  " << vector.apps[i].date.year << endl;
}

////////////////////////////////////------------SHOW INFO APP  METHODE AND READ APP FROM FILE METHODE----------///////////////////////////////////
App read_app(ifstream& in_file) {
	//pre: cert
	//post: ha llegit una app en el fitxer
	App app;
	in_file >> app.Id_app >> app.name_app >> app.type >> app.date.day >> app.date.month >> app.date.year >> app.downloads;
	return app;
}
void show_info_app(const Vector_apps vector_apps, unsigned pos_element) {
	//pre:cert
	//post:mostra la informacio de l'app
	cout << vector_apps.apps[pos_element].Id_app << "  " << vector_apps.apps[pos_element].name_app << "  " << vector_apps.apps[pos_element].type
		<< "  " << vector_apps.apps[pos_element].downloads << "  " << vector_apps.apps[pos_element].date.day << "  " << vector_apps.apps[pos_element].date.month
		<< "  " << vector_apps.apps[pos_element].date.year << endl;
}
////////////////////////////////////////-------------BINARY SERACH METHODE---------------////////////////////////////////////////////////////////////////
void search_element(Vector_apps& vector, App app, bool& is_there, int & pos_element) {
	//Pre: 0<=v.n<=MAX, v.t[0..v.n-1] ordenat creixentment
	//Post: retorna cert si x �s un dels elements de v.t[0..v.n-1] i la posicio, fals
	//altrament
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
/////////////////////////////////////-------------INSERT METHODE, IN ORDERED ARRAY-----------------////////////////////////////////////////////////////////
void fill_vector_sorting(Vector_apps &vector, App app) {
	//Pre: 0<=v.n<MAX, v.t[0..n-1] ordenat creixentment
	//Post: x inserit ordenadament a v.t
	int i = vector.curren_size;
	while (i > 0 && app.Id_app < vector.apps[i - 1].Id_app) {
		vector.apps[i] = vector.apps[i - 1];
		i--;
	}
	vector.apps[i] = app;
	vector.curren_size++;
}


void es_menor_data(App app_a, App app_b, bool &menor_data, bool &same) {
	//Pre: criteri ='t'
	//Post: retorna cert si app_a.date_a �s menor que app_b.date_b segons el criteri
	menor_data = app_a.date.year < app_b.date.year;
	if (app_a.date.year == app_b.date.year) {
		menor_data = app_a.date.month < app_b.date.month;
		if (app_a.date.month == app_b.date.month) {
			menor_data = app_a.date.day < app_b.date.day;
			if (app_a.date.day == app_b.date.day) {
				same = true;  //equal to true when both date are equal
			}
		}
	}
}
bool es_menor(App app_a, App app_b, char criteri) {
	//Pre: criteri = (�l�, �t�)
	//Post: retorna cert si a �s menor que b segons el criteri
	bool menor = true;
	string message;
	if (criteri == 'l') {
		menor = app_a.downloads > app_b.downloads;
		if (app_a.downloads == app_b.downloads) {
			menor = app_a.name_app < app_b.name_app;
		}
	}
	else {
		// sort by type option == 't'
		bool same = false, menor_data = false;
		es_menor_data(app_a, app_b, menor_data, same);
		menor = menor_data;
		if (same) {
			menor = app_a.name_app < app_b.name_app;
		}
	}
	return menor;
}


void fill_vector_sortiing(App app, Vector_apps &vector, char opcion) {
	//Pre: 0<=v.n<MAX, v.t[0..n-1] ordenat creixentment
	//Post: x inserit ordenadament a v.t

	int i = vector.curren_size;
	while (i > 0 && es_menor(app, vector.apps[i - 1], opcion)) {
		vector.apps[i] = vector.apps[i - 1];
		i--;
	}
	vector.apps[i] = app;
	vector.curren_size++;

}
void sort_apps_by_dowloads(Vector_apps& vector_apps, char option) {
	//Pre: 0<=v.n<=MAX
	//Post: v.t[0..v.n-1] cont� els elements inicials ordenats segons
	//downloads
	Vector_apps sorted_by_downloads;//new vector to store apps sorted by downloads
	sorted_by_downloads.curren_size = 0;
	for (unsigned i = 0; i < vector_apps.curren_size; i++) {
		fill_vector_sortiing(vector_apps.apps[i], sorted_by_downloads, option);// filling the vector 
	}
	print_vector(sorted_by_downloads);
}

void sort_apps_by_type(Vector_apps &vector_apps, char option) {
	//Pre: 0<=v.n<=MAX
	//Post: v.t[0..v.n-1] cont� els elements inicials ordenats segons
	//del tipu especificat per l'usuari
	Vector_apps new_vector;
	new_vector.curren_size = 0;
	string type;
	cin >> type;
	for (unsigned i = 0; i < vector_apps.curren_size; i++) {
		if (vector_apps.apps[i].type == type) {
			fill_vector_sortiing(vector_apps.apps[i], new_vector, option);// filling the new vector 
		}
	}
	print_vector(new_vector);
}
////////////////////////////////////////-----------METHODE THAT READ THE FILE---------------///////////////////////////////////////////////////
void read_file(ifstream &in_file, Vector_apps &vector_apps) {
	//pre:cert
	//post: 0<=vector_apps.n<=CAPACITY,vector_apps.n[0..t.n-1] ordenats per codi,conte els vectors_apps.n apps existents en el fitxer
	App app;
	app = read_app(in_file);
	while (!in_file.eof()) {
		fill_vector_sorting(vector_apps, app);
		app = read_app(in_file);
	}
}

////////////////////////////////////-----------REGISTER AN APP-------------//////////////////////////////////////////////////////////////////

void incert_element(Vector_apps &vector, App app, int pos) {
	//Pre: 0<=v.n<MAX, v.t[0..n-1] ordenat creixentment
	//Post: x inserit ordenadament a v.t
	//pre:
	//post:
	for (int i = vector.curren_size; i > pos; i--) {
		vector.apps[i] = vector.apps[i - 1];
	}
	vector.apps[pos] = app;
	vector.curren_size++;
}

void register_app(Vector_apps& vector_apps) {
	//pre:cert
	//post:Ha incerit dintre del vector l'info de l'app en cas cas existeixi
	App app;
	bool is_there = false;
	int pos_insersion;
	cin >> app.Id_app >> app.name_app >> app.type >> app.date.day >> app.date.month >> app.date.year >> app.downloads;
	search_element(vector_apps, app, is_there, pos_insersion);
	if (is_there) cout << "CODI EXISTENT" << endl;
	else incert_element(vector_apps, app, pos_insersion);
}

//////////////////////////////////---------QUERRY INFO VECTOR--------///////////////////////////////////////////////////////////////

void querry_info_app(Vector_apps &vector_apps) {
	//pre:cert
	//post:mostra l'info d'una aplicacio
	App app;
	cin >> app.Id_app;
	bool is_there = false;
	int pos_app = 0;
	search_element(vector_apps, app, is_there, pos_app);
	if (is_there) show_info_app(vector_apps, pos_app);
	else cout << "CODI INEXISTENT" << endl;

}
////////////////////////////////////////////--------------UPDATE AND DELETE METHODE-------------///////////////////////////////////////////////////

void delete_app_vector(Vector_apps &vector_app, App app, int pos_element) {
	//Pre: 0<=pos<v.n<MAX
	//Post: v.t[pos_elemrnt] eliminat de v.t mantenint l�ordre dels altres
	//elements
	for (unsigned i = pos_element; i <= vector_app.curren_size - 2; i++)
		vector_app.apps[i] = vector_app.apps[i + 1];
	vector_app.curren_size--;
}

void modifier_vector(Vector_apps &vector_apps, char option) {
	//Pre: opption= (�d�, �b�)
	//Post:actualizat les descargas de un especific app si l'opcio='d' altrament si l'opcio='b' elimina	una app 
	App app;
	bool is_there = false;
	int pos_element = 0, n_downloads;
	cin >> app.Id_app;
	search_element(vector_apps, app, is_there, pos_element);
	if (option == 'd' && is_there) {
		cin >> n_downloads;//ask user to enter the number of the new dowloads
		vector_apps.apps[pos_element].downloads += n_downloads; //update downloads
		//show_info_app(vector_apps, pos_element);
	}
	else if (option == 'b' && is_there) delete_app_vector(vector_apps, app, pos_element);//delete an app
	else {
		if (!is_there)cout << "CODI INEXISTENT " << endl;
		else cout << "CODI EXISTENT " << endl;
	}
}
///////////////////////////////////////////////////////------------MANAGER METHODS---------//////////////////////////////////////////////////////////
void compute_option(char option, Vector_apps& vector_apps) {
	//Pre: criteri = (�l�, �a�,�b�, �c�,�d�, �t�)
	//Post:executa el methode coresponent segon l'opcil elegit per l'usuari
	option = tolower(option);
	//choose methode to execute the operation choosen
	switch (option)
	{
	case 'l':
		// this methode the sorting by downloads 
		sort_apps_by_dowloads(vector_apps, option);
		break;
	case 'a':
		// this methode register an app to the array
		register_app(vector_apps);
		break;
	case 'b':
		// this methode modify the vector by updating the downloads to an specific app
		modifier_vector(vector_apps, option);
		break;
	case 'c':
		// retrive info to an especific app
		querry_info_app(vector_apps);
		break;
	case 'd':
		//this methode modify the array by deleting an element to the array
		modifier_vector(vector_apps, option);
		break;
	case 't':
		//this methode sort the apps by date and only showing a type chosent by the user
		sort_apps_by_type(vector_apps, option);
		break;
	case 'x':
		//this methode sort the apps by date and only showing a type chosent by the user
		print_vector(vector_apps);
		break;
	default:
		cout << "INEXISTENT" << endl;
		break;
	}
}
////////////////////////////////////////-------------MAIN-------------//////////////////////////////////////////////////////////////////////////////////
int main()
{
	// MAIN METHODE
	Vector_apps vector_apps;
	vector_apps.curren_size = 0;
	//enter the name of the file
	cout << "INTRODUEIX NOM FITXER: " << endl;
	string name_file;
	cin >> name_file;
	//create a reference(object) of type ifstream
	ifstream in_file(name_file.c_str());
	if (in_file.is_open()) {
		read_file(in_file, vector_apps);
		print_vector(vector_apps);
	}
	else {
		cout << "FITXER NO DISPONIBLE" << endl;
	}
	return 0;
}
