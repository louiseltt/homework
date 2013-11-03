class Customer {
public:
    Customer ();
    Customer (int id, double come_time, double leave_time);
    virtual ~Customer ();
    int getId() const;
    double getComeTime() const;
    double getLeaveTime() const;
    void setWaitTime(double wait_t);
    double getWaitTime() const;

private:
    int user_id;
    double user_come_time;
    double user_leave_time;
    double user_wait_time;
};
Customer::Customer():user_id(-1), user_come_time(0), user_leave_time(0), user_wait_time(0){}
Customer::Customer(int id, double come_time, double leave_time)
    :user_id(id), user_come_time(come_time), user_leave_time(leave_time), user_wait_time(0){}

Customer::~Customer(){}

int Customer::getId() const{
    return user_id;
}

double Customer::getComeTime() const{
    return user_come_time;
}

double Customer::getLeaveTime() const{
    return user_leave_time;
}

void Customer::setWaitTime(double wait_t){
    user_wait_time = wait_t;
    return;
}
double Customer::getWaitTime() const{
    return user_wait_time;
}
