#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

						// Main Choice
#define TypeInfor 105
#define Search 102
#define Modify 109
#define Cancel 99
#define Exit 113
#define SearchName 110
#define SearchDate 100
#define ResetSeat  114
					// Maximum number of tickets
#define MAX 32

typedef struct
{
	string name;
	string deparCity;
	string desCity;
	string date;
	string time;
	int noTicket;
} PersonalInf;

ofstream fout;

ifstream fin;

// arrSeat is used to find index of seat need to cancel
const string arrSeat[32] = {"A1", "A2", "A3", "A4",
		"B1", "B2", "B3", "B4",
		"C1", "C2", "C3", "C4",
		"D1", "D2", "D3", "D4",
		"E1", "E2", "E3", "E4",
		"F1", "F2", "F3", "F4",
		"G1", "G2", "G3", "G4",
		"H1", "H2", "H3", "H4",
};

					// Main function prototypes
void Start();

void printMainMenu();

// Type passenger information
void Getdetail(PersonalInf passenger);

// Save passenger information
void SaveInfor(PersonalInf passenger);

vector<string> MakeReservation(int numSeat);

void ModifyReservation();

void CancelReservation();

void SearchReservation();

void SearchInfo(char mode);

void RecoverSeat(vector<string> seat);

				// Handling function protocol
bool CompareString(string str1, string str2);

bool SplitAndCompare(string str1, string str2);

// Check if the date is valid or not
bool CheckValidDate(int dd, int mm, int yyyy);

bool IsLeepYear(int yyyy);

// check if the time is valid or not
bool CheckValidTime(int hh, int mm);

vector<string> ReturnListSeat();

vector<string> Split(string str, string delimiter);

string TypeDate();

string TypeTime();

bool IsNumeric(char in);

// Split string to get valid day format
vector<int> SplitString(string str);

// Convert Uppercase to Lowercase for char type
char make_lowercaseCh(char in);

// Convert Uppercase to Lowercase for string type
string make_lowercaseSt(string in);

// Get information to Display on Console when using SearchInfo function
void GetInfor(vector<string> &strName);

// global variable (use this variable to store the users menu selection)
char menuInput;
