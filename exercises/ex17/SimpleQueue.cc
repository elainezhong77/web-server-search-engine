// Elaine Zhong, ezhong4@uw.edu

#include "SimpleQueue.h"
#include <pthread.h>

SimpleQueue::SimpleQueue() {
  size = 0;
  front = nullptr;
  end = nullptr;
  //initialize pthread
  pthread_mutex_init(&queue_lock, NULL);
}

SimpleQueue::~SimpleQueue() {
  while (front != nullptr) {
    node *next = front->next;
    delete front;
    front = next;
  }
  // destroy pthread
  pthread_mutex_destroy(&queue_lock);
}

void SimpleQueue::Enqueue(string item) {
  node *new_node = new node();
  new_node->next = nullptr;
  new_node->item = item;
  if (end != nullptr) {
    end->next = new_node;
  } else  {
    front = new_node;
  }
  end = new_node;
  size++;
  pthread_mutex_unlock(&queue_lock);
}

bool SimpleQueue::Dequeue(string *result) {
  if (size == 0) {
    return false;
  }
  *result = front->item;
  node *next = front->next;
  delete front;
  if (end == front) {
    end = front = next;
  } else {
    front = next;
  }
  size--;
  pthread_mutex_unlock(&queue_lock);
  return true;
}

int SimpleQueue::Size() const {
  return size;
}

bool SimpleQueue::IsEmpty() const {
  return size == 0;
}