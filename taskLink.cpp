#include <iostream>

using namespace std;

// ANSI escape codes for text colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

// Task node 
struct TaskNode {
  string taskName;
  int priority;
  TaskNode *next, *prev;
  // Task constructor
  TaskNode(string new_task, int new_priority) {
    taskName = new_task;
    priority = new_priority;
    prev = next = nullptr;
  }
};

// Print list function
void printList(TaskNode *head) {
  if (!head) {
    return;
  }
  TaskNode *curr = head;
  int count = 1;
  cout << MAGENTA << "=============Task List=============\n" << RESET;
  cout << YELLOW << " ID"
       << "        Priority"
       << "       Task Name\n"
       << RESET;
  do {
    cout << " " << CYAN << count++ << RESET << "            " << curr->priority
         << BLUE << "           " << curr->taskName << RESET << '\n';
    curr = curr->next;

    if (curr == nullptr)
      return;

  } while (curr != head);
  cout << '\n';
}

// Function for adding task
TaskNode *addTask(TaskNode *head, string task_name, int task_priority) {
  TaskNode *newTask = new TaskNode(task_name, task_priority);
  if (!head || task_priority >= head->priority) {
    newTask->next = head;
    if (head)
      head->prev = newTask;
    return newTask;
  }
  TaskNode *curr = head;
  while (curr->next && curr->next->priority >= task_priority) {
    curr = curr->next;
  }
  newTask->next = curr->next;
  newTask->prev = curr;
  if (curr->next)
    curr->next->prev = newTask;
  curr->next = newTask;
  return head;
}

// Function for deleting task
TaskNode *deleteTask(TaskNode *head, int pos) {
  if (pos < 1) {
    cout << "Pos out of bounds";
    return head;
  }

  TaskNode *curr = head;
  for (int i = 1; i < pos && curr != nullptr; i++) {
    curr = curr->next;
  }
  if (curr == nullptr) {
    cout << RED << "Task empty\n" << RESET;
    return head;
  }

  if (curr->prev != nullptr) {
    curr->prev->next = curr->next;
  }

  if (curr->next != nullptr) {
    curr->next->prev = curr->prev;
  }

  if (head == curr) {
    head = curr->next;
  }
  delete curr;
  return head;
}

 // Example task
void exampleTask() {
  TaskNode *head = new TaskNode("Shopping", 3),
           *firsTask = new TaskNode("Gym", 2),
           *secondTask = new TaskNode("Coding", 1),
           *thirdTask = new TaskNode("Gaming", 1);
  head->next = firsTask;
  firsTask->next = secondTask;
  secondTask->next = thirdTask;

  firsTask->prev = head;
  secondTask->prev = firsTask;
  thirdTask->prev = secondTask;
  thirdTask->next = head;
  head->prev = thirdTask;
  return printList(head);
}

// Main function
int main() {
  TaskNode *head = nullptr;

  // ASCII art title
  cout << BLUE
       << "######     ##      ####    ##  ##            ##        ####    ##  "
          "##   ##  ##\n"
       << "  "
       << "##      ####    ##  ##   ## ##             ##         ##     ### ## "
          "  ## ##\n"
       << "  "
       << "##     ##  ##   ##       ####              ##         ##     ###### "
          "  ####\n"
       << "  "
       << "##     ######    ####    ###               ##         ##     ###### "
          "  ###\n"
       << "  "
       << "##     ##  ##       ##   ####              ##         ##     ## ### "
          "  ####\n"
       << "  "
       << "##     ##  ##   ##  ##   ## ##             ##         ##     ##  ## "
          "  ## ##\n"
       << "  "
       << "##     ##  ##    ####    ##  ##            ######    ####    ##  ## "
          "  ##  ##\n\n"
       << RESET;

  // User interaction
  while (true) {
    cout << GREEN
         << "=================================================================="
            "===============\n"
         << RESET
         << " To get started, please enter one of the numbers below "
            "(e.g 1 <Enter> to "
            "add task)\n"
         << " [1] - Add task\n"
         << " [2] - View tasks\n"
         << " [3] - Delete task\n"
         << " [4] - Load an example task list\n"
         << " [5] - Help\n"
         << " [0] - Exit the program\n"
         << GREEN
         << "=================================================================="
            "===============\n"
         << RESET << GREEN << "Enter your choice: " << RESET;
    int choice;
    string taskName;
    int priority, id;
    char userInput;
    cin >> choice;
    if (cin.fail()) {
      cout << "Invalid input. Try again..." << '\n';
      exit(1);
    }
    switch (choice) {
    case 1:
      do {
        cout << "Enter task name: ";
        cin >> taskName;
        cout << "Enter task priority(3 - High , 2 - Medium , 3 - Low): ";

        cin >> priority;
        if (priority < 1 || priority > 3) {
          cout << RED << "PRIORITY IS INVALID!. EXITING THE PROGRAM...\n"
               << RESET;
          return 1;
        }

        head = addTask(head, taskName, priority);
        cout << BLUE << "Task added\n" << RESET;
        printList(head);
        cout << "Do you want to add another task?(y/n): ";
        cin >> userInput;
      } while (userInput == 'y' || userInput == 'Y');
      break;
    case 2:
      do {
        if (!head) {
          cout << RED << "Task Empty!\n" << RESET;
        }
        printList(head);

        cout << "Do you want to go back to the menu? (y/n): ";
        cin >> userInput;
        if (userInput == 'n' || userInput == 'N') {
          cout << "Exiting the program...Thank you!\n";
          return 1;
        }
      } while (userInput == 'n' || userInput == 'N');
      break;
    case 3:
      do {
        cout << "Enter task ID: ";
        cin >> id;
        if (cin.fail()) {
          cout << "Invalid input. Exiting program..." << '\n';
          return 1;
        }
        head = deleteTask(head, id);
        printList(head);
        cout << "Do you want to delete another task?(y/n): ";
        cin >> userInput;
      } while (userInput == 'y' || userInput == 'Y');
      break;
    case 4:
      do {
        exampleTask();
        printList(head);
        cout << "Do you want to go back to the menu? (y/n): ";
        cin >> userInput;
        if (userInput == 'n' || userInput == 'N') {
          cout << "Exiting the program...\n";

          return 1;
        }
      } while (userInput == 'n' || userInput == 'N');

      break;
    case 5:
      do {
        cout << "To add task enter 1 <Enter>\n";
        cout << "To view task enter 2 <Enter>\n";
        cout << "To delete a task enter 3 <Enter>\n";
        cout << "To exit the program enter 0 <Enter>\n";
        cout << "Do you want to go back to the menu? (y/n): ";
        cin >> userInput;
        if (userInput == 'n' || userInput == 'N') {
          cout << "Exiting the program...Thank you!\n";
          return 1;
        }
      } while (userInput == 'n' || userInput == 'N');

      break;
    case 0:
      cout << "Exiting the program. Thank you!\n";
      return 1;
      break;
    default:
      cout << RED
           << "Your choice is Invalid! Please enter a valid number and try "
              "again.\n"
           << RESET;
      break;
    }
  }
}
