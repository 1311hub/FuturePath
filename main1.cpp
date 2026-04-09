#include <iostream>

#include<string> 
using namespace std;
class Matching; // forward declaration
class User {
private:
    string name;
    float sgpa;
    int year;

    int skills[10];      // skill ratings
    bool hasSkill[10];   // whether user has that skill

    string skillNames[10] = {
        "Data Structures & Algorithms",
        "C++ Programming",
        "Python Programming","Web Development",
        "Database Management (DBMS)",
        "Operating Systems",
        "Computer Networks",
        "AI / Machine Learning",
        "Projects",
        "Communication Skills"
    };

    // validation for yes/no
    char getValidChoice() {
        char ch;
        while (true) {
            cin >> ch;
if (ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N') {
                return ch;
            } else {
                cout << "Invalid, Enter y/n only: ";
            }
        }
    }

    // validation for rating
    int getValidRating() {
        int val;
        while (true) {
            cin >> val;
            if (val >= 1 && val <= 10) return val;
            cout << "Enter value between 1-10: ";
        }
    }

public:


    // INPUT FUNCTION
    
    void inputUser() {

     
        cout << "        ENTER USER DETAILS\n";
        

        cout << "Enter Name: ";
        cin >> name;

        cout << "Enter SGPA (0-10): ";
        while (true) {
            cin >> sgpa;
            if (sgpa >= 0 && sgpa <= 10) break;
            cout << "Invalid SGPA, Enter again: ";
        }

        cout << "Enter Year (1-4): ";
        while (true) {
            cin >> year;
            if (year >= 1 && year <= 4) break;
            cout << "❌Invalid Year, Enter again: ";
        }

        cout << "\nSelect your skills (y/n):\n";

        for (int i = 0; i < 10; i++) {
            cout << skillNames[i] << " (y/n): ";
            char choice = getValidChoice();

            if (choice == 'y' || choice == 'Y') {
                hasSkill[i] = true;

                cout << "Rate your level (1-10): ";
                skills[i] = getValidRating();
            } else {
                hasSkill[i] = false;
                skills[i] = 0;
            }
        }

        cout << "\nUser Added Successfully!!\n";
    }


    // DISPLAY FUNCTION
    void displayUser() {

        cout << "Name : " << name << endl;
        cout << "SGPA : " << sgpa << endl;
        cout << "Year : " << year << endl;

        cout << "\nSkills:\n";

        for (int i = 0; i < 10; i++) {
            if (hasSkill[i]) {
                cout << skillNames[i] << " -> " << skills[i] << "/10\n";
            }
        }
    }


    // PROFILE STRENGTH
    int calculateStrength() {
        int sum = 0;
        int count = 0;

        for (int i = 0; i < 10; i++) {
            if (hasSkill[i]) {
                sum += skills[i];
                
                count++;
            }
        }

        if (count == 0) return 0;

        return (sum / count) * 10;
    }

    void showStrength() {
        int strength = calculateStrength();
        cout << "Profile Strength: " << strength << "%\n";
    }

    friend class Matching;
};


// MAIN 

int main() {

    int n;

    cout << "Enter number of students: ";
    cin >> n;

    // Array of objects
    User users[100];  // max 100 students

    // Input multiple users
    for (int i = 0; i < n; i++) {
        cout << "        Student " << i + 1 << "\n";
        users[i].inputUser();
    }

    // Display all users
    cout << "        All Students Data\n";

    for (int i = 0; i < n; i++) {
        users[i].displayUser();
        users[i].showStrength();
    }

    return 0;
}