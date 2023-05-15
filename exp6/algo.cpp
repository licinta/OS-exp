#include <algorithm>
#include <charconv>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#define ACTIVE 1
#define UNACTIVE 0
#define N 5
#define time int
using namespace std;
typedef struct {
    int id;
    char name[16];
    time arrival;
    time serve;
    time finish;
} job;

typedef struct {
    float turnarround;
    float averrage_turnarround;
} result;

job default_workset[5];

void init()
{
    job workset[5] = { job({ 0, "A", 0, 4, -1 }), job({ 1, "B", 1, 3, -1 }), job({ 2, "C", 2, 4, -1 }),
        job({ 3, "D", 3, 2, -1 }), job({ 4, "E", 4, 4, -1 }) };
    memcpy(default_workset, workset, sizeof workset);
    cout << "The jobs are following:\n";
    printf("%7s\t%7s\t%7s\t%7s\t\n", "id", "name", "arvl", "serve");
    for (int i = 0; i < N; ++i) {
        printf("%7d\t%7s\t%7d\t%7d\t\n", default_workset[i].id, default_workset[i].name, default_workset[i].arrival,
            default_workset[i].serve);
    }
}
void prt()
{
    cout << "The jobs are following:\n";
    printf("%7s\t%7s\t%7s\t%7s\t%7s\t\n", "id", "name", "arvl", "serve", "finish");
    for (int i = 0; i < N; ++i) {
        printf("%7d\t%7s\t%7d\t%7d\t%7d\t\n", default_workset[i].id, default_workset[i].name,
            default_workset[i].arrival, default_workset[i].serve, default_workset[i].finish);
    }
}
bool comp_FCFS(const job& j1, const job& j2) { return j1.arrival < j2.arrival; }
bool comp_SJF(const job& j1, const job& j2)
{
    if (j1.serve == j2.serve)
        return j1.arrival < j2.arrival;
    return j1.serve < j2.serve;
}
void FCFS()
{
    init();
    sort(default_workset, default_workset + 5, comp_FCFS);
    for (int i = 0; i < N; ++i) {
        if (i == 0) {
            default_workset[i].finish = default_workset[i].arrival + default_workset[i].serve;
        } else {
            if (default_workset[i].arrival < default_workset[i - 1].finish) {
                default_workset[i].finish = default_workset[i - 1].finish + default_workset[i].serve;
            } else {
                default_workset[i].finish = default_workset[i].arrival + default_workset[i].serve;
            }
        }
    }
    prt();
    return;
}

void SJF()
{
    init();
    sort(default_workset, default_workset + 5, comp_SJF);
    for (int i = 0; i < N; ++i) {
        if (i == 0) {
            default_workset[i].finish = default_workset[i].arrival + default_workset[i].serve;
        } else {
            if (default_workset[i].arrival < default_workset[i - 1].finish) {
                default_workset[i].finish = default_workset[i - 1].finish + default_workset[i].serve;
            } else {
                default_workset[i].finish = default_workset[i].arrival + default_workset[i].serve;
            }
        }
    }
    prt();
    return;
}

void RR(int r)
{
    init();
    deque<job*> q;
    sort(default_workset, default_workset + 5, comp_FCFS);
    int t = default_workset[0].arrival; // current clock
    default_workset[0].finish = 0;
    while (!q.empty()) {
        // find a new job;
        for (int i = 1; i < N; ++i) {
            if (default_workset[i].finish != -1)
                continue;
            if (default_workset[i].arrival <= t) {
                job* j = &default_workset[i];
                j->finish = 0;
                q.push_back(j);
                break;
            }
        }
        // reproduce the jobs in circle deque;
        job* j = q.front();
        q.pop_front();
        if (j->serve <= r) {
            t += j->serve;
            j->serve = 0;
        }
    }
    return;
}

int main()
{
    init();
    FCFS();
    SJF();
    RR(1);
    return 0;
}
