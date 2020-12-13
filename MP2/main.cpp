//
//  main.cpp
//  MP2
//
//  Created by Егор Гончаров on 12.12.2020.
//

#include <iostream>
#include <thread>
#include <vector>
#include <pthread.h>
#include <unistd.h>

using namespace std;

const int HP = 100, DAMAGE = 20, COUNT_OF_WARRIORS = 100;
pthread_mutex_t mutexx = PTHREAD_MUTEX_INITIALIZER;

vector<int> ans;

int Anchur_money, Teran_money;

vector<int> Anchur_hp, Teran_hp;

int get_rand_between(int a, int b) {
    return (rand() % (b - a)) + a;
}

bool did_miss() {
    return (rand() % 3) == 0;
}

bool is_alive(vector<int> &team_hp, int index) {
    return team_hp[index] > 0;
}

void atack(vector<int> &aim, int num, int &money) {
    if(aim[num] <= 0) return;
    //cout << "and he has " << aim[num] << " HP" << endl;
    aim[num] -= DAMAGE;
    --money;
}

bool team_is_alive(vector<int> &team) {
    bool f = true;
    for(int i = 0; i < team.size(); ++i) {
        f &= (!is_alive(team, i));
    }
    return !f;
}

void* threadd(void *ptr) {
    int num = *(int *)ptr;
    if(num < 100) {
        while(is_alive(Anchur_hp, num)) {
            if(did_miss()) continue;
            int aim = get_rand_between(0, 100);
            if(is_alive(Teran_hp, aim)) {
                pthread_mutex_lock(&mutexx);
                cout << "Anchors soldier[" << num << "] ";
                atack(Teran_hp, aim, Anchur_money);
                cout << "has damaged " << aim << "s enemies soldier" << endl;
                sleep(0.5);
                pthread_mutex_unlock(&mutexx);
            } else {
                bool flag = false;
                for(int i = 0; i < 100; ++i) {
                    if(is_alive(Teran_hp, i)) {
                        flag = true;
                        int aim = i;
                        pthread_mutex_lock(&mutexx);
                        cout << "Anchors soldier[" << num << "] ";
                        atack(Teran_hp, aim, Anchur_money);
                        cout << "has damaged " << aim << "s enemies soldier" << endl;
                        sleep(0.5);
                        pthread_mutex_unlock(&mutexx);
                        break;
                    }
                    
                }
                if (!flag) {
                    return NULL;
                }
            }
            
        }
        return NULL;
    } else {
        while(is_alive(Teran_hp, num-100)) {
            
            
            int aim = get_rand_between(0, 100);
            if(is_alive(Anchur_hp, aim)) {
                pthread_mutex_lock(&mutexx);
                cout << "Teran soldier[" << num << "] ";
                atack(Anchur_hp, aim, Teran_money);
                cout << "has damaged " << aim << "s enemies soldier" << endl;
                sleep(0.5);
                pthread_mutex_unlock(&mutexx);
            } else {
                bool flag = false;
                for(int i = 0; i < 100; ++i) {
                    if(is_alive(Anchur_hp, i)) {
                        int aim = i;
                        flag = true;
                        pthread_mutex_lock(&mutexx);
                        cout << "Teran soldier[" << num << "] ";
                        atack(Anchur_hp, aim, Teran_money);
                        cout << "has damaged " << aim << "s enemies soldier" << endl;
                        sleep(0.5);
                        pthread_mutex_unlock(&mutexx);
                        break;
                    }
                }
                if (!flag) {
                    return NULL;
                }
            }
            
        }
        return NULL;
    }
    
}

int main(int argc, const char * argv[]) {
    Anchur_hp.resize(COUNT_OF_WARRIORS, HP);
    Teran_hp.resize(COUNT_OF_WARRIORS, HP);
    ans.resize(200);
    
    Anchur_money = get_rand_between(500, 1500);
    Teran_money = get_rand_between(500, 1500);
    
    cout << "Anchurs team has $" << Anchur_money << " money. " << endl;
    cout << "Terans team has $" << Teran_money << " money. " << endl;
    cout << "1 shell costs $1." << endl;
    
    vector<pthread_t> pths(200);
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    for (int i = 0; i < 200; ++i) {
        pthread_create(&pths[i], &attr, threadd, &i);
    }
    
    pthread_attr_destroy(&attr);
    for(int i = 0; i < 200; ++i) {
        pthread_join(pths[i], NULL);
    }
    
    pthread_mutex_destroy(&mutexx);
    
    bool f = true;
    for(int i = 0; i < 100; ++i) {
        cout << "HP of Anchors[" << i << "] solder is " <<Anchur_hp[i] << endl;
        f &= !(ans[i]);
    }
    cout << endl << endl;
    for(int i = 100; i < 200; ++i) {
        cout << "HP of Teran[" << i % 100 << "] solder is " << Teran_hp[i % 100] << endl;
    }
    if(team_is_alive(Anchur_hp)) {
        cout << "Anchors won " << endl;
    } else {
        cout << "Teran won" << endl;
    }
    return 0;
}
