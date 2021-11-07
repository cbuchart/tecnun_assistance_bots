#ifndef TECNUN_ARQUI_2021_2022_BROKER_H
#define TECNUN_ARQUI_2021_2022_BROKER_H

#include "Note.h"

#include <condition_variable>
#include <functional>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

namespace tecnun
{
    class Broker
    {
      public:
        using callback_t = std::function<void(std::shared_ptr<Note>)>;

        Broker();
        ~Broker();

        void publish(std::string const& p_topic, std::shared_ptr<Note> p_message);

        void subscribe(std::string const& p_topic, callback_t p_function);

        void join_all();

      protected:
        void run();

        void join(std::thread::id p_id);

      private:
        std::map<std::string, std::vector<callback_t>> m_subscribers;

        std::map<std::thread::id, std::thread> m_threads;
        std::mutex m_threads_mutex;

        std::atomic_bool m_terminate{false};
        std::thread m_join_thread;
        std::mutex m_join_mutex;
        std::condition_variable m_join_cv;
        std::queue<std::thread::id> m_join_queue;
    };
}

#endif
