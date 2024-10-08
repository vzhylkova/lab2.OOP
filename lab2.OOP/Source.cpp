#include "Reader.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Ukrainian");

    Reader* readers[5];
    readers[0] = new Reader("John Doe", 1, 30, 100.0);
    readers[1] = new Reader("Jane Smith", 2, 15, 50.0);
    readers[2] = new Reader("Alice Johnson", 3, 20, 75.5);
    readers[3] = new Reader("Bob Brown", 4, 10, 25.0);
    readers[4] = new Reader("Charlie Black", 5, 5, 60.0);

    Publication publications[5] = {
       Publication("C++ Programming", 29.99, 30),
       Publication("Data Structures and Algorithms", 39.99, 45),
       Publication("Design Patterns", 49.99, 60),
       Publication("Artificial Intelligence", 59.99, 90),
       Publication("Web Development", 19.99, 30)
    };

    // ����� ��� ������� � ����
    vector<Reader> readersVector;
    for (int i = 0; i < 5; ++i) {
        readersVector.push_back(*readers[i]); // Dereference the pointers
    }
    Reader::writeAllToFile(readersVector, "readers.txt");

    // ����� ��� ��������� � ����
    Publication::writeAllToFile(vector<Publication>(publications, publications + 5), "publications.txt");

    // ������� ��� ������� � �����
    vector<Reader> allReaders = Reader::readAllFromFile("readers.txt");
    cout << "������:\n";
    for (const auto& reader : allReaders) {
        cout << "Name: " << reader.getName() << endl;
        cout << "Reader Number: " << reader.getReaderNumber() << endl;
        cout << "Days Left: " << reader.getSubscriptionDaysLeft() << endl;
        cout << "Balance: " << reader.getBalance() << endl;
        cout << endl;
    }
    vector<Publication> allPublications = Publication::readAllFromFile("publications.txt");

    // ��������� ���������� ��� ���������
    cout << "���������:\n";
    for (const auto& publication : allPublications) {
        cout << "Title: " << publication.getTitle() << endl;
        cout << "Price: " << publication.getPrice() << endl;
        cout << "Subscription Period: " << publication.getSubscriptionPeriod() << endl;
        cout << "Average Rating: " << publication.getAverageRating() << endl;
        cout << endl;
    }

    // ������������ ��������� �� ��������� ����� Reader
    cout << "������������ ������������ ��������� �� ��������� ����� Reader:\n";
    Reader* readerPtr = readers[0];  // ��������� ��������� �� ��'���

    cout << readerPtr->getName() << " �� ������: " << readerPtr->getBalance() << endl;
    readerPtr->addBalance(75);
    cout << "" << readerPtr->getBalance() << endl;

    cout << readers[1]->getName() << " � ������� " << readers[1]->getReaderNumber() << " �� �� ��������� ������� " << readers[1]->getSubscriptionDaysLeft() << " ���." << endl;
    readers[1]->payForSubscription(50.0);
    cout << "���������� �� ������� ������ ������ " << readers[1]->getBalance() << " �� ������� ��� �� ��������� ������� " << readers[1]->getSubscriptionDaysLeft() << endl;
    cout << readers[4]->getName() << " � ������� " << readers[4]->getReaderNumber() << " �� �� ��������� ������� " << readers[4]->getSubscriptionDaysLeft() << " ���, �� ������ " << readers[4]->getBalance() <<endl;
    readers[4]->payForSubscription(50, 10);
    cout << "���������� �� ������� ������ ������ " << readers[4]->getBalance() << " �� ������� ��� �� ��������� ������� " << readers[4]->getSubscriptionDaysLeft() << endl;

    if (readerPtr->compareBalance(*readers[2])) {
        cout << readerPtr->getName() << " �� ������ ������, �� " << readers[2]->getName() << endl;
    }
    else {
        cout << readers[2]->getName() << " �� ������ ��� ����� ������, �� " << readerPtr->getName() << endl;
    }

    readers[3]->placeOrder(publications[1]);
    readerPtr->placeOrder(publications[2]);

    readers[4]->generateAndSortRandomNumbers(5);

    // ������������ ��� ������ ��� Publication
    cout << "\n������������ ������ ����� Publication:\n";
    cout << "����� ���������: " << publications[0].getTitle() << endl;
    cout << "ֳ�� �������: " << publications[0].getPrice() << endl;
    cout << "����� �������: " << publications[0].getSubscriptionPeriod() << endl;
    // ��������� �������� �� ������
    publications[1].addRating(5);
    publications[0].addRating(4);
    publications[0].addFeedback("���� ������� �����!", 5);
    cout << "������� ������� ���������: " << publications[0].getAverageRating() << endl;

    Publication copyOfPublication = publications[0].getCopy();
    cout << "���� ���������: " << copyOfPublication.getTitle() << " � �����: " << copyOfPublication.getPrice() << endl;

    // �������� ���'�� ��� ��������� ��'����
    for (int i = 0; i < 5; ++i) {
        delete readers[i];
    }
    return 0;
}