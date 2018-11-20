#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T> bool contains(vector<T> vec, T t) {
  return find(vec.begin(), vec.end(), t) != vec.end();
}

int main(int argc, char *argv[]) {
  if (argc < 1) {
    cout << "Usage: " << argv[0] << " numPlaintexts" << endl;
    return 1;
  }

  auto num = atoi(argv[1]);
  srand(time(0));

  auto headerFileName = "plaintexts.h";
  cout << "Opening " << headerFileName << endl;
  fstream headerFile{headerFileName, headerFile.trunc | headerFile.out};
  if (!headerFile.is_open()) {
    cout << "failed to open " << headerFileName << endl;
    return 1;
  }
  cout << "Writing preamble" << endl;
  headerFile << "#ifndef PLAINTEXTS_H\n#define PLAINTEXTS_H\n\n";
  headerFile << "char plaintexts[" << num << "] = {\n";

  auto textFileName = "plaintexts.txt";
  cout << "Opening " << textFileName << endl;
  fstream textFile{textFileName, textFile.trunc | textFile.out};
  if (!textFile.is_open()) {
    cout << "failed to open " << textFileName << endl;
    return 1;
  }

  auto randStart = 32;
  auto randEnd = 126;
  vector<char> needEscapes{'\\', '%', '\"'};

  for (int i = 0; i < num; ++i) {
    cout << "Writing plaintext " << i << endl;
    headerFile << "\"";
    // textFile << "\"";

    for (int j = 0; j < 16; ++j) {
      char newRand = (char)(rand() % (randEnd - randStart) + randStart);
      if (contains(needEscapes, newRand))
        headerFile << "\\";
      headerFile << newRand;
      textFile << newRand;
    }

    headerFile << "\",\n";
    textFile << "\n";
  }

  cout << "Writing postamble" << endl;
  headerFile << "}\n#endif";
  return 0;
}
