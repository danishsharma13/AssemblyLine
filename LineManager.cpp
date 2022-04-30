// Name: Danish Sharma
// Seneca Student ID: 148201205
// Seneca email: dsharma115@gmail.com
// Date of completion: December 1, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
namespace sdds {
	// stations have all the active station vector list. So
	LineManager::LineManager(const std::string& fileName, const std::vector<Workstation*>& stations) {
		std::ifstream fileOpen(fileName);
		Utilities util{};
		std::string line{}, station_str{};
		Workstation* curr_station{};
		Workstation* next_station{};
		size_t position{ 0 };
		bool tf = true;
		
		
		if (fileOpen.is_open()) {
			while (getline(fileOpen, line, '\n')) {
				position = 0;
				station_str = util.extractToken(line, position, tf);
				auto activeFunc = [&](Workstation* station) {
					return station->getItemName() == station_str;
				};

				curr_station = *std::find_if(stations.begin(), stations.end(), activeFunc);

				if (tf) {
					station_str = util.extractToken(line, position, tf);
					next_station = *std::find_if(stations.begin(), stations.end(), activeFunc);
					curr_station->setNextStation(next_station);
				}
				else {
					station_str = {};
					curr_station->setNextStation(nullptr);
				}

				activeLine.push_back(curr_station);
			}
			
			auto firstStationFunc = [&](Workstation* station) {
				auto firstStationFunc2 = [&](Workstation* station2) {
					tf = true;
					if (station->getNextStation() == station2 && station2->getNextStation() != nullptr) {
						tf = false;
					}
					return tf;
				};

				m_firstStation = *std::find_if(stations.begin(), stations.end(), firstStationFunc2);
			};

			std::for_each(stations.begin(), stations.end(), firstStationFunc);
		}

		fileOpen.close();

		m_cntCustomerOrder = pending.size();
	}

	void LineManager::linkStations() {
		Workstation* curr_station{ nullptr };
		std::vector<Workstation*> activeLineTemp{};
		if (m_firstStation) {
			curr_station = m_firstStation;
			activeLineTemp.push_back(curr_station);

			while ((curr_station = curr_station->getNextStation()))
				activeLineTemp.push_back(curr_station);
		}
		activeLine = activeLineTemp;
	}

	bool LineManager::run(std::ostream& ostr) {
		bool tf = false;
		static size_t count{ 0 };
		count++;
		ostr << "Line Manager Iteration: " << count << std::endl;

		if (pending.empty() != true) {
			// Can use .front() or [0] to move the CustomerOrder
			*m_firstStation += std::move(pending.front());
			pending.pop_front();
		}

		auto fill = [&](Workstation* station) {
			station->fill(ostr);
		};

		std::for_each(activeLine.begin(), activeLine.end(), fill);

		auto moveAttempt = [&](Workstation* station) {
			station->attemptToMoveOrder();
		};

		std::for_each(activeLine.begin(), activeLine.end(), moveAttempt);

		if ((incomplete.size() + completed.size()) == m_cntCustomerOrder) {
			tf = true;
		}

		return tf;
	}

	void LineManager::display(std::ostream& ostr) const {
		auto displayActiveLine = [&](Workstation* station) {
			station->display(ostr);
		};
		std::for_each(activeLine.begin(), activeLine.end(), displayActiveLine);
	}
}