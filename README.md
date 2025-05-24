# Math Quiz Game in C++

A simple console-based Math Quiz game implemented in C++. The game generates random arithmetic questions based on the chosen difficulty level and operation type, tracks player answers, and provides feedback and a final score summary.

## Features

- Supports 4 operation types: Addition, Subtraction, Multiplication, Division, plus a Mixed mode with random operations.
- Three difficulty levels: Easy, Medium, Hard, plus a Mixed mode with random difficulty.
- User chooses the number of questions (1 to 10).
- Interactive console input for answers.
- Feedback after each question (correct/wrong) with colored console background.
- Final pass/fail result summary based on the number of correct answers.
- Replay option to try again without restarting the program.

## How to Run

1. Clone the repository or download the source code.
2. Compile the code using a C++ compiler supporting C++11 or later:
   ```bash
   g++ -o MathQuizGame MathQuizGame.cpp
   ```
3. Run the executable:
   ```bash
   ./MathQuizGame
   ```
4. Follow on-screen prompts to play the game.

## Code Structure

- **Enums:** Define operation types and question difficulty levels.
- **Structs:** Represent individual questions and the entire quiz.
- **Functions:**  
  - Random number generation  
  - Question generation  
  - User input handling  
  - Answer checking and feedback  
  - Quiz summary display  
  - Game loop management  

## Notes

- Division operation does not currently handle division by zero or non-integer results.
- The program uses system calls (`system("cls")`, `system("color")`) which work on Windows OS.

## Future Improvements

- Add input validation for non-numeric inputs.
- Improve division question generation to avoid division by zero and handle remainders.
- Add timer for each question.
- Implement a GUI version.
- Support more operations and customization options.

---

Feel free to contribute or report issues!
