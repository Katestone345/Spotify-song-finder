//1000songs.cpp
//Author: Katlynn Stone


#include <shlwapi.h>
#include <iostream>
#include <fstream>
#include <cstring>

#include <algorithm>
#include <ctime>

using namespace std;
enum COLUMNINDEX { THEME, TITLE, ARTIST, YEAR, SPOTIFYURL };
enum COLUMNINDEX GetColumnIndex(string ColumnSearch);
void ExtractValues(string line, string delimiter, string &Theme, string &Title, string &Artist, string &Year, string &URL);
void GetColumnValue(COLUMNINDEX Column, string ColumnValue, int DisplayIndex);
string GetSpotifyURL();
void LaunchSpotify();

int main() {
	string ColumnSearch;
	string ColumnValue;
	int DisplayIndex;
	COLUMNINDEX Column;
	char userAccessKey;
	ifstream inFile;
	string Matched;
	//Attempt to open file
	inFile.open("1000songs.csv");
	if (inFile.fail())
	{
		cout << "Error loading files";
		return 1;
	}
	cout << "Welcome please press any key besides 'x' to start" << endl;
	cin >> userAccessKey;
	//While loop that will continue until user enters X
	while (userAccessKey != 'X' && userAccessKey != 'x') {
		cout << "Please enter the column to search (Theme, Title, Artist, or Year): ";
		cin >> ColumnSearch;
		transform(ColumnSearch.begin(), ColumnSearch.end(), ColumnSearch.begin(), ::toupper);
		cout << "Please enter the value in the '" << ColumnSearch << "' column to locate: ";
		cin >> ColumnValue;
		transform(ColumnValue.begin(), ColumnValue.end(), ColumnValue.begin(), ::toupper);
		cout << "Please enter the maximum number of records to display per page (1 to 100): " << endl;
		cin >> DisplayIndex;
		cout << endl;
		cout << "...Searching column " << ColumnSearch << " for the item '" << ColumnValue << "'." << endl;
		Column = GetColumnIndex(ColumnSearch);
		if (Column == THEME) {
			GetColumnValue(Column, ColumnValue, DisplayIndex);
			cout << endl;
		}
		else if (Column == TITLE) {
			GetColumnValue(Column, ColumnValue, DisplayIndex);
			cout << endl;
		}
		else if (Column == ARTIST) {
			GetColumnValue(Column, ColumnValue, DisplayIndex);
			cout << endl;
		}
		else if (Column == YEAR) {
			GetColumnValue(Column, ColumnValue, DisplayIndex);
			cout << endl;
		}
		else {
			cout << "Invalid choice" << endl;
			exit(0);
		}
		cout << "Press any key to continue searching or 'x' to stop..." << endl;
		cin >> userAccessKey;
		toupper(userAccessKey);

	}
	return 0;
}

enum COLUMNINDEX GetColumnIndex(string ColumnSearch)
{
	COLUMNINDEX Column;
	if (ColumnSearch == "THEME") {
		Column = THEME;
	}
	else if (ColumnSearch == "TITLE") {
		Column = TITLE;
	}
	else if (ColumnSearch == "ARTIST") {
		Column = ARTIST;
	}
	else if (ColumnSearch == "YEAR") {
		Column = YEAR;
	}
	else {
		cout << "Invalid choice" << endl;
		exit(0);
	}
	return Column;
}


void ExtractValues(string line, string delimiter, string &Theme, string &Title, string &Artist, string &Year, string &URL)
{

	long idx1 = 0, idx2 = line.find(delimiter);

	Theme = line.substr(idx1, idx2 - idx1);

	idx1 = idx2 + delimiter.length();
	idx2 = line.find(delimiter, idx1);
	Title = line.substr(idx1, idx2 - idx1);

	idx1 = idx2 + delimiter.length();
	idx2 = line.find(delimiter, idx1);
	Artist = line.substr(idx1, idx2 - idx1);

	idx1 = idx2 + delimiter.length();
	idx2 = line.find(delimiter, idx1);
	Year = line.substr(idx1, idx2 - idx1);

	idx1 = idx2 + delimiter.length();
	URL = line.substr(idx1);
}


void GetColumnValue(COLUMNINDEX Column, string ColumnValue, int DisplayIndex) {

	ifstream inFile;
	string Theme, Title, Artist, Year, URL;

	string iTheme[100], iTitle[100], iArtist[100], iYear[100];
	int i = 0;
	int unMatched = 0;
	int Matched = 0;
	inFile.open("1000songs.csv");
	if (inFile.fail())
	{
		cout << "Error loading files";
		exit(0);
	}

	string line;
	bool match;
	while (true) {
		getline(inFile, line);
		if (inFile.eof())
			break;

		transform(line.begin(), line.end(), line.begin(), ::toupper);

		ExtractValues(line, ",", Theme, Title, Artist, Year, URL);
		match = false;
		if (Column == THEME && Theme == ColumnValue)
			match = true;
		else if (Column == TITLE && Title == ColumnValue)
			match = true;
		else if (Column == ARTIST && Artist == ColumnValue)
			match = true;
		else if (Column == YEAR && Year == ColumnValue)
			match = true;

		if (match)
		{
			//cout << line << endl;
			Matched = Matched + 1;
			if (i < DisplayIndex)
			{
				iTheme[i] = Theme;
				iTitle[i] = Title;
				iArtist[i] = Artist;
				iYear[i] = Year;
				i = i + 1;
			}
		}
		else {
			unMatched = unMatched + 1;

		}
	}
	inFile.close();

	for (i = 0; i < Matched && i < DisplayIndex; i++) {
		cout << "Rec No. " << (i + 1) << endl;
		cout << "Title: " << iTitle[i] << endl;
		cout << "Artist: " << iArtist[i] << endl;
		cout << "Year: " << iYear[i] << endl << endl;
	}
	cout << Matched << " records found." << endl;
}
