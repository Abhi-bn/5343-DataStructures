#include <iostream>
#include <random>
using namespace std;

class Hasher {
    const string chrs = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<string> hashes;

    int closest_prime(int num) {
        for (int i = num;; i++) {
            bool isPrime = true;
            for (int j = 2; j < num / 2 + 1; j++) {
                if (num % j == 0) {
                    isPrime = true;
                    break;
                }
            }
            if (isPrime) return num;
        }
        return -1;
    }

   public:
    Hasher(int has_size = 31) { hashes = vector<string>(closest_prime(has_size)); }

    void extendIfNeeded() {
        int count = 0;
        for (int i = 0; i < hashes.size(); i++)
            if (hashes[i] != string()) count += 1;
        if (((float)count / hashes.size()) < 0.5) return;

        std::vector<string> vec_cpy(hashes);
        hashes = vector<string>(closest_prime(hashes.size() * 2));
        for (int i = 0; i < vec_cpy.size(); i++) {
            if (vec_cpy[i] == string()) continue;
            insert(vec_cpy[i]);
        }
    }

    std::string random_string(std::string::size_type length) {
        thread_local static std::mt19937 rg{std::random_device{}()};
        thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);
        std::string s;
        s.reserve(length);
        while (length--) s += chrs[pick(rg)];
        return s;
    }

    int custom_hash_func(string s) {
        int hash = 0;
        for (int i = 0; i < s.length(); i++) {
            // if (i % 2 == 0) continue;
            // cout << s[i] << (int)s[i] << endl;
            hash += ((int)s[i]) % chrs.length();
        }
        return hash;
    }

    int insert(string str) {
        int hash = custom_hash_func(str);
        int times = 0;
        while (true) {
            int pos = (hash + times * times) % hashes.size();
            if (hashes[pos] == string()) {
                hashes[pos] = str;
                break;
            }
            times += 1;
        }
        extendIfNeeded();
        return times;
    }

    void find(string str, int& index, int& collisions) {
        int hash = custom_hash_func(str);
        while (true) {
            int pos = (hash + collisions * collisions) % hashes.size();
            if (hashes[pos] == string()) {
                index = -1;
                return;
            }
            if (hashes[pos] == str) {
                index = pos;
                return;
            }
            collisions += 1;
        }
    }
};

int main() {
    srand(time(0));
    Hasher h = Hasher();
    vector<string> data;

    int data_count = 20;

    for (int i = 0; i < data_count; i++) data.push_back(h.random_string((rand() % 8) + 3));

    int total_col = 0;
    for (int i = 0; i < data_count; i++) {
        total_col += h.insert(data[i]);
    }

    for (int i = 0; i < data_count; i++) {
        int index = 0, collisions = 0;
        h.find(data[i], index, collisions);
        if (index != -1) {
            cout << "Inserted " << data[i] << " at " << index << " with " << collisions << " collisions" << endl;
        } else {
            cout << "Could not find " << data[i] << endl;
        }
    }
    cout << "Total Collisions for " << data_count << " is " << total_col << endl;
}