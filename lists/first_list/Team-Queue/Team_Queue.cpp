#include <iostream>

int main () {
    // Maps each element to its team index.
    int element_belonging_team[1000000];
    // Array-based queue storing elements in team-queue order.
    int queue[10000];
    int start_queue = 0;
    int end_queue = 0;
    int scenario = 1;

    int t;
    // Read number of teams per test case. Stops when t == 0.
    while (std::cin >> t && t != 0) {
        std::cout << "Scenario #" << scenario << std::endl;
        scenario++;

        start_queue = 0;
        end_queue = 0;

        // Read team descriptions and map each element to its team index.
        for (int j = 0; j < t; j++) {
            int number_elements;
            std::cin >> number_elements;
            
            for (int k = 0; k < number_elements; k++) {
                int element;
                std::cin >> element;
                element_belonging_team[element] = j;
            }
        }

        std::string command;
        while (std::cin >> command && command != "STOP") {
            if (command == "ENQUEUE") {
                int x;
                std::cin >> x;

                int team_x = element_belonging_team[x];

                // Search for the last teammate of x in the queue.
                int last_teammate = -1;
                for (int w = start_queue; w < end_queue; w++) {
                    if (element_belonging_team[queue[w]] == team_x) {
                        last_teammate = w;
                    }
                }

                if (last_teammate == -1) {
                    // No teammate found: insert at the end.
                    queue[end_queue] = x;
                    end_queue++;
                } else {
                    // Teammate found: shift elements right and insert after last teammate.
                    for (int m = end_queue; m > last_teammate + 1; m--) {
                        queue[m] = queue[m - 1];
                    }
                    queue[last_teammate + 1] = x;
                    end_queue++;
                }
            } else if (command == "DEQUEUE") {
                // Remove and print the front element of the queue.
                std::cout << queue[start_queue] << std::endl;
                start_queue++;
            }
        }
        // Blank line after each test case.
        std::cout << std::endl;
    }
}