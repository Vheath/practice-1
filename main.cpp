#include <cstring>
#include <fstream>
#include <iostream>

const int kAlphabetSize{26};
const int kMaxWordSize{33};

int GetWordSize(char* word) {
  for (int i{0};; ++i)
    if (word[i] == '\0') return i;
}

void SetLetterMap(bool* map, char* word, int wordSize) {
  for (int i{0}; i < kAlphabetSize; ++i) map[i] = false;
  for (int i{0}; i < wordSize; ++i) {
    map[word[i] - 'a'] = true;
  }
}

// Check if map2 contain all words of map1
bool SubLetterMap(bool* map1, bool* map2) {
  for (int i = 0; i < kAlphabetSize; ++i) {
    if (map1[i] && (map1[i] != map2[i])) return false;
  }
  return true;
}

int main(int argc, char** argv) {
  const char* kWordArgument{"--word"};
  const char* kFileArgument{"--file"};
  if (argc < 5) {
    std::cout << "Error: program expected more arguments\n Expected format: "
                 "./neatcounter "
              << kWordArgument << " <word> " << kFileArgument << " <file>\n";
    return 3;
  }
  char *userWord, *userFile;

  bool wordGiven = false, fileGiven = false;
  for (int i{1}; i < argc; ++i) {
    if (strcmp(argv[i], "--word") == 0) {
      if (i + 1 < argc) {
        userWord = argv[i + 1];
        wordGiven = true;
      }
    }
    if (strcmp(argv[i], "--file") == 0) {
      if (i + 1 < argc) {
        userFile = argv[i + 1];
        fileGiven = true;
      }
    }
  }

  if (!fileGiven || !wordGiven) {
    std::cout << "Error, wrong arguments\n Expected format: "
                 "./neatcounter "
              << kWordArgument << " <word> " << kFileArgument << " <file>\n";
    return 1;
  }

  bool promptLetterMap[kAlphabetSize];
  SetLetterMap(promptLetterMap, userWord, GetWordSize(userFile));

  std::ifstream fileInput{userFile};
  if (fileInput.fail()) {
    std::cout << "Error, wrong file name given\n";
    return 2;
  }

  int counter{};
  while (!fileInput.eof()) {
    char tempWord[kMaxWordSize];
    fileInput >> tempWord;
    if (fileInput.eof()) break;
    bool tempLetterMap[kAlphabetSize];
    SetLetterMap(tempLetterMap, tempWord, GetWordSize(tempWord));
    if (SubLetterMap(promptLetterMap, tempLetterMap)) {
      ++counter;
    }
  }
  std::cout << counter << '\n';
}
