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

    // Запис усіх читачів у файл
    vector<Reader> readersVector;
    for (int i = 0; i < 5; ++i) {
        readersVector.push_back(*readers[i]); // Dereference the pointers
    }
    Reader::writeAllToFile(readersVector, "readers.txt");

    // Запис усіх публікацій у файл
    Publication::writeAllToFile(vector<Publication>(publications, publications + 5), "publications.txt");

    // Читання всіх читачів з файлу
    vector<Reader> allReaders = Reader::readAllFromFile("readers.txt");
    cout << "Читачі:\n";
    for (const auto& reader : allReaders) {
        cout << "Name: " << reader.getName() << endl;
        cout << "Reader Number: " << reader.getReaderNumber() << endl;
        cout << "Days Left: " << reader.getSubscriptionDaysLeft() << endl;
        cout << "Balance: " << reader.getBalance() << endl;
        cout << endl;
    }
    vector<Publication> allPublications = Publication::readAllFromFile("publications.txt");

    // Виведення інформації про публікації
    cout << "Публікації:\n";
    for (const auto& publication : allPublications) {
        cout << "Title: " << publication.getTitle() << endl;
        cout << "Price: " << publication.getPrice() << endl;
        cout << "Subscription Period: " << publication.getSubscriptionPeriod() << endl;
        cout << "Average Rating: " << publication.getAverageRating() << endl;
        cout << endl;
    }

    // Використання покажчика на екземпляр класу Reader
    cout << "Демонстрація використання покажчика на екземпляр класу Reader:\n";
    Reader* readerPtr = readers[0];  // Створення покажчика на об'єкт

    cout << readerPtr->getName() << " має баланс: " << readerPtr->getBalance() << endl;
    readerPtr->addBalance(75);
    cout << "" << readerPtr->getBalance() << endl;

    cout << readers[1]->getName() << " з номером " << readers[1]->getReaderNumber() << " має до закінчення підписки " << readers[1]->getSubscriptionDaysLeft() << " днів." << endl;
    readers[1]->payForSubscription(50.0);
    cout << "Заплативши за підписку баланс читача " << readers[1]->getBalance() << " та кількість днів до закінчення підписки " << readers[1]->getSubscriptionDaysLeft() << endl;
    cout << readers[4]->getName() << " з номером " << readers[4]->getReaderNumber() << " має до закінчення підписки " << readers[4]->getSubscriptionDaysLeft() << " днів, та баланс " << readers[4]->getBalance() <<endl;
    readers[4]->payForSubscription(50, 10);
    cout << "Заплативши за підписку баланс читача " << readers[4]->getBalance() << " та кількість днів до закінчення підписки " << readers[4]->getSubscriptionDaysLeft() << endl;

    if (readerPtr->compareBalance(*readers[2])) {
        cout << readerPtr->getName() << " має більший баланс, ніж " << readers[2]->getName() << endl;
    }
    else {
        cout << readers[2]->getName() << " має більший або рівний баланс, ніж " << readerPtr->getName() << endl;
    }

    readers[3]->placeOrder(publications[1]);
    readerPtr->placeOrder(publications[2]);

    readers[4]->generateAndSortRandomNumbers(5);

    // Демонстрація всіх методів для Publication
    cout << "\nДемонстрація методів класу Publication:\n";
    cout << "Назва публікації: " << publications[0].getTitle() << endl;
    cout << "Ціна підписки: " << publications[0].getPrice() << endl;
    cout << "Термін підписки: " << publications[0].getSubscriptionPeriod() << endl;
    // Додавання рейтингу та відгуків
    publications[1].addRating(5);
    publications[0].addRating(4);
    publications[0].addFeedback("Дуже корисна книга!", 5);
    cout << "Середній рейтинг публікації: " << publications[0].getAverageRating() << endl;

    Publication copyOfPublication = publications[0].getCopy();
    cout << "Копія публікації: " << copyOfPublication.getTitle() << " з ціною: " << copyOfPublication.getPrice() << endl;

    // Очищення пам'яті для динамічних об'єктів
    for (int i = 0; i < 5; ++i) {
        delete readers[i];
    }
    return 0;
}