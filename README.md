# 📝 C++ To-Do List Application

A simple yet functional **To-Do List application** built in C++ during the early stages of my programming journey. While modest in scope, this project was a major milestone—it taught me the foundations of object-oriented programming, data handling, and user interaction within a console-based environment.

## 🚀 About the Project

This project was one of the very first assignments I completed using C++. My goal was to create a utility that could help users manage tasks with priority levels, due dates, and categories—all from the terminal.

It might not look like much, but for me, it marked the moment I started turning logic into structured code and building applications from scratch.

## 🎮 Features

- ✅ Add new tasks with descriptions, due dates, categories, and priority levels
- 📋 Mark tasks as completed
- 🔍 View tasks filtered by **category** or **priority**
- 🗑️ Delete tasks by index
- 💾 Save tasks to a file (`tasks.txt`) and load them later
- 📅 Auto-fill current date for due dates left blank
- 🧹 Clean console UI using `iomanip` for alignment and readability

## 💡 Core Concepts Used

- Classes and Object-Oriented Programming (`Task`, `ToDoList`)
- Enums and string conversions (`Priority`)
- File I/O (save/load tasks with custom serialization)
- Vectors and maps for task storage and organization
- Time/date handling with `ctime` and `stringstream`
- Basic stateful UI with a menu-driven interface

## 📁 File Structure

```bash
.
├── todo.cpp         # Main application source code
└── tasks.txt        # Saved task data (generated at runtime)
```

## 🛠️ How It Works

1. **Add a Task**: Enter a task description, due date (or leave blank for today's date), category, and priority.
2. **View Tasks**: Display all tasks or filter them by category or priority.
3. **Complete Tasks**: Mark specific tasks as done.
4. **Delete Tasks**: Remove unwanted or completed tasks from the list.
5. **Save/Load**: Store your tasks for later use in `tasks.txt`.

## 🖼️ Example Output

```
To-Do List Application
1. Add Task
2. View All Tasks
3. View Tasks by Category
4. View Tasks by Priority
5. Mark Task as Completed
6. Delete Task
7. Save Tasks to File
8. Load Tasks from File
9. Exit
Enter your choice:
```

---

## 🧠 Reflections

This project laid the foundation for everything I've built since. It taught me that even simple tools require thoughtful structure, data handling, and user experience design. It may be small, but it represents a big step in my growth as a developer.

---

## 🧪 To Run This Project

1. Clone the repo or download `todo.cpp`
2. Compile using a C++ compiler:
   ```bash
   g++ todo.cpp -o todo
   ```
3. Run the application:
   ```bash
   ./todo
   ```
