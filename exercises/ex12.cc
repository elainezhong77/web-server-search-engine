// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Must enter exactly 2 arguments" << endl;
    exit(EXIT_FAILURE);
  }

  string curr_file = argv[1];
  ifstream file(curr_file.c_str());

  if (!file.is_open()) {
    cout << "Could not open the file " << curr_file << endl;
    exit(EXIT_FAILURE);
  }

  // initialize the current word being read
  string word;
  // initialize a map that stores the word count (value) for each word (key)
  map<string, int> word_counts;

  while (file >> word) {
    if (word_counts.count(word)) {
      word_counts[word]++;
    } else {
      word_counts.insert(pair<string, int>(word, 1));
    }
  }
  file.close();

  for (pair<string, int> pair : word_counts) {
    cout << pair.first << " " << pair.second << endl;
  }

  return EXIT_SUCCESS;
}
