// Name: Danish Sharma
// Seneca Student ID: 148201205
// Seneca email: dsharma115@gmail.com
// Date of completion: December 1, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include "Utilities.h"
namespace sdds {
	char Utilities::m_delimiter;

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string extract = "";
		size_t found = str.find(m_delimiter, next_pos);
		if (found != next_pos) {
			extract = str.substr(next_pos, found - next_pos);
			m_widthField = extract.size() > m_widthField ? extract.size() : m_widthField;
			more = found != std::string::npos ? true : false;
			next_pos = more ? found + 1 : found;
		}
		else {
			more = false;
			throw std::string("No delimiter found!");
		}
		return extract;
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}
}
