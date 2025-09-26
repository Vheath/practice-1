#include <cstring>
#include <fstream>
#include <iostream>

const int kAlphabetSize{26};
const int kMaxWordSize{33};
const char* kWordArgument{"--word"};
const char* kFileArgument{"--file"};

char* GetWordFromArgs(int argc, char** argv) {
  for (int i{1}; i < argc; ++i) {
    if (strcmp(argv[i], kWordArgument) == 0) {
      if (i + 1 < argc) {
        return argv[i + 1];
      }
    }
  }

  return nullptr;
}

char* GetFileFromArgs(int argc, char** argv) {
  for (int i{1}; i < argc; ++i) {
    if (strcmp(argv[i], kFileArgument) == 0) {
      if (i + 1 < argc) {
        return argv[i + 1];
      }
    }
  }

  return nullptr;
}

int GetWordSize(const char* word) {
  for (int i{0}; i < kMaxWordSize; ++i) {
    if (word[i] == '\0') return i;
  }

  return 0;
}

void SetLetterMap(bool* map, const char* word, const int wordSize) {
  for (int i{0}; i < kAlphabetSize; ++i) {
    map[i] = false;
  }

  for (int i{0}; i < wordSize; ++i) {
    map[word[i] - 'a'] = true;
  }
}

// Check if map2 contain all letters of map1
bool SubLetterMap(const bool* map1, const bool* map2) {
  for (int i{0}; i < kAlphabetSize; ++i) {
    if (map1[i] && (map1[i] != map2[i])) return false;
  }
  return true;
}

int GetNumberOfMatchesInFile(char* promptWord, char* fileName) {
  std::ifstream fileInput{fileName};
  if (!fileInput) {
    std::cerr << "Error, wrong file name given\n";
    return 3;
  }

  bool promptLetterMap[kAlphabetSize];
  SetLetterMap(promptLetterMap, promptWord, GetWordSize(promptWord));
  int counter{0};

  while (!fileInput.eof()) {
    char tempWord[kMaxWordSize];
    fileInput.getline(tempWord, kMaxWordSize, ' ');
    bool tempLetterMap[kAlphabetSize];
    SetLetterMap(tempLetterMap, tempWord, GetWordSize(tempWord));
    if (SubLetterMap(promptLetterMap, tempLetterMap)) {
      ++counter;
    }
  }
  return counter;
}

int main(int argc, char** argv) {
  if (argc < 5) {
    std::cerr << "Error: program expected more arguments\n Expected format: "
              << "./neatcounter " << kWordArgument << " <word> "
              << kFileArgument << " <file>\n";
    return 1;
  }

  char* userWord{GetWordFromArgs(argc, argv)};
  char* userFile{GetFileFromArgs(argc, argv)};

  if ((userWord == nullptr) || (userFile == nullptr)) {
    std::cerr << "Error, wrong arguments\n Expected format: "
              << "./neatcounter " << kWordArgument << " <word> "
              << kFileArgument << " <file>\n";
    return 2;
  }
  std::cout << GetNumberOfMatchesInFile(userWord, userFile);
}
