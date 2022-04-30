// Name: Danish Sharma
// Seneca Student ID: 148201205
// Seneca email: dsharma115@gmail.com
// Date of completion: December 1, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include "CustomerOrder.h"
#include <deque>
namespace sdds {
	// Global double ended queues of CustomerOrder
	extern std::deque<CustomerOrder> pending;
	extern std::deque<CustomerOrder> incomplete;
	extern std::deque<CustomerOrder> completed;

	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{};
	public:
		// Contrustors
		Workstation(const std::string& line) : Station(line) {}

		// Copy
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;

		// Move
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;

		void fill(std::ostream&);
		bool attemptToMoveOrder();
		
		void setNextStation(Workstation*);
		Workstation* getNextStation() const;

		void display(std::ostream&) const;

		Workstation& operator+=(CustomerOrder&&);
	};
}
#endif // !SDDS_WORKSTATION_H

