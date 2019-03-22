//
//  DCollection.hpp
//  DSTD
//
//  'D' stands for 'Declarative'. So, it is DeclarativeCollection,
//  declarative std and so on.
//
//  Created by Artyom Rudakov on 3/20/19.
//  Copyright © 2019 Artyom Rudakov.
//  MIT license - see LICENSE.md
//

#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <map>

namespace dstd {
    
    // MARK: Lambda-operators
    const auto plus           = [](auto i0, auto i1) -> auto { return i0 + i1; };
    const auto minus          = [](auto i0, auto i1) -> auto { return i0 - i1; };
    const auto multiplication = [](auto i0, auto i1) -> auto { return i0 * i1; };
    const auto division       = [](auto i0, auto i1) -> auto { return i0 / i1; };
    
    const auto printOnNewLine = [](const auto & i0) -> auto& {
        return std::cout << "\n" << i0;
    };
    
    const auto printInLine    = [](const auto & i0) -> auto& {
        return std::cout << i0 << " ";
    };
    
    template <typename Type, Type value>
    const auto lessThan         = [](const auto & i0) -> bool {
        return i0 < value;
    };
    
    template <typename Type, Type value>
    const auto greaterThan      = [](const auto & i0) -> bool {
        return i0 > value;
    };
    
    template <typename Type, Type value>
    const auto equalTo          = [](const auto & i0) -> bool {
        return i0 == value;
    };
    
    template <typename Type, Type value>
    const auto lessOrEqualTo    = [](const auto & i0) -> bool {
        return i0 <= value;
    };
    
    template <typename Type, Type value>
    const auto greaterOrEqualTo = [](const auto & i0) -> bool {
        return i0 >= value;
    };
    
    // MARK: Macro-lambdas
#define  LA        [ ](auto & i0) 
#define  LAr(body) [ ](auto & i0) { return body; }
#define bLA        [ ](auto & i0, auto & i1)
#define bLAr(body) [ ](auto & i0, auto & i1) { return body; }
#define  CL        [&](auto & i0)
#define  CLr(body) [&](auto & i0) { return body; }
#define bCL        [&](auto & i0, auto & i1)
#define bCLr(body) [&](auto & i0, auto & i1) { return body; }
    
    template <template <typename ...> class Container,
              typename ValueType,
              typename ...Args>
    struct DCollection: Container<ValueType, Args...> {
        /// Inherits all constructors from a base type.
        using Container<ValueType, Args...>::Container;
        
        /// Calls given closure for every element of the sequence.
        template <typename Closure>
        inline void forEach(Closure action) {
            for (auto & item : *this) {
                action(item);
            }
        }
        
        /// A sequence whose elements consist of the elements of base
        /// sequence that also satisfy a given predicate.
        template <typename Predicate>
        inline DCollection filter(Predicate shouldInclude) const {
            DCollection filteredCollection;
            for (const auto & item : *this) {
                if (shouldInclude(item)) {
                    filteredCollection.insert(filteredCollection.end(), item);
                }
            }
            return filteredCollection;
        }
        
        /// Combines every element of the sequence into one Result
        /// by a given rule.
        template <typename Result, typename Closure>
        inline Result reduce(Result initialResult,
                           Closure nextPartialResult) const {
            for (const auto & item : *this) {
                initialResult = nextPartialResult(initialResult, item);
            }
            return initialResult;
        }
        
        /// Makes a new sequence which consists of the elements of base
        /// sequence, but transformed with a given rule.
        template <typename Closure>
        inline auto map(Closure transform) const {
            DCollection<Container, decltype(transform(*(this -> begin)()))>
            mappedCollection;
            for (const auto & item : *this) {
                mappedCollection.insert(mappedCollection.end(), transform(item));
            }
            return mappedCollection;
        }
    };
    
    // DVector
    template <typename Type, typename Allocator = std::allocator<Type>>
    using vector = DCollection<std::vector, Type, Allocator>;
    
    // DList
    template <typename Type, typename Allocator = std::allocator<Type>>
    using list = DCollection<std::list, Type, Allocator>;
    
    // DSet
    template <class Key, class Compare = std::less<Key>,
              class Allocator = std::allocator<Key>>
    using set = DCollection<std::set, Key, Compare, Allocator>;
    
    // DMap
    template <class Key, class Value, class Compare = std::less<Key>,
              class Allocator = std::allocator<std::pair<const Key, Value>>>
    using map = DCollection<std::map, Key, Value, Compare, Allocator>;
}
