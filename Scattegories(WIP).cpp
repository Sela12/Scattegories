// A program to keep track of points and time and to give a random letter for the game scattergories
#include<iostream>
#include<ctime>
#include<string>
#include <chrono>
#include <thread>
using std::cout;
using std::cin;
using std::string;
using std::getline;
using namespace std::chrono_literals;
using std::this_thread::sleep_for;

void ltr()    //gives a random letter
{
	srand(time(NULL));    //gives a differant pattern every time
	char letter;
	letter = rand() % 26 + 65;         //assigns a random letter in ascii code to a char (resulting in a random letter)
	cout << "The letter is " << letter << "\n";
}

void timer()
{
	cout << "You got 1.5 minutes to finish\n";    //Changing the duration of the timer is done by changing the value of 'i' in the "for" loop
	for (int i = 90; i > 0; i--)
	{
		if (i % 5 == 0)
			cout << i << "\n";
		sleep_for(1s);
	}
	cout << "DING DONG!!! DING DONG!!! Time's up!!!\n";
}

void table()
{
	int plr, ctr;
	string lst[5][20];           //first dimantion: how many players. second dimantion: how many catagories, third dimantion(if added) will be the round
	cout << "How many players?";
	cin >> plr;
	cout << "How many catagories?";
	cin >> ctr;       //parameters for later
	cin.ignore();                  //To avoid the "getline" reading the last input
	for (int x = 0; x<plr; x++)       //the player changes only after the previus player finishes
	{
		cout << "Player number " << x+1<<":";
		timer();       //gives time to write the words. Optimaly it would run in the background while each player writes the words.
		for (int i = 0; i<ctr; i++)        //changing catagory
		{
			getline(cin, lst[x][i]);
		}
		system("cls");
		cout << "Next player\n";
	}
	for (int x = 0; x<plr; x++)                   //this part (the whole "for" loop) is for confirming evreything is writen down
	{
		cout << "Player number " << x + 1 << ": ";
		for (int i = 0; i<ctr; i++)
		{
			cout << lst[x][i] << "    ";
		}
		cout << "\n";
	}
	sleep_for(5s);
}

int points()        //points gained per round
{
	int a, b, c, sum;
	cout << "How many sections only you got?\n";          //worth 15 points
	cin >> a;
	cout << "How many words only you got?\n";       //worth 10 points
	cin >> b;
	cout << "How many words you and another person got?\n";    //worth 5 points
	cin >> c;
	sum = a * 15 + b * 10 + c * 5;
	return sum;           //Note: It doesn't matter how many sections there are.
}

int act()    //running the program
{
	int Points;
	ltr();
	table();
	Points = points();
	cout << "You have earned " << Points << " this round\n\n";
	return Points;
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	int Points;
	cout << "Starting in five seconds\n";
	sleep_for(5s);
	Points = act();
	for (;;)          //inf loop
	{
		int ph;
		cout << "Press 1 to continue or anything else to stop\n";
		cin >> ph;
		if (ph == 1)
		{
			Points += act();    //keeping score of the rounds
		}
		else
		{
			auto end = std::chrono::high_resolution_clock::now();
			break;
		}
	}
	cout << "You have earned a total of " << Points << " great job!";
	sleep_for(5s);       //time to read the last text
	return 0;
}

/* 
   To do list:
   -Convert to arduino
   -Make timer work in background of of table
   -Check if words in the table (for differant players) are the same and give points accordingly
   -Check if words are actual words (connect an online dictonary?)
   -Make interface? (if possible and I have time to learn how)
   -Think of what to do with Hardwear
   -Comment rest of the code
   -Make a point count for each player
*/