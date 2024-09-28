#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "BinarySearchTree.cpp"
#include "HashtableProbing.cpp"


using namespace std;
int main() {

    BinarySearchTree<string, WordItem *> myTree;
    HashTable<string, WordItem *> myTable;
    vector<string> fileNames;

    int numOfFiles;
    cout << "Enter number of input files: ";
    cin >> numOfFiles;
    for (int j = 0; j < numOfFiles; ++j) {
        string fileName;
        cout << "Enter " << j + 1 << ". file name: ";
        cin >> fileName;
        fileNames.push_back(fileName);

    }
    for (int i = 0; i < numOfFiles; ++i) {

        ifstream file(fileNames[i]);
        if (!file.is_open()) {
            cout << "File cannot be opened!" << endl;
            return 1;
        }
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string word;
            while ((ss >> word)) {
                string newWord;
                for(char & j : word){
                    if(isalpha(j)){
                        newWord += (char)tolower(j);
                    }
                    else{
                        newWord += ' '; //separate the word
                    }
                }
                stringstream wordStream(newWord);
                string singleWord;
                while (getline(wordStream, singleWord, ' ')) { //iterate over the words seperated by " "
                    if(!singleWord.empty()){ //Insertion to BST and Hashtable
                        auto *documentItem = new DocumentItem(fileNames[i]);
                        auto *wordItemTree = new WordItem(singleWord, documentItem);
                        auto *wordItemTable = new WordItem(singleWord, documentItem);
                        myTree.insert(singleWord, wordItemTree);
                        myTable.insert(singleWord, wordItemTable);
                    }
                }
            }
        }
    }
    cout << "\nAfter preprocessing, the unique word count is " << myTable.uniqueWordCount
         << ". Current load ratio is " << (double)myTable.uniqueWordCount/myTable.arraySize() << endl;
    cin.clear();
    cin.ignore();

    //Reading the file is completed.
    string query;
    cout << "Enter queried words in one line: ";
    getline(cin, query);
    vector<string> queryList;
    transform(query.begin(), query.end(), query.begin(), ::tolower); //makes the string lowercase
    string tempWord;
    for(char & c : query){ //check for punctuation and digit and separate them into the list
        if(ispunct(c) || isdigit(c)){
            queryList.push_back(tempWord);
            tempWord = "";
        }
        else{
            tempWord += c;
        }
    }
    if (!tempWord.empty()) {
        queryList.push_back(tempWord);
    }
    //Getting the input and putting them in a list is completed.

    int k = 20;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        // QueryDocuments(with BST);,
        int count = 0;
        int wordCount = 0;
        int loopCount = 0;

        vector<string> wordDetails(numOfFiles, ""); //Vector that puts the string of the word in the corresponding index of the file
        vector<int>wordCountVector(numOfFiles, 0); //Vector that puts the count of the word in the corresponding index of the file
        while(loopCount < queryList.size()){
            wordCount++;
            count++;
            if(myTree.find(queryList.at(loopCount)) != "!"){
                WordItem *tempNode =  myTree.getDetails(queryList.at(loopCount));
                for(int n = 0; n < fileNames.size(); n++){
                    for(int j = 0; j < tempNode->details.size(); j++){
                        if(tempNode->details[j].documentName == fileNames[n]){
                            wordCountVector[n]++;
                            if(wordDetails[n].empty())
                                wordDetails[n] += "in Document " + tempNode->details[j].documentName + ", " + tempNode->word + " found " + to_string(tempNode->details[j].count) + " times";
                            else
                                wordDetails[n] += ", " + tempNode->word + " found " + to_string(tempNode->details[j].count) + " times";
                        }
                    }
                }
            }
            loopCount++;
        }
        int totalCountOfEmpty = 0;
        for(int j = 0; j < wordDetails.size(); j++){
            if(!wordDetails[j].empty() && wordCountVector[j] == wordCount && i == 0)
                cout << wordDetails[j] << "." << endl;
            else
                totalCountOfEmpty++;
        }

        if(totalCountOfEmpty == numOfFiles && i == 0)
            cout << "No document contains the given query" << endl;
    }

    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);


    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        // QueryDocuments (with hashtable);
        int count = 0;
        int wordCount = 0;
        int loopCount = 0;

        vector<string> wordDetails(numOfFiles, ""); //Vector that puts the string of the word in the corresponding index of the file
        vector<int>wordCountVector(numOfFiles, 0); //Vector that puts the count of the word in the corresponding index of the file
        while(loopCount < queryList.size()){
            wordCount++;
            count++;
            if(myTable.find(queryList.at(loopCount)) != "!"){
                WordItem *tempNode =  myTable.getDetails(queryList.at(loopCount));
                for(int n = 0; n < fileNames.size(); n++){
                    for(int j = 0; j < tempNode->details.size(); j++){
                        if(tempNode->details[j].documentName == fileNames[n]){
                            wordCountVector[n]++;
                            if(wordDetails[n].empty())
                                wordDetails[n] += "in Document " + tempNode->details[j].documentName + ", " + tempNode->word + " found " + to_string(tempNode->details[j].count) + " times";
                            else
                                wordDetails[n] += ", " + tempNode->word + " found " + to_string(tempNode->details[j].count) + " times";
                        }
                    }
                }
            }
            loopCount++;
        }
        int totalCountOfEmpty = 0;
        for(int j = 0; j < wordDetails.size(); j++){
            if(!wordDetails[j].empty() && wordCountVector[j] == wordCount && i == 0)
                cout << wordDetails[j] << "." << endl;
            else
                totalCountOfEmpty++;
        }

        if(totalCountOfEmpty == numOfFiles && i == 0)
            cout << "No document contains the given query" << endl;

    }
    auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now()- start);

    cout << "\nTime: " << BSTTime.count() / k;
    cout << "\nTime: " << HTTime.count() / k;
    cout << "\nSpeed Up: " << (double)BSTTime.count()/(double)HTTime.count();

    return 0;
}
