// Name: Danish Sharma
// Seneca Student ID: 148201205
// Seneca email: dsharma115@gmail.com
// Date of completion: December 1, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include "Station.h"
#include "Utilities.h"
#include <iomanip>
namespace sdds {
	size_t Station::m_widthField{};
	size_t Station::id_generator{};

	Station::Station(const std::string& singleRecord) {
		id_generator++;
		Utilities util;
		bool tf{};
		size_t position = 0;

		try {
			// Item Name
			m_item = util.extractToken(singleRecord, position, tf);

			// Serial Number
			m_serialNumber = std::stoi(util.extractToken(singleRecord, position, tf));

			// Stock Quantity
			m_stock = std::stoi(util.extractToken(singleRecord, position, tf));

			// Update Width Field
			m_widthField = util.getFieldWidth() > m_widthField ? util.getFieldWidth() : m_widthField;

			// Description
			m_description = util.extractToken(singleRecord, position, tf);
		}
		catch (std::string err_msg) {
			std::cout << err_msg;
		}

		m_id = id_generator;
	}

	const std::string& Station::getItemName() const {
		return m_item;
	}

	size_t Station::getNextSerialNumber() {
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const {
		return m_stock;
	}

	void Station::updateQuantity() {
		if (m_stock > 0) m_stock--;
	}

	void Station::display(std::ostream& ostr, bool full) const {
		ostr << "[" << std::right << std::setw(3) << std::setfill('0') << m_id << "]" << std::left << " Item: " << std::setw(m_widthField) << std::setfill(' ') << m_item 
			<< " [" << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << "]" << std::setfill(' ') << std::left;
		
		if (full) {
			ostr << " Quantity: " << std::setw(m_widthField) << m_stock << " Description: " << m_description;
		}

		ostr << std::endl;
	}
}