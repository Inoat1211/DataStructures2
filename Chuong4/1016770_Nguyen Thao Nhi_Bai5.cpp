#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

void demTanSuatTu()
{
    ifstream fin("vanban.txt");

    if (!fin)
    {
        cout << "Khong mo duoc file vanban.txt\n";
        return;
    }
    unordered_map<string, int> freq;
    string word;
    int tongSoTu = 0;
    while (fin >> word)
    {
        freq[word]++;
        tongSoTu++;
    }
    fin.close();
    vector<pair<string, int>> words;
    for (const auto& item : freq)
    {
        words.push_back(item);
    }
    sort(words.begin(), words.end(),
        [](const pair<string, int>& a,
           const pair<string, int>& b)
        {
            if (a.second != b.second)
            {
                return a.second > b.second;
            }
            return a.first < b.first;
        });
    cout << "PHAN A: DEM TAN SUAT TU\n";
    cout << "Tong so tu: " << tongSoTu << '\n';
    cout << "So tu khac nhau: " << words.size() << "\n\n";
    cout << "10 tu xuat hien nhieu nhat:\n";
    int soTuIn = words.size();
    if (soTuIn > 10)
    {
        soTuIn = 10;
    }
    for (int i = 0; i < soTuIn; i++)
    {
        cout << words[i].first
             << " : "
             << words[i].second
             << '\n';
    }
    cout << '\n';
}

class LRUCache
{
private:
    int capacity;
    list<pair<int, string>> cacheList;
    unordered_map<int, list<pair<int, string>>::iterator> cacheMap;

public:
    LRUCache(int cap)
    {
        capacity = cap;
    }
    string get(int key)
    {
        auto it = cacheMap.find(key);

        if (it == cacheMap.end())
        {
            return "-1";
        }
        auto listIt = it->second;
        string value = listIt->second;
        cacheList.splice(cacheList.begin(), cacheList, listIt);
        cacheMap[key] = cacheList.begin();
        return value;
    }

    void put(int key, string value)
    {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end())
        {
            auto listIt = it->second;
            listIt->second = value;
            cacheList.splice(cacheList.begin(), cacheList, listIt);
            cacheMap[key] = cacheList.begin();
            return;
        }
        if ((int)cacheList.size() == capacity)
        {
            auto last = cacheList.back();

            cout << "Cache day, loai bo: "
                 << last.first << '\n';
            cacheMap.erase(last.first);
            cacheList.pop_back();
        }
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }

    void display()
    {
        cout << "Cache: {";
        bool first = true;
        for (const auto& item : cacheList)
        {
            if (!first)
            {
                cout << ", ";
            }
            cout << item.first << ":" << item.second;
            first = false;
        }
        cout << "}\n";
    }
};

void chayLRU()
{
    cout << "PHAN B: LRU CACHE\n";
    LRUCache cache(2);
    cout << "put(1, A)\n";
    cache.put(1, "A");
    cache.display();

    cout << "\nput(2, B)\n";
    cache.put(2, "B");
    cache.display();

    cout << "\nget(1)\n";
    cout << "Tra ve: " << cache.get(1) << '\n';
    cache.display();

    cout << "\nput(3, C)\n";
    cache.put(3, "C");
    cache.display();

    cout << "\nget(2)\n";
    cout << "Tra ve: " << cache.get(2) << '\n';
    cache.display();

    cout << "\nget(3)\n";
    cout << "Tra ve: " << cache.get(3) << '\n';
    cache.display();
}

int main()
{
    demTanSuatTu();
    chayLRU();

    return 0;
}