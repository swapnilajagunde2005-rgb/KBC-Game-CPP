#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// Class to manage question structure
class Question {
public:
    string text;
    string options[4];
    char correctOption;
    long long prizeMoney;

    Question(string qText, string o1, string o2, string o3, string o4, char correct, long long prize) {
        text = qText;
        options[0] = o1;
        options[1] = o2;
        options[2] = o3;
        options[3] = o4;
        correctOption = toupper(correct);
        prizeMoney = prize;
    }
};

// Helper function to clear terminal output
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    // 1. Setup Questions Bank
    vector<Question> bank = {
        Question("What is the capital of India?", "A. Mumbai", "B. New Delhi", "C. Kolkata", "D. Chennai", 'B', 1000),
        Question("Which data type is used to store text in C++?", "A. int", "B. float", "C. char", "D. string", 'D', 5000),
        Question("Who is known as the father of computers?", "A. Charles Babbage", "B. Alan Turing", "C. Isaac Newton", "D. Albert Einstein", 'A', 10000),
        Question("Which planet is known as the Red Planet?", "A. Earth", "B. Venus", "C. Mars", "D. Jupiter", 'C', 50000),
        Question("What is the default return type of main() in C++?", "A. void", "B. int", "C. double", "D. char", 'B', 160000)
    };

    // 2. Initialize Game Variables
    long long safeAmount = 0;
    long long totalWon = 0;
    bool has5050 = true;

    cout << "===========================================\n";
    cout << "    WELCOME TO KAUN BANEGA CROREPATI!     \n";
    cout << "===========================================\n\n";
    cout << "Rules: Answer correctly to advance. Use 'L' for Lifelines.\n";
    cout << "Press Enter to start the hot seat...";
    cin.get();

    // 3. Main Gameplay Loop
    for (size_t i = 0; i < bank.size(); ++i) {
        clearScreen();
        Question current = bank[i];
        
        cout << "Question " << (i + 1) << " for ₹" << current.prizeMoney << "\n";
        cout << "-------------------------------------------\n";
        cout << current.text << "\n\n";
        for (int j = 0; j < 4; ++j) {
            cout << current.options[j] << "\n";
        }
        cout << "-------------------------------------------\n";

        char choice;
        bool validAnswer = false;

        while (!validAnswer) {
            cout << "Enter your answer (A, B, C, D) or 'L' for Lifelines: ";
            cin >> choice;
            choice = toupper(choice);

            // Handle Lifeline Request
            if (choice == 'L') {
                if (has5050) {
                    cout << "\nUsing 50:50 Lifeline...\n";
                    // Find correct index
                    int correctIdx = current.correctOption - 'A';
                    int wrongIdxToKeep = (correctIdx + 1) % 4; // Keep one arbitrary wrong answer
                    
                    cout << "Remaining options:\n";
                    for(int j = 0; j < 4; j++) {
                        if(j == correctIdx || j == wrongIdxToKeep) {
                            cout << current.options[j] << "\n";
                        }
                    }
                    has5050 = false; // Burn the lifeline
                } else {
                    cout << "You have already used your 50:50 lifeline!\n";
                }
                continue;
            }

            // Handle Answer Verification
            if (choice == 'A' || choice == 'B' || choice == 'C' || choice == 'D') {
                validAnswer = true;
            } else {
                cout << "Invalid input! Try again.\n";
            }
        }

        // Process Result
        if (choice == current.correctOption) {
            totalWon = current.prizeMoney;
            cout << "\n🎉 Sahi Jawaab! (Correct Answer!) You have won: ₹" << totalWon << "\n";
            
            // Set milestones (Safe Amounts)
            if (i == 1) safeAmount = 5000;
            if (i == 3) safeAmount = 50000;
            
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        } else {
            cout << "\n❌ Galat Jawaab! (Wrong Answer!) The correct choice was " << current.correctOption << ".\n";
            totalWon = safeAmount;
            break;
        }
    }

    // 4. Game End Screen
    clearScreen();
    cout << "===========================================\n";
    cout << "                GAME OVER                  \n";
    cout << "===========================================\n";
    cout << "Thank you for playing KBC.\n";
    cout << "Total Prize Money Take-home: ₹" << totalWon << "\n";
    cout << "===========================================\n";

    return 0;
}