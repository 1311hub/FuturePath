#include <iostream>
#include <string>
#include <limits> 

using namespace std;

// ================= USER =================
class User {
private:
    string name;
    float sgpa;
    int year;
    int skills[10];
    bool hasSkill[10];

public:
    string skillNames[10] = {
        "DSA", "C++", "Python", "Web Dev", "DBMS",
        "OS", "CN", "AI/ML", "Projects", "Communication"
    };

    char getValidChoice() {
        char ch;
        while (true) {
            cin >> ch;
            if (ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N') return ch;
            cout << "Enter y/n: ";
        }
    }

    int getValidRating() {
        int x;
        while (true) {
            cin >> x;
            if (x >= 1 && x <= 10) return x;
            cout << "Enter 1-10: ";
        }
    }

    void inputUser() {
        

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter SGPA: ";
        while (true) {
            if (cin >> sgpa && sgpa >= 0 && sgpa <= 10) break;
            cout << "Invalid (0-10): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter Year (1-4): ";
        while (true) {
            if (cin >> year && year >= 1 && year <= 4) break;
            cout << "Invalid (1-4): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        for (int i = 0; i < 10; i++) {
            cout << skillNames[i] << " (y/n): ";
            char ch = getValidChoice();
            if (ch == 'y' || ch == 'Y') {
                hasSkill[i] = true;
                cout << "Rating (1-10): ";
                skills[i] = getValidRating();
            } else {
                hasSkill[i] = false;
                skills[i] = 0;
            }
        }
    }

    int calculateStrength() {
        int sum = 0, count = 0;
        for (int i = 0; i < 10; i++) {
            if (hasSkill[i]) {
                sum += skills[i];
                count++;
            }
        }
        if (count == 0) return 0;
        return (sum / (float)count) * 10; 
    }

    string getRank() {
        int s = calculateStrength();
        if (s >= 80) return "Excellent";
        else if (s >= 60) return "Good";
        else if (s >= 40) return "Average";
        else return "Weak";
    }

    friend class Matching;
};

// ================= JOB ROLE =================
struct JobRole {
    string roleName;
    float minCgpa;
    int req[10];
};

// ================= COMPANY =================
class company {
public:
    string name;
    JobRole roles[5];
    int roleCount;
    virtual void setRoles() = 0;
    virtual ~company() {}
};

class google : public company {
public:
    google() { name = "Google"; }
    void setRoles() override {
        roleCount = 2;
        roles[0] = {"SDE", 8.5, {9, 9, 8, 7, 8, 8, 7, 7, 9, 7}};
        roles[1] = {"ML Engineer", 8.7, {8, 7, 9, 6, 7, 7, 6, 10, 8, 7}};
    }
};

class amazon : public company {
public:
    amazon() { name = "Amazon"; }
    void setRoles() override {
        roleCount = 2;
        roles[0] = {"Web Dev", 7.5, {7, 6, 6, 9, 7, 6, 6, 5, 8, 7}};
        roles[1] = {"SDE-1", 7.8, {8, 8, 7, 7, 7, 7, 6, 6, 8, 8}};
    }
};

class microsoft : public company {
public:
    microsoft() { name = "Microsoft"; }
    void setRoles() override {
        roleCount = 2;
        roles[0] = {"Cloud Support", 7.0, {6, 6, 6, 5, 7, 8, 8, 5, 6, 8}};
        roles[1] = {"Software Engineer", 8.2, {9, 8, 8, 7, 8, 8, 7, 7, 9, 8}};
    }
};

// ================= MATCHING =================
class Matching {
public:
    void suggestions(JobRole &r, User &u) {
        // FIX 2: Check if any suggestions exist before printing header
        bool hasSuggestions = false;
        string output = "";

        for (int i = 0; i < 10; i++) {
            if (!u.hasSkill[i]) {
                output += "  - Acquire skill: " + u.skillNames[i] + "\n";
                hasSuggestions = true;
            } else if (u.skills[i] < r.req[i]) {
                output += "  - Level up " + u.skillNames[i] + " to " + to_string(r.req[i]) + "\n";
                hasSuggestions = true;
            }
        }

        if (hasSuggestions) {
            cout << "Suggestions for improvement:" << endl;
            cout << output;
        }
    }

    void match(company *c, User &u) {
        cout << "\n==============================================";
        cout << "\n--- HIRING ANALYSIS: " << c->name << " ---" << endl;
        bool eligibleForAtLeastOne = false;

        for (int r = 0; r < c->roleCount; r++) {
            if (u.sgpa < c->roles[r].minCgpa) continue;

            eligibleForAtLeastOne = true;
            int matched = 0;
            for (int i = 0; i < 10; i++) {
                if (u.hasSkill[i] && u.skills[i] >= c->roles[r].req[i])
                    matched++;
            }

            int percent = (matched * 10); 
            cout << "\nRole: " << c->roles[r].roleName;
            cout << "\nTechnical Match: " << percent << "%" << endl;
            if (percent >= 70) cout << "Verdict: Strong Match!" << endl;
            else if (percent >= 50) cout << "Verdict: Moderate Match." << endl;
            else cout << "Verdict: Weak Match." << endl;

            suggestions(c->roles[r], u);
        }
        if (!eligibleForAtLeastOne) cout << "No current openings match your academic profile." << endl;
    }
};

// ================= MAIN =================
int main() {
    company* companies[3];
    companies[0] = new google();
    companies[1] = new amazon();
    companies[2] = new microsoft();

    for (int i = 0; i < 3; i++) companies[i]->setRoles();

    User currentUser;
    currentUser.inputUser();

    cout << "\n----------------------------------------------";
    cout << "\nUSER PROFILE RANK: " << currentUser.getRank();
    cout << "\n----------------------------------------------" << endl;

    Matching matcher;
    for (int i = 0; i < 3; i++) matcher.match(companies[i], currentUser);

    for (int i = 0; i < 3; i++) delete companies[i];
    return 0;
}