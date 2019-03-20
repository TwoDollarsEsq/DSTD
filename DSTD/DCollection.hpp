//
//  DCollection.hpp
//  DSTD
//
//  'D' stands for 'Declative'. So, it is DeclativeCollection,
//  declarative std and so on.
//
//  Created by Artyom Rudakov on 3/20/19.
//  Copyright © 2019 Artyom Rudakov. All rights reserved.
//

#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <list>

namespace dstd {
    
#define LA (body) [ ](auto & i0) { body; }
#define LAr(body) [ ](auto & i0) { return body; }
#define CL (body) [&](auto & i0) { body; }
#define CLr(body) [&](auto & i0) { return body; }
    
    template <typename Type, template <typename, typename = std::allocator<Type>> class Container>
    struct DCollection: Container<Type> {
        using Container<Type>::Container;
        
        template <typename closure>
        inline void forEach(closure action) {
            for (Type & item : *this) {
                action(item);
            }
        }
        
        template <typename closure>
        inline DCollection filter(closure shouldInclude) {
            DCollection filteredCollection;
            forEach([&](Type & item) {
                if (shouldInclude(item)) {
                    filteredCollection.insert(filteredCollection.end(), item);
                }
            });
            return filteredCollection;
        }
        
        template <typename closure>
        inline Type reduce(Type initialResult, closure nextPartialResult) {
            forEach([&](Type & item) {
                initialResult = nextPartialResult(initialResult, item);
            });
            return initialResult;
        }
        
        template <typename closure>
        inline auto map(closure transform) {
            DCollection<decltype(transform(*(this -> begin)())), Container>
            mappedCollection;
            forEach([&](Type & item) {
                mappedCollection.insert(mappedCollection.end(), transform(item));
            });
            return mappedCollection;
        }
    };
    
    template <typename Type> using vector = DCollection<Type, std::vector>;
    template <typename Type> using queue  = DCollection<Type, std::queue>;
    template <typename Type> using list   = DCollection<Type, std::list>;
    
    // MARK: Lambda-operators
    const auto plus           = [](auto i0, auto i1) -> auto { return i0 + i1; };
    const auto minus          = [](auto i0, auto i1) -> auto { return i0 - i1; };
    const auto multiplication = [](auto i0, auto i1) -> auto { return i0 * i1; };
    const auto division       = [](auto i0, auto i1) -> auto { return i0 / i1; };
    
    const auto printOnNewLine = [](const auto & i0) { std::cout << "\n" << i0 << "\n"; };
    const auto printInLine    = [](const auto & i0) { std::cout << i0 << " "; };
}
