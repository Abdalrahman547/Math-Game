#include <iostream>
#include <cstdlib>
using namespace std;

enum enQuestionsLevel { Eesy = 1, Mid = 2, Hard = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

string GetOpTypeSympol(enOperationType OperationType)
{

	string arrLevelName[5] = { " +", " -", " *", " /", "Mix" };
	return arrLevelName[OperationType - 1];
}

string GetQuestionsLevelText(enQuestionsLevel QuestionLevel)
{

	string arrLevelName[4] = { "Easy", "Mid", "Hard", "Mix" };
	return arrLevelName[QuestionLevel - 1];
}

int RandomNumber(int from, int to)
{
	int RandNum = rand() % (to - from + 1) + from;
	return RandNum;
}

void SetScreenColor(bool Right)
{
	if(Right)
		system("color 2f");  // Green
	else
	{
		system("color 4f");  // Red
		cout << "\a";
	}
}

short HowManyQuestions()
{
	short Questions = 0;

	do
	{
		cout << "How many questions do you want to answer? from 1 to 100\n";
		cin >> Questions;
	} while (Questions < 1 || Questions > 100);
	return Questions;
}

enQuestionsLevel ReadQuestionLevel()
{
	int LevelName = 1;
	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Mid, [3] Hard, [4] Mix ? ";
		cin >> LevelName;
	} while (LevelName < 1 || LevelName > 4);

	return (enQuestionsLevel)LevelName;
}

enOperationType ReadOperationType()
{
	int OpType = 1;
	do
	{
		cout << "[1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);
	return (enOperationType)OpType;
}

struct stQuestion
{
	int number1 = 0;
	int number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuiz
{
	stQuestion QuestionList[100];
	short NumberOfQestions = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool IsPass = false;
};

int SimpleCalculator(int number1, int number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return number1 + number2;

	case enOperationType::Sub:
		return number1 - number2;

	case enOperationType::Mult:
		return number1 * number2;

	case enOperationType::Div:
		return number1 / number2;

	default:
		return number1 + number2;
	}
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::Mix)
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);

	if (OpType == enOperationType::MixOp)
		OpType = (enOperationType)RandomNumber(1, 4);

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::Eesy:
		Question.number1 = RandomNumber(1, 10);
		Question.number2 = RandomNumber(1, 10);

		Question.CorrectAnswer =
			SimpleCalculator(Question.number1, Question.number2, Question.OperationType);

		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::Mid:
		Question.number1 = RandomNumber(10, 50);
		Question.number2 = RandomNumber(10, 50);

		Question.CorrectAnswer =
			SimpleCalculator(Question.number1, Question.number2, Question.OperationType);

		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::Hard:
		Question.number1 = RandomNumber(50, 100);
		Question.number2 = RandomNumber(50, 100);

		Question.CorrectAnswer =
			SimpleCalculator(Question.number1, Question.number2, Question.OperationType);

		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
	return Question;

}

void GenerateQizzQuestions(stQuiz& Quiz)
{
	for (short Question = 0; Question < Quiz.NumberOfQestions; Question++)
	{
		Quiz.QuestionList[Question] = GenerateQuestion(Quiz.QuestionsLevel, Quiz.OpType);
	}
}

int ReadQuistionAnswer()
{
	int answer = 0;
	cin >> answer;
	return answer;
}

void PrintTheQuestion(stQuiz& Quiz, short QuestionNumber)
{
	cout << endl;
	cout << "Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQestions << "]" << endl;
	cout << Quiz.QuestionList[QuestionNumber].number1 << endl;
	cout << Quiz.QuestionList[QuestionNumber].number2 << " ";
	cout << GetOpTypeSympol(Quiz.QuestionList[QuestionNumber].OperationType);
	cout << "\n____________\n";
}

void CorrectTheQuestionAnswer(stQuiz& Quiz, short QuestionNumber)
{
	if (Quiz.QuestionList[QuestionNumber].PlayerAnswer != Quiz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quiz.QuestionList[QuestionNumber].AnswerResult = false;
		Quiz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-( \n";
		cout << "The rigth Answer is: ";
		cout << Quiz.QuestionList[QuestionNumber].CorrectAnswer << endl;
		cout << endl;
	}
	else
	{
		Quiz.QuestionList[QuestionNumber].AnswerResult = true;
		Quiz.NumberOfRightAnswers++;

		cout << "Right Answer :-) \n";
	}
	cout << endl;
	SetScreenColor(Quiz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuiz& Quiz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQestions; QuestionNumber++)
	{
		PrintTheQuestion(Quiz, QuestionNumber);
		Quiz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuistionAnswer();
		CorrectTheQuestionAnswer(Quiz, QuestionNumber);
	}
	Quiz.IsPass = (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool pass)
{
	if (pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

void PrintQuizResult(stQuiz Quiz)
{
	cout << "\n";
	cout << "______________________________\n\n";
	cout << " Final Results is:      " << GetFinalResultsText(Quiz.IsPass);
	cout << "\n______________________________\n\n";

	cout << "Number of Questions:    " << Quiz.NumberOfQestions << endl;
	cout << "Questions level:        " << Quiz.QuestionsLevel << endl;
	cout << "Operation type:         " << Quiz.OpType << endl;
	cout << "Number of right answer: " << Quiz.NumberOfRightAnswers << endl;
	cout << "Number of wrong answer: " << Quiz.NumberOfWrongAnswers << endl;
	cout << "______________________________\n";
}

void PlayMathGame()
{
	stQuiz Quiz;

	Quiz.NumberOfQestions = HowManyQuestions();
	Quiz.QuestionsLevel = ReadQuestionLevel();
	Quiz.OpType = ReadOperationType();

	GenerateQizzQuestions(Quiz);
	AskAndCorrectQuestionListAnswers(Quiz);
	PrintQuizResult(Quiz);
}

void ResetScreen()
{
	system("cls");
	system("color 0f");
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		PlayMathGame();

		cout << endl << "Do you want to play again? Y/N ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}

