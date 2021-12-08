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
    /**
     * Broker for notes.
     */
    class Broker
    {
      public:
        /**
         * Callback receives a note.
         */
        using callback_t = std::function<void(std::shared_ptr<Note>)>;

        Broker();
        ~Broker();

        /**
         * Publish a message on a topic.
         *
         * @param p_topic The topic (case sensitive).
         * @param p_message Message to publish.
         */
        void publish(std::string const& p_topic, std::shared_ptr<Note> p_message);

        /**
         * Subscribe a callback to a topic
         *
         * @param p_topic The topic (case sensitive).
         * @param p_function Callback to execute when a message is received.
         */
        void subscribe(std::string const& p_topic, callback_t p_function);

        /**
         * Wait for joining all the running threads.
         */
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
