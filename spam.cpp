#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//Spam Test Functions
bool UpperSubject(string text);
bool LastWordGibberish(string text);
bool hasMultipleExclamations(string text);
bool UpperBody(string text);
int SpamWord(string text);

//Other Functions
string getFirstWord(string text);
string getLastWord(string text);
string extractWord(string& text);
bool isUppercase(string text);
string makeUppercase(string text);
bool isGibberishWord(string text);

int main()
{
	string YesOrNo;			//YesOrNo variable created to ask user if he/she wants to reclassify another email
	int SpamNumber = 0;		//LegitNumber variable represents number of legit emails
	int LegitNumber = 0;	//SpamNumber variable  represents number of spam emails


	//loops if user inputs "y" to YesOrNo to reclassify another email
	do
	{	
		//Taking subject line
		cout << "Enter the subject line of the email: ";
		string SubjectLine;
		getline(cin,SubjectLine);

		//Taking body message input
		cout << "Enter the body of the email.  Press Enter on an empty line to finish." << endl;
		
		string RealBody; //Real message that will compile all the lines of text
		string TempBody; //"Temporary" message that will be appended to RealBody string

		//Makes sure user presses enter on a new line to continue, checks by 
		//making sure the new getline string is an empty string before moving on
		do
		{
			getline(cin,TempBody);
			if (TempBody == "")
				break;
			else
			{
				RealBody += TempBody;
				RealBody += "\n";
			}
		} while (TempBody != "");

		//resets SpamScore in case user wants to reclassify another email
		int SpamScore = 0;

		//Checks spam tests, if true, adds to spam score
		if (UpperSubject(SubjectLine))
			SpamScore += 30;

		if (LastWordGibberish(SubjectLine))
			SpamScore += 40;

		if (hasMultipleExclamations(SubjectLine))
			SpamScore += 20;

		if (UpperBody(RealBody))
			SpamScore += 40;

		SpamScore += (5 * SpamWord(RealBody));

		//Output email as spam or legitamate, along with spam score
		if (SpamScore > 100)
			cout << "This email is classified as spam, because its spam score is " << SpamScore << "." << endl;
		else 
			cout << "This email is classified as legitimate, because its spam score is " << SpamScore << "." << endl;
	
		//Spam/Legit email counter
		if (SpamScore > 100)
			SpamNumber++;
		else
			LegitNumber++;

		//Asks for another email and loops if answer is not 'y' or 'n'
		do 
		{
			cout << "Would you like to classify another email (y or n)? ";
			getline(cin,YesOrNo);

			if ( YesOrNo != "y" && YesOrNo != "n")
				cout << "Please enter y or n." << endl;

		} while ( YesOrNo != "y" && YesOrNo != "n");

	} while ( YesOrNo == "y" );

	//if 'n', prints number of spam and legitimate messages
		cout << "\nNumber of spam messages: " << SpamNumber << endl
			 << "Number of legitimate messages: " << LegitNumber << endl;
}

//Precondition: Subject at least 1 word long.
//Returns true if 90% of words in subject are all-uppercase.
bool UpperSubject(string text)
{
	double WordCount = 0;	//represents total number of words
	double UpperWords = 0;	//represents number of uppercase words
	string TempWord;		//represents temporary word extracted

	//extracts a word and adds to word counter
	//if the word is uppercase, adds to uppercase words counter
	//stops when there are no more words to extract
	do
	{
	//makes sure extractWord does not loop forever
	if(text == "")
		break;

	TempWord = extractWord(text);
	WordCount++;

	if(isUppercase(TempWord))
			UpperWords++;

	} while (text != "");

	if (UpperWords / WordCount > .90)
		return true;
	else
		return false;
}

//Precondition: Subject at least 1 word long.
//Returns true if last word contains at least 3 consecutive consonants.
bool LastWordGibberish(string text)
{
	string LastWord;	//represents last word in subject line
	LastWord = getLastWord(text);

	if (isGibberishWord(LastWord))
		return true;
	else
		return false;
}

//Precondition: Subject line is at least 1 character long.
//Returns true if subject line has 3 or more consecutive exclamation points.
bool hasMultipleExclamations(string text)
{
	int ExclamationCount = 0;	//represents number of consecutive !'s

	//Counts # of consecutive !'s, if char is not !,
	//or a space, count of consecutive !'s resets
	for (size_t k = 0; k != text.size(); k++)
	{
		if (text[k] != '!' || text[k] == ' ')
			ExclamationCount = 0;
		else
			ExclamationCount++;

		if (ExclamationCount == 3)
			return true;
	}
	return false;
}

//Precondition: Body at least one word long
//Returns true if 50% of words in body are all-uppercase words.
bool UpperBody(string text)
{
	double WordCount = 0;	//represents total number of words
	double UpperWords = 0;	//represents number of uppercase words
	string TempWord;		//represents temporary word extracted
	

	//extracts a word and adds to word counter
	//if the word is uppercase, adds to uppercase words counter
	//stops when there are no more words to extract
	do
	{
	//makes sure extractWord does not loop forever
	if(text == "")
		break;

	TempWord = extractWord(text);
	WordCount++;

	if(isUppercase(TempWord))
			UpperWords++;

	} while (text != "");

	if (UpperWords / WordCount > .50)
		return true;
	else
		return false;
}

//Precondition: Body at least one word long
//Returns true if 50% of words in body are all-uppercase words.
int SpamWord(string text)
{
	int SpamWordNumber = 0;	//represents number of special spam words
	string UppercaseBody = makeUppercase(text);	//new string that represents an all uppercase string so spam filter is not case sensitive
	string TempWord;		//temporary word that is extracted

	//extracts a word to check if it a special spam word
	//if it is, add one to SpamWordNumber
	do
	{
	//makes sure extractWord does not loop forever
		if(UppercaseBody == "")
		break;

	TempWord = extractWord(UppercaseBody);

	if (TempWord == "BUY" || 
		TempWord == "CHEAP" ||
		TempWord == "CLICK" ||
		TempWord == "DIPLOMA" ||
		TempWord == "ENLARGE" ||
		TempWord == "FREE" ||
		TempWord == "LONELY" ||
		TempWord == "MONEY" ||
		TempWord == "NOW" ||
		TempWord == "OFFER" ||
		TempWord == "ONLY" ||
		TempWord == "PILLS" ||
		TempWord == "SEX")
		SpamWordNumber++;

	} while (UppercaseBody != "");

	return SpamWordNumber;
}

//Precondition: string can be empty.
//returns first word in string.
string getFirstWord(string text)
{
	if (text.size() == 0)
		return "";

	string newText = ""; //represents first word that will be returned

	//makes sure if first word is empty string, continues
	//until first word is at least a letter
	for (size_t k=0; k != text.size(); k++)
	{
		if (isalpha(text[k]))					
			newText += text[k];					

		//makes sure newText
		//is not an empty string
		if (!isalpha(text[k]) && newText != "")
			break;
	}
		return newText;
}

//Precondition: string can be empty.
//returns last word in a string
string getLastWord(string text)
{
	string LastWord = ""; //represents last word that will be returned

	//loops until there are no more words left
	do
	{
		//checks if there are any more words in the string text
		if (getFirstWord(text) == "")
		break;

		LastWord = extractWord(text);

	} while (getFirstWord(text) != "");

	return LastWord;
}

//Precondition: string can be empty.
//extracts first word out of string and changes original string.
string extractWord(string& text)
{
	if (text.size() == 0)
		return "";

	string FirstWord = getFirstWord(text);

	//checks if the resulting substring contains any words
	//returns empty string if the string does not have any more words
	if (getFirstWord(text) == "")
		text = "";
	
	//need to find position of the first non-letter after the first word
	//finds j, the position of the first letter, to "bypass" characters in front of first word
	int j = 0;
	for (size_t k=0; k != text.size(); k++)
	{
		if (isalpha(text[k]))
		{
			j = k;
			break;
		}	
	}

	//starting position is j, the position of the first letter, plus the size of the first word
	//the starting position would then be the char right after the first word
	text = text.substr(j + getFirstWord(text).size(),text.size());

	return	FirstWord;	
}

//Precondition: string can be empty.
//returns true if every leter in the string is uppercase.
bool isUppercase(string text)
{
	if (text == "")
		return true;

	//checks if each letter is uppercase
	for (size_t k=0; k!= text.size(); k++)
	{
		//makes sure it is checking a letter, not another character
		if (isalpha(text[k]))
		{
		if (!isupper(text[k]))
			return false;
		}
	}
	return true;
}

//Precondition: string can be empty.
//returns string with all the letters uppercase.
string makeUppercase(string text)
{
	string newText = ""; //represents new text that will be all uppercase

	//goes through each char and makes it uppercase
	for (size_t k=0; k != text.size(); k++)
	{
		newText += toupper(text[k]);
	}
	return newText;
}

//Precondition: string can be empty.
//Tests if word has more than 3 consecutive consonants.
bool isGibberishWord(string text)
{
	//represents number of consecutive consonants
	int ConsCount = 0;

	//checks if char is a vowel
	for (size_t k = 0; k != text.size(); k++)
	{
		if (text[k] == ' ')
			ConsCount = 0;

		if (isalpha(text[k]))
		{
			if (text[k] == 'a' ||
				text[k] == 'e' ||
				text[k] == 'i' ||
				text[k] == 'o' ||
				text[k] == 'u' ||
				text[k] == 'A' ||
				text[k] == 'E' ||
				text[k] == 'I' ||
				text[k] == 'O' ||
				text[k] == 'U')
				ConsCount = 0;
			else
				ConsCount++;		

			if (ConsCount > 3)
				return true;
		}
	}
	return false;
}