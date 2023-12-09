#pragma once
#include "Header.h"

// Boyer-Moore algorithm
class BoyerMoore
{
private:

    // Pattern for search
    std::wstring pattern;

    // Table
    std::vector<int> table;

    // Build table
    void build()
    {
        table.resize(1 << (8 * sizeof(wchar_t)), -1);
        const int len = (int)pattern.length();
        for (int i = 0; i < len; ++i)
            table[static_cast<int>(pattern[i])] = i;
    }


public:

    // Default
    BoyerMoore() = default;

    // Basic constructor
    BoyerMoore(const std::wstring& pattern)
        : pattern(pattern)
    {
        build();
    }

    // std::string constructor
    BoyerMoore(const std::string& _pattern)
    {
        std::wstring curr(_pattern.begin(), _pattern.end());
        BoyerMoore::pattern = curr;
        build();
    }

    // Rebuild(std::string)
    void rebuild(const std::string& _pattern)
    {
        std::wstring curr(_pattern.begin(), _pattern.end());
        BoyerMoore::pattern = curr;
        rebuild(curr);
    }

    // Rebuild
    void rebuild(const std::wstring& pattern)
    {
        if (BoyerMoore::pattern == pattern) return;

        BoyerMoore::pattern = pattern;
        build();
    }

    // Check build it or not
    bool is_build() const
    {
        return pattern != L"";
    }

    // Find (std::string)
    std::vector<int> find(const std::string& text)
    {
        std::wstring curr(text.begin(), text.end());
        return find(curr);
    }

    // Find 
    std::vector<int> find(const std::wstring& text)
    {
        std::vector<int> ans;
        int text_len = (int)text.length();
        int patt_len = (int)pattern.length();
        int shift{};

        while (shift <= text_len - patt_len)
        {
            int j = patt_len - 1;

            while (j >= 0 && pattern[j] == text[shift + j])
                --j;

            if (j < 0)
            {
                ans.push_back(shift);
                shift += (shift + patt_len < text_len) ? patt_len - table[text[shift + patt_len]] : 1;
            }
            else shift += std::max(1, j - table[text[shift + j]]);
        }

        return ans;
    }

    // Basic destructor
    ~BoyerMoore() = default;


};

///
/// I use polinomial hashing
/// a0 * p^n + a1 * p^(n-1) + ... + an-1 * p + an
/// Build O(n + m)
/// 

// Hash searching 
class Hash
{
private:

    // Module q
    static constexpr uint32_t q = static_cast<uint64_t>((1LL << 31) - 1LL);

    // Prime p
    int p;

    // Type of searching (1 - fast search with no checks (inaccurate)                               O(n + m), 
    //                    2 - search with checking random symbols to avoid wrong answers(optimal)   O(n + m + m/2) = O(n + m), Constant bigger,
    //                    3 - full check (100% answers, bad perfomance)                       worth O(nm)               ) 
    int type;

    // Build
    void build(int n)
    {
        p = gen(n / 2, n - 2);
    }

    // Generate
    static int gen(int min = 0LL, int max = INT_MAX)
    {
        std::mt19937_64 mt{ std::random_device{}() };
        std::uniform_int_distribution<> die{ min, max };
        return die(mt);
    }

    // Calculate hash
    int hash(const std::wstring& str) const
    {
        int result{};
        const int sz = static_cast<int>(str.size());
        int p_power = 1;
        for (int i = sz-1; i >=0; --i) {
            result = (result + str[i] * 1LL * p_power) % q;
            p_power = (1LL * p_power * p) % q;
        }
        return result;

    }

    // Binary pow + module q
    int binpow(long long a, long long n)    const
    {
        if (!n) return 1;

        long long res = 1 % q;
        while (n)
        {
            if (n & 1)
            {
                res *= a;
                res %= q;
            }
            a *= a;
            a %= q;
            n >>= 1;
        }

        return res % q;
    }

    // Compare hashes
    void cmp_hashes(int curr_hash, int patt_hash, int index, const std::wstring& text, const std::wstring& pattern, std::vector<int>& ans) const
    {
        if (curr_hash == patt_hash)
        {
            if (type == 2)
            {
                const int sz = static_cast<int>(pattern.size());
                std::wstring::const_iterator iterator = text.begin() + index;
                int i;
                for (i = 0; i < sz; ++i,++iterator)
                    if (pattern[i] != *iterator)
                        return;
            }

            ans.push_back(index);
        }
    }

    // Module q
    long long module(long long x)
    {
        return (x < 0 ? (q - (-x % q) % q) : (x % q));
    }


public:

    // Basic constructor
    Hash()
        : type(2)
    { }

    // Construcotr with std::wstring
    Hash(const std::wstring& text) : Hash()
    { }

    // Constructor with std::string
    Hash(const std::string& text) : Hash(std::wstring{ text.begin(),text.end() })
    { }

    // Find pattern positions in text
    std::vector<int> find(const std::wstring& pattern, const std::wstring& text)
    {
        const int n = (int)text.size();
        const int patt_size = static_cast<int>(pattern.size());

        if (patt_size > n) return {};
        build(n);

        const int end = n - static_cast<int>(pattern.size()) + 1;
        const int patt_hash = hash(pattern);

        std::wstring currs{ text.begin(), text.begin() + patt_size };

        int curr_hash = hash(text.substr(0, patt_size));

        std::vector<int> ans;
        cmp_hashes(curr_hash, patt_hash, 0, text, pattern, ans);
        const int p_pow = binpow(p, patt_size - 1);

        for (int i = 1; i < end; ++i)
        {
            curr_hash = (module(curr_hash - text[i - 1] * 1LL * p_pow) * p * 1LL + text[i + patt_size - 1]) % q;
            cmp_hashes(curr_hash, patt_hash,i, text, pattern, ans);
        }

        return ans;
    }

    // Find with std::string
    std::vector<int> find(const std::string& pattern, const std::string& text)
    {
        return find(std::wstring{ pattern.begin(), pattern.end() }, std::wstring{ text.begin(),text.end() });
    }

    // Turn on quickSearch type
    void quick()
    {
        type = 1;
    }

    // Turn on accurace slow mode
    void accurate()
    {
        type = 2;
    }

    //Return current type
    const int state()   const
    {
        return type;
    }

    // Basic destructor
    ~Hash() = default;


};

// Knuth-Morris-Pratt
class KMP
{
private:

    // Text for searching
    std::wstring text;

    // Build prefix_function for pattern
    std::vector<int> build_prefix(const std::wstring& pattern)
    {
        const int n = (int)pattern.size();
        std::vector<int> prefix(n + 1, -1);

        int k;

        for (int i = 1; i <= n; ++i)
        {
            k = prefix[i - 1];
            while (k >= 0 && pattern[k] != pattern[i - 1])
            {
                k = prefix[k];
            }
            prefix[i] = k + 1;
        }

        return prefix;
    }


public:

    // Basic constructor
    KMP() = default;

    // Constructor with std::wstring
    KMP(const std::wstring& text)
        : text(text)
    { }

    // Consturtor with std::string
    KMP(const std::string& text) : KMP(std::wstring{ text.begin(),text.end() })
    { }

    // Rebuild with std::wstring
    void rebuild(const std::wstring& text)
    {
        KMP::text = text;
    }

    // Rebuild with std::string
    void rebuild(const std::string& text)
    {
        rebuild(std::wstring{ text.begin(),text.end() });
    }

    // Check build it or not
    bool is_build() const
    {
        return text != L"";
    }

    // Find std::wstring from begin index
    std::vector<int> find(const std::wstring& pattern, int begin = 0)
    {
        std::vector<int> prefix = build_prefix(pattern);
        std::vector<int> ans;

        const int n = (int)text.size();
        const int m = (int)pattern.size();

        for (int i = begin, k = 0; i < n; ++i)
        {
            while (k >= 0 && pattern[k] != text[i])
                k = prefix[k];

            ++k;

            if (k == m)
            {
                ans.push_back(i - m + 1);
                k = prefix[k];
            }
        }

        return ans;
    }

    // Find std::string from begin index
    std::vector<int> find(const std::string& pattern, int begin = 0)
    {
        return find(std::wstring{ pattern.begin(),pattern.end() }, begin);
    }

    // Basic destructor
    ~KMP() = default;


};


// Innacurate searching with Damerau-Levenshtein distance
class Innacurate_search
{
private:

    // Text
    std::wstring text;

    // Pattern
    std::wstring pattern;

    // Text size
    int n;

    // Pattern size
    int m;

    // Cost of inserting a symbol
    int insertCost;

    // Cost of the deletion a symbol
    int deleteCost;

    // Cost of replace the symbol
    int replaceCost;

    // Cost of transposition
    int transposeCost;

    // Percent of similarity
    double similar;

    // Calculating the Damerau-Levenshtein distance between strings
    int damerau_Levenshtein_Distance(const std::wstring& source, const std::wstring& target, int k)    const
    {
        const int len1 = (int)source.size();
        const int len2 = (int)target.size();

        if (len1 > len2)
            return damerau_Levenshtein_Distance(target, source,k);

        std::vector<int> prev(len1 + 1), curr(len1 + 1);

        std::iota(prev.begin(), prev.end(), 0);

        for (int j = 1; j <= len2; j++)
        {
            curr[0] = j;

            for (int i = 1; i <= len1; i++)
            {
                const int cost = (source[i - 1] == target[j - 1]) ? 0 : replaceCost;

                curr[i] = std::min({ curr[i - 1] + insertCost, prev[i] + deleteCost, prev[i - 1] + cost });

                if (i > 1 && j > 1 && source[i - 1] == target[j - 2] && source[i - 2] == target[j - 1])
                    curr[i] = std::min(curr[i], prev[i - 2] + transposeCost);
            }

            prev.swap(curr);
        }

        return (prev[len1] > k ? k + 1 : prev[len1]);
    }


public:

    // Default
    Innacurate_search()
        : n(0)
        , m(0)
        , text{ L"" }
        , pattern{ L"" }
        , insertCost(1)
        , deleteCost(1)
        , replaceCost(1)
        , transposeCost(1)
        , similar(0.75)
    { }

    // Basic constructor with std::wstring
    Innacurate_search(const std::wstring& text, const std::wstring& pattern)
        : text(text)
        , pattern(pattern)
    {
        n = (int)text.length();
        m = (int)pattern.length();
    }

    // Basic constructor with std::string
    Innacurate_search(const std::string& text, const std::string& pattern) : Innacurate_search(std::wstring{ text.begin(),text.end() }, std::wstring{ pattern.begin(), pattern.end() })
    { }

    // Full constructor with std::wstring
    Innacurate_search(const std::wstring& text, const std::wstring& pattern, int insertCost, int deleteCost, int replaceCost, int transposeCost) : Innacurate_search(text, pattern)
    {
        Innacurate_search::insertCost = insertCost;
        Innacurate_search::deleteCost = deleteCost;
        Innacurate_search::replaceCost = replaceCost;
        Innacurate_search::transposeCost = transposeCost;
    }

    // Full constructor with std::string
    Innacurate_search(const std::string& text, const std::string& pattern, int insertCost, int deleteCost, int replaceCost, int transposeCost)
        : Innacurate_search(std::wstring{ text.begin(),text.end() }, std::wstring{ pattern.begin(),pattern.end() }, insertCost, deleteCost, replaceCost, transposeCost)
    { }

    // Rebuild text std::wstring
    void text_rebuild(const std::wstring& text)
    {
        Innacurate_search::text = text;
        n = (int)text.length();
    }

    // Rebuild text std::string
    void text_rebuild(const std::string& text)
    {
        text_rebuild(std::wstring{ text.begin(),text.end() });
    }

    // Rebuild pattern std::wstring
    void pattern_rebuild(const std::wstring& pattern)
    {
        Innacurate_search::pattern = pattern;
        m = (int)pattern.length();
    }

    // Rebuild pattern std::string
    void pattern_rebuild(const std::string& pattern)
    {
        pattern_rebuild(std::wstring{ pattern.begin(),pattern.end() });
    }

    // Find inclusions of pattern in text (filtered)
    std::vector<std::pair<int, int>> find()     const
    {
        // Return pair<position, length>
        std::vector<std::pair<int, int>> ans;

        // We are interested in strings, which are similar more than 75%
        const int k = m * (1.0 - similar);

        const int minSubstrLength = std::max(1, m - k);
        const int maxSubstrLength = m + k;
        int lastLevenshtein{};

        for (int i = 0; i <= n - minSubstrLength; ++i)
        {
            // Pair of <best distance, length of the best distance string>
            std::pair<int, int> best{ k + 1, 0 };

            // Iterate allowable length of substrings(m +-k)
            for (int currLength = minSubstrLength; currLength <= std::min(n - i, maxSubstrLength); ++currLength)
            {
                std::wstring substring = text.substr(i, currLength);
                const int currDist = damerau_Levenshtein_Distance(substring, pattern, k);

                if (currDist <= k && currDist < best.first)
                {
                    best.first = currDist;
                    best.second = currLength;
                }
            }

            if (best.second)
            {
                if (ans.size())
                    if (ans.back().first + ans.back().second > i)
                        if (lastLevenshtein > best.first)
                            ans.back() = { i, best.second };
                        else ;
                    else
                        ans.push_back({ i, best.second });
                else
                  ans.push_back({ i, best.second });

                lastLevenshtein = best.first;
            }
        }

        return ans;
    }

    // Set accuracy
    void accuracy(double similar)
    {
        Innacurate_search::similar = similar / 100.0;
    }

    // Setters
    void setInsertCost(int insertCost)
    {
        Innacurate_search::insertCost = insertCost;
    }


    void setDeleteCost(int deleteCost)
    {
        Innacurate_search::deleteCost = deleteCost;
    }


    void setReplaceCost(int replaceCost)
    {
        Innacurate_search::replaceCost = replaceCost;
    }


    void setTransposeCost(int transposeCost)
    {
        Innacurate_search::transposeCost = transposeCost;
    }

    // Get the current accuracy
    const double get_accuracy() const
    {
        return similar * 100.0;
    }

    // Destructor
    ~Innacurate_search() = default;


};


// Naive search
class Naive
{
public:

    // Default constructor
    Naive() = default;

    // Find with std::wstring
    std::vector<int> find(const std::wstring& pattern, const std::wstring& text)    const
    {
        std::vector<int> ans;
        const int n = (int)text.size();
        const int m = (int)pattern.size();

        std::wstring buff;

        for (int i = 0; i < n - m + 1; ++i)
        {
            buff = text.substr(i, m);
            if (buff == pattern)
                ans.push_back(i);
        }

        return ans;
    }

    // Find with std::string
    std::vector<int> find(const std::string& pattern, const std::string& text) const
    {
        return find(std::wstring{ pattern.begin(),pattern.end() }, std::wstring{ text.begin(),text.end() });
    }

    // Default destructor
    ~Naive() = default;

};


// Timer
class Timer
{
private:
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1> >;
    std::chrono::time_point<Clock> m_beg{ Clock::now() };
public:

    void reset()
    {
        m_beg = Clock::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }
};