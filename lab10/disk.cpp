#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define LEFT 0
#define RIGHT 1
#define LOWER_CYLINDER 0
#define UPPER_CYLINDER 4999

int SSTF(vector<int> requests, int initialPos) {
    vector<int> localRequests = requests;
    int position = initialPos;
    int movement = 0;

    while (!localRequests.empty()) {
        auto closestIt = min_element(localRequests.begin(), localRequests.end(),
            [&position](int a, int b) {
                return abs(position - a) < abs(position - b);
            });
        int closest = *closestIt;
        movement += abs(position - closest);
        position = closest;
        localRequests.erase(closestIt);
    }
    return movement;
}

int FCFS(vector<int> requests, int initialPos) {
    int position = initialPos;
    int movement = 0;

    for (int req : requests) {
        movement += abs(position - req);
        position = req;
    }
    return movement;
}

int SCAN(vector<int> requests, int initialPos, int direction) {
    vector<int> localRequests = requests;
    localRequests.push_back(UPPER_CYLINDER);
    localRequests.push_back(LOWER_CYLINDER);
    sort(localRequests.begin(), localRequests.end());

    int position = initialPos;
    int movement = 0;
    int index = find(localRequests.begin(), localRequests.end(), initialPos) - localRequests.begin();

    if (direction == RIGHT) {
        for (int i = index; i < localRequests.size(); ++i) {
            movement += abs(position - localRequests[i]);
            position = localRequests[i];
        }
        for (int i = index - 1; i >= 0; --i) {
            movement += abs(position - localRequests[i]);
            position = localRequests[i];
        }
    } else {
        for (int i = index; i >= 0; --i) {
            movement += abs(position - localRequests[i]);
            position = localRequests[i];
        }
        for (int i = index + 1; i < localRequests.size(); ++i) {
            movement += abs(position - localRequests[i]);
            position = localRequests[i];
        }
    }
    return movement;
}

int C_SCAN(vector<int> requests, int initialPos) {
    vector<int> localRequests = requests;
    localRequests.push_back(UPPER_CYLINDER);
    sort(localRequests.begin(), localRequests.end());

    int position = initialPos;
    int movement = 0;
    int index = find(localRequests.begin(), localRequests.end(), initialPos) - localRequests.begin();

    for (int i = index; i < localRequests.size(); ++i) {
        movement += abs(position - localRequests[i]);
        position = localRequests[i];
    }
    movement += UPPER_CYLINDER;
    position = LOWER_CYLINDER;
    for (int i = 0; i < index; ++i) {
        movement += abs(position - localRequests[i]);
        position = localRequests[i];
    }
    return movement;
}

int main() {
    vector<int> requests;
    srand(time(0));
    for (int i = 0; i < 1000; ++i) {
        requests.push_back(rand() % 5000);
    }

    while (true) {
        cout << "tolgoin bairlal oruul (garah bol -1 oruul): ";
        int initialPos;
        cin >> initialPos;

        if (initialPos == -1) {
            break;
        }

        cout << "FCFS = " << FCFS(requests, initialPos) << endl;
        cout << "SSTF = " << SSTF(requests, initialPos) << endl;
        cout << "SCAN = " << SCAN(requests, initialPos, RIGHT) << endl;
        cout << "C-SCAN = " << C_SCAN(requests, initialPos) << endl;
    }

    return 0;
}