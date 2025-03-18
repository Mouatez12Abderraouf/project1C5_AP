#include <iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

enum levelQuestion {Easy = 1,Med = 2,Hard = 3,Mix = 4};

enum OperationOfQuestion {Add = 1,Sub = 2,Mul = 3,Div = 4,MixOp = 5};

struct InfoRounds
{
	short num1, num2;
	float answer;
	float rightAnswer;
	char symbolOfOperation;
	levelQuestion level;
	OperationOfQuestion op;
};

struct infoFinalGame
{
	string finalResult;
	short nbQuestion;
	string QuestionLevel;
	string opType;
	short nbRightQuestion = 0;
	short nbWrongQuestion = 0;

};

short readNumberInRange()
{
	short num;
	do
	{
		cout << "how many question do you want to play? 1 to 10?";
		cin >> num;

	} while (num < 1 || num > 10);

	return num;

}

void printNbQuestion(short count, short lim)
{
	cout << "-------------------" << endl;
	cout << "|  Question [" << count << "/" << lim << "] |" << endl;
	cout << "-------------------" << endl << endl << endl;
}

short randomNumber(int from, short to)
{
	return from + (rand() % (to + 1 - from));
}

float roundOne(float f)
{
    int integer,floatt;
    integer = (int)f;
    floatt = (f - integer) * 10;
    return integer + (floatt / 10.0);
}

InfoRounds choiceNumbers(InfoRounds infoRounds)
{
	switch (infoRounds.level)
	{
	case levelQuestion::Easy :
		infoRounds.num1 = randomNumber(5, 10);
		infoRounds.num2 = randomNumber(1, 5);
		break;
	case levelQuestion::Hard:
		infoRounds.num1 = randomNumber(75, 100);
		infoRounds.num2 = randomNumber(50, 75);
		break;
	case levelQuestion::Med:
		infoRounds.num1 = randomNumber(30, 49);
		infoRounds.num2 = randomNumber(11, 30);
		break;
	case levelQuestion::Mix:
		infoRounds.num1 = randomNumber(20, 100);
		infoRounds.num2 = randomNumber(1, 20);
		break;
	}

	return infoRounds;
}

short readInfo(string message, int from, int to)
{
	short num;
	do
	{
		cout << message;
		cin >> num;

	} while (num < from || num > to);

	return num;
}

char fillCharacter(OperationOfQuestion op)
{
	switch (op)
	{
	case Add:
		return '+';
		
	case Sub:
		return '-';
		
	case Mul:
		return '*';

	case Div:
		return '/';
	
    default :
        return '\0';
	}

}

float calQuestion(InfoRounds info)
{
    
	switch (info.symbolOfOperation)
	{
	case '+' :
		return info.num1 + info.num2;

	case '/' :
		return roundOne((info.num1 / (float)info.num2));

	case '*' :
		return info.num1 * info.num2;

	case '-' : 
		return info.num1 - info.num2;

	default:
		cout << "this operation is not existed\n";
		return 1;
	}
}

string tab(int nb)
{
	string res;
	for (int i = 1; i <= nb; i++)
	{
		res += '\t';
	}
	return res;
}

void printQuestion(InfoRounds info)
{
	cout << info.num1 << endl;
	cout << info.num2 << tab(1) << info.symbolOfOperation << endl;
	cout << "______________" << endl;
}

float readNumber(InfoRounds info)
{
	printQuestion(info);
	float num;
	cin >> num;
	return num;

}

bool printResultOfQuestion(InfoRounds info)
{
	if (info.answer == info.rightAnswer)
	{
		cout << "Right answer :-)\n\n\n";
        system("color 2F");
        return true;

	}
	else
	{
		cout << "worng answer :-(\n";
		cout << "The right answer is :" << info.rightAnswer << "\n\n\n";
        system("color 4F");
        return false;
	}
}

string nameOfLevel(levelQuestion l)
{
    switch (l)
    {
    case levelQuestion::Easy :
        return "Easy";
    
    case levelQuestion::Hard :
        return "Hard";
    
    case levelQuestion::Med :
        return "Med";

    case levelQuestion::Mix :
        return "Mix";

    }
}

string nameOfOperation(OperationOfQuestion op)
{
    switch (op)
    {
    case OperationOfQuestion::Add :
        return "Add";
        
    case OperationOfQuestion::Div :
        return "Div";

    case OperationOfQuestion::Mul :
        return "Mul";

    case OperationOfQuestion::MixOp :
        return "Mix";

    case OperationOfQuestion::Sub :
        return "Sub";

    }
}

infoFinalGame playGame(short nbRounds)
{
	InfoRounds QuestionInfo;
	infoFinalGame finalGame;
    finalGame.nbQuestion = nbRounds;

	QuestionInfo.level = (levelQuestion)readInfo("Enter Question level [1] Easy, [2] Med, [3] Hard, [4] Mix ?", 1, 4);
    finalGame.QuestionLevel = nameOfLevel(QuestionInfo.level);
	QuestionInfo.op = (OperationOfQuestion)readInfo("Enter operation type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?", 1, 5);
    finalGame.opType = nameOfOperation(QuestionInfo.op);
	if (QuestionInfo.op != OperationOfQuestion::MixOp)
	{
		QuestionInfo.symbolOfOperation = fillCharacter(QuestionInfo.op);
	}
	
	for (short i = 1; i <= nbRounds; i++)
	{
		printNbQuestion(i, nbRounds);
		QuestionInfo = choiceNumbers(QuestionInfo);
		if (QuestionInfo.op == OperationOfQuestion::MixOp)
		{

			QuestionInfo.op = (OperationOfQuestion)randomNumber(1, 4);
			QuestionInfo.symbolOfOperation = fillCharacter(QuestionInfo.op);
			QuestionInfo.op = OperationOfQuestion::MixOp;

		}

		QuestionInfo.rightAnswer = calQuestion(QuestionInfo);
		QuestionInfo.answer = readNumber(QuestionInfo);
		if(printResultOfQuestion(QuestionInfo))
        {
            finalGame.nbRightQuestion ++;
        }
        else
        {
            finalGame.nbWrongQuestion ++;
        }
		//print Question
		//read answer

	}

    if(finalGame.nbRightQuestion >= finalGame.nbWrongQuestion)
    {
        finalGame.finalResult = "pass";
    }
    else
    {
        finalGame.finalResult = "fail";
    }

    return finalGame;

}

void resetScreen()
{
	system("cls");
	system("color 0F");
}

void printResultOfQuestion(string result)
{
    string emuji;
    if (result == "pass")
    {
        emuji = ":-)";
    }
    else
    {
        emuji = ":-(";
    }
    
    cout << "________________________________________________________\n";
    cout << tab(2) << "final rasult is " << result << " " << emuji << endl;
    cout << "________________________________________________________\n\n\n";
}

void printTutalGame(infoFinalGame infoTutal)
{
    printResultOfQuestion(infoTutal.finalResult);
    cout << "Number of Questions    :" << infoTutal.nbQuestion << endl;
    cout << "Question Level         :" << infoTutal.QuestionLevel << endl;
    cout << "Operation type         :" << infoTutal.opType << endl;
    cout << "Number of right answer :" << infoTutal.nbRightQuestion << endl;
    cout << "Number of worng answer :" << infoTutal.nbWrongQuestion << endl << endl;
}

void startGame()
{
	infoFinalGame infoGame;
	char offOn;

	do
	{
		resetScreen();
		infoGame.nbQuestion = readNumberInRange();
		infoGame = playGame(infoGame.nbQuestion);
        printTutalGame(infoGame);

		cout << "do you want to play again? [y/n]? ";
		cin >> offOn;

	} while (offOn == 'y' || offOn == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	startGame();
    
    
	
}					
