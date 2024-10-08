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

//Методи для отримання інформації читача
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

//Метод для додавання грошей на рахунок
void Reader::addBalance(double amount) {
    balance += amount;
}

//Перевантажені методи для сплати заявки
void Reader::payForSubscription(double amount) {
    if (balance >= amount) {
        balance -= amount;
        subscriptionDaysLeft += 30;
    }
    else
    {
        cout << "Не вистачає грошей на рахунку" << endl;
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
        cout << "Не вистачає грошей на рахунку" << endl;
    }
}

//Метод, що приймає об'єкт класу як параметр
bool Reader::compareBalance(const Reader& otherReader) const {
    return this->balance > otherReader.balance;
}

//Метод для оформлення замовлення на видання
void Reader::placeOrder(Publication& publication) {
    if (balance >= publication.getPrice()) {
        balance -= publication.getPrice();
        subscriptionDaysLeft += publication.getSubscriptionPeriod();
        cout << name << " успішно підписався на " << publication.getTitle() << "." << endl;
    }
    else {
        cout << name << " не має достатньо коштів для підписки на " << publication.getTitle() << "." << endl;
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

            if (!getline(inFile, name)) break; // Зчитуємо ім'я
            inFile >> readerNumber >> subscriptionDaysLeft >> balance;
            inFile.ignore(); // Ігноруємо символ нового рядка після зчитування double

            readers.emplace_back(name, readerNumber, subscriptionDaysLeft, balance);
        }
        inFile.close();
    }
    else {
        cerr << "Помилка відкриття файлу для читання." << endl;
    }
    return readers;
}

int* Reader::generateAndSortRandomNumbers(int n) {
    int* randomNumbers = new int[n];  // Виділення динамічної пам'яті для масиву цілих чисел

    // Ініціалізація генератора випадкових чисел
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < n; ++i) {
        randomNumbers[i] = rand() % 100;
    }
    sort(randomNumbers, randomNumbers + n);
    cout << "Відсортований масив: ";
    for (int i = 0; i < n; ++i) {
        cout << randomNumbers[i] << " ";
    }
    cout << endl;

    return randomNumbers;  // Повертаємо вказівник на перший елемент масиву
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

//додавання рейтингу
void Publication::addRating(int rating) {
    ratings.push_back(rating);
}

//отримання середнього рейтингу
double Publication::getAverageRating() const {
    if (ratings.empty()) return 0.0;
    double sum = 0.0;
    for (int rating : ratings) {
        sum += rating;
    }
    return sum / ratings.size();
}

//методи для відгуків
void Publication::addFeedback(string feedback) {
    this->feedback = feedback;
}
void Publication::addFeedback(string feedback, int rating) {
    this->feedback = feedback;
    this->addRating(rating);
}

//метод що повертає тип класу 
Publication Publication::getCopy() const {
    return *this;
}

void Publication::writeAllToFile(const vector<Publication>& publications, const string& filename) {
    ofstream outFile(filename, ios::trunc); // Відкриваємо файл в режимі перезапису
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

            if (!getline(inFile, title)) break; // Зчитуємо назву
            inFile >> price >> subscriptionPeriod;
            inFile.ignore(); // Ігноруємо символ нового рядка після зчитування

            publications.emplace_back(title, price, subscriptionPeriod);
        }
        inFile.close();
    }
    else {
        cerr << "Error opening file for reading." << endl;
    }
    return publications;
}

