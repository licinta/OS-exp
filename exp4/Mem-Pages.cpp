#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#include "algorithm"
#include "deque"
#include "iostream"
#include "list"
#include <unistd.h>

#define INVALID -1
#define total_instruction 320
#define total_vp 32
#define clear_period 50
using namespace std;

struct pl_type {
    // virtual page number , physics page number , usage counter , unused time
    int vpn = 0, ppn = -1, counter = 0, time = -1;
    bool operator==(const pl_type& pother) const { return vpn == pother.vpn && ppn == pother.ppn && counter == pother.counter && time == pother.time; }
};

pl_type pagelist[total_vp];
///*页面控制结构*/

list<pl_type> ppage; // physics pages

int diseffect, a[total_instruction];
int page[total_instruction], offset[total_instruction];

void initialize(int total_pp)
{
    /*初始化相关数据结构*/
    int i = 0;
    diseffect = 0;
    ppage.clear();
    for (i = 0; i < total_vp; i++) { // 32页虚拟内存页数
        pagelist[i].vpn = i;         // round of 0~31
        pagelist[i].ppn = INVALID;   // The vpage hasn't been moved to physics memory, so it hasn't ppn yet
        pagelist[i].counter = 0;
        pagelist[i].time = -1; // 置页面控制结构中的访问时间,时间为-1
    }
}

void FIFO(int total_pp)
{
    initialize(total_pp);
    for (int i = 0; i < total_instruction; ++i) {
        pl_type curpage = pagelist[page[i]];
        if (curpage.ppn == INVALID) { // Hasn't been move to physics memory
            diseffect++;
            if (ppage.size() == total_pp) { // no space
                pl_type ppage_select = ppage.front();
                pagelist[ppage_select.vpn].ppn = INVALID;
                ppage.pop_front();
            }
            pagelist[page[i]].ppn = ppage.size() + 1;
            ppage.push_back(pagelist[page[i]]);
        } else {
            // do nothing for fifo
        }
    }
    printf("FIFO:%6.4f\t", 1 - ((float)diseffect / 320));
}

bool lru_cmp(const pl_type& p1, const pl_type& p2) { return p1.time < p2.time; }

void LRU(int total_pp)
{
    initialize(total_pp);
    for (int i = 0; i < total_instruction; ++i) {
        int vpn = page[i];
        if (pagelist[vpn].ppn == INVALID) { // Hasn't been move to physics memory
            diseffect++;
            if (ppage.size() == total_pp) { // no space
                auto ppage_select = min_element(ppage.begin(), ppage.end(), lru_cmp);
                int del = ppage_select->vpn;
                ppage.remove(*ppage_select);
                pagelist[del].time = -1;
                pagelist[del].ppn = INVALID;
            }
            pagelist[page[i]].ppn = ppage.size() + 1;
            pagelist[page[i]].time = i;
            ppage.push_back(pagelist[page[i]]);
        } else { // not miss
            int vpn = page[i];
            for (auto p = ppage.begin(); p != ppage.end(); p++) {
                if (p->vpn == vpn) {
                    p->time = i;
                    break;
                }
            }
        }
    }
    printf("LRU:%6.4f\t", 1 - ((float)diseffect / 320));
}

int find_next(int i, int vpn)
{
    for (int k = i; k < total_instruction; ++k) {
        if (page[k] == vpn) {
            return k;
        }
    }
    return total_instruction;
}

void OPT(int total_pp)
{
    initialize(total_pp);
    for (int i = 0; i < total_instruction; ++i) {
        int vpn = page[i];
        if (pagelist[vpn].ppn == INVALID) { // Hasn't been move to physics memory
            diseffect++;
            if (ppage.size() == total_pp) {
                // no space
                // select most unusually-used pages
                int mn = 0;
                pl_type* mm;
                for (auto& p : ppage) {
                    int temp = find_next(i + 1, p.vpn);
                    if (temp > mn) {
                        mm = &p;
                        mn = temp;
                    }
                }

                pagelist[mm->vpn].ppn = INVALID;
                ppage.remove(*mm);
            }
            pagelist[vpn].ppn = ppage.size() + 1;
            ppage.push_back(pagelist[vpn]);
        } else { // not miss
            // do nothing
        }
    }
    printf("OPT:%6.4f\t", 1 - ((float)diseffect / 320));
}

bool lfu_cmp(const pl_type& p1, const pl_type& p2) { return p1.counter < p2.counter; }

void LFU(int total_pp)
{
    initialize(total_pp);
    for (int i = 0; i < total_instruction; ++i) {
        int vpn = page[i];
        if (pagelist[vpn].ppn == INVALID) { // Hasn't been move to physics memory
            diseffect++;
            if (ppage.size() == total_pp) { // no space
                auto ppage_select = min_element(ppage.begin(), ppage.end(), lfu_cmp);
                int del = ppage_select->vpn;
                ppage.remove(*ppage_select);
                pagelist[del].counter = 0;
                pagelist[del].ppn = INVALID;
            }
            pagelist[page[i]].ppn = ppage.size() + 1;
            pagelist[page[i]].counter++;
            ppage.push_back(pagelist[page[i]]);
        } else { // not miss
            int vpn = page[i];
            for (auto p = ppage.begin(); p != ppage.end(); p++) {
                if (p->vpn == vpn) {
                    p->counter++;
                    break;
                }
            }
        }
    }

    printf("LFU:%6.4f\t", 1 - ((float)diseffect / 320));
}

void CLOCK(int total_pp)
{
    initialize(total_pp);
    for (int i = 0; i < total_pp; ++i) {
        ppage.push_back({ -1, -1, 0, -1 }); // let counter be the mark bit
    }
    int array = -1; // initial stat.
    for (int i = 0; i < total_instruction; ++i) {
        int vpn = page[i];
        if (pagelist[vpn].ppn == INVALID) { // miss
            diseffect++;
            int full = 1;
            for (auto& p : ppage) {
                if (p.time == -1) {
                    full = 0;
                    break;
                }
            }
            //            for (auto &p:ppage) {
            //                cout << p.vpn << ":" << p.time << ":" << p.counter << " ";
            //            }
            //            cout << endl;
            auto iter = ppage.begin();
            advance(iter, (array + 1) % total_pp);
            array++;
            if (full) { // no memory
                while (iter->counter == 1) {
                    iter->counter = 0;
                    iter = ppage.begin();
                    advance(iter, (array + 1) % total_pp);
                    array++;
                }
                //                cout << iter->vpn << ":" << iter->time << ":" << iter->counter << "\n";
                pagelist[iter->vpn].ppn = INVALID;
                iter->vpn = INVALID;
            } else {
                iter->vpn = vpn;
                iter->time = 0;
            }
            iter->counter = 1;
            iter->vpn = vpn;
            pagelist[vpn].ppn = abs(distance(iter, ppage.begin())) >> 2;
        } else {
            auto iter = ppage.begin();
            advance(iter, (pagelist[vpn].ppn) % total_pp);
            iter->counter = 1;
        }
    }
    printf("CLOCK:%6.4f\t", 1 - ((float)diseffect / 320));
}

int main()
{
    int S, i;
    srand(10 * getpid());
    /*由于每次运行时进程号不同,故可用来作为初始化随机数队列的“种子”*/
    S = rand() % 320;                            //[0,319]
    for (i = 0; i < total_instruction; i += 4) { /*产生指令队列*/
        a[i] = S;                                /*任选一指令访问点*/
        a[i + 1] = a[i] + 1;                     /*顺序执行下一条指令*/
        a[i + 2] = rand() % a[i];                /*执行前地址指令m'*/
        a[i + 3] = a[i + 2] + 1;                 /*执行后地址指令*/
        S = rand() % (318 - a[i + 2]) + a[i + 2] + 2;
    }
    for (i = 0; i < total_instruction; i++) { /*将指令序列变换成页地址流*/
        page[i] = a[i] / 10;
        offset[i] = a[i] % 10;
    }
    for (i = 4; i <= 32; i++) { /*用户内存工作区从4个页面到32个页面*/
        printf("%2d page frames\t", i);
        FIFO(i);
        LRU(i);
        OPT(i);
        LFU(i);
        CLOCK(i);
        printf("\n");
        //        usleep(0.1*1e6);
    }
    return 0;
}
