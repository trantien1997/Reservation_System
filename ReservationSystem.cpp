#include "ReservationSystem.hpp"

int main()
{
	fout.open("PersonalInformation.txt", std::ios_base::app);

	Start();

	fout.close();
	return 0;
}

void Start()
{
	while(true)
	{
		PersonalInf passenger;
		printMainMenu();
		menuInput = cin.get();
		cin.ignore();
		menuInput = make_lowercaseCh(menuInput);
		switch((int)menuInput)
		{
			case TypeInfor:
				Getdetail(passenger);
				break;
			case Search:
				SearchReservation();
				break;
			case Modify:
				ModifyReservation();
				break;
			case Cancel:
				CancelReservation();
				break;
			case Exit:
				cout << "Thanks for stopping by!";
				exit(0);
				break;
			default:
				cout << "Unknown" << endl;
				break;
		}
	}
}

void printMainMenu()
{
	cout << "\t\t\tWelcome to Daewoo Bus Ticket Reservation System!" << endl;
	cout << "I -> Type your information" << endl;
	cout << "C -> Cancel a particular reservation" << endl;
	cout << "M -> Modify the already made reservation" << endl;
	cout << "F -> Search reservation information of a particular passenger" << endl;
	cout << "Q -> Quit" << endl;
	cout << "Please enter your choice: ";
}

void Getdetail(PersonalInf passenger)
{
	cout << "Enter the details as follows:" << endl;
	cout << "Please enter your name: ";
	getline(cin, passenger.name);
	cout << "Please enter your Departure City: ";
	getline(cin, passenger.deparCity);
	cout << "Please enter your Destination City: ";
	getline(cin, passenger.desCity);
	cout << "Please enter your date of travel (dd/mm/yyyy):" << endl;
	passenger.date = TypeDate();
	cout << "Please enter your time of travel:" << endl;
	passenger.time = TypeTime();
	cout << "Please enter number of tickets: ";
	cin >> passenger.noTicket;
	cin.ignore();
	SaveInfor(passenger);
}

string TypeDate()
{
	int dd, mm, yyyy;
	string result = "";
	cout << "Day: ";
	cin >> dd;
	cout << "Month: ";
	cin >> mm;
	cout << "Year: ";
	cin >> yyyy;
	cin.ignore();

	while(!CheckValidDate(dd, mm, yyyy))
	{
		cout << "Invalid date!" << endl;
		cout << "Please re-enter!" << endl;
		cout << "Day: ";
		cin >> dd;
		cout << "Month: ";
		cin >> mm;
		cout << "Year: ";
		cin >> yyyy;
	}

	// format: dd/mm/yyyy
	if(dd < 10)
	{
		result = result + "0" + to_string(dd) + "/";
	}
	else
	{
		result = result + to_string(dd) + "/";
	}

	if(mm < 10)
	{
		result = result + "0" + to_string(mm) + "/";
	}
	else
	{
		result = result + to_string(mm) + "/";
	}

	result = result + to_string(yyyy);

	return result;
}

bool IsLeepYear(int year)
{
    if (year % 400 == 0)
        return true;

    if (year % 4 == 0 && year % 100 != 0)
        return true;

    return false;
}

bool CheckValidDate(int dd, int mm, int yyyy)
{
	// Check year is valid or not
	if(yyyy < 0)
		return false;

	// Check month is valid or not
	if(mm < 0 || mm > 12)
		return false;

	// Check day is valid or not
	switch(mm)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			if(dd > 0 && dd <= 31)
				return true;
			else
				return false;
			break;
		case 4: case 6: case 9: case 11:
			if(dd > 0 && dd <= 30)
				return true;
			else
				return false;
			break;
		case 2:
			if(IsLeepYear(yyyy))
			{
				if(dd > 0 && dd <= 29)
					return true;
				else
					return false;
			}
			else
			{
				if(dd > 0 && dd <= 28)
					return true;
				else
					return false;
			}
			break;
		default:
			return false;
	}
}

string TypeTime()
{
	int hh, mm;
	string result = "";
	cout << "Hour: ";
	cin >> hh;
	cout << "Minute: ";
	cin >> mm;
	cin.ignore();

	while(!CheckValidTime(hh, mm))
	{
		cout << "Invalid time!" << endl;
		cout << "Please re-enter!" << endl;
		cout << "Hour: ";
		cin >> hh;
		cout << "Minute: ";
		cin >> mm;
	}

	// format: hh:mm
	if(hh < 10)
	{
		result = result + "0" + to_string(hh) + ":";
	}
	else
	{
		result = result + to_string(hh) + ":";
	}

	if(mm < 10)
	{
		result = result + "0" + to_string(mm);
	}
	else
	{
		result = result + to_string(mm);
	}

	return result;
}

bool CheckValidTime(int hh, int mm)
{
	if(hh < 0 || hh > 24 || mm < 0 || mm > 60)
		return false;
	return true;
}

void SaveInfor(PersonalInf passenger)
{
	ostringstream convert1;
	vector<string> arrTickets;
	string date;
	string time;

	while(fout)
	{
		arrTickets = MakeReservation(passenger.noTicket);

		if(arrTickets.size() == 0)
		{
			cout << "Seats are not available at the moment." << endl;
			return;
		}

		fout << "Name of passenger: " << passenger.name << endl;
		fout << "Departure City: " << passenger.deparCity << endl;
		fout << "Destination City: " << passenger.desCity << endl;
		fout << "Date of travel: " << passenger.date << endl;
		fout << "Time of travel: " << passenger.time << endl;

		convert1 << passenger.noTicket;
		fout << "Number of tickets: " << convert1.str() << endl;

		fout << "Seat number: ";
		for(int i = 0; i < (int)arrTickets.size(); i++)
		{
			fout << arrTickets[i] << " ";
		}
		fout << "\n" <<endl;
		break;
	}

	cout << "Successfully added in database." << endl;

	return;
}

vector<string> MakeReservation(int numSeat)
{
	vector<string> arrTickets;
	vector<string> result;

	// Get information about number of seats
	arrTickets = ReturnListSeat();

	if((int)arrTickets.size() == 0 || (int)arrTickets.size() < numSeat)
	{
		return result;
	}

	for(int i = 0; i < numSeat; i++)
	{
		int count = 0;

		while(count < 32)
		{
			if(arrTickets[count] != "XX")
			{
				result.push_back(arrTickets[count]);
				arrTickets[count] = "XX";
				break;
			}
			count ++;
		}
	}

	// Update the location already book in Seat.txt
	ofstream fileSeat;
	fileSeat.open("Seat.txt");

	while(fileSeat)
	{
		fileSeat << "********  Available Seat  ********" << endl;
		fileSeat << "  (XX is already booked!!)" << endl;
		fileSeat << endl;
		fileSeat << "  |Entry|          |Driver|" << endl;
		for(int i = 3; i < (int)arrTickets.size(); i += 4)
		{
			fileSeat << "|" << arrTickets[i - 3] << "|" << "  " << "|" << arrTickets[i - 2] << "|" << "       " <<  "|" << arrTickets[i - 1] << "|" << "  " << "|" << arrTickets[i] << "|" << endl;
		}
		break;
	}

	fileSeat.close();

	return result;
}

vector<string> ReturnListSeat()
{
	ifstream SeatAvailbility;
	string line;
	vector<string> result;

	SeatAvailbility.open("Seat.txt");

	// Skip the first 4 lines
	for(int i = 0; i < 4; i++)
	{
		getline(SeatAvailbility, line);
	}

	while(SeatAvailbility)
	{
		vector<string> temp;
		getline(SeatAvailbility, line);
		temp = Split(line, "|");

		for(int i = 0; i < (int)temp.size(); i++)
			result.push_back(temp[i]);
	}

	SeatAvailbility.close();

	return result;
}

vector<string> Split(string str, string delimiter)
{
	vector<string> temp;
	vector<string> result;

	while (!str.empty())
	{
		temp.push_back(str.substr(0, str.find(delimiter)));// add word to vector

		if (str.find(delimiter) > str.size()) //Check if found " " (Space)
		{
			break;
		}
		else
		{
			str.erase(0, str.find(delimiter) + 1); // Update string
		}
	}

	for(int i = 0; i < (int)temp.size(); i++)
	{
		if(temp[i] != "" && temp[i].find(" ") == string::npos)
			result.push_back(temp[i]);
	}

	return result;
}
void ModifyReservation()
{
	string name;
	string line;
	string changeDate;
	string changeTime;
	string changeNoTickets;
	int numOfASeat = 0;
	// temp variable is used to save the number of ticket previous
	int temp1;
	vector<string> arrTickets;
	bool flag = true;
	vector<vector<string>> allResult;
	vector<string> temp;
	int indexModify;
	PersonalInf updateInfor;

	cout << "Please enter your name: ";
	getline(cin, name);

	// Get information about number of available seats
	arrTickets = ReturnListSeat();
	for(int i = 0; i < (int)arrTickets.size(); i++)
	{
		if(arrTickets[i] != "XX")
			numOfASeat += 1;
	}

	// Open file and get data
	fin.open("PersonalInformation.txt");

	while(fin)
	{
		getline(fin, line);
		if(line != "")
			temp.push_back(line);
		else
		{
			if(temp.size())
			{
				allResult.push_back(temp);
				temp.clear();
			}
		}
	}

	fin.close();

	// Find index need to modify
	for(int i = 0; i < (int)allResult.size(); i++)
	{
		for(int j = 0; j < (int)allResult[i].size(); j++)
		{
			if(allResult[i][j].find("Name of passenger: ") != string::npos)
			{
				if(CompareString(allResult[i][j], name))
				{
					indexModify = i;
					flag = false;
				}
			}
		}
	}

	if(flag)
	{
		cout << "Your name Not Found in database!" << endl;
		return;
	}

	//Enter your information you need update
	cout << "Enter your name. (X to not change): ";
	getline(cin, updateInfor.name);
	if (make_lowercaseSt(updateInfor.name) == "x")
	{
		updateInfor.name = allResult[indexModify][0];
	}
	else
	{
		allResult[indexModify][0] = "Name of passenger: " + updateInfor.name;
	}
	cout << "Enter your departure city (X to not change): ";
	getline(cin, updateInfor.deparCity);
	if (make_lowercaseSt(updateInfor.deparCity) == "x")
	{
		updateInfor.deparCity = allResult[indexModify][1];
	}
	else
	{
		allResult[indexModify][1] = "Departure City: " + updateInfor.deparCity;
	}
	cout << "Enter your destination city (X to not change): ";
	getline(cin, updateInfor.desCity);
	if (make_lowercaseSt(updateInfor.desCity) == "x")
	{
		updateInfor.desCity = allResult[indexModify][2];
	}
	else
	{
		allResult[indexModify][2] = "Destination City: " + updateInfor.desCity;
	}
	cout << "Do you want to change the date of travel. (N to not change or Y to change): ";
	getline(cin, changeDate);
	if (make_lowercaseSt(changeDate) == "n")
	{
		updateInfor.date = allResult[indexModify][3];
	}
	else if(make_lowercaseSt(changeDate) == "y")
	{
		updateInfor.date = TypeDate();
		allResult[indexModify][3] = "Date of travel: " + updateInfor.date;
	}
	cout << "Do you want to change the time of travel?. (N to not change or Y to change): ";
	getline(cin, changeTime);
	if (make_lowercaseSt(changeTime) == "n")
	{
		updateInfor.time = allResult[indexModify][4];
	}
	else if(make_lowercaseSt(changeTime) == "y")
	{
		updateInfor.time = TypeTime();
		allResult[indexModify][4] = "Time of travel: " + updateInfor.time;
	}
	cout << "Do you want to change the number of tickets?. (N to not change or Y to change): ";
	getline(cin, changeNoTickets);
	if (make_lowercaseSt(changeNoTickets) == "n")
	{
		updateInfor.noTicket = atoi (allResult[indexModify][5].c_str());
	}
	else if(make_lowercaseSt(changeNoTickets) == "y")
	{
		cout << "Please enter your number of tickets need change: " << endl;
		cin >> updateInfor.noTicket;
		allResult[indexModify][5] = allResult[indexModify][5].substr(allResult[indexModify][5].find(": ") + 1, allResult[indexModify][5].length());
		temp1 = atoi (allResult[indexModify][5].c_str());
		// Bool more tickets
		if(updateInfor.noTicket > temp1)
		{
			if(atoi (allResult[indexModify][5].c_str()) + numOfASeat >=  updateInfor.noTicket)
			{
				vector<string> seatUpdate;
				allResult[indexModify][5] = "Number of tickets: " + to_string(updateInfor.noTicket);


				if(updateInfor.noTicket > temp1)
				{
					seatUpdate = MakeReservation(updateInfor.noTicket - temp1);
					for(int i = 0; i < (int)seatUpdate.size(); i++)
					{
						allResult[indexModify][6] = allResult[indexModify][6] + seatUpdate[i] + " ";
					}
				}
			}
			else
			{
				cout << "The number of tickets you booked exceeds the number of seats available!" << endl;
				updateInfor.noTicket = atoi (allResult[indexModify][5].c_str());
			}
		}
		else
		{
			vector<string> Ticket;
			vector<string> cancelTickets;
			allResult[indexModify][5] = "Number of tickets: " + to_string(updateInfor.noTicket);
			allResult[indexModify][6] = allResult[indexModify][6].substr(allResult[indexModify][6].find(": ") + 1, allResult[indexModify][6].length());
			Ticket = Split(allResult[indexModify][6], " ");
			allResult[indexModify][6] = "Seat number: ";
			for(int i = 0; i < updateInfor.noTicket; i++)
			{
				allResult[indexModify][6] += Ticket[i] + " ";
			}

			for(int i = updateInfor.noTicket; i < temp1; i++)
			{
				cancelTickets.push_back(Ticket[i]);
			}

			RecoverSeat(cancelTickets);
		}
	}

	fout.close();

	fout.open("PersonalInformation.txt");

	while(fout)
	{
		for(int i = 0; i < (int)allResult.size(); i++)
		{
			for(int j = 0; j < (int)allResult[i].size(); j++)
			{
				if(allResult[i][j] != "")
					fout << allResult[i][j] << endl;
			}
			fout<< endl;
		}
		break;
	}
}

void CancelReservation()
{
	string name;
	string line;
	vector<vector<string>> allResult;
	vector<string> temp;
	vector<string> cancelTickets;

	cout << "Please enter the name you want to cancel!";
	getline(cin, name);

	fin.open("PersonalInformation.txt");

	while(fin)
	{
		getline(fin, line);
		if(line != "")
			temp.push_back(line);
		else
		{
			if(temp.size())
			{
				allResult.push_back(temp);
				temp.clear();
			}
		}
	}

	for(int i = 0; i < (int)allResult.size(); i++)
	{
		for(int j = 0; j < (int)allResult[i].size(); j++)
		{
			if(allResult[i][j].find("Name of passenger: ") != string::npos)
			{
				if(CompareString(allResult[i][j], name))
				{
					allResult[i][6] = allResult[i][6].substr(allResult[i][6].find(": ") + 1, allResult[i][6].length());
					cancelTickets = Split(allResult[i][6], " ");
					allResult[i].clear();
				}
			}
		}
	}

	fin.close();

	fout.close();

	fout.open("PersonalInformation.txt");

	while(fout)
	{
		for(int i = 0; i < (int)allResult.size(); i++)
		{
			for(int j = 0; j < (int)allResult[i].size(); j++)
			{
				if(allResult[i][j] != "")
					fout << allResult[i][j] << endl;
			}
			fout<< endl;
		}
		break;
	}

	RecoverSeat(cancelTickets);
}

void RecoverSeat(vector<string> seat)
{
	ofstream fileSeat;
	vector<string> arrTickets;
	// return index of seat in arrTickets array
	vector<int> index;

	// Save postion seat in arrTickets array
	arrTickets = ReturnListSeat();


	for(int i = 0; i < (int)seat.size(); i++)
	{
		for(int j = 0; j < MAX; j++)
		{
			if(seat[i] == arrSeat[j])
				index.push_back(j);
		}
	}

	// update arrTickets with recovered seat
	for(int i = 0; i < (int)index.size(); i++)
	{
		arrTickets[index[i]] = seat[i];
	}

	// open Seat.txt to update canceled position seats
	ofstream fSeat;
	fSeat.open("Seat.txt");

	while(fSeat)
	{
		fSeat << "********  Available Seat  ********" << endl;
		fSeat << "  (XX is already booked!!)" << endl;
		fSeat << endl;
		fSeat << "  |Entry|          |Driver|" << endl;
		for(int i = 3; i < (int)arrTickets.size(); i += 4)
		{
			fSeat << "|" << arrTickets[i - 3] << "|" << "  " << "|" << arrTickets[i - 2] << "|" << "       " <<  "|" << arrTickets[i - 1] << "|" << "  " << "|" << arrTickets[i] << "|" << endl;
		}
		break;
	}

	fSeat.close();
}

void SearchReservation()
{
	cout << "N -> Search by passenger name" << endl;
	cout << "D -> Search by Date of travel" << endl;
	cout << "Q -> Quit" << endl;
	cout << "Please enter your choice: ";
	menuInput = cin.get();
	cin.ignore();
	menuInput = make_lowercaseCh(menuInput);
	switch((int)menuInput)
	{
		case SearchName:
			SearchInfo(menuInput);
			break;
		case SearchDate:
			SearchInfo(menuInput);
			break;
		case Exit:
			cout << "Thanks for stopping by!";
			exit(0);
			break;
		default:
			cout << "Unknown" << endl;
			break;
	}
}

void SearchInfo(char mode)
{
	string line;
	string searchKey;
	string searchStr;
	vector<vector<string>> allResult;
	vector<string> temp;

	cout << "Please enter the key you are looking for:";
	getline(cin, searchKey);

	fin.open("PersonalInformation.txt");

	if((int)mode == 110)
		searchStr = "Name of passenger: ";
	else if((int)mode == 100)
		searchStr = "Date of travel: ";

	while(fin)
	{
		getline(fin, line);

		if((int)mode == 100)
			if(line != "")
				temp.push_back(line);

		if(line.find(searchStr) != string::npos)
		{
			if((int)mode == 100)
			{
				string delimiter = ": ";
				string lineSplited = line.substr(line.find(delimiter) + 2, line.length());
				if(SplitAndCompare(lineSplited, searchKey))
				{
					GetInfor(temp);
					allResult.push_back(temp);
					temp.clear();
				}
				else
					temp.clear();
			}
			else if((int) mode == 110)
			{
				if(CompareString(line, searchKey))
				{
					temp.push_back(line);
					GetInfor(temp);
					allResult.push_back(temp);
					temp.clear();
				}
			}
			else
			{
				// Do something
			}
		}
		else if(line == "")
			temp.clear();
	}

	if(allResult.size())
	{
		for(int i = 0; i < (int)allResult.size(); i++)
		{
			for(int j = 0; j < (int)allResult[i].size(); j++)
			{
				cout << allResult[i][j] << endl;
			}
			cout<<endl;
		}
	}
	else
	{
		cout << "Can not find!" << endl;
	}

	fin.close();
}

bool CompareString(string str1, string str2)
{
	string delimiter = ": ";
	string strCompare = str1.substr(str1.find(delimiter) + 2, str1.length());
	if(make_lowercaseSt(strCompare) == make_lowercaseSt(str2))
		return true;
	else if(make_lowercaseSt(strCompare).find(make_lowercaseSt(str2))!= string::npos)
		return true;
	else
		return false;
}

bool SplitAndCompare(string str1, string str2)
{
	vector<int> arr1 = SplitString(str1);
	vector<int> arr2 = SplitString(str2);

	for(int i = 0; i < (int)arr1.size(); i++)
	{
		if(arr1[i] != arr2[i])
			return false;
	}

	return true;
}

bool IsNumeric(char in)
{
	for(int i = 48; i <= 57; i++)
	{
		if(in == i)
			return true;
	}
	return false;
}

vector<int> SplitString(string str)
{
	vector<int> result;
	string Str = "";
	vector<string> arrStr;

	for(int i = 0; i < (int)str.length(); i++)
	{
		if(IsNumeric(str[i]))
			Str += str[i];
		else
		{
			if(Str.length())
			{
				arrStr.push_back(Str);
				Str = "";
			}
		}
	}

	arrStr.push_back(Str);

 	for(int i = 0; i < (int)arrStr.size(); i++)
 		result.push_back(atoi(arrStr[i].c_str()));

 	return result;
}

void GetInfor(vector<string> &strName)
{
	string info;
	while(fin)
	{
		getline(fin, info);
		if(info != "")
			strName.push_back(info);
		else
			break;
	}
}

char make_lowercaseCh(char in)
{
    if(in >= 65 && in <= 90)
       in = in + 32;
    return in;
}

string make_lowercaseSt(string in)
{
	string out;
	transform(in.begin(), in.end(), back_inserter(out), ::tolower);
    return out;
}

/*void ResetSeatFile()
{
	ofstream seatFile;
	seatFile.open("Seat.txt");

	while(seatFile)
	{
		seatFile << "********  Available Seat  ********" << endl;
		seatFile << "  (XX is already booked!!)" << endl;
		seatFile << endl;
		seatFile << "  |Entry|          |Driver|" << endl;
		seatFile << "|A1|  |A2|       |A3|  |A4|" << endl;
		seatFile << "|B1|  |B2|       |B3|  |B4|" << endl;
		seatFile << "|C1|  |C2|       |C3|  |C4|" << endl;
		seatFile << "|D1|  |D2|       |D3|  |D4|" << endl;
		seatFile << "|E1|  |E2|       |E3|  |E4|" << endl;
		seatFile << "|F1|  |F2|       |F3|  |F4|" << endl;
		seatFile << "|G1|  |G2|       |G3|  |G3|" << endl;
		seatFile << "|H1|  |H2|       |H3|  |H4|" << endl;
		break;
	}

	seatFile.close();
}*/
