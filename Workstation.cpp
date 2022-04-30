// Name: Danish Sharma
// Seneca Student ID: 148201205
// Seneca email: dsharma115@gmail.com
// Date of completion: December 1, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"
namespace sdds {
	// Global double ended queues of CustomerOrder
	std::deque<CustomerOrder> pending{};
	std::deque<CustomerOrder> incomplete{};
	std::deque<CustomerOrder> completed{};
	
	void Workstation::fill(std::ostream& ostr) {
		// Can either use [0] or .front on m_orders to fill Customer's order
		if (m_orders.empty() == false) m_orders[0].fillItem(*this, ostr);
	}

	bool Workstation::attemptToMoveOrder() {
		bool tf;

		if (m_orders.empty() == true) tf = false;
		else {
			// Can either use [0] or .front on m_orders
			if (this->getQuantity() <= 0 || m_orders[0].isItemFilled(getItemName())) {
				if (!m_pNextStation) {
					if (m_orders[0].isFilled() == false) {
						// Can either use [0] or .front on m_orders
						incomplete.push_back(std::move(m_orders[0]));
					}
					else if (m_orders[0].isFilled() == true) {
						// Can either use [0] or .front on m_orders
						completed.push_back(std::move(m_orders[0]));
					}
				}
				else {
					// Can either use [0] or .front on m_orders
					*m_pNextStation += std::move(m_orders[0]);
				}

				m_orders.pop_front();
			}
			tf = true;
		}
		return tf;
	}

	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& ostr) const {
		if (!m_pNextStation) {
			ostr << getItemName() << " --> End of Line";
		}
		else {
			ostr << getItemName() << " --> ";
			ostr << getNextStation()->getItemName();
		}
		ostr << std::endl;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}
