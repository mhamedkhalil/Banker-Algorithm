#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;
/*fill the data about the resources in vectors to allow flexibility in examples (like adding more resources)
to change the number of processes we need to change the initialized row size of the vectors*/
vector<vector<int>> needMatrix(5);
vector<vector<int>> allocationMatrix(5);
vector<vector<int>> maxMatrix(5);
vector<int> available;

void getSafeSequence() 
{
    vector<int> safeSequence;
    int size = maxMatrix.size(); 
    bool * label = new bool[size]; //a dynamic array that contains flags about all the processes taken into consideration
    //the flags mark if a specific process has been served by all the resources it needs or not
    //we need to initialize all the flags to 0 (false)  
    for(int i=0; i<size; i++){label[i] = 0;}
    bool Break = 0; //this variable is going to be used to break the loop when an unsafe state is detected
    int FCount = size; //this variable is going to determine if the system is not in a safe state
    int old; //we will compafre the number of false flags after each iteration over all the processes
    //if the false flags' number did not change, then no more processes can access the resources --> unsafe state
    while(!Break && FCount != 0) //loop until no more processes waiting for resources or when unsafe state is detected
    {
        old = FCount;
        for(int i=0; i<needMatrix.size(); i++) //loop over all processes
        {
            if(!label[i]) //if the process is waiting for resources 
            {
                bool temp = 1;
                for(int j=0; j<needMatrix[i].size(); j++)
                {
                    temp = temp && (needMatrix[i][j] <= available[j]);//check if the need of the process is doable by the available resources
                }
                if(temp == 1) //if the needs of the process are affordable
                {
                    label[i] = temp; //assign the process the resources it needs 
                    FCount--;
                    safeSequence.push_back(i); //push the process into the safe sequence vector
                    for(int k=0; k<available.size(); k++)
                    {
                        available[k] += allocationMatrix[i][k]; //after finishing execution, add all the resources 
                                                               //of this process to the available section
                    }
                }
            }
        }
        if(old == FCount){Break = 1;} //if unsafe state detected
    }
    if(safeSequence.size() != size)
    {
        cout << "No safe sequence found! System is not in a safe state!" << endl;
    }
    else
    {
        cout << "System is in safe state!" << endl;
        cout << "Safe Sequence: " << endl;
        for(int i : safeSequence)
        {
            cout << "P" + to_string(i) << "  "; //print safe sequence
        }
    }
}

void generateNeed() //a function to generate the Need Matrix
{ //Need = Max - Allocated 
    int need;
    for(int i=0; i<maxMatrix.size(); i++)
    {
        for(int j=0; j<maxMatrix[i].size(); j++)
        {
            need = maxMatrix[i][j]-allocationMatrix[i][j];
            needMatrix[i].push_back(need);
        }
    }
    cout << "Need Matrix: " << endl;
    for(auto i : needMatrix)
    {
        for(auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}

int getData() //a function to parse the resources txt file and extract the data we need
{
    fstream resources("resources.txt", std::ios::in);
    if(!resources.is_open())
    {
        cerr << "Error opening resources file!" << endl;
        return 1;
    }
    string line;
    int count;
    vector<string> parsed;
    int index;
    int num;
    while(getline(resources,line))
    {
        parsed.push_back(line); //add each line in the txt file to a vector for easier manipulation 
    }
    for(int i = 0; i < parsed.size(); i++)
    {
        if(parsed[i].find("Allocation") != string::npos) //parse Allocation section
        {
            ++i;
            count = i + 5;
            index = 0;
            while(i < count)
            {
                stringstream ss(parsed[i].substr(parsed[i].find(':') + 1));
                while(ss >> num)
                {
                    allocationMatrix[index].push_back(num);
                    ss.ignore(1,',');
                }
                index++;
                i++;
            }
        }
        if(parsed[i].find("Max") != string::npos) //parse Max section
        {
            ++i;
            count = i + 5;
            index = 0;
            while(i < count)
            {
                stringstream ss(parsed[i].substr(parsed[i].find(':') + 1));
                while(ss >> num)
                {
                    maxMatrix[index].push_back(num);
                    ss.ignore(1,',');
                }
                index++;
                i++;
            }
        }
        if(parsed[i].find("Available") != string::npos) //parse Available section
        {
            ++i;
            stringstream ss(parsed[i]);
            while(ss >> num)
            {
                available.push_back(num);
                ss.ignore(1,',');
            }
        }
    }
    cout << "Allocation Matrix:" << endl;
    for(auto i : allocationMatrix)
    {
        for(auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << "Max Matrix: " << endl;
    for(auto i : maxMatrix)
    {
        for(auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << "Available Resources: " << endl;
    for(auto i : available)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}

int main() //call the functions needed in the right order
{
    getData();
    generateNeed();
    getSafeSequence();
}