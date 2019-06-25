#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <string>

std::condition_variable empty, full;
std::mutex mu_c, mu_p;
std::mutex mcout;

void print2stdout(std::string msg) {
    if(!msg.empty()) {
        std::unique_lock<std::mutex> lck(mcout);
        std::cout << msg << std::endl;
    }
}

int main()
{
    class OrderBuf {
        int order_num;
        int ORDER_BUFFER[10];
    public:
        OrderBuf() {order_num = 0;}
        void AddOrder(int order_id) {
            if(order_num < 10) 
                ORDER_BUFFER[order_num++] = order_id;
        }
        void RemoveOrder() {
            if(order_num > 0) {order_num--;}
        }
        int CurOrders() {return (order_num+1);}
        int MaxSize(){return 10;}
    };
    
    OrderBuf Orders;
    
    auto cook = [](OrderBuf &ordr) {
        while(true) {
            std::unique_lock<std::mutex> lck(mu_p);
            while(ordr.CurOrders() == ordr.MaxSize()) {
                full.wait(lck);
                print2stdout("Maximum Order produced ! waiting for supplier to serve");
            }
            print2stdout("Cook produced an Order ");
            ordr.AddOrder(static_cast<int>(rand() % 1000));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            empty.notify_all();
        }
    };
    
    auto supplier = [](OrderBuf &ordr) {
        while(true) {
            std::unique_lock<std::mutex> lck(mu_c);
            while(ordr.CurOrders() == 0) {
                print2stdout("No Order to supply ! waiting for cook to produce");
                empty.wait(lck);
            }
            print2stdout("Supplier has served one order ");
            ordr.RemoveOrder();
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            full.notify_all();
        }
    };

    std::thread consumer = std::thread(supplier, std::ref(Orders));
    std::thread producer = std::thread(cook, std::ref(Orders));
    consumer.join();
    producer.join();
    
    return 0;
}


