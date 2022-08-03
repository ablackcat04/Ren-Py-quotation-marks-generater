////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//C++ Init
#include <iostream>
#include <string>
#include <fstream>

using namespace::std;

int main()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Program Init

	int max_lines = 100000 + 2; 	//change the number to what you want(but it may crash if you set it too high)

	int script_amount = 0;				//how many lines you acullay have

	int max_characters = 1000 + 2; //change the number to how many you want(but it may crash if you set it too high)

	int character_amount = max_characters;		//how many character you acullay have

	string script[max_lines];		//set the maximum lines of rhe scripts(But it doesn't really matter because at most time you'll need to end your script with the end_phrase "E_N_D" at default)

	string script_name[max_lines];	//the place to keep the names(in order to move it outside of the brackets)

	string character_list[max_characters];		//the place to store character's name


	string bracket_type = "\"";		//change \" to whatever bracket you want, make sure you know how escape character(\) works

	string end_phrase = "E_N_D";	//the phrase to stop the program from recieving character names or scripts

	string character_suffix = ": ";
	/*
		The suffix of the chracter's name, it should appears right after the character's name,
		an example looks like this:
			ABlackCat: Hello world!

		Then the program will generate this:
			ABlackCat "Hello world!"

		After that, you can copy it and paste it in your script.rpy
	*/


	int index;		//the varible to know if there're names we want

	string temp;	//


	string script_file_name = "Unprogressed script.txt";							//the name of the unprogressed script file

	string progressed_script_file_name = "Progressed script.txt";	//the name of the progressed script file

	string character_list_file_name = "Character list.txt";			//the name of the character list file


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Title and Guidance

	cout << "===============================\n  The Renpy Bracket Generator\n===============================\n" << endl;

	//cout << "Copy your visual novel script and paste it into the terminal and press enter" << endl;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Input and Show Character Name

	ifstream file;

	file.open(character_list_file_name);

	if (file.is_open())
	{
		//cout << "\n===============================\n        Character  List\n===============================\n" <<endl;

		cout << "Character List Found.\n" << endl;

		character_amount = 0;

		for (int count3 = 1; getline(file, character_list[count3]) && (character_list[count3] != end_phrase); count3++)
		{
			character_amount = character_amount + 1;				//update the amount of character

			//cout << character_list[count3] << endl;				//check character list

			character_list[count3] = character_list[count3] + character_suffix;			//add suffix to names
		}
		file.close();

		//cout << character_amount << endl;					//check the total amount of characters
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//Set up chracter name if character list not found
	else
	{



		cout << "Set your chracter name base now, type in the end_phrase to stop, the end phrase is " << end_phrase << " right now.\n" << endl;

		for (int count3 = 1; (count3 < max_characters) and (character_list[count3 - 1] != end_phrase + character_suffix); count3++)
		{
			cout << "Enter your chracter name:";

			cin >> character_list[count3];					//put names into array character_list[], the first data will be saved in [1](not [0] as usual)

			character_list[count3] = character_list[count3] + character_suffix;	//add suffix behind the name(to seperate speaking people from script)
		}


		//Checking chracter list
		/*
		for(int count2=1;(count2<max_characters) and (character_list[count2] != end_phrase + character_suffix);count2++)
		{
			cout << character_list[count2] << endl;
		}
		*/
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Input script

	file.open(script_file_name);

	if (file.is_open())
	{
		//cout << "\n===============================\n      Unprogressed Script\n===============================\n" <<endl;

		cout << "Unprogressed Script Found." << endl;

		for (int count3 = 1; getline(file, script[count3]) && (script[count3] != end_phrase); count3++)
		{
			script_amount = script_amount + 1;			//update the amount of character

			//cout << script[count3] << endl;				//check the script
		}
		file.close();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Recieve Scripts if script not found
	else
	{
		cout << "\n===============================\n    Start Recieving Scripts\n===============================\n" << endl;

		for (int count1 = 1; (count1 < max_lines) and (script[count1 - 1] != end_phrase); count1++)
		{
			script_amount = script_amount + 1;

			getline(cin, script[count1]);					//put scripts into array script[], the first data will be saved in [1](not [0] as usual)
		}
	}



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Finding character name in scripts


	for (int count1 = 1; (count1 <= script_amount) and (script[count1 - 1] != end_phrase); count1++)		//line of scripts, from the first line to the last
	{
		for (int count3 = 1; (count3 <= character_amount) and (character_list[count3 - 1] != end_phrase + character_suffix); count3++)	//character, from the first one to the last
		{
			index = script[count1].rfind(character_list[count3], character_list[count3].length());
			//if it found the exact same name with the exact suffix behind, index will be asigned to the position of where it was found

			//cout << index << "\t" << character_list[count3].length() << endl;			//check index


			if (index < script[count1].length())			//if that name was found in that line of script, do the action below
			{
				//cout << "Find " << character_list[count3] << "in " << script[count1];		//check the finding result

				script_name[count1] = character_list[count3];				//save the chracter name in another place
				script_name[count1].erase((character_list[count3].length()) - (character_suffix.length()), (character_suffix.length()));	//delete the suffix
				script_name[count1] = script_name[count1] + " ";			//add a space after the name

				script[count1].erase(0, character_list[count3].length());	//remove chracter name from script

				//cout << "\nAfter process:" << script[count1] << endl;		//check the progessed result

				break;			//preventing some bugs
			}
		}
	}

	//cout << "\n===============================\n     End Recieving Scripts\n===============================\n" <<endl;

	//cout << "\n===============================\n    Start Generating Script\n===============================\n" <<endl;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Generate and output processed script file
	ofstream Wfile;

	Wfile.open(progressed_script_file_name);

	for (int count2 = 1; (count2 <= script_amount) and (script[count2] != end_phrase); count2++)		//line of scripts, from the first line to the last
	{
		temp = script_name[count2] + bracket_type + script[count2] + bracket_type + "\n";

		Wfile << temp;				//

		//cout << temp << endl;		//output the result to screen
	}

	Wfile.close();

	cout << "\nScript generated.\n" << endl;

	cout << "===============================\n\tFinish Progress\n===============================" << endl;

	system("pause");
	return 0;		//The program ends here
}
