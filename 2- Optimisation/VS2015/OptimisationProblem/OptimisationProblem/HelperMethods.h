#pragma once

#include <list>
#include <codecvt>

template <class T>
static std::list<T> Sort(std::list<T> lst, bool ascending = true)
{
    if (lst.size() == 0)
        return lst;

    auto last = lst.end();
    auto first = lst.begin();
    auto second = ++lst.begin();

    if (first == lst.end() || second == lst.end())
        return lst;

    do
    {
        auto prev = first;
        auto curr = second;

        while (prev != last && curr != last)
        {
            if (ascending && *prev > *curr || !ascending && *prev < *curr)
            {
                std::swap(*prev, *curr);
            }

            prev = curr;
            curr++;
        }

        last = prev;
    } while (last != second);

    return lst;
}

static std::wstring s2ws(const std::string str)
{
    size_t charsConverted = 0;
    wchar_t pDest[2048];

    mbstowcs_s(&charsConverted, pDest, str.c_str(), 2048-1);

    return std::wstring(pDest);
}

static std::string ws2s(const std::wstring wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}
