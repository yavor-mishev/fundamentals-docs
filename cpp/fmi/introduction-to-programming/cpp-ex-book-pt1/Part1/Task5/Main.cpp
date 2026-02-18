#include <iostream>
using namespace std;

int main() {
	int age_years, age_months, age_days;
	cout << "Please enter your age: ";
	cin >> age_years >> age_months >> age_days;

	int age_days_total = age_years * 365 + age_days;
	int age_hours_total = age_days_total * 24;
	int age_min_total = age_hours_total * 60;
	int age_sec_total = age_min_total * 60;
	
	cout << "You have lived more than " << age_days_total << " days.\n";
	cout << "You have lived more than " << age_hours_total << " hours.\n";
	cout << "You have lived more than " << age_min_total << " minutes.\n";
	cout << "You have lived more than " << age_sec_total << " seconds.\n";

	return 0;
}