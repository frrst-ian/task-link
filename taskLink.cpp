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

TaskNode *addTask(TaskNode *head, string task_name, int task_priority) {
  TaskNode *newTask = new TaskNode(task_name, task_priority);
  if (task_priority == 1) {
    newTask->next = head;
    if (head != nullptr) {
      head->prev = newTask;
    }
    head = newTask;
    return head;
  } //<5>
  // 1<->3<->4
  TaskNode *curr = head;
  for (int i = 1; i < task_priority - 1 && curr != nullptr; i++) {
    curr = curr->next;
  }

  newTask->next = curr->next;
  newTask->prev = curr;
  curr->next = newTask;
  if (newTask->next != nullptr) {
    newTask->next->prev = newTask;
  }
  return head;
}

TaskNode *exampleTask() {
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
  return head;
}

void printList(TaskNode *head) {
  if (!head)
    return;
  TaskNode *curr = head;
  do {
    cout << curr->taskName << " " << curr->priority << " ";
    curr = curr->next;
  } while (curr != head);
}

int main() {
  TaskNode *head;
  head = exampleTask();
  printList(head);
}
