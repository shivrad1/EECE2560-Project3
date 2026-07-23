
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
    
    void selectionSort();
    int binarySearch(const string& target) const;

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

//Sorts words in dictionary alphabetically using selection sort
void dictionary::selectionSort() {
    int min;
    
    //Loop through all the positions in the vector except the last
    for (int i = 0; i < words.size() - 1; i++){
        
        //Assume that the current word is the smallest
        min = i;
        
        //Search the remaining words for a smaller word
        for (int j = i + 1; j < words.size(); j++){
            if (words[j] < words[min]){
                //Update the index of the smallest word found
                min = j;
            }
        }
        
        //Swap current word for the smallest word found
        swap(words[i],words[min]);
    }
}


//Performs a binary search on the sorted dictionary
int dictionary::binarySearch(const string& target) const {
    //Initalize the search range
    int first = 0;
    int last = words.size() - 1;
    
    //Search while within the range
    while (first <= last) {
        
        //Find middle index of the current search range
        int mid = (first + last) / 2;
        string midValue = words[mid];
        
        //Check if target word matches search word
        if (target == midValue) {
            return mid;
        }
        
        //If target word comes before the middle word search the left half
        else if (target < midValue) {
            last = mid - 1;
        }
        
        //If target word comes after the middle word search the right half
        else {
            first = mid + 1;
        }
    }
    
    //Returns -1 if word is not found in the dictionary
    return -1;
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
    
    d.selectionSort();
    
    cout << d;
    
    string word;
    
    cout << "Enter word to search: ";
    cin >> word;
    
    if (d.binarySearch(word) != -1)
        cout << word << " was found";
    else
        cout << word << " was not found";

    return 0;
}
