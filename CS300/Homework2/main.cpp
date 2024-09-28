#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "avlTree.cpp"

using namespace std;

int main() {
    AVLSearchTree<string, WordItem *> myTree;

    vector<string> fileNames;
    // Read the input files and create the tree
    int numOfFiles;
    cout << "Enter number of input files: ";
    cin >> numOfFiles;
    for (int i = 0; i < numOfFiles; ++i) {
        string fileName;
        cout << "Enter " << i + 1 << ". file name: ";
        cin >> fileName;
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "File cannot be opened!" << endl;
            return 1;
        }
        fileNames.push_back(fileName);
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string word;
            bool wordIsOk; //for checking punctuation and numbers
            while ((ss >> word)) {
                wordIsOk = true;
                for(int j = 0; j < word.size(); j++){
                    if(ispunct(word[j]) || isdigit(word[j])){
                        wordIsOk = false; //don't include the word in the tree
                        word.erase(j--, 1);
                    }
                    else{
                        word[j] = (char)tolower(word[j]);
                    }
                }
                if(!word.empty() && wordIsOk){
                    auto *documentItem = new DocumentItem(fileName);
                    auto *wordItem = new WordItem(word, documentItem);
                    myTree.insert(word, wordItem);
                }

            }

        }
    }
    cout << endl;
    cin.clear();
    cin.ignore();

    // Read the queries and print the results
    string query;
    while(true){ //until the user enters "endofinput"
        cout << "Enter queried words in one line: ";
        getline(cin, query);
        for(char & i : query){
            i = (char)tolower(i);
        }
        if(query == "endofinput"){ //if the user enters "endofinput", break the loop
            break;
        }
        stringstream ss(query);
        string word;
        int count = 0;
        bool remove = false;
        int wordCount = 0;
        vector<string> wordDetails(numOfFiles, ""); //Vector that puts the string of the word in the corresponding index of the file
        vector<int>wordCountVector(numOfFiles, 0); //Vector that puts the count of the word in the corresponding index of the file
        while(ss >> word){
            wordCount++;
            if(count == 0 && word == "remove"){ //Assuming that the user will enter only one word after the remove command, example: REMOVE sabanci
                //removing operation
                ss >> word;
                remove = true;
                myTree.remove(word);
                cout << word << " has been REMOVED" << endl;
                break;
            }
            count++;
            if(myTree.find(word) != "!"){
                WordItem *tempNode =  myTree.getDetails(word);
                for(int k = 0; k < fileNames.size(); k++){
                    for(int i = 0; i < tempNode->details.size(); i++){
                        if(tempNode->details[i].documentName == fileNames[k]){
                            wordCountVector[k]++;
                            if(wordDetails[k].empty())
                                wordDetails[k] += "in Document " + tempNode->details[i].documentName + ", " + tempNode->word + " found " + to_string(tempNode->details[i].count) + " times";
                            else
                                wordDetails[k] += ", " + tempNode->word + " found " + to_string(tempNode->details[i].count) + " times";
                        }
                    }
                }
            }
        }
        int totalCountOfEmpty = 0;
        for(int i = 0; i < wordDetails.size(); i++){
           if(!wordDetails[i].empty() && wordCountVector[i] == wordCount)
               cout << wordDetails[i] << "." << endl;
           else
               totalCountOfEmpty++;
        }

        if(totalCountOfEmpty == numOfFiles && !remove)
            cout << "No document contains the given query" << endl;
        cout << endl;
    }
    return 0;
}
