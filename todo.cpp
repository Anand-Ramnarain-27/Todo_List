#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

enum class Priority { LOW, MEDIUM, HIGH };

string priorityToString(Priority p) {
    switch(p) {
        case Priority::LOW: return "Low";
        case Priority::MEDIUM: return "Medium";
        case Priority::HIGH: return "High";
        default: return "Unknown";
    }
}

Priority stringToPriority(const string& s) {
    if (s == "Low") return Priority::LOW;
    if (s == "Medium") return Priority::MEDIUM;
    if (s == "High") return Priority::HIGH;
    return Priority::LOW;
}

class Task {
private:
    string description;
    string dueDate;
    string category;
    Priority priority;
    bool completed;

public:
    Task(const string& desc, const string& date, const string& cat, Priority prio)
        : description(desc), dueDate(date), category(cat), priority(prio), completed(false) {}

    string getDescription() const { return description; }
    string getDueDate() const { return dueDate; }
    string getCategory() const { return category; }
    Priority getPriority() const { return priority; }
    bool isCompleted() const { return completed; }

    void setDescription(const string& desc) { description = desc; }
    void setDueDate(const string& date) { dueDate = date; }
    void setCategory(const string& cat) { category = cat; }
    void setPriority(Priority prio) { priority = prio; }
    void setCompleted(bool comp) { completed = comp; }

    void display() const {
        cout << (completed ? "[X] " : "[ ] ");
        cout << left << setw(40) << description.substr(0, 40);
        cout << setw(15) << dueDate;
        cout << setw(15) << category;
        cout << setw(10) << priorityToString(priority);
        cout << endl;
    }

    string serialize() const {
        return description + "|" + dueDate + "|" + category + "|" + 
               priorityToString(priority) + "|" + (completed ? "1" : "0");
    }

    static Task deserialize(const string& data) {
        stringstream ss(data);
        string part;
        vector<string> parts;
        
        while (getline(ss, part, '|')) {
            parts.push_back(part);
        }
        
        if (parts.size() != 5) {
            throw invalid_argument("Invalid task data format");
        }
        
        Task task(parts[0], parts[1], parts[2], stringToPriority(parts[3]));
        task.setCompleted(parts[4] == "1");
        return task;
    }
};

class ToDoList {
private:
    vector<Task> tasks;
    map<string, vector<Task*>> categories;

    void updateCategories() {
        categories.clear();
        for (auto& task : tasks) {
            categories[task.getCategory()].push_back(&task);
        }
    }

public:
    void addTask(const Task& task) {
        tasks.push_back(task);
        updateCategories();
    }

    void completeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].setCompleted(true);
        }
    }

    void deleteTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
            updateCategories();
        }
    }

    void displayAll() const {
        cout << left << setw(5) << "#";
        cout << setw(42) << "Description";
        cout << setw(15) << "Due Date";
        cout << setw(15) << "Category";
        cout << setw(10) << "Priority";
        cout << endl;
        cout << string(87, '-') << endl;

        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << left << setw(5) << i + 1;
            tasks[i].display();
        }
    }

    void displayByCategory(const string& category) const {
        auto it = categories.find(category);
        if (it != categories.end()) {
            cout << "Tasks in category '" << category << "':" << endl;
            for (const auto& task : it->second) {
                task->display();
            }
        } else {
            cout << "No tasks found in category '" << category << "'" << endl;
        }
    }

    void displayByPriority(Priority priority) const {
        cout << "Tasks with priority '" << priorityToString(priority) << "':" << endl;
        for (const auto& task : tasks) {
            if (task.getPriority() == priority) {
                task.display();
            }
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& task : tasks) {
                file << task.serialize() << endl;
            }
            file.close();
            cout << "Tasks saved to " << filename << endl;
        } else {
            cerr << "Unable to open file for writing: " << filename << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            tasks.clear();
            string line;
            while (getline(file, line)) {
                try {
                    tasks.push_back(Task::deserialize(line));
                } catch (const invalid_argument& e) {
                    cerr << "Error parsing task: " << e.what() << endl;
                }
            }
            file.close();
            updateCategories();
            cout << "Tasks loaded from " << filename << endl;
        } else {
            cerr << "Unable to open file for reading: " << filename << endl;
        }
    }

    size_t size() const {
        return tasks.size();
    }
};

void displayMenu() {
    cout << "\nTo-Do List Application\n";
    cout << "1. Add Task\n";
    cout << "2. View All Tasks\n";
    cout << "3. View Tasks by Category\n";
    cout << "4. View Tasks by Priority\n";
    cout << "5. Mark Task as Completed\n";
    cout << "6. Delete Task\n";
    cout << "7. Save Tasks to File\n";
    cout << "8. Load Tasks from File\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

string getCurrentDate() {
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-" 
       << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
       << setw(2) << setfill('0') << ltm->tm_mday;
    return ss.str();
}

int main() {
    ToDoList todoList;
    string filename = "tasks.txt";
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string description, dueDate, category, priorityStr;
                Priority priority;
                
                cout << "Enter task description: ";
                getline(cin, description);
                
                cout << "Enter due date (YYYY-MM-DD, leave blank for today): ";
                getline(cin, dueDate);
                if (dueDate.empty()) {
                    dueDate = getCurrentDate();
                }
                
                cout << "Enter category: ";
                getline(cin, category);
                
                cout << "Enter priority (Low/Medium/High): ";
                getline(cin, priorityStr);
                priority = stringToPriority(priorityStr);
                
                Task newTask(description, dueDate, category, priority);
                todoList.addTask(newTask);
                cout << "Task added successfully!\n";
                break;
            }
            case 2:
                if (todoList.size() > 0) {
                    todoList.displayAll();
                } else {
                    cout << "No tasks available.\n";
                }
                break;
            case 3: {
                string category;
                cout << "Enter category to view: ";
                getline(cin, category);
                todoList.displayByCategory(category);
                break;
            }
            case 4: {
                string priorityStr;
                cout << "Enter priority to view (Low/Medium/High): ";
                getline(cin, priorityStr);
                todoList.displayByPriority(stringToPriority(priorityStr));
                break;
            }
            case 5: {
                int index;
                if (todoList.size() > 0) {
                    todoList.displayAll();
                    cout << "Enter task number to mark as completed: ";
                    cin >> index;
                    if (index > 0 && index <= todoList.size()) {
                        todoList.completeTask(index - 1);
                        cout << "Task marked as completed.\n";
                    } else {
                        cout << "Invalid task number.\n";
                    }
                } else {
                    cout << "No tasks available.\n";
                }
                break;
            }
            case 6: {
                int index;
                if (todoList.size() > 0) {
                    todoList.displayAll();
                    cout << "Enter task number to delete: ";
                    cin >> index;
                    if (index > 0 && index <= todoList.size()) {
                        todoList.deleteTask(index - 1);
                        cout << "Task deleted.\n";
                    } else {
                        cout << "Invalid task number.\n";
                    }
                } else {
                    cout << "No tasks available.\n";
                }
                break;
            }
            case 7:
                todoList.saveToFile(filename);
                break;
            case 8:
                todoList.loadFromFile(filename);
                break;
            case 9:
                cout << "Exiting application.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}