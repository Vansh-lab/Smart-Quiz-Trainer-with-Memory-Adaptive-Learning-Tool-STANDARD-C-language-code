# Smart-Quiz-Trainer-with-Memory-Adaptive-Learning-Tool-STANDARD-C-language-code
A C-based adaptive quiz app that logs wrong answers and quizzes them again until the user masters them. Built with file-based memory to reinforce learning with immediate feedback.

 Features

-  Multiple-choice questions via `questions.txt`
-  Tracks wrong answers and logs them to `mistakes.txt`
-  Repeats only incorrect questions in future sessions
- File-handling based memory — no database needed
-  Reinforces learning through repetition

 How It Works

1. Loads and asks questions from `questions.txt`
2. If you answer wrong, it logs to `mistakes.txt`
3. On the next launch, it first asks from `mistakes.txt` (if present)
4. When answered correctly, those are cleared

 Files

- `main.c`: The source code
- `questions.txt`: List of MCQs with answers
- `mistakes.txt`: Auto-generated file for incorrect answers

`questions.txt` Format:


