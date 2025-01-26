// Elaine Zhong, ezhong4@uw.edu

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>
#include <ctime>

#include "SimpleQueue.h"

using std::cout;
using std::endl;
using std::string;
using std::thread;

const int NUM_PIES = 6;                 // # pies created by each producer
static SimpleQueue queue;               // queue of pies
static unsigned int seed = time(NULL);  // initialize random sleep time
static pthread_mutex_t write_lock;      // mutex for cout

// Thread safe print that prints the given str on a line
void thread_safe_print(string str) {
  pthread_mutex_lock(&write_lock);
  // Only one thread can hold the lock at a time, making it safe to
  // use cout. If we didn't lock before using cout, the order of things
  // put into the stream could be mixed up.
  cout << str << endl;
  pthread_mutex_unlock(&write_lock);
}

// Produces NUM_PIES pies of the given type
// You should NOT modify this method at all
void producer(string pie_type) {
  for (int i = 0; i < NUM_PIES; i++) {
    queue.Enqueue(pie_type);
    thread_safe_print(pie_type + " pie ready!");
    int sleep_time = rand_r(&seed) % 500 + 1;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  }
}

// Eats 2 * NUM_PIES pies
// You should NOT modify this method at all
void consumer() {
  for (int i = 0; i < NUM_PIES * 2; i++) {
    bool successful = false;
    string pie_type;
    while (!successful) {
      while (queue.IsEmpty()) {
        // Sleep for a bit and then check again
        int sleep_time = rand_r(&seed) % 800 + 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
      }
      successful = queue.Dequeue(&pie_type);
    }
    thread_safe_print(pie_type + " pie eaten!");
  }
}

// Producer wrapper method
void* producer_wrapper(void* argument) {
  producer(*(reinterpret_cast<string *>(argument)));
  return nullptr;
}

// Consumer wrapped method
void* consumer_wrapper(void* argument) {
  consumer();
  return nullptr;
}

int main(int argc, char **argv) {
    pthread_mutex_init(&write_lock, NULL);
    // Your task: Make the two producers and the single consumer
    // all run concurrently (hint: use pthreads)

    // Array of threads
    pthread_t threads[3];

    // Create thread 1
    string t1 = "Apple";
    if (pthread_create(&threads[0], nullptr, &producer_wrapper, reinterpret_cast<void *>(&t1)) != 0) {
      std::cerr << "pthread1 failed" << std::endl;
      return EXIT_FAILURE;
    }

    // Create thread 2
    string t2 = "Blackberry";
    if (pthread_create(&threads[1], nullptr, &producer_wrapper, reinterpret_cast<void *>(&t2)) != 0) {
      std::cerr << "pthread2 failed" << std::endl;
      return EXIT_FAILURE;
    }

    // Create thread 3
    string t3 = "";
    if (pthread_create(&threads[2], nullptr, &consumer_wrapper, reinterpret_cast<void *>(&t3)) != 0) {
      std::cerr << "pthread3 failed" << std::endl;
      return EXIT_FAILURE;
    }

    // Join the threads
    for (int i = 0; i < 3; i++) {
      if (pthread_join(threads[i], nullptr) != 0) {
        std::cerr << "pthread join failed" << std::endl;
      }
    }

    // Destroy threads
    pthread_mutex_destroy(&write_lock);
    return EXIT_SUCCESS;
}