#include "Date.h"

bool Date::operator==(const Date& rhs) {
	if (this->d_year == rhs.d_year &&
		this->d_month == rhs.d_month &&
		this->d_day == rhs.d_day) {
		return true;
	}
	return false;
}

bool Date::operator<(const Date& rhs) {
	if (this->d_year < rhs.d_year) {
		return true;
	}
	if (this->d_year == rhs.d_year) {
		if (this->d_month < rhs.d_month) {
			return true;
		}

		if (this->d_month == rhs.d_month) {
			if (this->d_day < rhs.d_day) {
				return true;
			}
		}
	}
	return false;
}