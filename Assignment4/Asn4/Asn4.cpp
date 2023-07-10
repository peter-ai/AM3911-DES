#include <iostream>
#include <queue>
using namespace std;

int main() {
	const int CUSTOMERS = 13;
	double arrival_times[CUSTOMERS] = {3.2, 10.9, 13.2, 14.8, 17.7, 19.8, 21.5, 26.3, 32.1, 36.6, 40.0, 41.0, 41.3};
	double service_times[CUSTOMERS] = {3.8, 3.5, 4.2, 3.1, 2.4, 4.3, 2.7, 2.1, 2.5, 3.4, 2.0, 5.0, 3.0};
	double start_service[CUSTOMERS] = { 0.0 };
	double departure_times[CUSTOMERS] = { 0.0 };

	bool teller_idle = true;
	int arrival_count = 0, departure_count = 0;
	queue <double> line;
	double arrival_event = arrival_times[arrival_count], departure_event = arrival_times[arrival_count];
	double current_time, time_queue, time_bank;
	double avg_time_queue = 0.0, avg_time_bank = 0.0, idle_time = 3.2;


	while (departure_count != CUSTOMERS - 1) {
		// Arrival Event
		if (arrival_event <= departure_event && arrival_count != CUSTOMERS) {
			current_time = arrival_times[arrival_count];

			if (teller_idle) {
				teller_idle = false;

				start_service[arrival_count] = current_time;

				departure_event = current_time + service_times[arrival_count];
				departure_times[arrival_count] = departure_event;
			}
			else {
				line.push(service_times[arrival_count]);
			}

			arrival_count++;
			if (arrival_count < CUSTOMERS) {
				arrival_event = arrival_times[arrival_count];
			}
		}
		// Departure Event
		else {
			current_time = departure_times[departure_count];
			departure_count++;
			

			if (line.size() == 0) {
				teller_idle = true;
				departure_event = arrival_event + service_times[arrival_count];
			}
			else {
				teller_idle = false;

				start_service[departure_count] = current_time;

				departure_event = current_time + line.front();
				line.pop();


				departure_times[departure_count] = departure_event;
				
			}


			
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
	avg_time_queue /= CUSTOMERS;
	avg_time_bank /= CUSTOMERS;
	cout << "Average Time Spent In Queue: " << avg_time_queue << "\n";
	cout << "Average Time Spent In Bank: " << avg_time_bank << "\n";



	return 0;
}