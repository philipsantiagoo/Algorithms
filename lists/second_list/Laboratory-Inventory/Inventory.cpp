#include <iostream>


struct Entry {
    char name[31];
    int quantity;
    Entry* next;
};


const int SIZE = 200003;
Entry* table[SIZE];


int hashName(const char* name) {
    long long h = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        h = (h * 31 + name[i]) % SIZE;
    }
    return h;
}


bool equals(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}


void copy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}


Entry* search(const char* name) {
    int index = hashName(name);
    Entry* current = table[index];
    while (current != nullptr) {
        if (equals(current->name, name)) return current;
        current = current->next;
    }
    return nullptr;
}


void insert(const char* name, int quantity) {
    Entry* e = search(name);
    if (e != nullptr) {
        e->quantity += quantity;
        return;
    }
    int index = hashName(name);
    Entry* newEntry = new Entry();
    copy(newEntry->name, name);
    newEntry->quantity = quantity;
    newEntry->next = table[index];
    table[index] = newEntry;
}


void remove(const char* name) {
    int index = hashName(name);
    Entry* current = table[index];
    Entry* previous = nullptr;
    while (current != nullptr) {
        if (equals(current->name, name)) {
            if (previous == nullptr) table[index] = current->next;
            else previous->next = current->next;
            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
}


struct Pair {
    char name[31];
    int quantity;
};


void swap(Pair& a, Pair& b) {
    Pair temp = a;
    a = b;
    b = temp;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    for (int i = 0; i < SIZE; i++) table[i] = nullptr;

    int N;
    std::cin >> N;

    for (int i = 0; i < N; i++) {
        char command[10];
        std::cin >> command;

        if (equals(command, "ENTRADA")) {
            char name[31];
            int qty;
            std::cin >> name >> qty;
            insert(name, qty);

        } else if (equals(command, "CONSUMO")) {
            char name[31];
            int qty;
            std::cin >> name >> qty;
            Entry* e = search(name);
            if (e != nullptr) {
                e->quantity -= qty;
                if (e->quantity <= 0) remove(name);
            }

        } else if (equals(command, "CONSULTA")) {
            char name[31];
            std::cin >> name;
            Entry* e = search(name);
            if (e == nullptr) std::cout << "AUSENTE\n";
            else std::cout << e->quantity << '\n';

        } else if (equals(command, "CRITICOS")) {
            int k;
            std::cin >> k;

            Pair criticals[200000];
            int total = 0;

            for (int j = 0; j < SIZE; j++) {
                Entry* current = table[j];
                while (current != nullptr) {
                    if (current->quantity <= k) {
                        copy(criticals[total].name, current->name);
                        criticals[total].quantity = current->quantity;
                        total++;
                    }
                    current = current->next;
                }
            }

            if (total == 0) {
                std::cout << "NENHUM\n";
            } else {
                for (int a = 1; a < total; a++) {
                    Pair key = criticals[a];
                    int b = a - 1;
                    while (b >= 0 && (criticals[b].quantity > key.quantity ||
                           (criticals[b].quantity == key.quantity && !equals(criticals[b].name, key.name) && criticals[b].name[0] > key.name[0]))) {
                        criticals[b + 1] = criticals[b];
                        b--;
                    }
                    criticals[b + 1] = key;
                }
                for (int a = 0; a < total; a++)
                    std::cout << criticals[a].name << ' ' << criticals[a].quantity << '\n';
            }
        }
    }

    return 0;
}