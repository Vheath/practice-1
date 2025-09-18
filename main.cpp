#include <cstring>
#include <fstream>
#include <iostream>

int GetWordSize(char* word) {
  for (int i{0};; ++i)
    if (word[i] == '\0') return i;
}

void SetLetterMap(bool* map, char* word, int wordSize) {
  for (int i{0}; i < 26; ++i) map[i] = false;
  for (int i{0}; i < wordSize; ++i) {
    map[word[i] - 97] = true;
  }
}

// Check if map2 contain all words of map1
bool SubLetterMap(bool* map1, bool* map2) {
  for (int i = 0; i < 26; ++i) {
    if (map1[i]) {
      if (map2[i])
        continue;
      else
        return false;
    }
  }
  return true;
}

int main(int argc, char** argv) {
  char* word;
  char* file;
  bool wordGiven = false, fileGiven = false;
  if (argc > 1) {
    for (int i{1}; i < argc; ++i) {
      if (strcmp(argv[i], "--word") == 0) {
        if (i + 1 < argc) {
          word = argv[i + 1];
          wordGiven = true;
        }
      }
      if (strcmp(argv[i], "--file") == 0) {
        if (i + 1 < argc) {
          file = argv[i + 1];
          fileGiven = true;
        }
      }
    }
  }

  if (!fileGiven || !wordGiven) {
    std::cout << "Error, wrong arguments\n";
    return 1;
  }

  bool promptLetterMap[26];
  SetLetterMap(promptLetterMap, word, GetWordSize(word));

  std::ifstream fileInput{file};
  if (fileInput.fail()) {
    std::cout << "Error, wrong file name given\n";
    return 2;
  }

  int counter{};
  while (true) {
    char tempWord[33];
    fileInput >> tempWord;
    if (fileInput.eof()) break;
    bool tempLetterMap[26];
    SetLetterMap(tempLetterMap, tempWord, GetWordSize(tempWord));
    if (SubLetterMap(promptLetterMap, tempLetterMap)) {
      ++counter;
    }
  }
  std::cout << counter << '\n';
}
