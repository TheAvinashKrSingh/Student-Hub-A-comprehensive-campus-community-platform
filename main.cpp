#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

struct Member
{
    string name;
    string department;
    string college;
};

int calculatePadding(int screenWidth, int textWidth)
{
    return (screenWidth - textWidth) / 2;
}

class Login
{
private:
    char username[20], password[20], branch[20], pno[20], email[30];

public:
    Login();
    int log_in();
    bool regester();
    void display();
    void delete_user();
    void main_menu();
    void sub_menu1();
    void sub_menu2();
    void update_data_user();
    void update_data_admin();
    void search_user();
    void read_news();
    void write_news();
    void schedule();
    void impt_con();
    void write_reviews();
    void read_reviews();
};

Login l1, l2;

void clear_screen();

Login::Login()
{
    strcpy(username, "no data");
    strcpy(password, "no data");
    strcpy(branch, "no data");
    strcpy(pno, "no data");
    strcpy(email, "no data");
}

int Login::log_in()
{
    char user[20], pass[20];
    cout << "Username : ";
    cin >> user;
    cout << "\nPassword : ";
    cin >> pass;
    clear_screen();
    if (!(strcmp(user, "admin")) && !(strcmp(pass, "admin101")))
        return 2;
    else
    {
        ifstream fin;
        fin.open("user_data.dat", ios::in | ios::binary);
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (!(strcmp(user, username)) && !(strcmp(pass, password)))
                return 1;
            fin.read((char *)this, sizeof(*this));
        }
    }
    return 10;
}

bool Login::regester()
{
    int err;
    cout << "Username    : ";
    cin >> username;
    cout << "\nPassword  : ";
    cin >> password;
    cout << "\nBranch    : ";
    cin >> branch;
    cout << "\nPhone No. : ";
    cin >> pno;
    cout << "\nEmail     : ";
    cin >> email;
    try
    {
        if (!(strcmp(username, "no data")) || !(strcmp(password, "no data")))
            throw err;
        else
        {
            ofstream fout;
            fout.open("user_data.dat", ios::app | ios::binary);
            fout.write((char *)this, sizeof(*this));
            fout.close();
            clear_screen();
            return true;
        }
    }
    catch (int e)
    {
        cout << "Username or password cannot be blank" << endl;
        return false;
    }
}

void Login::display()
{
    int ctr = 0;
    cout << "Currently registered users are: \n\n";
    ifstream display;
    display.open("user_data.dat", ios::in | ios::binary);
    display.read((char *)this, sizeof(*this));
    while (!display.eof())
    {
        cout << "\nName      : " << username;
        cout << "\nBranch    : " << branch;
        cout << "\nPhone No. : " << pno;
        cout << "\nEmail     : " << email << endl
             << endl;
        display.read((char *)this, sizeof(*this));
        ctr++;
    }
    cout << "Total registered users : ";
    cout << "\033[1;31m" << ctr << "\033[0m\n\n";
    display.close();
}

void Login::delete_user()
{
    char user[20];
    cout << "Enter the user to be deleted" << endl;
    cin >> user;
    ifstream fin;
    ofstream fout;
    fin.open("user_data.dat", ios::in | ios::binary);
    fout.open("temp.dat", ios::out | ios::binary);
    fin.read((char *)this, sizeof(*this));
    while (!fin.eof())
    {
        if (strcmp(user, username))
            fout.write((char *)this, sizeof(*this));
        fin.read((char *)this, sizeof(*this));
    }
    fin.close();
    fout.close();
    remove("user_data.dat");
    rename("temp.dat", "user_data.dat");
    cout << "User : " << user << " deleted successfully" << endl;
}

void Login::main_menu()
{
    int ch;
    int log;
    do
    {
        cout << "\033[1;31mW E L C O M E   T O   S T U D E N T - H U B\033[0m\n";
        cout << "\033[1;37m";
        cout << "============================================\n";
        cout << "Enter your choice" << endl;
        cout << "1.SIGN UP" << endl;
        cout << "2.LOGIN" << endl;
        cout << "3.EXIT" << endl;
        cout << "=============================================\n";
        cout << "\033[0m\n";
        cin >> ch;
        switch (ch)
        {
        case 1:
            if (l1.regester())
            {
                cout << "Registration successful - you may now login!" << endl;
                cout << "\033[1;33mWELCOME TO THE COMMUNITY!\033[0m\n";
                cout << "Press any key to continue..." << endl;
                cin.ignore();
                cin.get();
                clear_screen();
            }
            break;
        case 2:
            log = l1.log_in();
            if (log == 1)
                l1.sub_menu1();
            else if (log == 2)
                l1.sub_menu2();
            else
            {
                cout << "\033[1;31mInvalid username or password\033[0m\n";
                cout << "\033[1;33mNOTE: Usernames and passwords are case-sensitive\033[0m\n";
                cout << "Press any key to continue..." << endl;
                cin.ignore();
                cin.get();
                clear_screen();
            }
            break;
        case 3:
            break;
        default:
            cout << "Invalid option\n";
            break;
        }
    } while (ch != 3);
}

void Login::sub_menu2()
{
    int ch;
    do
    {
        cout << "======================================\n";
        cout << "WELCOME ";
        cout << "\033[1;31mADMIN\033[0m\n\n";
        cout << "Enter your choice" << endl;
        cout << "1.Display all users" << endl;
        cout << "2.Delete a user" << endl;
        cout << "3.Update a user's data" << endl;
        cout << "4.Read reviews from users" << endl;
        cout << "5.Logout" << endl;
        cout << "=======================================\n";
        cin >> ch;
        switch (ch)
        {
        case 1:
            l2.display();
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            clear_screen();
            break;
        case 2:
            l2.delete_user();
            cin.ignore();
            cin.get();
            cout << "Press any key to continue..." << endl;
            clear_screen();
            break;
        case 3:
            l2.update_data_admin();
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            clear_screen();
            break;
        case 4:
            cout << "\033[1;31mTHESE ARE THE REVIEWS FROM THE ACTIVE USERS\033[0m\n";
            l1.read_reviews();
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            clear_screen();
            break;
        case 5:
            cout << "Logged out successfully" << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            clear_screen();
            break;
        default:
            cout << "Invalid option\n";
            break;
        }

    } while (ch != 5);
}

void Login::sub_menu1()
{
    int ch;
    do
    {
        cout << "==============================================\n";
        cout << "WELCOME ";
        cout << "\033[1;31m" << username << "\033[0m\n\n";
        cout << "Enter your choice" << endl;
        cout << "1.See what's happening around you?!" << endl;
        cout << "2.Write news" << endl;
        cout << "3.Semester schedule" << endl;
        cout << "4.Important Contacts" << endl;
        cout << "5.Update Your Profile" << endl;
        cout << "6.Search friends" << endl;
        cout << "7.Give us your review" << endl;
        cout << "8.Logout" << endl;
        cout << "===============================================\n";
        cin >> ch;
        switch (ch)
        {
        case 1:
            clear_screen();
            cout << "\033[1;31mHERE ARE THE LATEST HAPPENINGS FROM AROUND THE CAMPUS\033[0m\n";
            l1.read_news();
            cout << "THAT'S ALL FOLKS\n";
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            clear_screen();
            break;
        case 2:
            clear_screen();
            cout << "\033[1;31mGot something to share with all your college mates?\nFrom academics to fun events anything can be posted here in this section\033[0m\n";
            l1.write_news();
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            clear_screen();
            break;
        case 3:
            clear_screen();
            cout << "\033[1;31mHERE'S THE ACADEMIC CALENDAR FOR THE CURRENT SEMESTER\033[0m\n";
            l1.schedule();
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            clear_screen();
            break;
        case 4:
            clear_screen();
            cout << "\033[1;31mTHESE CONTACTS MAY COME IN HANDY\033[0m\n";
            l1.impt_con();
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            clear_screen();
            break;
        case 5:
            l1.update_data_user();
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            clear_screen();
            break;
        case 6:
            l2.search_user();
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            clear_screen();
            break;
        case 7:
            clear_screen();
            cout << "\033[1;33mTell us about this app... loved it?, hated it? , want some features to be added? any feedback is much appreciated!\033[0m\n";
            l1.write_reviews();
            cout << "\033[1;33mThanks for the feedback and for being an active community member!\033[0m\n";
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            clear_screen();
            break;
        case 8:
            cout << "Logged out successfully! ";
            cout << "\033[1;33mSayonara ;)\033[0m\n";
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            clear_screen();
            break;
        default:
            cout << "Invalid option\n";
            break;
        }
    } while (ch != 8);
}

void Login::update_data_user()
{
    char user[20];
    strcpy(user, username);
    fstream file("user_data.dat", ios::in | ios::out | ios::binary);

    if (!file)
    {
        cerr << "Error opening file" << endl;
        return;
    }

    bool user_found = false;
    Login temp;

    file.seekg(0);

    while (file.read((char *)&temp, sizeof(temp)))
    {
        if (strcmp(user, temp.username) == 0)
        {
            cout << "Enter new credentials" << endl;
            cout << "\nNew Password  : ";
            cin >> temp.password;
            cout << "\nBranch    : ";
            cin >> temp.branch;
            cout << "\nPhone No. : ";
            cin >> temp.pno;
            cout << "\nEmail     : ";
            cin >> temp.email;

            file.seekp(file.tellg() - static_cast<streampos>(sizeof(temp)));
            file.write((char *)&temp, sizeof(temp));

            cout << "\033[1;31mYou're all set! Your profile has been updated\033[0m\n";
            user_found = true;
            break;
        }
    }

    if (!user_found)
    {
        cout << "\033[1;31mUser not found\033[0m\n";
    }

    file.close();
}

void Login::update_data_admin()
{
    char user[20];
    cout << "Enter the username to be updated: ";
    cin >> user;

    fstream file("user_data.dat", ios::in | ios::out | ios::binary);

    if (!file)
    {
        cerr << "Error opening file" << endl;
        return;
    }

    bool user_found = false;
    Login temp;

    file.seekg(0);

    while (file.read((char *)&temp, sizeof(temp)))
    {
        if (strcmp(user, temp.username) == 0)
        {
            cout << "Enter new credentials for " << user << endl;
            cout << "\nNew Password  : ";
            cin >> temp.password;
            cout << "\nBranch    : ";
            cin >> temp.branch;
            cout << "\nPhone No. : ";
            cin >> temp.pno;
            cout << "\nEmail     : ";
            cin >> temp.email;

            file.seekp(file.tellg() - static_cast<streampos>(sizeof(temp)));
            file.write((char *)&temp, sizeof(temp));

            cout << "\033[1;31mProfile for " << user << " has been updated\033[0m\n";
            user_found = true;
            break;
        }
    }

    if (!user_found)
    {
        cout << "\033[1;31mUser not found\033[0m\n";
    }

    file.close();
}

void Login::search_user()
{
    char user[20];
    cout << "Enter the user to be searched" << endl;
    cin >> user;
    ifstream fin;
    fin.open("user_data.dat", ios::in | ios::binary);
    fin.read((char *)this, sizeof(*this));
    while (!fin.eof())
    {
        if (!(strcmp(user, username)))
        {
            cout << "\nName      : " << username;
            cout << "\nBranch    : " << branch;
            cout << "\nPhone No. : " << pno;
            cout << "\nEmail     : " << email << endl
                 << endl;
            break;
        }
        fin.read((char *)this, sizeof(*this));
    }
    if (fin.eof())
        cout << "User not found" << endl;
    fin.close();
}

void Login::read_news()
{
    ifstream readn;
    readn.open("news.dat", ios::in);
    char ch;
    while (!readn.eof())
    {
        readn.get(ch);
        cout << ch;
    }
    readn.close();
}

void Login::write_news()
{
    ofstream writen;
    writen.open("news.dat", ios::app);
    time_t now = time(0);
    char *dt = ctime(&now);
    writen << "Date and Time: " << dt << endl;
    char ch;
    cout << "Write your news: ";
    cin.ignore();
    cin.get(ch);
    while (ch != '\n')
    {
        writen.put(ch);
        cin.get(ch);
    }
    writen.put('\n');
    writen.close();
}

void Login::schedule()
{
    ifstream reads;
    reads.open("schedule.dat", ios::in);
    char ch;
    while (!reads.eof())
    {
        reads.get(ch);
        cout << ch;
    }
    reads.close();
}

void Login::impt_con()
{
    ifstream readc;
    readc.open("contact.dat", ios::in);
    char ch;
    while (!readc.eof())
    {
        readc.get(ch);
        cout << ch;
    }
    readc.close();
}

void Login::write_reviews()
{
    ofstream writer;
    writer.open("reviews.dat", ios::app);
    char ch;
    cout << "Write your review: ";
    cin.ignore();
    cin.get(ch);
    while (ch != '\n')
    {
        writer.put(ch);
        cin.get(ch);
    }
    writer.put('\n');
    writer.close();
}

void Login::read_reviews()
{
    ifstream reader;
    reader.open("reviews.dat", ios::in);
    char ch;
    while (!reader.eof())
    {
        reader.get(ch);
        cout << ch;
    }
    reader.close();
}

void clear_screen()
{
    cout << "\033[2J\033[1;1H";
}

int main()
{
    string teamName = "Awesome Coders";
    vector<Member> members = {
        {"Avinash Kumar Singh", "B.Tech. (CSE)", "HNBGU"},
        {"Aman Raj", "B.Tech. (CSE)", "HNBGU"},
        {"Suhani Sharma", "B.Tech. (CSE)", "HNBGU"},
        {"Shabnam Kumari", "B.Tech. (CSE)", "HNBGU"}};

    // Calculate total width for centering
    int screenWidth = 80; // Assuming terminal width is 80 characters
    int teamNameWidth = teamName.length();
    int memberInfoWidth = 0;
    for (const auto &member : members)
    {
        int infoWidth = member.name.length() + member.college.length() + member.department.length() + 4; // 4 for separating spaces
        if (infoWidth > memberInfoWidth)
        {
            memberInfoWidth = infoWidth;
        }
    }

    int totalWidth = max(teamNameWidth, memberInfoWidth);

    // Calculate padding for centering
    int padding = calculatePadding(screenWidth, totalWidth);

    // Print team name centered on the screen
    cout << string(padding, ' ') << teamName << endl;

    // Print member details centered on the screen
    for (const auto &member : members)
    {
        int memberPadding = calculatePadding(screenWidth, member.name.length() + 2); // 2 for separating spaces
        cout << string(memberPadding, ' ') << member.name << " - " << member.college << " - " << member.department << endl;
    }

    cout << string(padding, ' ') << "Our Team: " << teamName << endl;

    cout << string(padding, ' ') << "Welcome to our mini project!" << endl;

    l1.main_menu();

    return 0;
}