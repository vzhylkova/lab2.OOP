#include "Reader.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

Reader::Reader(string name,  int readerNumber, int subscriptionDaysLeft, double balance)
    : name(name), readerNumber(readerNumber), subscriptionDaysLeft(subscriptionDaysLeft), balance(balance) {
    totalReaders++;
}

//������ ��� ��������� ���������� ������
string Reader::getName() const {
    return name;
}
double Reader::getBalance() const {
    return balance;
} 
int Reader::getSubscriptionDaysLeft() const {
    return subscriptionDaysLeft;
}
int Reader::getReaderNumber() const{
    return readerNumber;
}

//����� ��� ��������� ������ �� �������
void Reader::addBalance(double amount) {
    balance += amount;
}

//������������ ������ ��� ������ ������
void Reader::payForSubscription(double amount) {
    if (balance >= amount) {
        balance -= amount;
        subscriptionDaysLeft += 30;
    }
    else
    {
        cout << "�� ������� ������ �� �������" << endl;
    }
}
void Reader::payForSubscription(double amount, double discount) {
    double discountedAmount = amount * (1 - discount/100);
    if (balance >= discountedAmount) {
        balance -= discountedAmount;
        subscriptionDaysLeft += 30;
    }
    else
    {
        cout << "�� ������� ������ �� �������" << endl;
    }
}

//�����, �� ������ ��'��� ����� �� ��������
bool Reader::compareBalance(const Reader& otherReader) const {
    return this->balance > otherReader.balance;
}

//����� ��� ���������� ���������� �� �������
void Reader::placeOrder(Publication& publication) {
    if (balance >= publication.getPrice()) {
        balance -= publication.getPrice();
        subscriptionDaysLeft += publication.getSubscriptionPeriod();
        cout << name << " ������ ��������� �� " << publication.getTitle() << "." << endl;
    }
    else {
        cout << name << " �� �� ��������� ����� ��� ������� �� " << publication.getTitle() << "." << endl;
    }
}
//void Reader::writeToFile(const string& filename) const {
//    ofstream outFile(filename, ios::app); // Open file in append mode
//    if (outFile) {
//        outFile << name << "\n"
//            << readerNumber << "\n"
//            << subscriptionDaysLeft << "\n"
//            /*<< blacklisted << "\n"*/
//            << balance << "\n";
//        outFile.close();
//    }
//    else {
//        cerr << "Error opening file for writing." << endl;
//    }
//}
void Reader::writeAllToFile(const vector<Reader>& readers, const string& filename) {
    ofstream outFile(filename, ios::trunc);
    if (outFile) {
        for (const auto& reader : readers) {
            outFile << reader.getName() << "\n"
                << reader.readerNumber << "\n" 
                << reader.subscriptionDaysLeft << "\n"
                << reader.balance << "\n"; 
        }
    }
    else {
        cerr << "Error opening file for writing." << endl;
    }
}
vector<Reader> Reader::readAllFromFile(const string& filename) {
    vector<Reader> readers;
    ifstream inFile(filename);
    if (inFile) {
        while (true) {
            string name;
            int readerNumber;
            int subscriptionDaysLeft;
            double balance;

            if (!getline(inFile, name)) break; // ������� ��'�
            inFile >> readerNumber >> subscriptionDaysLeft >> balance;
            inFile.ignore(); // �������� ������ ������ ����� ���� ���������� double

            readers.emplace_back(name, readerNumber, subscriptionDaysLeft, balance);
        }
        inFile.close();
    }
    else {
        cerr << "������� �������� ����� ��� �������." << endl;
    }
    return readers;
}

int* Reader::generateAndSortRandomNumbers(int n) {
    int* randomNumbers = new int[n];  // �������� �������� ���'�� ��� ������ ����� �����

    // ����������� ���������� ���������� �����
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < n; ++i) {
        randomNumbers[i] = rand() % 100;
    }
    sort(randomNumbers, randomNumbers + n);
    cout << "³����������� �����: ";
    for (int i = 0; i < n; ++i) {
        cout << randomNumbers[i] << " ";
    }
    cout << endl;

    return randomNumbers;  // ��������� �������� �� ������ ������� ������
}
     

int Publication::totalPublications = 0;
double Publication::maxDiscount = 0.2;
double Publication::minPrice = 5.0;

Publication::Publication(string title, double price, int subscriptionPeriod)
    : title(title), price(price), subscriptionPeriod(subscriptionPeriod) {
    totalPublications++;
}

string Publication::getTitle() const {
    return title;
}
double Publication::getPrice() const {
    return price;
}
int Publication::getSubscriptionPeriod() const {
    return subscriptionPeriod;
}

//��������� ��������
void Publication::addRating(int rating) {
    ratings.push_back(rating);
}

//��������� ���������� ��������
double Publication::getAverageRating() const {
    if (ratings.empty()) return 0.0;
    double sum = 0.0;
    for (int rating : ratings) {
        sum += rating;
    }
    return sum / ratings.size();
}

//������ ��� ������
void Publication::addFeedback(string feedback) {
    this->feedback = feedback;
}
void Publication::addFeedback(string feedback, int rating) {
    this->feedback = feedback;
    this->addRating(rating);
}

//����� �� ������� ��� ����� 
Publication Publication::getCopy() const {
    return *this;
}

void Publication::writeAllToFile(const vector<Publication>& publications, const string& filename) {
    ofstream outFile(filename, ios::trunc); // ³�������� ���� � ����� ����������
    if (outFile) {
        for (const auto& publication : publications) {
            outFile << publication.getTitle() << "\n"
                << publication.getPrice() << "\n"
                << publication.getSubscriptionPeriod() << "\n";
        }
    }
    else {
        cerr << "Error opening file for writing." << endl;
    }
}

vector<Publication> Publication::readAllFromFile(const string& filename) {
    vector<Publication> publications;
    ifstream inFile(filename);

    if (inFile) {
        while (true) {
            string title;
            double price;
            int subscriptionPeriod;

            if (!getline(inFile, title)) break; // ������� �����
            inFile >> price >> subscriptionPeriod;
            inFile.ignore(); // �������� ������ ������ ����� ���� ����������

            publications.emplace_back(title, price, subscriptionPeriod);
        }
        inFile.close();
    }
    else {
        cerr << "Error opening file for reading." << endl;
    }
    return publications;
}

