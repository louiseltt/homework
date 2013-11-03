#include <iostream>
#include <ctime>
#include <queue>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include "possion.cpp"
#include "unistd.h"
//#include "windows.h"
#include "customer.h"
#include "Console.h"
using namespace std;

const double MAX = 480;

/*
 *print daily log
 */
void daily_log(Console console[], int si, vector<Customer>& v){

    double total_wait_t = 0;
    //system("cls");// under windows
    system("clear");
    cout << "Good job.We have finished our work today.\nHere is the log:\n" ;
    cout << setw(42) << setfill('*') << "\n";
    cout << setw(17) << setfill(' ') << left << "*" ;
    cout << "Counter" ;
    cout << setw(17) << right << "*" << endl;
    cout << setw(42) << setfill('*') << "\n";


    cout << setw(42) << setfill('+') << "\n";
    cout << '+';
    cout << setw(12) << setfill(' ') << "Customer_ID";
    cout << setw(4) << setfill(' ') << '+';
    cout << setw(16) << setfill(' ') << "Waiting Time";
    cout << setw(8) << setfill(' ') << '+';
    cout << endl;

    for (int i = 0; i < v.size(); i++) {
        cout << '+';
        cout << setw(8) << v[i].getId() ;
        cout << setw(8) << right << '+';
        cout << setw(12) << v[i].getWaitTime() ;
        cout << setw(12) << right << '+';
        cout << endl;
        total_wait_t += v[i].getWaitTime();
    }
    cout << setw(42) << setfill('+') << "\n";

    cout << "Total Serve Time: " << MAX << endl;
    cout << "Average waiting time: " << total_wait_t/v.size() << endl;
    cout << "Console Serve: " << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Console " << i << ": " << console[i].getServeNum() << endl;
    }
    cout << "That's all." << endl;
}
/*
 *print the interface
 */
void print_counter(Console console[], int si, queue<Customer>& q, double cur_t){
    //system("cls");
    system("clear");

    cout << setw(42) << setfill('*') << "\n";
    cout << setw(17) << setfill(' ') << left << "*" ;
    cout << "Counter" ;
    cout << setw(17) << right << "*" << endl;
    cout << setw(42) << setfill('*') << "\n";

    cout << "Total Serve Time: " << MAX << " mins   Remain Time: " << MAX-cur_t << " mins" << endl;
    cout << q.size() << " people are linging up" << endl;
    cout << setw(42) << setfill('+') << '\n';
    cout << '+';
    for (int i = 0; i < 5; i++) {
        cout << setw(8) << setfill(' ') << '+';
    }
    cout << endl;

    cout << '+' ;
    for (int i = 0; i < 5; i++) {
        cout << setw(4) << i+1 << setw(4) << '+';
    }
    cout << endl;

    cout << '+';
    for (int i = 0; i < 5; i++) {
        cout << setw(8) << setfill(' ') << '+';
    }
    cout << endl;
    cout << setw(42) << setfill('+') << '\n';

    cout << '+';
    for (int i = 0; i < 5; i++) {
        cout << setw(8) << setfill(' ') << '+';
    }
    cout << endl;

    cout << '+';
    for (int i = 0; i < 5; i++) {
        if ( console[i].getCustomer()!=NULL )
            cout << setw(4) << setfill(' ') << (console[i].getCustomer())->getId()
                << setw(4) << '+';
        else
            cout << setw(4) << setfill(' ') << "0"
                << setw(4) << '+';

    }
    cout << endl;

    cout << '+';
    for (int i = 0; i < 5; i++) {
        cout << setw(8) << setfill(' ') << '+';
    }
    cout << endl;
    cout << setw(42) << setfill('+') << '\n';

    sleep(2);
    //sleep(1000);// under windows
    return;
}
/*
 *refresh the console at cur_time
 */
bool ref(Console console[], int si, queue<Customer>& q, double cur_t, vector<Customer>& v){

    for (int i = 0; i < si; i++) {
        if (console[i].getCustomer()!=NULL){
            if (console[i].getCustomer()->getLeaveTime() <= cur_t){
                console[i].setCustomer(NULL);
            }
        }
    }

    while (!q.empty()){
        int tmp = 0;
        for (int i = 0; i < si; i++) {
            if (console[i].getCustomer()==NULL){
                console[i].newCustomer(&q.front());
                if ( console[i].getLast() >= q.front().getComeTime() )
                v[ q.front().getId()-1 ].setWaitTime( console[i].getLast() - q.front().getComeTime());
                q.pop();
                break;
            }
            tmp++;
        }
        if (tmp == 5) break;
    }
    return true;
}
/*
 *simulation the counter system in the bank
 */
void simulation(){

    //initial
    Console console[5];
    queue<Customer> wait_q;
    vector<Customer> v;

    double init = 0;
    double cur_t = 0;
    double next_t = 0;
    double nserve_t;

    int userid = 0;
    Random ncome_t(true);
    Random serve_t(true);

    //work begin
    while ( ref(console, 5, wait_q, cur_t, v) ){

        //generate new customer
        next_t = ncome_t.poisson(1);
        cur_t += next_t;
        nserve_t = serve_t.poisson(30);
        userid++;
        Customer customer = Customer( userid, cur_t, nserve_t+cur_t );

        //push the customer in the queue
        wait_q.push(customer);
        v.push_back(customer);

        //judge if it's out of working time
        if ( cur_t >= MAX ) break;

        //print the current counter
        print_counter(console, 5, wait_q, cur_t);
    }

    daily_log(console, 5, v);
    return;
}
int main(void)
{
    simulation();
    return 0;
}
