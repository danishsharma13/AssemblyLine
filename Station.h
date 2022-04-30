// Name: Danish Sharma
// Seneca Student ID: 148201205
// Seneca email: dsharma115@gmail.com
// Date of completion: December 1, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <string>
namespace sdds {
	class Station {
		int m_id{};
		std::string m_item{};
		std::string m_description{};
		size_t m_serialNumber{};
		int m_stock{};
		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string&);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& ostr, bool full) const;
	};
}
#endif // !SDDS_STATION_H

