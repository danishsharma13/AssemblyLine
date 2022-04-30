// Name: Danish Sharma
// Seneca Student ID: 148201205
// Seneca email: dsharma115@gmail.com
// Date of completion: December 1, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include "CustomerOrder.h"
#include "Utilities.h"
#include <algorithm>
#include <iomanip>
namespace sdds {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() {}

	CustomerOrder::CustomerOrder(const std::string& line) {
		Utilities util;
		bool tf{};
		size_t position = 0;
		std::string tempLine{};

		try {
			// Customer Name
			m_name = util.extractToken(line, position, tf);

			// Order Name
			m_product = util.extractToken(line, position, tf);

			// List of items
			if (tf) {
				tempLine = line.substr(position, line.length() - position);
				m_cntItem = std::count(tempLine.begin(), tempLine.end(), util.getDelimiter());
				// Not counting the first delimiter, so need to add 1 to it
				m_cntItem++;

				m_lstItem = new Item* [m_cntItem];

				for (size_t i = 0; tf && i < m_cntItem; i++) {
					m_lstItem[i] = new Item(util.extractToken(line, position, tf));
				}
			}
			
			// Update Width Field
			m_widthField = util.getFieldWidth() > m_widthField ? util.getFieldWidth() : m_widthField;
		}
		catch (std::string err_msg) {
			std::cout << err_msg;
		}
	}
	
	CustomerOrder::CustomerOrder(const CustomerOrder& co) {
		throw std::string("Cannot make copies.");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept {
		*this = std::move(co);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept {
		if (this != &co) {
			m_name = co.m_name;
			m_product = co.m_product;

			if (m_lstItem != nullptr) {
				for (size_t i = 0; i < m_cntItem; i++) {
					delete m_lstItem[i];
				}
				delete[] m_lstItem;
			}
			m_lstItem = co.m_lstItem;
			m_cntItem = co.m_cntItem;

			co.m_name = "\0";
			co.m_product = "\0";
			co.m_cntItem = 0;
			co.m_lstItem = nullptr;
		}

		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
			m_lstItem[i] = nullptr;
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	bool CustomerOrder::isFilled() const {
		bool tf = true;

		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_isFilled == false) {
				tf = false;
			}
		}
		return tf;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool tf = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_isFilled == false && m_lstItem[i]->m_itemName == itemName) {
				tf = false;
			}
		}
		return tf;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& ostr) {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (1 <= station.getQuantity()) {
					m_lstItem[i]->m_isFilled = true;
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					station.updateQuantity();

					ostr << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else ostr << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
		}
	}

	void CustomerOrder::display(std::ostream& ostr) const {
		std::string fill{};
		ostr << m_name << " - " << m_product << std::endl;

		for (size_t i = 0; i < m_cntItem; i++) {

			if (m_lstItem[i]->m_isFilled) fill = "FILLED";
			else fill = "TO BE FILLED";

			ostr << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::left;
			ostr << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
			ostr << fill << std::endl;
		}
	}

}