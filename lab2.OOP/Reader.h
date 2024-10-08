#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Publication;
class Reader
{
private:
	string name;
	int readerNumber;
	int subscriptionDaysLeft;
	/*bool blacklisted; */// Приватне поле, яке вказує, чи є читач в чорному списку
	double balance;

public:
	int totalReaders; // Загальна кількість читачів
	double discountRate; // Загальна знижка для читачів
	double minimumBalance; // Мінімальний баланс для підписки

	Reader(string name, int readerNumber, int subscriptionDaysLeft, double balance);
	
	string getName() const;
	double getBalance() const;
	int getSubscriptionDaysLeft() const;
	int getReaderNumber() const;
	void addBalance(double amount);//додавання грошей на рахунок
	void payForSubscription(double amount);//метод для сплати заявки
	void payForSubscription(double amount, double discount);//метод для сплати заявки
	bool compareBalance(const Reader& otherReader) const;//метод що приймає об'єкт класу як параметр
	void placeOrder(Publication& publication);//оформлення замовлення на видання (зв'язок між об'єктами)
	static void writeAllToFile(const vector<Reader>& readers, const string& filename);//запис у файл
	static vector<Reader> readAllFromFile(const string& filename);//зчитуаання з файлу
	int* generateAndSortRandomNumbers(int n);
};

class Publication {
private:
	string title;           
	double price;           
	int subscriptionPeriod; 
	vector<int> ratings;    
	string feedback; 

public:
	static int totalPublications;
	static double maxDiscount;
	static double minPrice;

	Publication(string title, double price, int subscriptionPeriod);

	string getTitle() const;
	double getPrice() const;
	int getSubscriptionPeriod() const;
	void addRating(int rating);
	double getAverageRating() const;
	void addFeedback(string feedback);
	void addFeedback(string feedback, int rating);
	Publication getCopy() const;
	static void writeAllToFile(const vector<Publication>& publications, const string& filename);
	static vector<Publication> readAllFromFile(const string& filename);
};
