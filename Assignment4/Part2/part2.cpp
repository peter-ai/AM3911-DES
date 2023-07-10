#include <iostream>
#include <queue>
using namespace std;

int main() {
	const int CUSTOMERS = 9;
	double arrival_times[CUSTOMERS] = { 3.2, 5.5, 11.4, 14.8, 17.7, 18.5, 22.7, 24.3, 32.2 };
	double service_times[CUSTOMERS] = { 2.8, 3.1, 5.2, 1.6, 3.4, 3.5, 2.9, 1.8, 2.1 };
	double start_service[CUSTOMERS] = { 0.0 };
	double departure_times[CUSTOMERS] = { 0.0 };

	bool teller1_idle = true;
	bool teller2_idle = true;

	int arrival_count = 0, departure_count = 0;
	
	queue <double> line1;
	queue <double> line2;

	double arrival_event = arrival_times[arrival_count], departure_event = arrival_times[arrival_count];
	double current_time, time_queue, time_bank;
	double avg_time_queue = 0.0, avg_time_bank = 0.0;

	while (departure_count != CUSTOMERS - 1) {
		// Arrival Event
		if (arrival_event <= departure_event && arrival_count != CUSTOMERS) {
			current_time = arrival_times[arrival_count];

			if (line1.size() <= line2.size()) {
				if (teller1_idle) {
					teller1_idle = false;

					start_service[arrival_count] = current_time;

					departure_event = current_time + service_times[arrival_count];
					departure_times[arrival_count] = departure_event;
				}
				else {
					line1.push(service_times[arrival_count]);
					cout << "Line 1 (" << departure_event << ") Size(" << line1.size() << ")\n";

				}
			}
			else {
				if (teller2_idle) {
					teller2_idle = false;

					start_service[arrival_count] = current_time;

					departure_event = current_time + service_times[arrival_count];
					departure_times[arrival_count] = departure_event;
				}
				else {
					line2.push(service_times[arrival_count]);
					cout << "Line 2 (" << departure_event << ") Size(" << line2.size() << ")\n";

				}
			}
			
			arrival_count++;
			if (arrival_count < CUSTOMERS) {
				arrival_event = arrival_times[arrival_count];
			}
			cout << current_time << " Arrival " << arrival_event << " " << departure_event << "\n";

			
		}
		// Departure Event
		else {
			current_time = departure_times[departure_count];
			departure_count++;


			if (line1.size() == 0 && line2.size() == 0) { 
				teller1_idle = true;
				teller2_idle = true;
				departure_event = arrival_event + service_times[arrival_count];
			}
			else {
				if (line1.size() != 0 && line2.size() == 0) { // || line1.front() <= line2.front()
					teller1_idle = false;
					teller2_idle = true;

					start_service[departure_count] = current_time;

					departure_event = current_time + line1.front();
					line1.pop();

					departure_times[departure_count] = departure_event;
				}
				else if (line1.size() == 0 && line2.size() != 0) {
					teller1_idle = true;
					teller2_idle = false;

					start_service[departure_count] = current_time;

					departure_event = current_time + line2.front();
					line2.pop();

					departure_times[departure_count] = departure_event;
				}
				else {
					teller1_idle = false;
					teller2_idle = false;
					if (line1.front() <= line2.front()) {
						start_service[departure_count] = current_time;

						departure_event = current_time + line1.front();
						line1.pop();

						departure_times[departure_count] = departure_event;
					}
					else {
						start_service[departure_count] = current_time;

						departure_event = current_time + line2.front();
						line2.pop();

						departure_times[departure_count] = departure_event;
					}
				}
			}
			cout << current_time << " Departure " << arrival_event << " " << departure_event << " ";
			if (line1.empty() == 0) {
				cout << line1.front() << "\n";
			}
			else {
				cout << "\n";
			}
				//" " << line1.front() <<
		}
	}

	for (int i = 0; i < CUSTOMERS; i++) {
		cout << i + 1 << "  " << arrival_times[i] << "  " << start_service[i] << "  " << departure_times[i] << "  ";
		time_queue = start_service[i] - arrival_times[i];
		time_bank = departure_times[i] - arrival_times[i];
		cout << time_queue << "  " << time_bank << "\n";
		avg_time_queue += time_queue;
		avg_time_bank += time_bank;
	}
	avg_time_queue /= CUSTOMERS; // CUSTOMERS;
	avg_time_bank /= CUSTOMERS; // CUSTOMERS;
	cout << "Average Time Spent In Queue: " << avg_time_queue << "\n";
	cout << "Average Time Spent In Bank: " << avg_time_bank << "\n";


	return 0;
}