#ifndef MAIN_CPP_PREDICATE_HPP
#define MAIN_CPP_PREDICATE_HPP
#include <iostream>

template<typename iterator, typename predicate>
bool allOf(iterator current, iterator end, const predicate &function){
    while(current != end){
        if (!function(*current))
            return false;
        ++current;
    }
    return true;
}

template<typename iterator, typename predicate>
bool anyOf(iterator current, iterator end, const predicate &function){
    while(current != end){
        if (function(*current))
            return true;
        ++current;
    }
    return false;
}

template<typename iterator, typename predicate>
bool noneOf(iterator current, iterator end, const predicate &function){
    while(current != end){
        if (function(*current))
            return false;
        ++current;
    }
    return true;
}

template<typename iterator, typename predicate>
bool oneOf(iterator current, iterator end, const predicate &function){
    int count = 0;
    while(current != end){
        if (function(*current))
            count++;
        ++current;
    }
    if (count == 1)
        return true;
    return false;
}

template<typename iterator, typename predicate = std::less<>>
bool isSorted(iterator current, iterator end, const predicate &function = predicate()){
    iterator prev = current;
    current++;
    while(current != end){
        if (!function(*prev, *current))
            return false;
        ++current;
        ++prev;
    }
    return true;
}

template<typename iterator, typename predicate>
bool isPartitioned(iterator current, iterator end, const predicate &function){
    bool condition = function(*current);
    bool hasChanged = false;
    ++current;
    while (current != end){
        if (function(*current) != condition){
            if (!hasChanged)
                hasChanged = true;
            else
                return false;
        }
        ++current;
    }
    return true;
}

template<typename iterator, typename element>
iterator findNot(iterator current, [[maybe_unused]] iterator end, const element &elem){
    while(*current == elem){
        ++current;
    }
    return current;
}

template<typename iterator, typename element>
iterator findBackward(iterator current, iterator end, const element &elem){
    iterator found = end;
    while(current != end){
        if (*current == elem){
            found = current;
        }
        ++current;
    }
    return found;
}

template<typename iterator, typename predicate>
bool isPalindrome(iterator current, iterator end, const predicate &function){
    while(current != end){
        --end;
        if(!function(*current, *end))
           return false;
        if(current == end)
            return true;
        ++current;
    }
    return true;
}

#endif //MAIN_CPP_PREDICATE_HPP
