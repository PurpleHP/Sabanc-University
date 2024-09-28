#include <iostream>
#include <algorithm> //for transform
#include <utility>
#include <deque> //for binary search
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <fstream>

using namespace std;

class Person{
public:
    string name;
    string surname;
    string phone;
    string city;

    Person(string name, string surname, string phone, string city):
            name(std::move(name)), surname(std::move(surname)), phone(std::move(phone)), city(std::move(city)){};

    Person(){
        name = "";
        surname = "";
        phone = "";
        city = "";
    }

    bool operator<(const Person& other) const {
        if (name != other.name) return name < other.name;
        if (surname != other.surname) return surname < other.surname;
        if (phone != other.phone) return phone < other.phone;
        return city < other.city;
    }
    bool operator<=(const Person& other) const {
        if (name != other.name) return name <= other.name;
        if (surname != other.surname) return surname <= other.surname;
        if (phone != other.phone) return phone <= other.phone;
        return city <= other.city;
    }
    bool operator==(string other) const {
        return (name + " " + surname == other);
    }
    Person& operator=(const Person& other) {
        if (this != &other) {
            name = other.name;
            surname = other.surname;
            phone = other.phone;
            city = other.city;
        }
        return *this;
    }

    [[nodiscard]] string FullName() const{
        return name + " " + surname;
    }

    [[nodiscard]] string FullDetail() const{
        string upperCaseFullName = name + " " + surname;
        transform(upperCaseFullName.begin(), upperCaseFullName.end(), upperCaseFullName.begin(), ::toupper); //makes the string lowercase
        return upperCaseFullName  + " " + phone + " " + city;
    }

};


template <class Comparable>
void printVector(const vector<Comparable>& arr) {
    for (const auto& element : arr) {
        cout << element.name << " " << element.surname << " " << element.phone << " " << element.city << endl;
    }
}

// Insertion Sort -----------------------------------------------------------------------

template <class Comparable>
void insertionSort (vector <Comparable>  a)
{
    int j;
    // loop over the passes
    for (int p = 1;  p < a.size(); p++)
    {
        Comparable tmp = a[p];
        // loop over the elements
        for (j = p; j > 0 &&  tmp < a[j-1]; j--)
            a[j] = a[j-1];
        a[j] = tmp;
    }
}

// Heap Sort -----------------------------------------------------------------------

template <class Comparable>
void percDown( vector<Comparable> & a, int i, int n )
{
    int child;
    Comparable tmp;

    for (tmp=a[i] ; 2*i+1 < n; i = child )
    {
        child = 2*i+1;
        if ( child != n-1 && a[ child  ] < a[ child+1 ] )
            child++;
        if(tmp < a[child])
            a[i] = a[ child ];
        else
            break;
    }
    a[ i ] = tmp;
}

template <class Comparable>
void heapsort(vector<Comparable>  a)
{
    // buildHeap
    for (int i = a.size()/2; i >=0; i--)
        percDown(a, i, a.size());

    // sort
    for (int j = a.size()-1; j >0; j--)
    {
        swap(a[0], a[j]);    // swap max to the last pos.
        percDown(a, 0, j); // re-form the heap
    }
}

// Merge Sort -----------------------------------------------------------------------

template <class Comparable>
void merge(vector<Comparable>& a, int start, int mid, int end) {
    int start2 = mid + 1;

    //Already sorted
    if (a[mid] <= a[start2]) {
        return;
    }

    //Two pointers
    while (start <= mid && start2 <= end) {
        //In right place
        if (a[start] <= a[start2]) {
            start++;
        }
        else {
            Comparable value = a[start2];
            int index = start2;
            // Shift all the elements between element 1 element 2, right by 1.
            while (index != start) {
                a[index] = a[index - 1];
                index--;
            }
            a[start] = value;

            start++;
            mid++;
            start2++;
        }
    }
}

template <class Comparable>
void mergeSort(vector<Comparable>& a, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}
template <class Comparable>
void mergeSort(vector<Comparable> a) {
    mergeSort(a, 0, a.size()-1);
}

// Quick Sort -----------------------------------------------------------------------

template <class Comparable>
void quickSort( vector<Comparable>  a )
{
    quickSort( a, 0, a.size( ) - 1 );
}

template <class Comparable>
const Comparable & median3( vector<Comparable> & a,
                            int left, int right )
{
    int center = ( left + right ) / 2;
    if ( a[ center ] < a[ left ] )
        swap( a[ left ], a[ center ] );
    if ( a[ right ] < a[ left ] )
        swap( a[ left ], a[ right ] );
    if ( a[ right ] < a[ center ] )
        swap( a[ center ], a[ right ] );

    // Place pivot at position right - 1
    swap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}

template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
    for ( int p = left + 1; p <= right; p++ )
    {
        Comparable tmp = a[ p ];
        int j;

        for ( j = p; j > left && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}


template <class Comparable>
void quickSort( vector<Comparable> & a,
                int left, int right )
{
    if ( left + 10 <= right ) //Else do insertion sort
    {
        Comparable pivot = median3( a, left, right );
        // Begin partitioning
        int i = left, j = right - 1;
        for ( ; ; )
        {
            while ( a[ ++i ] < pivot ) { }

            while ( pivot < a[ --j ] ) { }

            if ( i < j )
                swap( a[ i ], a[ j ] );
            else
                break;
        }
        swap( a[ i ], a[ right - 1 ] );   // Restore pivot

        quickSort( a, left, i - 1 );       // Sort small elements
        quickSort( a, i + 1, right );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}

// Sequential Search -----------------------------------------------------------------------

template <class Comparable>
vector<Comparable> sequentialSearch(string searchName, const vector<Comparable> & a){
    vector<Comparable> temp;
    for(Comparable const & Person : a ){
        if(Person == searchName){ //Found the exact match.
            temp.push_back(Person);
            break;
        }
        bool found = true;
        for (int i = 0; i < searchName.size()-1; ++i) {
            if(Person.FullName().size() + 1 >= searchName.size()){
                if(Person.FullName().at(i) != searchName.at(i)){
                    found = false;
                    break;
                }
            }
        }
        if(found){
            temp.push_back(Person);
        }
    }
    return temp;
}

// Binary Search -----------------------------------------------------------------------

template <class Comparable>
void BinarySearch(const string& searchName, const vector<Comparable>& a, std::deque<Comparable>& tempDeque) {
    int left = 0;
    int right = a.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        string midName = a[mid].FullName();

        if(midName.size() == searchName.size()){
            if(midName == searchName){
                tempDeque.push_back(a[mid]); // found
                break; // break if exact match found
            }
        }

        if (midName.size() >= searchName.size()) {
            midName = midName.substr(0, searchName.size());

            if (midName == searchName) {
                // Check left
                int temp = mid;
                while (temp >= 0) {
                    string tempName = a[temp].FullName();
                    if (tempName.size() >= searchName.size()) {
                        tempName = tempName.substr(0, searchName.size());
                        if (tempName == searchName) {
                            tempDeque.push_front(a[temp]); // push to front
                        } else {
                            break;
                        }
                    }
                    temp--;
                }
                // Check right
                temp = mid + 1;
                while (temp < a.size()) {
                    string tempName = a[temp].FullName();
                    if (tempName.size() >= searchName.size()) {
                        tempName = tempName.substr(0, searchName.size());
                        if (tempName == searchName) {
                            tempDeque.push_back(a[temp]); // push to back
                        } else {
                            break;
                        }
                    }
                    temp++;
                }
                break;
            }
        }

        if (midName < searchName) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
}

// MAIN ------------------------------------------------------------------------------------------------------------------------------------

int main() {
    string fileName;
    string query;
    int wordCount = 0;
    vector<Person> persons;
    cout << "Please enter the contact file name:";
    cin >> fileName;
    cin.clear();
    cin.ignore();
    cout << "Please enter the word to be queried:";
    getline(cin, query);
    for ([[maybe_unused]] auto q: query) {
        wordCount++;
    }
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "File cannot be opened!" << endl;
        return 1;
    }
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string nameTemp, surnameTemp, phoneTemp, cityTemp;
        ss >> nameTemp;
        ss >> surnameTemp;
        ss >> phoneTemp;
        ss >> cityTemp;
        Person p = Person(nameTemp, surnameTemp, phoneTemp, cityTemp);
        persons.push_back(p);
    }

    //All inputs are read -----------------------------------------------------------------------

    vector<Person> tempVector = persons;
    int N = 100;

    // Quick Sort
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++){
        quickSort(tempVector);
    }
    auto QuickTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);


    //Insertion Sort
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++){
        insertionSort(tempVector);
    }
    auto InsertionTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);


    // Heap Sort
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++){
        heapsort(tempVector);
    }
    auto HeapTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);

    // Merge Sort
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++){
        mergeSort(tempVector);
    }

    auto MergeTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);

    insertionSort(persons, 0, tempVector.size()-1); //now it's sorted

    cout << "\nSorting the vector copies\n"
            "======================================\n";
    cout << "Quick Sort Time: " << QuickTime.count() << " Nanoseconds\n"
                                                        "Insertion Sort Time: " << InsertionTime.count() << " Nanoseconds\n"
                                                                                                            "Merge Sort Time: " << MergeTime.count() << " Nanoseconds\n"
                                                                                                                                                        "Heap Sort Time: " << HeapTime.count() << " Nanoseconds\n";


    //------------------------------------------------------------------------------------
    //Binary Search
    std::deque<Person> foundPerson1;

    cout << "\nSearching for " << query << "\n"<<
         "======================================\n";
    start = std::chrono::high_resolution_clock::now();
    BinarySearch(query, persons, foundPerson1);
    auto BinaryTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);

    if(!foundPerson1.empty()){
        for (const auto & person : foundPerson1) {
            cout << person.FullDetail() << endl;
        }
    }
    else{
        transform(query.begin(), query.end(), query.begin(), ::toupper); //makes the string lowercase
        cout << query << " does NOT exist in the dataset\n";
    }
    cout << "Binary Search Time: "<< BinaryTime.count() << " Nanoseconds\n";

    //------------------------------------------------------------------------------------
    //Sequential Search
    vector<Person> foundPerson2;

    cout << "\nSearch results for Sequential Search: " << "\n";
    start = std::chrono::high_resolution_clock::now();
    foundPerson2 = sequentialSearch(query, persons);
    auto SequentialTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);

    if(!foundPerson2.empty()){
        for (const auto & person : foundPerson2) {
            cout << person.FullDetail() << endl;
        }
    }
    else{
        transform(query.begin(), query.end(), query.begin(), ::toupper); //makes the string lowercase
        cout << query << " does NOT exist in the dataset\n";
    }

    cout << "\nSequential Search Time: "<< SequentialTime.count() << " Nanoseconds\n";

    cout << "\nSpeedUp between Search Algorithms\n"
            "======================================\n"
            "(Sequential Search/ Binary Search) SpeedUp = "
         << (double)SequentialTime.count() / (double) BinaryTime.count() << "\n";

    cout << "\nSpeedUps between Sorting Algorithms\n"
         << "======================================\n"
         << "(Insertion Sort/ Quick Sort) SpeedUp = " << (double)InsertionTime.count() / (double)QuickTime.count() << "\n"
         << "(Merge Sort / Quick Sort) SpeedUp = " <<  (double)MergeTime.count() / (double)QuickTime.count() << "\n"
         << "(Heap Sort / Quick Sort) SpeedUp = " <<  (double)HeapTime.count() / (double)QuickTime.count() << "\n";

    return 0;
}
