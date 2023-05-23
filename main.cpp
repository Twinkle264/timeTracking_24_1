#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

struct Task {
    string name;
    time_t start_time;
    time_t end_time;
};

vector<Task> tasks;
Task current_task;

bool task_active = false;

void beginTask(string &name) {
    if (task_active) {
        current_task.end_time = time(nullptr);
        tasks.push_back(current_task);
        task_active = false;
    }

    current_task.name = name;
    current_task.start_time = time(nullptr);
    current_task.end_time = 0;
    task_active = true;
}

void endTask() {
    if (task_active) {
        current_task.end_time = time(nullptr);
        tasks.push_back(current_task);
        task_active = false;
    }
}

void statusTask() {
    cout << "Completed tasks and time spent on them:" << endl;
    cout << endl;

    for (Task &task: tasks) {
        time_t duration = task.end_time - task.start_time;
        int hours = duration / 3600;
        int minutes = (duration % 3600) / 60;
        int seconds = duration % 60;

        cout << "\tTask: " << task.name << endl;
        cout << "\tTime: " << setfill('0') << setw(2) << hours << ":" << setw(2) << minutes << ":"
                << setw(2) << seconds << endl;
        cout << endl;
    }

    if (task_active) {
        cout << "\tCurrent task: " << current_task.name << endl;
    }
    cout << endl;
}

int main() {
    string command;

    while (true) {
        cout << "Enter the command (begin, end, status, exit): ";
        getline(cin, command);

        if (command == "begin") {
            string task_name;
            do {
                cout << "Enter the name of task:";
                getline(cin, task_name);
            } while (task_name.empty());
            beginTask(task_name);
        } else if (command == "end") {
            endTask();
        } else if (command == "status") {
            statusTask();
        } else if (command == "exit") {
            break;
        } else {
            cerr << "ERROR: Wrong command. Please, try again." << endl;
        }
    }
    return 0;
}
