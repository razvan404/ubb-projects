#ifndef _LIST_HPP_
#define _LIST_HPP_

template <class T>
class Node
{
public:
    T Data;
    Node* Flink = nullptr;
    std::mutex Mutex;

    explicit Node(_In_ const T& Data) : Data{ Data }, Flink{ nullptr } { }
    Node() = delete;
    ~Node() = default;

    Node(_In_ const Node& Other) = delete;
    Node& operator=(_In_ const Node& Other) = delete;

    Node(_Inout_ Node&& Other) = delete;
    Node& operator=(_Inout_ Node&& Other) = delete;
};

template <class T>
class List
{
public:
    List()
    {
        this->Head = new Node<T>(T{}); // sentinel
        this->Tail = new Node<T>(T{}); // sentinel
        this->Head->Flink = Tail;
    }

    ~List() noexcept
    {
        Node<T>* current = this->Head;
        while (current)
        {
            Node<T>* next = current->Flink;
            delete current;
            current = next;
        }
    }

    _Requires_exclusive_lock_held_(LastNode->Mutex)
    VOID
    EmplaceBack(_In_ const T& Data, _Inout_ Node<T>* LastNode)
    {
        if (this->DeletedIDs.Contains(Data.GetId()))
        {
            return;
        }

        if (Data.GetScore() == -1)
        {
            this->DeletedIDs.Emplace(Data.GetId());
            return;
        }

        Node<T>* newNode = new Node<T>(Data);
        newNode->Flink = this->Tail;
        LastNode->Flink = newNode;
    }

    _Requires_lock_not_held_(this->Head->Mutex)
    VOID
    Process(_Inout_ T& Data)
    {
        Node<T>* previous = this->Head;
        previous->Mutex.lock();

        Node<T>* current = previous->Flink;
        current->Mutex.lock();

        while (current != this->Tail)
        {
            if (current->Data.GetId() == Data.GetId())
            {
                if (Data.GetScore() == -1)
                {
                    this->DeletedIDs.Emplace(Data.GetId());
                    previous->Flink = current->Flink;
                    current->Mutex.unlock();
                    delete current;
                    previous->Mutex.unlock();
                    return;
                }

                current->Data.SetScore(current->Data.GetScore() + Data.GetScore());

                current->Mutex.unlock();
                previous->Mutex.unlock();
                return;
            }

            previous->Mutex.unlock();
            current->Flink->Mutex.lock();

            previous = current;
            current = current->Flink;
        }

        this->EmplaceBack(Data, previous);

        current->Mutex.unlock();
        previous->Mutex.unlock();
    }

    _No_competing_thread_
    VOID
    GetResults(_Inout_ std::vector<T>& Results) const
    {
        Node<T>* current = this->Head->Flink;
        while (current != this->Tail)
        {
            Results.emplace_back(current->Data);
            current = current->Flink;
        }

        std::sort(Results.begin(), Results.end());
    }

private:
    Node<T>* Head = nullptr;
    Node<T>* Tail = nullptr;
    TSUnorderedSet<ULONG> DeletedIDs;
};

#endif//_LIST_HPP_