#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct problema {
    string idProblema, specializare;
    int duration, priority;

    bool operator<(const problema& a) const {
        return a.priority > priority;
    }
}problems[10000];

struct doctor {
    string idDoctor, specializare;
    int worked_hours, nr_problems_solved;
    vector<string> problems_solved;
}doctors[10000];


vector<doctor> d;
priority_queue<problema> pq;
int main()
{
    ifstream inFile("input.txt");
    int n;

    inFile >> n;
    for (int i = 0; i < n; i++) {
        inFile >> problems[i].idProblema >> problems[i].specializare >> problems[i].duration >> problems[i].priority;
        pq.push(problems[i]);
    }
    inFile >> n;
    for (int i = 0; i < n; i++) {
        inFile >> doctors[i].idDoctor >> doctors[i].specializare;
        d.push_back(doctors[i]);
    }

    while (!pq.empty()) {
        problema current = pq.top();

        auto it = find_if(d.begin(), d.end(), [&current](const doctor& Dr) {
            return (Dr.specializare == current.specializare) && (current.duration + Dr.worked_hours <= 8);
            });

        if (it != d.end()) {
            it->worked_hours += current.duration;
            it->problems_solved.push_back(current.idProblema);
            it->nr_problems_solved += 1;
        }

        pq.pop();
    }

    for (const auto& doc : d) {
        if (doc.nr_problems_solved > 0) {
            cout << doc.idDoctor << ": " << doc.nr_problems_solved << " ";
            for (const auto& prob : doc.problems_solved) {
                cout << prob << " ";
            }
            cout << endl;
        }
    }

    return 0;
}