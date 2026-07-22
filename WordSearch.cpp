
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;



class dictionary {
private:
    vector<string> words;

public:

void readDict(const string& filename);

friend ostream& operator<<(ostream& outputstring, const dictionary& d);
};

void dictionary::readDict(const string& filename) {
    ifstream dict(filename);
    string word;
    if (!dict) {
        //error handling if the file cannot be opened
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    while (getline(dict, word)) {
        if (!word.empty() && word.back() == '\r') {
            word.pop_back(); // Remove carriage return if present
        }
        //checks if the word is at least 5 characters long before adding it to the vector
        if (word.length() >= 5) {
            //adds the word to the vector of strings for the dictionary to be parsed.
            words.push_back(word);
        }
    }
}
//overloaded operator to print the dictionary words
ostream& operator<<(ostream& outputstring, const dictionary& d) {
    for (const auto& word : d.words) {
        outputstring << word << "\n";
    }
    return outputstring;
}

int main() {
//must create a dictionary class before using readDict!
dictionary d;
d.readDict("dictionary.txt");

cout << d;

return 0;
}
