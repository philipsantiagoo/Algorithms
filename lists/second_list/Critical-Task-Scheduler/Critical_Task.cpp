#include <iostream>
#include <string>


struct Task {
    std::string id;
    int priority;
    int time;
};


struct Comparator {
    bool operator()(const Task &a, const Task &b) const {
        if (a.priority != b.priority) {
            return a.priority < b.priority;
        }

        if (a.time != b.time) {
            return a.time > b.time;
        }

        return a.id > b.id;
    }
};


void heapify_up(Task arr[], int i) {
    Comparator comp;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (!comp(arr[parent], arr[i])) {
            break;
        }
        Task temp = arr[i];
        arr[i] = arr[parent];
        arr[parent] = temp;
        i = parent;
    }
}


void heapify_down(Task arr[], int i, int size) {
    Comparator comp;
    while (true) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int best = i;

        if (left < size && comp(arr[best], arr[left])) {
            best = left;
        }

        if (right < size && comp(arr[best], arr[right])) {
            best = right;
        }

        if (best == i) {
            break;
        }

        Task temp = arr[i];
        arr[i] = arr[best];
        arr[best] = temp;
        i = best;
    }
}


int main() {
    int offset = 0;
    int Q; 
    Task pq[100000];
    int size = 0;

    std::cin >> Q;

    for (int i = 0; i < Q; i++) {
        std::string command;
        std::cin >> command;

        if (command == "ADD") {
            Task task;
            std::cin >> task.id >> task.priority >> task.time;
            task.priority -= offset;
            pq[size] = task;
            heapify_up(pq, size);
            size++;

        } else if (command == "RUN") {
            if (size == 0) {
                std::cout << "IDLE\n";
            } else {
                std::cout << pq[0].id << '\n';
                size--;
                if (size > 0) {
                    pq[0] = pq[size];
                    heapify_down(pq, 0, size);
                }
            }

        } else if (command == "BOOST") {
            int k;
            std::cin >> k;
            if (size > 0) {
                offset += k;
            }
        }
    }

    return 0;
}
