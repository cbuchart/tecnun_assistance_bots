#include "Broker.h"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

tecnun::Broker::Broker()
{
    m_join_thread = std::thread{&Broker::run, this};
}

tecnun::Broker::~Broker()
{
    m_terminate = true;
    m_join_thread.join();
}

void tecnun::Broker::publish(std::string const& p_topic, std::shared_ptr<Note> p_message)
{
    auto it = m_subscribers.find(p_topic);
    if (it == m_subscribers.end()) { return; }

    for (auto const& callback : it->second) {
        std::lock_guard lock{m_threads_mutex};

        std::thread thread{[callback, p_message, this]() {
            callback(p_message);

            join(std::this_thread::get_id());
        }};

        m_threads[thread.get_id()] = std::move(thread);
    }
}

void tecnun::Broker::subscribe(std::string const& p_topic, callback_t p_function)
{
    m_subscribers[p_topic].push_back(p_function);
}

void tecnun::Broker::join_all()
{
    while (true) {
        {
            std::lock_guard lock{m_threads_mutex};
            if (m_threads.empty()) { return; }
        }

        std::this_thread::sleep_for(100ms);
    }
}

void tecnun::Broker::run()
{
    while (!m_terminate) {
        std::unique_lock lock{m_join_mutex};
        if (m_join_cv.wait_for(lock, 500ms) == std::cv_status::timeout) { continue; }

        while (!m_join_queue.empty()) {
            auto const thread_id = m_join_queue.front();
            m_join_queue.pop();

            std::lock_guard lock{m_threads_mutex};

            auto it = m_threads.find(thread_id);
            if (it != m_threads.end()) {
                if (it->second.joinable()) { it->second.join(); }
                m_threads.erase(it);
            }
        }
    }
}

void tecnun::Broker::join(std::thread::id p_id)
{
    std::lock_guard lock{m_join_mutex};
    m_join_queue.push(p_id);

    m_join_cv.notify_one();
}
