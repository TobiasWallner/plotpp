#pragma once

#include <concepts>
#include <iterator>

namespace plotpp
{

    namespace Concepts
    {
        template<class T>
        concept has_mut_begin_end = requires(T&& obj){
            { std::ranges::begin(obj) };
            { std::ranges::end(obj) };
        };

        template<class T>
        concept has_immut_begin_end = requires(T&& obj){
            { std::ranges::cbegin(obj) };
            { std::ranges::cend(obj) };
        };

        template<class T>
        concept has_data_size = requires(T&& obj){
            { obj.data()} -> std::contiguous_iterator;
            { obj.size()} -> std::integral;
        };
    } // namespace concept
    
    template<class T>
    requires(Concepts::has_mut_begin_end<T> || Concepts::has_data_size<T>)
    auto begin(T& obj){
        if constexpr (Concepts::has_mut_begin_end<T>){
            return std::ranges::begin(obj);
        }else if constexpr (Concepts::has_data_size<T>){
            return obj.data();
        }else{
            static_assert(false, "Error: the container needs to have either `std::begin`/`std::end` iterators or `.data()`/`.size()` methods for them to be plotable");
        }
    }

    template<class T>
    requires(Concepts::has_immut_begin_end<T> || Concepts::has_data_size<T>)
    auto begin(const T& obj){
        if constexpr (Concepts::has_immut_begin_end<T>){
            return std::ranges::cbegin(obj);
        }else if constexpr (Concepts::has_data_size<T>){
            return obj.data();
        }else{
            static_assert(false, "Error: the container needs to have either `std::begin`/`std::end` iterators or `.data()`/`.size()` methods for them to be plotable");
        }
    }

    template<class T>
    requires(Concepts::has_immut_begin_end<T> || Concepts::has_data_size<T>)
    auto cbegin(const T& obj){
        if constexpr (Concepts::has_immut_begin_end<T>){
            return std::ranges::cbegin(obj);
        }else if constexpr (Concepts::has_data_size<T>){
            return obj.data();
        }else{
            static_assert(false, "Error: the container needs to have either `std::begin`/`std::end` iterators or `.data()`/`.size()` methods for them to be plotable");
        }
    }

    template<class T>
    requires(Concepts::has_mut_begin_end<T> || Concepts::has_data_size<T>)
    auto end(T& obj){
        if constexpr (Concepts::has_mut_begin_end<T>){
            return std::ranges::end(obj);
        }else if constexpr (Concepts::has_data_size<T>){
            return obj.data() + obj.size();
        }else{
            static_assert(false, "Error: the container needs to have either `std::begin`/`std::end` iterators or `.data()`/`.size()` methods for them to be plotable");
        }
    }

    template<class T>
    requires(Concepts::has_immut_begin_end<T> || Concepts::has_data_size<T>)
    auto end(const T& obj){
        if constexpr (Concepts::has_immut_begin_end<T>){
            return std::ranges::cend(obj);
        }else if constexpr (Concepts::has_data_size<T>){
            return obj.data() + obj.size();
        }else{
            static_assert(false, "Error: the container needs to have either `std::begin`/`std::end` iterators or `.data()`/`.size()` methods for them to be plotable");
        }
    }

    template<class T>
    requires(Concepts::has_immut_begin_end<T> || Concepts::has_data_size<T>)
    auto cend(const T& obj){
        if constexpr (Concepts::has_immut_begin_end<T>){
            return std::ranges::cend(obj);
        }else if constexpr (Concepts::has_data_size<T>){
            return obj.data() + obj.size();
        }else{
            static_assert(false, "Error: the container needs to have either `std::begin`/`std::end` iterators or `.data()`/`.size()` methods for them to be plotable");
        }
    }
} // namespace plotpp
