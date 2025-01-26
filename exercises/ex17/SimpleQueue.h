// Elaine Zhong, ezhong4@uw.edu

#ifndef _SIMPLEQUEUE_H_
#define _SIMPLEQUEUE_H_

#include <string>

using std::string;

// A simple FIFO queue class that stores strings
// Your task: Make SimpleQueue thread safe!
class SimpleQueue {
 public:
  SimpleQueue();

  ~SimpleQueue();

  // Enqueues the given item
  void Enqueue(string item);

  // Dequeues the item at the front of the queue
  // and stores it at the location pointed to by result.
  // Returns true if there was an item to return and
  // false if the queue was empty.
  bool Dequeue(string *result);

  // Returns the size of the queue
  int Size() const;

  // Returns true if the queue if empty, false otherwise
  bool IsEmpty() const;

 private:
  mutable pthread_mutex_t queue_lock;
  struct node {
    string item;
    node *next;
  } *front, *end;
  int size;
};  // class SimpleQueue

#endif  // _SIMPLEQUEUE_H_