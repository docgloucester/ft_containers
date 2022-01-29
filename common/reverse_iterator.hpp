/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:52:38 by rgilles           #+#    #+#             */
/*   Updated: 2022/01/29 14:53:10 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iterator_traits.hpp>

namespace ft 
{

//TODO - Reverse iterator
template <class Iterator>
class myiterator_reverse : public iterator< typename iterator_traits<Iterator>::iterator_category,
                                            typename iterator_traits<Iterator>::value_type,
                                            typename iterator_traits<Iterator>::difference_type,
                                            typename iterator_traits<Iterator>::pointer,
                                            typename iterator_traits<Iterator>::reference>
{
    public:
        typedef Iterator iterator_type;
        typedef typename iterator_traits<Iterator>::difference_type     difference_type;
        typedef typename iterator_traits<Iterator>::pointer             pointer;
        typedef typename iterator_traits<Iterator>::reference           reference;

        //TODO - Constructor Default
        myiterator_reverse() : _itr(NULL) {}

        //TODO - initialization
        explicit myiterator_reverse (iterator_type it) : _itr(it) {}

        //TODO - copy
        template <class Iter>
        myiterator_reverse (const myiterator_reverse<Iter>& rev_it) : _itr(rev_it.base()) {}
        
        //TODO - Return base iterator
        iterator_type base() const
        {
            return _itr;
        }

        //TODO - Dereference iterator
        reference operator*() const
        {
            return (*(--this->base()));
        }

        //TODO - Addition operator
        myiterator_reverse operator+ (difference_type n) const
        {
            return myiterator_reverse(_itr - n);
        }

        //TODO - Increment iterator position
        myiterator_reverse& operator++()
        {
            --_itr;
            return (*this);
        }
        myiterator_reverse  operator++(int)
        {
            myiterator_reverse tmp = *this;
            --_itr;
            return tmp;
        }
        myiterator_reverse& operator+= (difference_type n)
        {
            this->_itr -= n;
            return (*this);
        }
        myiterator_reverse operator- (difference_type n) const
        {
            return myiterator_reverse(this->_itr + n);
        }
        myiterator_reverse& operator--()
        {
            ++_itr;
            return (*this);
        }
        myiterator_reverse  operator--(int)
        {
            myiterator_reverse tmp = *this;
            ++_itr;
            return (tmp);
        }
        myiterator_reverse& operator-= (difference_type n)
        {
            _itr += n;
            return (*this);
        }
        pointer operator->() const
        {
            return &(operator*());
        }
        reference operator[] (difference_type n) const
        {
            return (*(_itr - n - 1));
        }
    private:
        iterator_type _itr;
};

    template <class It1, class It2>
    bool operator== (const myiterator_reverse<It1>& lhs, const myiterator_reverse<It2>& rhs)
    {
        return (rhs.base() == lhs.base());
    }
    template <class It1, class It2>
    bool operator!= (const myiterator_reverse<It1>& lhs, const myiterator_reverse<It2>& rhs)
    {
        return (rhs.base() != lhs.base());
    }
    template <class It1, class It2>
    bool operator< (const myiterator_reverse<It1>& lhs, const myiterator_reverse<It2>& rhs)
    {
        return (rhs.base() < lhs.base());
    }
    template <class It1, class It2>
    bool operator<= (const myiterator_reverse<It1>& lhs, const myiterator_reverse<It2>& rhs)
    {
        return (rhs.base() <= lhs.base());
    }
    template <class It1, class It2>
    bool operator> (const myiterator_reverse<It1>& lhs, const myiterator_reverse<It2>& rhs)
    {
        return (rhs.base() > lhs.base());
    }
    template <class It1, class It2>
    bool operator>= (const myiterator_reverse<It1>& lhs, const myiterator_reverse<It2>& rhs)
    {
        return (rhs.base() >= lhs.base());
    }
    template <class It>
    myiterator_reverse<It> operator+ (typename myiterator_reverse<It>::difference_type n, const myiterator_reverse<It>& rev_it)
    {
        return (myiterator_reverse<It>(rev_it.base() - n));
    }
    template <class It1, class It2>
    typename myiterator_reverse<It1>::difference_type operator- (const myiterator_reverse<It1>& lhs, const myiterator_reverse<It2>& rhs)
    {
        return (rhs.base() - lhs.base());
    }

}
#endif