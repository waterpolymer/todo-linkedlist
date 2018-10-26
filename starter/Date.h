#ifndef DATE_H
#define DATE_H

class Date {
private:
	int d_month;
	int d_day;
	int d_year;
public:
	//Date() : d_month(0), d_day(0), d_year(0) {};
	Date(int month, int day, int year) : d_month(month), d_day(day), d_year(year) {};
	~Date() {};

	int getMonth() const{ return d_month; };
	int getDay() const{ return d_day; };
	int getYear() const{ return d_year; };
	
	
	bool operator==(const Date& rhs); 
	bool operator<(const Date& rhs); 

};

#endif //DATE_H