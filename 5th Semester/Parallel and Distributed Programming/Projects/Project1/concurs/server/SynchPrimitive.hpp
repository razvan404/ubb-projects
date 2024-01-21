#ifndef _SYNCH_PRIMITIVE_HPP_
#define _SYNCH_PRIMITIVE_HPP_

template <typename T>
class ProducerConsumerQueue
{
public:
    explicit ProducerConsumerQueue(_In_ size_t MaxSize, _In_ int ProducersCount, _In_ int ConsumersCount)
        : MaxSize{ MaxSize }, ActiveProducers{ ProducersCount }, ActiveConsumers{ ConsumersCount } {}
    ProducerConsumerQueue() = delete;
    ~ProducerConsumerQueue() = default;

    VOID
    Produce(_In_ const T& Item)
    {
        {
            std::unique_lock<std::mutex> lock(this->Mutex);
            this->CvConsumer.wait(lock, [this] { return this->Queue.size() < this->MaxSize; });
            this->Queue.push(std::move(Item));
        }
        this->CvConsumer.notify_one();
    }

    std::optional<T>
    Consume()
    {
        std::optional<T> item;
        {
            std::unique_lock<std::mutex> lock(this->Mutex);
            this->CvConsumer.wait(lock, [this] { return !this->Queue.empty() || this->ActiveProducers.load() == 0; });
            if (this->Queue.empty())
            {
                return std::nullopt;
            }
            item = std::move(this->Queue.front());
            this->Queue.pop();
        }
        this->CvConsumer.notify_one();
        return item;
    }

    VOID
    UnregisterProducer()
    {
        --this->ActiveProducers;
        if (this->ActiveProducers.load() == 0)
        {
            this->CvConsumer.notify_all();
        }
    }

    VOID
    UnregisterConsumer()
    {
        --this->ActiveConsumers;
        if (this->ActiveConsumers.load() == 0)
        {
            this->CvProducer.notify_one();
        }
    }

    bool
    IsAnyConsumerActive()
    {
        std::unique_lock<std::mutex> lock(this->Mutex);
        this->CvProducer.wait(lock, [this] { return this->ActiveConsumers.load() == 0; });
        return this->ActiveConsumers.load() != 0;
    }

private:
    size_t MaxSize;
    std::queue<T> Queue;
    std::mutex Mutex;
    std::condition_variable CvProducer;
    std::condition_variable CvConsumer;
    std::atomic<int> ActiveProducers;
    std::atomic<int> ActiveConsumers;
};

template <typename T>
class TSUnorderedSet
{
public:
    VOID
    Emplace(_In_ const T& Value)
    {
        std::lock_guard<std::mutex> lock(this->Mutex);
        this->USet.emplace(Value);
    }

    bool
    Contains(_In_ const T& Value) const
    {
        std::lock_guard<std::mutex> lock(this->Mutex);
        return this->USet.find(Value) != this->USet.cend();
    }

private:
    std::unordered_set<T> USet;
    mutable std::mutex Mutex;
};

#endif//_SYNCH_PRIMITIVE_HPP_