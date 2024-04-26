#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

const int N = 5; // количество философов
std::mutex forks[N]; // вилки

void philosopher(int id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 3000);

    while (true) {
        // размышление
        std::cout << "Философ " << id << " размышляет" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));

        // взятие вилок
        forks[id].lock();
        forks[(id + 1) % N].lock();
        std::cout << "Философ " << id << " ест" << std::endl;

        // поедание спагетти
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));

        // освобождение вилок
        forks[id].unlock();
        forks[(id + 1) % N].unlock();
    }
}

int main() {
    std::thread philosophers[N];

    // запуск философов
    for (int i = 0; i < N; i++) {
        philosophers[i] = std::thread(philosopher, i);
    }

    // ожидание окончания работы философов
    for (int i = 0; i < N; i++) {
        philosophers[i].join();
    }

    return 0;
}
