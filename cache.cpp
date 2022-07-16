#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class Node
{
public:
    string key;
    int value;
    Node(string key, int value)
    {
        this->key = key;
        this->value = value;
    }
};

class LRUCache
{
public:
    int maxSize;
    list<Node> l;
    unordered_map<string, list<Node>::iterator> m;
    LRUCache(int maxSize)
    {
        this->maxSize = maxSize > 1 ? maxSize : 1;
    }
    void insertKeyValue(string key, int value)
    {
        if (m.count(key) != 0)
        {
            auto it = m[key];
            it->value = value;
        }
        else
        {
            if (l.size() == maxSize)
            {

                Node last = l.back();
                m.erase(last.key);
                cout << last.key << "wdw" << endl;
                l.pop_back();
            }
            Node n(key, value);
            l.push_front(n);
            m[key] = l.begin();
        }
    }
    int *getValue(string key)
    {
        if (m.count(key) != 0)
        {
            auto it = m[key];
            l.push_front(*it);
            l.erase(it);
            m[key] = l.begin();
            return &(*l.begin()).value;
        }
        return NULL;
    }
    string mostRecentKey()
    {
        return l.front().key;
    }
};
int main()
{
    LRUCache lru(3);
    lru.insertKeyValue("mango", 10);
    lru.insertKeyValue("apple", 10);
    lru.insertKeyValue("guava", 10);
    cout << lru.mostRecentKey() << endl;
    lru.insertKeyValue("mango", 40);
    cout << lru.mostRecentKey() << endl;
    lru.insertKeyValue("banana", 20);
    cout << lru.mostRecentKey() << endl;
    if (lru.getValue("apple") == NULL)
    {
        cout << "apple doesnot exist" << endl;
    }
    if (lru.getValue("mango") == NULL)
    {
        cout << "mango doesnot exist" << endl;
    }
    cout << lru.mostRecentKey() << endl;
}
