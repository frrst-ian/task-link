#include <iostream>
// Task Scheduling: Circular linked lists can be used to implement task
// scheduling algorithms,
//  where each node in the list represents a task and its priority.
//   The “next” pointer can point to the next task in the queue, with the end of
//   the queue pointing back to the beginning to create a circular structure.
//  This allows for a continuous loop of task scheduling, where tasks are added
//  and removed from the queue based on their priority.
using namespace std;

// ANSI escape codes for text colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\03[36m"

struct TaskNode {
  string taskName;
  int priority;
  TaskNode *next, *prev;
  TaskNode(string new_task, int new_priority) {
    taskName = new_task;
    priority = new_priority;
    prev = next = nullptr;
  }
};

void printList(TaskNode *head) {
  if (!head) {
    return;
  }
  TaskNode *curr = head;
  int count = 1;
  do {
    cout << count++ << " " << curr->taskName << " " << curr->priority << " "
         << '\n';
    curr = curr->next;

    if (curr == nullptr)
      return;

  } while (curr != head);
  cout << '\n';
}

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

TaskNode *deleteTask(TaskNode *head, int pos) {
  if (pos < 1) {
    cout << "Pos out of bounds";
    return head;
  }
  // 1-2-3
  TaskNode *curr = head;
  for (int i = 1; i < pos && curr != nullptr; i++) {
    curr = curr->next;
  }
  if (curr == nullptr) {
    cout << "Task empty";
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

int main() {
  TaskNode *head = nullptr;

  while (true) {
    cout << GREEN
         << "To get started, please enter one of the numbers below "
            "(e.g 1 <Enter> to "
            "add task)\n"
         << "[1] - Add task\n"
         << "[2] - View task\n"
         << "[3] - Delete task\n"
         << "[4] - Load an example task\n"
         << "[5] - Help\n"
         << "[0] - Exit the program\n"
         << "Enter your choice: " << RESET;
    int choice;
    string taskName;
    int priority, id;
    char userInput;
    cin >> choice;

    switch (choice) {
    case 1:
      do {
        cout << "Enter task name: ";
        cin >> taskName;
        cout << "Enter priority: ";

        cin >> priority;

        head = addTask(head, taskName, priority);
        printList(head);
        cout << "Do you want to add another task?(y/n): ";
        cin >> userInput;
      } while (userInput == 'y' || userInput == 'Y');
      break;
    case 2:
      if (!head) {
        cout << "Task Empty\n";
      }
      printList(head);
      break;
    case 3:
      cout << "Enter task ID: ";
      cin >> id;
      head = deleteTask(head, id);
      printList(head);
      break;
    case 4:
      exampleTask();
      printList(head);
      break;
    case 5:
      cout << "To add task enter 1 <Enter>\n";
      cout << "To view task enter 2 <Enter>\n";
      cout << "To delete a task enter 3 <Enter>\n";
      cout << "To exit the program enter 0 <Enter>\n";
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
