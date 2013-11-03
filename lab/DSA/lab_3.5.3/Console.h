class Console {
public:
    Console ();
    virtual ~Console ();
    void newCustomer(Customer* cur);
    Customer* getCustomer() const;
    int getServeNum() const;
    void setCustomer(Customer* cur);
    double getLast() const;
private:
    Customer* cur;
    double last_serve_t;
    int cnt;
};

Console::Console():cur(NULL), cnt(0), last_serve_t(0){}

Console::~Console(){}

void Console::newCustomer(Customer* cur){
    this->cur = cur;
    cnt++;
}
Customer* Console::getCustomer() const{
    return cur;
}
int Console::getServeNum() const{
    return cnt;
}

void Console::setCustomer(Customer* cur){
    last_serve_t = this->cur->getLeaveTime();
    this->cur = cur;
    return;
}

double Console::getLast() const{
    return last_serve_t;
}
