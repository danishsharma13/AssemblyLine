// Name: Danish Sharma
// Seneca Student ID: 148201205
// Seneca email: dsharma115@gmail.com
// Date of completion: December 1, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include "Station.h"
namespace sdds {
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder {
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};
		static size_t m_widthField;
	public:
		// Constructors
		CustomerOrder();
		CustomerOrder(const std::string&);

		// Copy
		CustomerOrder(const CustomerOrder&);
		CustomerOrder& operator=(const CustomerOrder&) = delete;

		// Move
		CustomerOrder(CustomerOrder&&) noexcept;
		CustomerOrder& operator=(CustomerOrder&&) noexcept;

		// Destructor
		~CustomerOrder();

		bool isFilled() const;
		bool isItemFilled(const std::string&) const;
		void fillItem(Station&, std::ostream&);

		void display(std::ostream&) const;

	};
}
#endif // !SDDS_CUSTOMERORDER_H

