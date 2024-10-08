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
	/*bool blacklisted; */// �������� ����, ��� �����, �� � ����� � ������� ������
	double balance;

public:
	int totalReaders; // �������� ������� �������
	double discountRate; // �������� ������ ��� �������
	double minimumBalance; // ̳�������� ������ ��� �������

	Reader(string name, int readerNumber, int subscriptionDaysLeft, double balance);
	
	string getName() const;
	double getBalance() const;
	int getSubscriptionDaysLeft() const;
	int getReaderNumber() const;
	void addBalance(double amount);//��������� ������ �� �������
	void payForSubscription(double amount);//����� ��� ������ ������
	void payForSubscription(double amount, double discount);//����� ��� ������ ������
	bool compareBalance(const Reader& otherReader) const;//����� �� ������ ��'��� ����� �� ��������
	void placeOrder(Publication& publication);//���������� ���������� �� ������� (��'���� �� ��'������)
	static void writeAllToFile(const vector<Reader>& readers, const string& filename);//����� � ����
	static vector<Reader> readAllFromFile(const string& filename);//���������� � �����
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
