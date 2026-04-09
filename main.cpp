#include<iostream>
using namespace std;
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
class company{
protected:
    string companyname;
    float mincgpa;
    int skills[10];
        
public:
string skillNames[10] = {
        "Data Structures & Algorithms",
        "C++ Programming",
        "Python Programming",
        "Web Development",
        "Database Management (DBMS)",
        "Operating Systems",
        "Computer Networks",
        "AI / Machine Learning",
        "Projects",
        "Communication Skills"
        };

    company(string name, float cgpa){
        companyname = name;
        mincgpa = cgpa;
        
    }
    
    virtual void setrequirement() = 0;

    virtual void displayrequirement() {
        cout << "\n==============================";
        cout << "\n Company name:: " << companyname;
        cout << "\n Minimum Cgpa required:: " << mincgpa << endl;

        string skillNames[10] = {
        "Data Structures & Algorithms",
        "C++ Programming",
        "Python Programming",
        "Web Development",
        "Database Management (DBMS)",
        "Operating Systems",
        "Computer Networks",
        "AI / Machine Learning",
        "Projects",
        "Communication Skills"
        };

        for(int i=0;i<10;i++){
            cout << skillNames[i] << " : " << skills[i] << endl;
        }
    }
    friend class Matching;

    virtual ~company() {}
};


// GOOGLE
class google: public company{
public:
    google():company("Google",8.5){}

    void setrequirement(){
        int arr[10] = {9,9,8,7,8,8,7,9,9,8};
        for(int i=0;i<10;i++){
            skills[i]=arr[i];
        }
    }
    friend class Matching;
};


// AMAZON
class amazon: public company{
public:
    amazon():company("Amazon",7.5){}

    void setrequirement(){
        int arr[10] = {8,7,7,6,7,7,6,7,8,7};
        for(int i=0;i<10;i++){
            skills[i]=arr[i];
        }
    }
    friend class Matching;
};


// MICROSOFT
class microsoft: public company{
public:
    microsoft():company("Microsoft",8.0){}

    void setrequirement(){
        int arr[10] = {9,8,8,7,8,8,7,8,9,8};
        for(int i=0;i<10;i++){
            skills[i]=arr[i];
        }
    }
    friend class Matching;
};


// META
class meta: public company{
public:
    meta():company("Meta",8.3){}

    void setrequirement(){
        int arr[10] = {9,8,9,7,8,8,7,9,9,8};
        for(int i=0;i<10;i++){
            skills[i]=arr[i];
        }
    }
    friend class Matching;
};


// APPLE
class apple: public company{
public:
    apple():company("Apple",8.2){}

    void setrequirement(){
        int arr[10] = {8,8,7,7,8,8,7,8,8,9};
        for(int i=0;i<10;i++){
            skills[i]=arr[i];
        }
    }
    friend class Matching;
};
class Matching
{
    bool ismatch = false;
    public:
    void match_company(company *c,User &u)
    {
        if(u.sgpa<c->mincgpa)
        {
            return;
        }
        cout<<"--------------------"<<u.name<<", your cgpa is eligible for "<<c->companyname<<"----------------------"<<endl<<endl<<endl;
        for(int i = 0; i < 10; i++)
        {
            if(u.skills[i]>c->skills[i])
            {
                cout<<c->skillNames[i]<<" matches the norms of "<<c->companyname<<endl<<endl;
            }
        }
}
};

// MAIN FUNCTION
int main(){

    company* c[5];   // base class pointer array

    c[0] = new google();
    c[1] = new amazon();
    c[2] = new microsoft();
    c[3] = new meta();
    c[4] = new apple();

    for(int i=0;i<5;i++){
        c[i]->setrequirement();      // runtime polymorphism
        c[i]->displayrequirement();
    }
    
    User a;
    a.inputUser();
    Matching b;
    for(int i = 0; i < 4; i++)
    {
    b.match_company(c[i],a);
    }
    return 0;
}





