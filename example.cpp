#include <bits/stdc++.h>
using namespace std;

bool validateName(string fullName);
bool validateParticipantUserName(string userName);
bool validateTransactionUserName(string userName);
bool validateAmount(string amount);

bool validateName(string fullName)
{
    bool digitCheck = false;
    bool lengthCheck = false;
    bool specialCharCheck = false;
    int nameIndex;

    if (fullName.length() <= 40)
    {
        lengthCheck = true;
    }

    // Loop for Digit Check
    for (nameIndex = 0; nameIndex < fullName.length(); nameIndex++)
    {
        if (fullName[nameIndex] >= 48 && fullName[nameIndex] <= 57 && fullName[nameIndex] != 32)
        {
            digitCheck = true;
            break;
        }
    }

    // Loop for Special Character Check
    for (nameIndex = 0; nameIndex < fullName.length(); nameIndex++)
    {
        if ((fullName[nameIndex] < 65 || fullName[nameIndex] > 90) && (fullName[nameIndex] < 97 || fullName[nameIndex] > 122) && (fullName[nameIndex] < 48 || fullName[nameIndex] > 57) && fullName[nameIndex] != 32)
        {
            specialCharCheck = true;
            break;
        }
    }

    try
    {
        if (specialCharCheck || digitCheck)
        {
            throw "Invalid Name Exception";
        }
        else
        {
            return true;
        }
    }
    catch (const char *e)
    {
        cout << endl
             << "Exception Ocurred" << endl
             << e << endl;
        return false;
    }
}

class person
{
public:
    string personUsername;
    string nameOfPerson;
    array<char, 6> modesOfPayment;
    int netAmount;
    set<string> paymentTypes;

    person() : nameOfPerson(""), modesOfPayment({'0', '0', '0', '0', '0', '0'}), netAmount(0) {}

    // Serialize to binary format
    void writeToFile(ofstream &file) const
    {
        size_t usernameLength = personUsername.size();
        file.write(reinterpret_cast<const char *>(&usernameLength), sizeof(usernameLength)); // Write length of username
        file.write(personUsername.c_str(), usernameLength);                                  // Write username string

        size_t nameLength = nameOfPerson.size();
        file.write(reinterpret_cast<const char *>(&nameLength), sizeof(nameLength));              // Write length of the name
        file.write(nameOfPerson.c_str(), nameLength);                                             // Write name string
        file.write(reinterpret_cast<const char *>(modesOfPayment.data()), modesOfPayment.size()); // Write payment modes
    }

    // Deserialize from binary format
    void readFromFile(ifstream &file)
    {
        size_t usernameLength;
        file.read(reinterpret_cast<char *>(&usernameLength), sizeof(usernameLength)); // Read length of username
        personUsername.resize(usernameLength);
        file.read(&personUsername[0], usernameLength); // Read username string

        size_t nameLength;
        file.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength)); // Read length of the name
        nameOfPerson.resize(nameLength);
        file.read(&nameOfPerson[0], nameLength);                                           // Read name string
        file.read(reinterpret_cast<char *>(modesOfPayment.data()), modesOfPayment.size()); // Read payment modes
    }

    bool setPaymentMode(const string &paymentMode)
    {
        static const array<string, 6> validModes = {"Cash", "PayTM", "GPay", "PhonePe", "Credit Card", "Debit Card"};

        for (int i = 0; i < validModes.size(); ++i)
        {
            if (paymentMode == validModes[i] && modesOfPayment[i] == '0')
            {
                modesOfPayment[i] = '1'; // Mark this payment mode as selected
                return true;
            }
        }
        return false; // Invalid or already used payment mode
    }

    void display() const
    {
        cout << "Name: " << nameOfPerson << " (Username: " << personUsername << ")\n";
        cout << "Payment Modes: ";
        for (int i = 0; i < 6; ++i)
        {
            if (modesOfPayment[i] == '1')
            {
                switch (i)
                {
                case 0:
                    cout << "Cash\t";
                    break;
                case 1:
                    cout << "PayTM\t";
                    break;
                case 2:
                    cout << "GPay\t";
                    break;
                case 3:
                    cout << "PhonePe\t";
                    break;
                case 4:
                    cout << "Credit Card\t";
                    break;
                case 5:
                    cout << "Debit Card\t";
                    break;
                }
            }
        }
        cout << "\n"
             << endl;
    }
};

class transaction
{
public:
    string payee;
    string debtor;
    string amount;

    // Serialize to binary format
    void writeToFile(ofstream &file) const
    {
        // Write the lengths of the strings first
        size_t payeeLength = payee.size();
        size_t debtorLength = debtor.size();
        size_t amountLength = amount.size();

        file.write(reinterpret_cast<const char *>(&payeeLength), sizeof(payeeLength));
        file.write(payee.c_str(), payeeLength); // Write payee string

        file.write(reinterpret_cast<const char *>(&debtorLength), sizeof(debtorLength));
        file.write(debtor.c_str(), debtorLength); // Write debtor string

        file.write(reinterpret_cast<const char *>(&amountLength), sizeof(amountLength));
        file.write(amount.c_str(), amountLength); // Write amount string
    }

    // Deserialize to binary format
    void readFromFile(ifstream &file)
    {
        size_t payeeLength, debtorLength, amountLength;

        // Read the lengths of the strings
        file.read(reinterpret_cast<char *>(&payeeLength), sizeof(payeeLength));
        payee.resize(payeeLength);
        file.read(&payee[0], payeeLength);

        file.read(reinterpret_cast<char *>(&debtorLength), sizeof(debtorLength));
        debtor.resize(debtorLength);
        file.read(&debtor[0], debtorLength);

        file.read(reinterpret_cast<char *>(&amountLength), sizeof(amountLength));
        amount.resize(amountLength);
        file.read(&amount[0], amountLength);
    }
};

void createNewParticipant()
{
    ofstream file("participants.dat", ios::binary | ios::app);

    person p;

    // Input person name
    cout << "Enter person name: ";
    getline(cin, p.nameOfPerson);

    // Input payment modes
    int n;
    do
    {
        cout << "Enter number of payment modes available: ";
        cin >> n;
        if (n > 6 || n <= 0)
        {
            cout << "Invalid Number of Payment Methods\n";
        }
    } while (n > 6 || n <= 0);
    cin.ignore(); // To discard the newline character left in the buffer

    string paymentMode;
    for (int i = 0; i < n; ++i)
    {
        bool validMode = false;
        do
        {
            cout << "Enter mode of payment " << i + 1 << ": ";
            getline(cin, paymentMode);
            validMode = p.setPaymentMode(paymentMode);
            if (!validMode)
            {
                cout << "Invalid or duplicate payment mode. Please try again.\n";
            }
        } while (!validMode); // Keep asking until a valid payment mode is provided
    }
    cout << "Enter username: ";
    getline(cin, p.personUsername);

    if (validateParticipantUserName(p.personUsername) && validateParticipantUserName(p.nameOfPerson))
    {
        p.writeToFile(file);
        cout << "Participant details added successfully." << endl;
    }
    else
    {
        cout << "Participant couldn't be added." << endl;
        char ch;
        cout << "Would you like to try again?(y/n): ";
        cin >> ch;
        if (ch == 'y' || ch == 'Y')
        {
            createNewParticipant();
        }
        else
        {
            // main_menu();
        }
    }

    system("pause");
    file.close();
}

void recordTransaction()
{
    ofstream file("transactions.dat", ios::binary | ios::app);

    transaction t;

    // Input debtor username
    do
    {
        cout << "Enter debtor username: ";
        getline(cin, t.debtor);
    } while (!validateTransactionUserName(t.debtor));

    // Input payee username
    do
    {
        cout << "Enter payee username: ";
        getline(cin, t.payee);
    } while (!validateTransactionUserName(t.payee));

    // Input amount
    do
    {
        cout << "Enter amount: ";
        getline(cin, t.amount);
    } while (!validateAmount(t.amount));

    if (!file.is_open())
    {
        cout << "Transaction not recorded." << endl;
        char ch;
        cout << "Would you like to try again?(y/n): ";
        cin >> ch;
        if (ch == 'y' || ch == 'Y')
        {
            recordTransaction();
        }
        else
        {
            // main_menu();
        }
    }
    else
    {
        t.writeToFile(file);
        cout << "Transaction recorded successfully. " << endl;
    }

    system("pause");
    file.close();
}

void displayParticipants()
{
    ifstream file("participants.dat", ios::binary);

    if (!file.is_open())
    {
        cout << "Error reading participants file." << endl;
        return;
    }

    person p;
    int count = 0;

    while (file)
    {
        p.readFromFile(file);
        if (file)
        { // Check if we read a valid person object
            cout << "Name of person " << ++count << ": " << p.nameOfPerson << endl;
            cout << "UserName of person " << count << ": " << p.personUsername << endl;
            cout << "Payment Modes Available: ";

            // Loop through the payment modes and print those that are '1'
            for (int i = 0; i < 6; ++i)
            {
                if (p.modesOfPayment[i] == '1')
                {
                    switch (i)
                    {
                    case 0:
                        cout << "Cash\t";
                        break;
                    case 1:
                        cout << "PayTM\t";
                        break;
                    case 2:
                        cout << "GPay\t";
                        break;
                    case 3:
                        cout << "PhonePe\t";
                        break;
                    case 4:
                        cout << "Credit Card\t";
                        break;
                    case 5:
                        cout << "Debit Card\t";
                        break;
                    }
                }
            }
            cout << "\n"
                 << endl;
        }
    }

    if (!count)
    {
        cout << "No participants found." << endl;
    }

    file.close();
}

void displayTransactions()
{
    ifstream file("transactions.dat", ios::binary);

    if (!file.is_open())
    {
        cout << "Error reading transactions file." << endl;
        return;
    }

    transaction t;
    int count = 0;

    while (file)
    {
        t.readFromFile(file);
        if (file)
        { // Check if we read a valid transaction object
            cout << "Transaction " << ++count << ": " << endl;
            cout << "Username of Payee: " << t.payee << endl;
            cout << "Username of Debtor: " << t.debtor << endl;
            cout << "Amount: " << t.amount << endl;
            cout << "\n"
                 << endl;
        }
    }

    if (!count)
    {
        cout << "No transactions found." << endl;
    }

    file.close();
}

bool validateParticipantUserName(string userName)
{
    // !----------------------------------
    // 1. should not be longer than 15 characters
    // 2. should not contain any special character except underscore
    // 3. there should not be any two same usernames in the file
    // !----------------------------------

    // 1. Check if the username is longer than 15 characters
    if (userName.length() > 15)
    {
        cout << "Username cannot be longer than 15 characters." << endl;
        return false;
    }

    // 2. Check if the username contains only letters, digits, and underscores
    regex validUsernamePattern("^[a-zA-Z0-9_]+$");
    if (!regex_match(userName, validUsernamePattern))
    {
        cout << "Username can only contain letters, digits, and underscores." << endl;
        return false;
    }

    // 3. Check if the username already exists in the file
    ifstream file("participants.dat", ios::binary);
    if (!file.is_open())
    {
        cout << "Error reading participants file." << endl;
        return false;
    }

    person p;
    while (file)
    {
        p.readFromFile(file); // Read a person object from the file
        if (file)
        { // Check if a valid person object is read
            if (p.personUsername == userName)
            {
                cout << "Username already exists. Please choose another username." << endl;
                file.close();
                return false; // Username already exists in the file
            }
        }
    }

    // If no issues were found, the username is valid
    file.close();
    return true;
}

bool validateTransactionUserName(string userName)
{
    // Check if the username already exists in the participants file
    ifstream file("participants.dat", ios::binary);
    if (!file.is_open())
    {
        cout << "Error reading participants file." << endl;
        return false;
    }

    person p;
    while (file)
    {
        p.readFromFile(file); // Read a person object from the file
        if (file)
        { // Check if a valid person object is read
            if (p.personUsername == userName)
            {
                file.close();
                return true; // Username already exists in the file
            }
        }
    }

    // If username not found in participants file, return error
    cout << "Username not found" << endl;
    file.close();
    return false;
}

bool validateAmount(string amount)
{
    bool digitCheck = true;
    bool negativeCheck = true;
    int amountIndex;

    int length = amount.length();

    // Loop for checking that the amount doesn't have any other character than digits
    for (amountIndex = 0; amountIndex < length; amountIndex++)
    {
        if (amount[amountIndex] < 48 || amount[amountIndex] > 57)
        {
            digitCheck = false;
        }
    }

    // Checking that the amount is greater than zero
    if (stoi(amount) <= 0)
    {
        negativeCheck = false;
    }

    try
    {
        if (!(digitCheck && negativeCheck))
        {
            throw "Invalid Amount";
        }
        else
        {
            return true;
        }
    }
    catch (const char *e)
    {
        cout << endl
             << "Exception Ocurred" << endl
             << e << endl;
        return false;
    }
}

int getMinIndex(person listOfNetAmounts[], int numberOfParticipants)
{
    int min = INT_MAX, minIndex = -1;
    for (int i = 0; i < numberOfParticipants; i++)
    {
        if (listOfNetAmounts[i].netAmount == 0)
            continue;

        if (listOfNetAmounts[i].netAmount < min)
        {
            minIndex = i;
            min = listOfNetAmounts[i].netAmount;
        }
    }
    return minIndex;
}

int getSimpleMaxIndex(person listOfNetAmounts[], int numberOfParticipants)
{
    int max = INT_MIN, maxIndex = -1;
    for (int i = 0; i < numberOfParticipants; i++)
    {
        if (listOfNetAmounts[i].netAmount == 0)
            continue;

        if (listOfNetAmounts[i].netAmount > max)
        {
            maxIndex = i;
            max = listOfNetAmounts[i].netAmount;
        }
    }
    return maxIndex;
}

pair<int, string> getMaxIndex(person listOfNetAmounts[], int numberOfParticipants, int minIndex, person input[], int maxNumTypes)
{
    int max = INT_MIN;
    int maxIndex = -1;
    string matchingType;

    for (int i = 0; i < numberOfParticipants; i++)
    {
        if (listOfNetAmounts[i].netAmount == 0)
            continue;

        if (listOfNetAmounts[i].netAmount < 0)
            continue;

        vector<string> v(maxNumTypes);
        vector<string>::iterator ls = set_intersection(listOfNetAmounts[minIndex].paymentTypes.begin(), listOfNetAmounts[minIndex].paymentTypes.end(), listOfNetAmounts[i].paymentTypes.begin(), listOfNetAmounts[i].paymentTypes.end(), v.begin());

        if ((ls - v.begin()) != 0 && max < listOfNetAmounts[i].netAmount)
        {
            max = listOfNetAmounts[i].netAmount;
            maxIndex = i;
            matchingType = *(v.begin());
        }
    }

    // if there is NO such max which has a common type with any remaining banks then maxIndex has -1
    //  also return the common payment type
    return make_pair(maxIndex, matchingType);
}

void printAns(vector<vector<pair<int, string>>> ansGraph, int numberOfParticipants, person input[])
{
    cout << "\nThe transactions for minimum cash flow are as follows : \n\n";
    for (int i = 0; i < numberOfParticipants; i++)
    {
        for (int j = 0; j < numberOfParticipants; j++)
        {
            if (i == j)
                continue;

            if (ansGraph[i][j].first != 0 && ansGraph[j][i].first != 0)
            {

                if (ansGraph[i][j].first == ansGraph[j][i].first)
                {
                    ansGraph[i][j].first = 0;
                    ansGraph[j][i].first = 0;
                }
                else if (ansGraph[i][j].first > ansGraph[j][i].first)
                {
                    ansGraph[i][j].first -= ansGraph[j][i].first;
                    ansGraph[j][i].first = 0;

                    cout << input[i].nameOfPerson << "(" << input[i].personUsername << ")" << " pays Rs" << ansGraph[i][j].first << "to " << input[j].nameOfPerson << "(" << input[j].personUsername << ")" << " via " << ansGraph[i][j].second << endl;
                }
                else
                {
                    ansGraph[j][i].first -= ansGraph[i][j].first;
                    ansGraph[i][j].first = 0;

                    cout << input[j].nameOfPerson << "(" << input[j].personUsername << ")" << " pays Rs " << ansGraph[j][i].first << " to " << input[i].nameOfPerson << "(" << input[i].personUsername << ")" << " via " << ansGraph[j][i].second << endl;
                }
            }
            else if (ansGraph[i][j].first != 0)
            {
                cout << input[i].nameOfPerson << "(" << input[i].personUsername << ")" << " pays Rs " << ansGraph[i][j].first << " to " << input[j].nameOfPerson << "(" << input[j].personUsername << ")" << " via " << ansGraph[i][j].second << endl;
            }
            else if (ansGraph[j][i].first != 0)
            {
                cout << input[j].nameOfPerson << "(" << input[j].personUsername << ")" << " pays Rs " << ansGraph[j][i].first << " to " << input[i].nameOfPerson << "(" << input[i].personUsername << ")" << " via " << ansGraph[j][i].second << endl;
            }

            ansGraph[i][j].first = 0;
            ansGraph[j][i].first = 0;
        }
    }
    cout << "\n";
}

void settleDebts(int numberOfParticipants, person input[], unordered_map<string, int> &indexOf, int numberOfTransactions, vector<vector<int>> &graph, int maxNumTypes)
{
    // Find net amount of each Person has
    person listOfNetAmounts[numberOfParticipants];

    for (int b = 0; b < numberOfParticipants; b++)
    {
        listOfNetAmounts[b].personUsername = input[b].personUsername;
        listOfNetAmounts[b].paymentTypes = input[b].paymentTypes;

        int amount = 0;
        // incoming edges
        // column travers
        for (int i = 0; i < numberOfParticipants; i++)
        {
            amount += (graph[i][b]);
        }

        // outgoing edges
        // row traverse
        for (int j = 0; j < numberOfParticipants; j++)
        {
            amount += ((-1) * graph[b][j]);
        }

        listOfNetAmounts[b].netAmount = amount;
    }

    vector<vector<pair<int, string>>> ansGraph(numberOfParticipants, vector<pair<int, string>>(numberOfParticipants, {0, ""})); // adjacency matrix

    // find min and max net amount
    int numZeroNetAmounts = 0;

    for (int i = 0; i < numberOfParticipants; i++)
    {
        if (listOfNetAmounts[i].netAmount == 0)
            numZeroNetAmounts++;
    }
    while (numZeroNetAmounts != numberOfParticipants)
    {

        int minIndex = getMinIndex(listOfNetAmounts, numberOfParticipants);
        pair<int, string> maxAns = getMaxIndex(listOfNetAmounts, numberOfParticipants, minIndex, input, maxNumTypes);

        int maxIndex = maxAns.first;

        if (maxIndex == -1)
        {

            (ansGraph[minIndex][0].first) += abs(listOfNetAmounts[minIndex].netAmount);
            (ansGraph[minIndex][0].second) = *(input[minIndex].paymentTypes.begin());

            int simpleMaxIndex = getSimpleMaxIndex(listOfNetAmounts, numberOfParticipants);
            (ansGraph[0][simpleMaxIndex].first) += abs(listOfNetAmounts[minIndex].netAmount);
            (ansGraph[0][simpleMaxIndex].second) = *(input[simpleMaxIndex].paymentTypes.begin());

            listOfNetAmounts[simpleMaxIndex].netAmount += listOfNetAmounts[minIndex].netAmount;
            listOfNetAmounts[minIndex].netAmount = 0;

            if (listOfNetAmounts[minIndex].netAmount == 0)
                numZeroNetAmounts++;

            if (listOfNetAmounts[simpleMaxIndex].netAmount == 0)
                numZeroNetAmounts++;
        }
        else
        {
            int transactionAmount = min(abs(listOfNetAmounts[minIndex].netAmount), listOfNetAmounts[maxIndex].netAmount);

            (ansGraph[minIndex][maxIndex].first) += (transactionAmount);
            (ansGraph[minIndex][maxIndex].second) = maxAns.second;

            listOfNetAmounts[minIndex].netAmount += transactionAmount;
            listOfNetAmounts[maxIndex].netAmount -= transactionAmount;

            if (listOfNetAmounts[minIndex].netAmount == 0)
                numZeroNetAmounts++;

            if (listOfNetAmounts[maxIndex].netAmount == 0)
                numZeroNetAmounts++;
        }
    }

    printAns(ansGraph, numberOfParticipants, input);
}

void minimizeCashFlow()
{
    ifstream participantFile("participants.dat", ios::binary);

    if (!participantFile.is_open())
    {
        cout << "Error reading participants file." << endl;
        return;
    }

    person p;
    int numberOfParticipants = 0;

    while (participantFile)
    {
        p.readFromFile(participantFile);
        if (participantFile)
        {
            ++numberOfParticipants;
        }
    }

    if (!numberOfParticipants)
    {
        cout << "No participants found." << endl;
        return;
    }

    participantFile.close();

    person input[numberOfParticipants]; // Array of Participant objects
    int maxNumTypes; // Maximum number of payment mode types possible from super participant
    unordered_map<string, int> indexOf; // Stores Index Of Person Object

    ifstream participantFile2("participants.dat", ios::binary);

    if (!participantFile2.is_open())
    {
        cout << "Error reading participants file." << endl;
        return;
    }

    int participantIndex = 0;

    while (participantFile2)
    {
        p.readFromFile(participantFile2);
        if (participantFile2)
        {
            input[participantIndex].nameOfPerson = p.nameOfPerson;
            input[participantIndex].personUsername = p.personUsername;
            indexOf[input[participantIndex].personUsername] = participantIndex;

            int numTypes = 0;
            // Loop through the payment modes and print those that are '1'
            for (int i = 0; i < 6; ++i)
            {
                if (p.modesOfPayment[i] == '1')
                {
                    switch (i)
                    {
                    case 0:
                        input[participantIndex].paymentTypes.insert("Cash");
                        break;
                    case 1:
                        input[participantIndex].paymentTypes.insert("PayTM");
                        break;
                    case 2:
                        input[participantIndex].paymentTypes.insert("GPay");
                        break;
                    case 3:
                        input[participantIndex].paymentTypes.insert("PhonePe");
                        break;
                    case 4:
                        input[participantIndex].paymentTypes.insert("Credit Card");
                        break;
                    case 5:
                        input[participantIndex].paymentTypes.insert("Debit Card");
                        break;
                    }
                    numTypes++;
                }
            }
            if (participantIndex == 0){
                maxNumTypes = numTypes;
            }
            participantIndex++;
        }
    }

    participantFile2.close();

    ifstream transactionFile("transactions.dat", ios::binary);

    if (!transactionFile.is_open())
    {
        cout << "Error reading transactions file." << endl;
        return;
    }

    transaction t;
    int numberOfTransactions = 0;

    while (transactionFile)
    {
        t.readFromFile(transactionFile);
        if (transactionFile)
        { // Check if we read a valid transaction object
            ++numberOfTransactions;
        }
    }

    if (!numberOfTransactions)
    {
        cout << "No transactions found." << endl;
    }

    vector<vector<int>> graph(numberOfParticipants, vector<int>(numberOfParticipants, 0)); // adjacency matrix

    transactionFile.close();

    ifstream transactionFile2("transactions.dat", ios::binary);

    if (!transactionFile2.is_open())
    {
        cout << "Error reading transactions file." << endl;
        return;
    }

    while (transactionFile2)
    {
        t.readFromFile(transactionFile2);
        if (transactionFile2)
        { 
            graph[indexOf[t.debtor]][indexOf[t.payee]] = stoi(t.amount); //Debtor has to pay payee x amount -> Graph[debtor][payee] = amount
        }
    }

    transactionFile2.close();

    settleDebts(numberOfParticipants, input, indexOf, numberOfTransactions, graph, maxNumTypes);
}

int main(){
    displayParticipants();
    displayTransactions();
    minimizeCashFlow();
    return 0;
}
