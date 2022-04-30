// Name: Danish Sharma
// Seneca Student ID: 148201205
// Seneca email: dsharma115@gmail.com
// Date of completion: December 1, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_LINEMANAGER_SDDS
#define SDDS_LINEMANAGER_SDDS
#include <vector>
#include "Workstation.h"
namespace sdds {
	class LineManager {
		std::vector<Workstation*> activeLine{};
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};
	public:
		LineManager(const std::string&, const std::vector<Workstation*>&);
		void linkStations();
		bool run(std::ostream&);
		void display(std::ostream&) const;
	};
}
#endif // !SDDS_LINEMANAGER_SDDS


