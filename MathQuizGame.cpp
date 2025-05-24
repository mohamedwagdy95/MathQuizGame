#include <iostream>   // Include iostream for input/output operations.
#include <cstdlib>    // Include cstdlib for system functions like clearing the screen.
#include <ctime>      // Include ctime for random number seeding.
using namespace std;  // Use the standard namespace to avoid prefixing std:: before standard functions.

// Enumeration for operation types
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

// Enumeration for question difficulty levels
enum enQuestionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

// Struct to represent a single math question
struct stQuestion {
	int Number1 = 0;
	int Number2 = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

// Struct to represent the entire quiz
struct stQuiz {
	stQuestion QuestionList[100];
	short NumberOfQuestions = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};

// Returns a random number in a given range
int RandomNumber(int From, int To) {
	return rand() % (To - From + 1) + From;
}

// Performs calculation based on the operation type
int SimpleCalculator(int Number1, int Number2, enOperationType OperationType) {
	switch (OperationType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2; 
	default:
		return Number1 + Number2; // Default case
	}
}

// Generates a question with given difficulty and operation
stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType) {
	stQuestion Question;

	// If level or operation is mixed, randomize it
	if (QuestionLevel == enQuestionLevel::Mix)
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);

	if (OperationType == enOperationType::MixOp)
		OperationType = (enOperationType)RandomNumber(1, 4);

	// Set actual question parameters
	Question.QuestionLevel = QuestionLevel;
	Question.OperationType = OperationType;

	// Set numbers based on level
	switch (QuestionLevel)
	{
	case enQuestionLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		break;
	case enQuestionLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		break;
	case enQuestionLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		break;
	}

	// Calculate correct answer
	Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

	return Question;
}

// Generates a full quiz based on selected level and operation
void GenerateQuizQuestions(stQuiz& Quiz) {
	for (short i = 0; i < Quiz.NumberOfQuestions; i++)
		Quiz.QuestionList[i] = GenerateQuestion(Quiz.QuestionLevel, Quiz.OperationType);
}

// Prompts the user to choose an operation type
enOperationType ReadOpType() {
	short OperationType;
	do {
		cout << "Enter operation type [1] Add, [2] Sub, [3] Mult, [4] Div, [5] Mix ? ";
		cin >> OperationType;
	} while (OperationType < 1 || OperationType > 5);

	return (enOperationType)OperationType;
}

// Prompts the user to choose a question level
enQuestionLevel ReadQuestionLevel() {
	short QuestionLevel;
	do {
		cout << "Enter questions level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionLevel)QuestionLevel;
}

// Reads number of questions to generate in the quiz
short ReadHowManyQuestions() {
	short NumberOfQuestions;
	do {
		cout << "How many questions do you want to answer ? ";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return NumberOfQuestions;
}

// Returns symbol for each operation type
string GetOpTypeSymbol(enOperationType OperationType) {
	switch (OperationType)
	{
	case enOperationType::Add: return "+";
	case enOperationType::Sub: return "-";
	case enOperationType::Mult: return "*";
	case enOperationType::Div: return "/";
	case enOperationType::MixOp: return "Mixed Operations";
	default: return "Unknown";
	}
}

// Displays a question to the player
void PrintTheQuestion(stQuiz& Quiz, short QuestionNumber) {
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestions << "]\n\n";
	cout << Quiz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quiz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quiz.QuestionList[QuestionNumber].OperationType);
	cout << "\n_____________" << endl;
}

// Reads player answer
int ReadQuestionAnswer() {
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

// Sets console color based on answer correctness
void SetScreenColor(bool AnswerResult) {
	if (AnswerResult)
		system("color 2F"); // Green background
	else
		system("color 4F"); // Red background
}

// Checks answer and updates result counters
void CorrectTheQuestionAnswer(stQuiz& Quiz, short QuestionNumber) {
	if (Quiz.QuestionList[QuestionNumber].PlayerAnswer != Quiz.QuestionList[QuestionNumber].CorrectAnswer) {
		Quiz.QuestionList[QuestionNumber].AnswerResult = false;
		Quiz.NumberOfWrongAnswers++;
		cout << "Wrong Answer :-( \n";
		cout << "The right answer is: " << Quiz.QuestionList[QuestionNumber].CorrectAnswer << "\n";
	}
	else {
		Quiz.QuestionList[QuestionNumber].AnswerResult = true;
		Quiz.NumberOfRightAnswers++;
		cout << "Right Answer :-) \n";
	}
	cout << endl;

	SetScreenColor(Quiz.QuestionList[QuestionNumber].AnswerResult);
}

// Iterates through questions and corrects them
void AskAndCorrectQuestionListAnswers(stQuiz& Quiz) {
	for (short i = 0; i < Quiz.NumberOfQuestions; i++) {
		PrintTheQuestion(Quiz, i);
		Quiz.QuestionList[i].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quiz, i);
	}

	Quiz.isPass = (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);
}

// Returns pass/fail as string
string GetFinalResultsText(bool isPass) {
	return isPass ? "Pass" : "Fail";
}

// Maps enum level to text
string GetQuestionLevelText(enQuestionLevel QuestionLevel) {
	string arrQuestionLevelText[4] = { "Easy", "Med", "Hard", "Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];
}

// Prints final result summary
void PrintQuizResults(stQuiz Quiz) {
	cout << "\n";
	cout << "__________________________________\n\n";
	cout << "Final result is: " << GetFinalResultsText(Quiz.isPass) << endl;
	cout << "__________________________________\n\n";

	cout << "Number of Questions     : " << Quiz.NumberOfQuestions << endl;
	cout << "Questions Level         : " << GetQuestionLevelText(Quiz.QuestionLevel) << endl;

	if (Quiz.OperationType == enOperationType::MixOp)
		cout << "Operation Type          : Mixed Operations\n";
	else
		cout << "Operation Type          : " << GetOpTypeSymbol(Quiz.OperationType) << endl;

	cout << "Number of right answers : " << Quiz.NumberOfRightAnswers << endl;
	cout << "Number of wrong answers : " << Quiz.NumberOfWrongAnswers << endl;
	cout << "__________________________________\n\n";
}

// Manages one full game round
void PlayMathGame() {
	stQuiz Quiz;
	Quiz.NumberOfQuestions = ReadHowManyQuestions();
	Quiz.QuestionLevel = ReadQuestionLevel();
	Quiz.OperationType = ReadOpType();

	GenerateQuizQuestions(Quiz);
	AskAndCorrectQuestionListAnswers(Quiz);
	PrintQuizResults(Quiz);
}

// Clears screen and resets color
void ResetScreen() {
	system("cls");
	system("color 0F");
}

// Main game loop
void StartGame() {
	char PlayAgain = 'Y';

	do {
		ResetScreen();
		PlayMathGame();

		cout << "\nDo you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

// Main Function
int main() {
	srand((unsigned)time(NULL)); // Seed random number generator
	StartGame(); // Start the quiz game.

	return 0; // Exit the program successfully.
}