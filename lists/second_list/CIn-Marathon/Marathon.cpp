#include <iostream>
#include <cstring>

struct Participant {
    char name[31];
    int time;
};

int compare(const void* a, const void* b) {
    Participant* pa = (Participant*) a;
    Participant* pb = (Participant*) b;

    if (pa->time != pb->time) {
        return pa->time - pb->time;
    }

    return strcmp(pa->name, pb->name);
}

int main() {
    int c;
    std::cin >> c;

    Participant participants[100000];

    for (int i = 0; i < c; i++) {
        std::cin >> participants[i].name >> participants[i].time;
    }

    qsort(participants, c, sizeof(Participant), compare);

    for (int i = 0; i < c; i++) {
        std::cout << participants[i].name << ' ' << participants[i].time << '\n';
    }

    return 0;
}