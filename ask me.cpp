#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include<sstream>
using namespace std;

//under work
struct SignupUser
{
    int id;
    string username;
    string name;
    string password;
    string gmail;
    bool allow_anyonmous;
};

struct LoginUser
{
    string name;
    string pass;
};

struct question
{
    string qu;
    string ans;
    string thread;
    int id_ques;
    int id_choice;
    int user_id;
};

vector<SignupUser> users;
vector<question> questions;
LoginUser l;
question q;
SignupUser user;

//for reading all the file
vector<string> read_users(string path)
{
    vector<string>lines;
    fstream file_users(path.c_str());

    if (file_users.fail())
    {
        cerr << "The file can not open \n";
        return lines;
    }
    string line;
    while (getline(file_users,line))
    {
        if (line.size() == 0)
        {
            continue;
        }
    }
    file_users.close();
}

void write_users(string path, vector<string>lines,bool append=true)
{
    auto status = ios::in | ios::out | ios::app;

    if (!append)
    {
        status = ios::in | ios::out | ios::trunc;
        return;
    }
    fstream file_users(path.c_str(), status);
    if (file_users.fail())
    {
        cerr << "the file fail\n";
        return;
    }
    for (const auto& line: lines)
    {
        file_users << line<<'\n';
    }
    file_users.close();
}
vector<string> split_string(string s,string comma=",")
{
    vector <string>sts;
    int it = 0;
    string sub;
    while (it = (int)s.find(comma) != -1)
    {
        sub = s.substr(0, it);
        sts.push_back(sub);
        s.erase(0, it+comma.length());
    }
    sts.push_back(s);
    return sts;
}
vector<string> read_questions()
{
    ifstream read_question("questions.txt");
    if (read_question.fail())
    {
        cerr << "ERROR\n";
        return;
    }
    while (read_question >> q.qu >> q.ans >> q.id_ques >> q.thread >> q.id_choice >> q.user_id)
    {
        questions.push_back(q);
    }
    read_question.close();
}

void write_questions()
{
    ofstream write_question("questions.txt");
    if (write_question.fail())
    {
        cerr << "ERROR\n";
        return;
    }
    for (const auto& q : questions)
    {
        write_question << q.qu << " " << q.ans << " " << q.id_ques << " " << q.thread << " " << q.id_choice << " " << q.user_id << "\n";
    }
    write_question.close();
}

void true_pass()
{
    bool pass_true = true;
    if (!pass_true)
    {
        cin >> user.password;
    }
}

int menu_one()
{
    int choice_m1 = -1;
    cout << "----------------------------------------\n";
    cout << "Welcome to the Ask Me website:\n";
    cout << '\t' << "1: Log in\n";
    cout << '\t' << "2: Sign up\n";
    cout << "----------------------------------------\n";
    cout << "Enter number one or two: ";
    cin >> choice_m1;
    if (choice_m1 == 1)
    {
        cout << "Your name: ";
        cin >> l.name;
        cout << "Password: ";
        cin >> l.pass;
        bool login = false;
        for (const auto& user : users)
        {
            if (l.name == user.name && l.pass == user.password)
            {
                login = true;
                cout << "Logged in successfully\n";
                break;
            }
        }
        if (!login)
        {
            cout << "Incorrect username or password. Please sign up instead.\n";
            return -1;
        }
    }
    else if (choice_m1 == 2)
    {
        cout << "Username (no spaces): ";
        cin >> user.username;
        cout << "Password: (should contain 8 characters including numbers and symbols): ";
        cin >> user.password;

        while (user.password.length() != 8)
        {
            cout << "Invalid password, try another one\n";
            true_pass();
            break;

        }

        cout << "Name: ";
        cin >> user.name;
        cout << "Name: ";
        cin >> user.name;
        cout << "Gmail: ";
        cin >> user.gmail;
        cout << "Allow anonymous questions (0 or 1)? ";
        cin >> user.allow_anyonmous;
        cout << "-----------------------------------------\n";
        cout << '\a';
        cout << "Signed UP Successfully\n";
        user.id = users.size() + 1; // Assign a unique ID
        users.push_back(user);
        write_users();
    }
    else
    {
        cout << "Invalid choice\n";
        return -1;
    }
    return choice_m1;
}

int menu_two()
{
    int range = -1;
    cout << "Menu:\n";
    cout << '\t' << "1) Print questions to me\n";
    cout << '\t' << "2) Print questions from me\n";
    cout << '\t' << "3) Answer questions\n";
    cout << '\t' << "4) Delete question\n";
    cout << '\t' << "5) Ask question\n";
    cout << '\t' << "6) List system users\n";
    cout << '\t' << "7) List the user feed\n";
    cout << '\t' << "8) Log out\n";
    cout << "Enter a number from the range [1:8]: ";
    cin >> range;
    if (range < 1 || range > 8)
    {
        cout << "Invalid choice\n";
        range = -1;
    }
    return range;
}

void ask_question()
{
    cout << "Enter user id or -1 to cancel: ";
    cin >> user.id;
    if (user.id == -1)
    {
        cout << "Cancelled.\n";
        return;
    }

    if (!user.allow_anyonmous)
    {
        cout << "Note: Anonymous questions are not allowed for this user.\n";
    }
    else
    {
        cout << "Anonymous questions are allowed for this user\n";
    }

    cout << "For thread question, enter question id or -1 to add new question: ";
    cin >> q.id_ques;

    if (q.id_ques == -1)
    {
        cout << "Enter new question id: ";
        cin >> q.id_ques;
        cout << "Enter question text: ";
        cin.ignore(); // To ignore any trailing newline character
        getline(cin, q.qu);
        questions.push_back(q);
    }
    else
    {
        cout << "Enter thread text: ";
        cin.ignore();
        getline(cin, q.thread);
        questions.push_back(q);
    }
    write_questions();
}


void list_system_users()
{
    cout << "List of registered users:\n";
    for (const auto& user : users)
    {
        cout << "Name: "<< user.name << ", ID : " << user.id << '\n';
    }
}


void delete_question()
{
    cout << "Enter question id or -1 to cancel: ";
    int id_delete;
    cin >> id_delete;
    if (id_delete == -1)
    {
        cout << "Cancelled successfully\n";
        return;
    }

    auto it = remove_if(questions.begin(), questions.end(), [id_delete](const question& q) { return q.id_ques == id_delete; });
    if (it != questions.end())
    {
        questions.erase(it, questions.end());
        cout << "The Question deleted successfully\n";
    }
    else
    {
        cout << "This question is not in our system\n";
    }
    write_questions();
}

void answer_question()
{
    cout << "Enter question id or -1 to cancel: ";
    int q_id;
    cin >> q_id;
    if (q_id == -1)
    {
        cout << "Cancelled\n";
        return;
    }

    for (auto& q : questions)
    {
        if (q_id == q.id_ques)
        {
            cout << "Question ID (" << q_id << ") from user ID (" << q.user_id << "): " << q.qu << '\n';
            if (q.ans.empty())
            {
                cout << "Answer: ";
                cin.ignore();
                getline(cin, q.ans);
            }

            else
            {
                cout << "Warning: The question has already been answered. Update it if needed:\n";
                cin.ignore();
                getline(cin, q.ans);
            }

            break;
        }
    }
    write_questions();
}

void print_questions_to_me()
{

    for (const auto& quest : questions)
    {
        if (user.allow_anyonmous )
        {
            cout << "Question ID: " << quest.id_ques << ", from user ID: " << user.id << '\n';
            cout << "Question: " << quest.qu << '\n';
            cout << "Answer: " << (quest.ans.empty() ? "No answer yet" : quest.ans) << '\n';
            cout << "Thread: " << (quest.thread.empty() ? "No thread" : quest.thread) << '\n';
        }
        else
        {
            cout << "Question ID: " << quest.id_ques << ", from user ID: (anonymous)\n";
            cout << "Question: " << quest.qu << '\n';
            cout << "Answer: " << (quest.ans.empty() ? "No answer yet" : quest.ans) << '\n';
            cout << "Thread: " << (quest.thread.empty() ? "No thread" : quest.thread) << '\n';
        }
    }
    write_questions();
}


void print_questions_from_me()
{
        //id which he has logged in with ot signed up with

        if (q.user_id == user.id)
        {
            cout << "Question ID: " << q.id_ques << ", from user ID: " << user.id<< '\n';
            cout << "Question: " << q.qu << '\n';
            cout << "Answer: " << (q.ans.empty() ? "Not answered yet" : q.ans) << '\n';
            cout << "Thread: " << (q.thread.empty() ? "No thread" : q.thread) << '\n';
        }

    write_questions();
}

void list_feed()
{
    cout << "User Feed:\n";
    for (const auto& question_feed : questions)
    {
        cout << "Question ID: " << question_feed.id_ques << ", User ID: " << user.id << '\n';
        cout << "Question: " << question_feed.qu << '\n';
        cout << "Answer: " << (question_feed.ans.empty() ? "No answer yet" : question_feed.ans) << '\n';
        cout << "Thread: " << (question_feed.thread.empty() ? "No thread" : question_feed.thread) << '\n';
        cout << "---------------------------\n";
    }
    write_questions();
}

void ask_me()
{
    int choice_menu_one = menu_one();
    if (choice_menu_one == -1)
    {
        return;
    }
    while (true)
    {

        int choice_menu_two = menu_two();
        switch (choice_menu_two)
        {
        case 1:
            print_questions_to_me();
            break;
        case 2:
            print_questions_from_me();
            break;
        case 3:
            answer_question();
            break;
        case 4:
            delete_question();
            break;
        case 5:
            ask_question();
            break;

       case 6:
            list_system_users();
            break;

        case 7:
            list_feed();
            break;
        case 8:
            cout << "Logged out.\n";
            return;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}

int main()
{
    read_users();
    read_questions();
    ask_me();
    return 0;
}
