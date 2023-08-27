//
// Created by hakim15 on 8/24/23.
//

#include <bits/stdc++.h>
using namespace std;

char random_char() {
    return (char) (random() % 26 + 'a');
}

char random_tilde() {
    return (random() & 1) ? '~' : '\0';
}


void generate() {
    int n = random() % 10 + 40;
    cout << n;
    for(int i=0; i<n; ++i) {
        cout << endl << ((random() & 1) ? "~" : "") << random_char();
        if(random() % 26)
            cout << " " << ((random() & 1) ? "~" : "") << random_char();
    }
}

int main() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    generate();
}
