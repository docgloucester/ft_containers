#include "Vector/vector.hpp"
#include "Stack/stack.hpp"
#include "Map/map.hpp"

#include <vector>
#include <stack>
#include <map>
#include <iostream>

#ifndef NS
# define NS ft
#endif

int main()
{
    std::cout << "*************************************************************************" << std::endl;
    std::cout << "\t\t\t\tStack" << std::endl;
    std::cout << "*************************************************************************" << std::endl;

    {
        std::cout << "\n------------- FT Stack (Constructor)-------------" << std::endl;
        NS::vector<int> myvector (2,200);
        NS::stack<int> first;
        NS::stack<int,NS::vector<int> > second;
        NS::stack<int,NS::vector<int> > third(myvector);

        std::cout << "size of first: " << first.size() << std::endl;
        std::cout << "size of second: " << second.size() << std::endl;
        std::cout << "size of third " << third.size() << std::endl;
    }

    {
        std::cout << "\n------------- FT Stack (Empty)-------------" << std::endl;
        NS::stack<int> mystack;
        int sum(0);
        for (int i = 1; i <= 10; i++)
            mystack.push(i);
        while (!mystack.empty())
        {
            sum += mystack.top();
            mystack.pop();
        }
        std::cout << "total: " << sum << std::endl;
    }

    {
        std::cout << "\n------------- FT Stack (Size)-------------" << std::endl;
        NS::stack<int> myints;
        std::cout << "0. size: " << myints.size() << std::endl;
        for (int i = 0; i < 5; i++)
            myints.push(i);
        std::cout << "1. size: " << myints.size() << std::endl;
        myints.pop();
        std::cout << "2. size: " << myints.size() << std::endl;
    }

    {
        std::cout << "\n------------- FT Stack (Top)-------------" << std::endl;
        NS::stack<int> mystack;
        mystack.push(10);
        mystack.push(20);
        mystack.top() -= 5;
        std::cout << "mystack.top() is now " << mystack.top() << std::endl;
        const NS::stack<int> const_stack(mystack);
        std::cout << "const_stack.top() is also " << const_stack.top() << std::endl;
    }

    {
        std::cout << "\n------------- FT Stack (Push/Pop)-------------" << std::endl;
        NS::stack<int> mystack;
        for (int i = 0; i < 5; ++i)
            mystack.push(i);
        std::cout << "size is now: " << mystack.size() << std::endl;
        std::cout << "Popping out elements...";
        while (!mystack.empty())
        {
            std::cout << ' ' << mystack.top();
            mystack.pop();
        }
        std::cout << "size is now: " << mystack.size() << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "\n------------- FT Stack (operator== / operator!=)-------------" << std::endl;
        NS::stack<int, NS::vector<int> > s1, s2, s3;
        s1.push(1);
        s2.push(2);
        s3.push(1);

        if (s1 == s2)
            std::cout << "The stacks s1 and s2 are equal." << std::endl;
        if (s1 != s2)
            std::cout << "The stacks s1 and s2 are not equal." << std::endl;

        if (s1 == s3)
            std::cout << "The stacks s1 and s3 are equal." << std::endl;
        if (s1 != s2)
            std::cout << "The stacks s1 and s3 are not equal." << std::endl;
    }

    {
        std::cout << "\n------------- FT Stack (operator>= / operator<)-------------" << std::endl;
        NS::stack<int, NS::vector<int> > s1, s2, s3;
        s1.push(2);
        s1.push(4);
        s1.push(6);
        s1.push(8);
        s2.push(5);
        s2.push(10);
        s3.push(2);
        s3.push(4);
        s3.push(6);
        s3.push(8);
        if (s1 < s2)
            std::cout << "The stack s1 is less than the stack s2." << std::endl;
        if (s1 >= s2)
            std::cout << "The stack s1 is greater than or equal to the stack s2." << std::endl;
        if (s1 < s3)
            std::cout << "The stack s1 is less than the stack s3." << std::endl;
        if (s1 >= s3)
            std::cout << "The stack s1 is greater than to the stack s3." << std::endl;
    }

    {
        std::cout << "\n------------- FT Stack (operator<= / operator>)-------------" << std::endl;
        NS::stack<int> s1, s2, s3;
        s1.push(5);
        s1.push(10);
        s2.push(1);
        s2.push(2);
        s3.push(5);
        s3.push(10);
        if (s1 <= s2)
            std::cout << "The stack s1 is less than or equal to the stack s2." << std::endl;
        if (s1 > s2)
            std::cout << "The stack s1 is greater than the stack s2." << std::endl;
        if (s1 <= s3)
            std::cout << "The stack s1 is less than or equal to the stack s3." << std::endl;
        if (s1 > s3)
            std::cout << "The stack s1 is greater than the stack s3." << std::endl;
    }

    std::cout << "\n\n\n*************************************************************************" << std::endl;
    std::cout << "\t\t\t\tVector" << std::endl;
    std::cout << "*************************************************************************" << std::endl;

    {
        std::cout << "\n------------- FT Vector (Constructor) -------------" << std::endl;
        NS::vector<int> first1;
        NS::vector<int> second(4, 100);
        NS::vector<int> third(second.begin(), second.end());
        NS::vector<int> fourth(third);
        int myints[] = {16, 2, 77, 29};
        NS::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
        std::cout << "The contents of fifth are:";
        for (NS::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (operator=)-------------" << std::endl;
        NS::vector<int> foo1(3, 0);
        NS::vector<int> bar1(5, 0);
        bar1 = foo1;
        foo1 = NS::vector<int>();
        std::cout << "Size of foo: " << int(foo1.size()) << std::endl;
        std::cout << "Size of bar: " << int(bar1.size()) << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (iterator walk)-------------" << std::endl;
        NS::vector<int> myvector1;
        for (int i = 1; i <= 5; i++)
            myvector1.push_back(i);
        std::cout << "myvector contains:";
        for (NS::vector<int>::iterator it = myvector1.begin(); it != myvector1.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (reverse iterator walk)-------------" << std::endl;
        NS::vector<int> myvector1(5);
        int i1 = 0;
        NS::vector<int>::reverse_iterator rit1 = myvector1.rbegin();
        for (; rit1 != myvector1.rend(); ++rit1)
            *rit1 = ++i1;
        std::cout << "myvector contains:";
        for (NS::vector<int>::iterator it1 = myvector1.begin(); it1 != myvector1.end(); ++it1)
            std::cout << ' ' << *it1;
        std::cout << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (size)-------------" << std::endl;
        NS::vector<int> myints1;
        std::cout << "size (should be 0):  " << myints1.size() << std::endl;
        for (int i = 0; i < 10; i++)
            myints1.push_back(i);
        std::cout << "size (should be 10): " << myints1.size() << std::endl;
        myints1.insert(myints1.end(), 10, 100);
        std::cout << "size (should be 20): " << myints1.size() << std::endl;
        myints1.pop_back();
        std::cout << "size (should be 19): " << myints1.size() << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (max_size)-------------" << std::endl;
        NS::vector<int> myvector1;
        for (int i = 0; i < 100; i++)
            myvector1.push_back(i);
        std::cout << "size: " << myvector1.size() << std::endl;
        std::cout << "max_size: " << myvector1.max_size() << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (resize)-------------" << std::endl;
        NS::vector<int> myvector1;
        for (int i = 0; i < 10; i++)
            myvector1.push_back(i);
        std::cout << "myvector contains 10 elements:                          ";
        for (size_t i = 0; i < myvector1.size(); i++)
            std::cout << ' ' << myvector1[i];
        std::cout << std::endl;

        myvector1.resize(5);
        std::cout << "myvector contains 5 elements:                           ";
        for (size_t i = 0; i < myvector1.size(); i++)
            std::cout << ' ' << myvector1[i];
        std::cout << std::endl;

        myvector1.resize(6);
        std::cout << "myvector contains 6 elements, filled up with value 0:   ";
        for (size_t i = 0; i < myvector1.size(); i++)
            std::cout << ' ' << myvector1[i];
        std::cout << std::endl;

        myvector1.resize(8, 100);
        std::cout << "myvector contains 8 elements, filled up with value 100: ";
        for (size_t i = 0; i < myvector1.size(); i++)
            std::cout << ' ' << myvector1[i];
        std::cout << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (capacity)-------------" << std::endl;
        NS::vector<int> myvector1;
        for (int i = 0; i < 100; i++)
            myvector1.push_back(i);
        std::cout << "size: " << (int)myvector1.size() << std::endl;
        std::cout << "capacity: " << (int)myvector1.capacity() << std::endl;
        std::cout << "max_size: " << (int)myvector1.max_size() << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (empty)-------------" << std::endl;
        NS::vector<int> myvector1;
        int sum1(0);
        for (int i = 1; i < 10; i++)
            myvector1.push_back(i);
        std::cout << "size after pushing values 1 to 9 included: " << (int)myvector1.size() << std::endl;
        while (!myvector1.empty())
        {
            sum1 += myvector1.back();
            myvector1.pop_back();
        }
        std::cout << "size after pop back until empty:           " << (int)myvector1.size() << std::endl;
        std::cout << "total of erased values (should be 45): " << sum1 << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (auto reallocation and reserve)-------------" << std::endl;
        NS::vector<int>::size_type sz1;
        NS::vector<int> foo1;
        sz1 = foo1.capacity();
        std::cout << "making foo grow naturally:" << std::endl;
        for (int i = 0; i < 100; ++i)
        {
            foo1.push_back(i);
            if (sz1 != foo1.capacity())
            {
                sz1 = foo1.capacity();
                std::cout << "capacity changed: " << sz1 << std::endl;
            }
        }
        NS::vector<int> bar1;
        sz1 = bar1.capacity();
        std::cout << "making bar grow once with resize:" << std::endl;
        bar1.reserve(100);
        for (int i = 0; i < 100; ++i)
        {
            bar1.push_back(i);
            if (sz1 != bar1.capacity())
            {
                sz1 = bar1.capacity();
                std::cout << "capacity changed: " << sz1 << std::endl;
            }
        }
    }

    {
        std::cout << "\n------------- FT Vector (operator[])-------------" << std::endl;
        NS::vector<int> myvector1(10);
        for (unsigned i = 0; i < myvector1.size(); i++)
            myvector1[i] = i;
        std::cout << "myvector contains:";
        for (unsigned i = 0; i < myvector1.size(); i++)
            std::cout << ' ' << myvector1[i];

        for (unsigned i = 0; i < myvector1.size() / 2; i++)
        {
            int temp1;
            temp1 = myvector1[myvector1.size() - 1 - i];
            myvector1[myvector1.size() - 1 - i] = myvector1[i];
            myvector1[i] = temp1;
        }

        std::cout << "\nmyvector contains:";
        for (unsigned i = 0; i < myvector1.size(); i++)
            std::cout << ' ' << myvector1[i];
        std::cout << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (at)-------------" << std::endl;
        NS::vector<int> myvector1(10);
        for (unsigned i = 0; i < myvector1.size(); i++)
            myvector1.at(i) = i;
        std::cout << "myvector contains:";
        for (unsigned i = 0; i < myvector1.size(); i++)
            std::cout << ' ' << myvector1.at(i);

        myvector1.at(5) = 28;

        std::cout << "\nmyvector contains:";
        for (unsigned i = 0; i < myvector1.size(); i++)
            std::cout << ' ' << myvector1.at(i);

        try
        {
            std::cout << myvector1.at(45);
        }
        catch(const std::exception& e)
        {
            std::cout << "\nwhew, that was close";
        }
        std::cout << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (front/back)-------------" << std::endl;
        NS::vector<int> myvector1;
        myvector1.push_back(78);
        myvector1.push_back(16);
        std::cout << "myvector.front() (should be 78) is " << myvector1.front() << std::endl;
        std::cout << "myvector.back() (should be 16) is  " << myvector1.back() << std::endl;
        myvector1.push_back(42);
        std::cout << "myvector.front() (should be 78) is " << myvector1.front() << std::endl;
        std::cout << "myvector.back() (should be 42) is  " << myvector1.back() << std::endl;
        myvector1.front() -= myvector1.back();
        std::cout << "myvector.front() (should be 78 - 42) is now " << myvector1.front() << std::endl;
        std::cout << "myvector.back() (should be 42) is  " << myvector1.back() << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (assign)-------------" << std::endl;
        NS::vector<int> first;
        first.assign(7, 100);
        std::cout << "Size of first: " << int(first.size()) << std::endl;

        NS::vector<int> second;
        NS::vector<int>::iterator it1;
        it1 = first.begin() + 1;
        second.assign(it1, first.end() - 1);
        std::cout << "Size of second: " << int(second.size()) << std::endl;

        int myints1[] = {1776, 7, 4};
        first.assign(myints1, myints1 + 3);
        std::cout << "Size of first: " << int(first.size()) << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (push_back)-------------" << std::endl;
        NS::vector<int> myvector1;
        int ints[] = {15, 78, 99, 45, 78, 99, 65, 44, 0};
        for (int i = 0; ints[i]; i++)
            myvector1.push_back(ints[i]);
        std::cout << "myvector stores " << int(myvector1.size()) << " numbers (should be 8), which are";
        for (NS::vector<int>::iterator it = myvector1.begin(); it != myvector1.end(); it++)
            std::cout << " " << *it;
        std::cout << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (pop_back)-------------" << std::endl;
        NS::vector<int> myvector1;
        int sum1(0);
        myvector1.push_back(100);
        myvector1.push_back(200);
        myvector1.push_back(300);
        while (!myvector1.empty())
        {
            sum1 += myvector1.back();
            myvector1.pop_back();
        }
        std::cout << "The elements of myvector add up to " << sum1 << " (expected result is 600). Is the vector empty? : " << myvector1.empty() << " (should be 1)" << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (clear)-------------" << std::endl;
        NS::vector<int> myvector1;
        myvector1.push_back(100);
        myvector1.push_back(200);
        myvector1.push_back(300);
        std::cout << "myvector contains:";
        for (unsigned i = 0; i < myvector1.size(); i++)
            std::cout << ' ' << myvector1[i];
        std::cout << std::endl;
        std::cout << "Its size is of     " << myvector1.size() << std::endl;
        std::cout << "Its capacity is of " << myvector1.capacity() << std::endl;
        myvector1.clear();
        std::cout << "CLEAR!" << std::endl;
        std::cout << "Its size is now of " << myvector1.size() << std::endl;
        std::cout << "Its capacity is of " << myvector1.capacity() << std::endl;
        myvector1.push_back(1101);
        myvector1.push_back(2202);
        std::cout << "myvector contains:";
        for (unsigned i = 0; i < myvector1.size(); i++)
            std::cout << ' ' << myvector1[i];
        std::cout << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (insert)-------------" << std::endl;
        NS::vector<int> myvector1(3, 100);
        std::cout << "Its size is of     " << myvector1.size() << std::endl;
        std::cout << "Its capacity is of " << myvector1.capacity() << std::endl;

        NS::vector<int>::iterator it1;
        it1 = myvector1.begin();
        it1 = myvector1.insert(it1, 200);
        myvector1.insert(it1, 2, 300);

        std::cout << "\nIts size is of     " << myvector1.size() << std::endl;
        std::cout << "Its capacity is of " << myvector1.capacity() << std::endl;

        NS::vector<int> anothervector1(2, 400);
        it1 = myvector1.begin();
        myvector1.insert(it1 + 2, anothervector1.begin(), anothervector1.end());
        std::cout << "\nIts size is of     " << myvector1.size() << std::endl;
        std::cout << "Its capacity is of " << myvector1.capacity() << std::endl;

        int myarray1[] = {501, 502, 503};
        myvector1.insert(myvector1.begin(), myarray1, myarray1 + 3);
        std::cout << "\nmyvector contains:";
        for (it1 = myvector1.begin(); it1 < myvector1.end(); it1++)
            std::cout << ' ' << *it1;
        std::cout << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (erase)-------------" << std::endl;
        NS::vector<int> myvector;
        for (int i = 1; i <= 10; i++)
            myvector.push_back(i);
        std::cout << "myvector contains:";
        for (unsigned i = 0; i < myvector.size(); ++i)
            std::cout << ' ' << myvector[i];

        myvector.erase(myvector.begin() + 5);
        std::cout << "\nmyvector contains:";
        for (unsigned i = 0; i < myvector.size(); ++i)
            std::cout << ' ' << myvector[i];

        myvector.erase(myvector.begin(), myvector.begin() + 3);
        std::cout << "\nmyvector contains:";
        for (unsigned i = 0; i < myvector.size(); ++i)
            std::cout << ' ' << myvector[i];
        std::cout << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (swap)-------------" << std::endl;
        NS::vector<int> foo(3, 100);
        NS::vector<int> bar(5, 200);
        std::cout << "Size of foo before " << foo.size() << std::endl;
        std::cout << "Capa of foo before " << foo.capacity() << std::endl;
        std::cout << "Size of bar before " << bar.size() << std::endl;
        std::cout << "Capa of bar before " << bar.capacity() << std::endl;
        foo.swap(bar);
        std::cout << "SWAP!" << std::endl;
        std::cout << "Size of foo after " << foo.size() << std::endl;
        std::cout << "Capa of foo after " << foo.capacity() << std::endl;
        std::cout << "Size of bar after " << bar.size() << std::endl;
        std::cout << "Capa of bar after " << bar.capacity() << std::endl;
        std::cout << "foo contains:";
        for (unsigned i = 0; i < foo.size(); i++)
            std::cout << ' ' << foo[i];
        std::cout << std::endl;
        std::cout << "bar contains:";
        for (unsigned i = 0; i < bar.size(); i++)
            std::cout << ' ' << bar[i];
        std::cout << std::endl;
    }

    {
        std::cout << "\n------------- FT Vector (get_allocator)-------------" << std::endl;
        NS::vector<int> myvector;
        int             *p;
        unsigned int    i;

        p = myvector.get_allocator().allocate(5);
        for (i = 0; i < 5; i++)
            myvector.get_allocator().construct(&p[i], i);
        std::cout << "The manually allocated array contains:";
        for (i = 0; i < 5; i++)
            std::cout << ' ' << p[i];
        std::cout << std::endl;
        for (i = 0; i < 5; i++)
            myvector.get_allocator().destroy(&p[i]);
        myvector.get_allocator().deallocate(p, 5);
    }

    {
        std::cout << "\n------------- FT Vector (Relational operators)-------------" << std::endl;
        NS::vector<int> foo(2, 200);
        NS::vector<int> bar(foo);
        if (foo == bar)
            std::cout << "foo and bar are equal" << std::endl;
        if (foo != bar)
            std::cout << "foo and bar are not equal" << std::endl;
        if (foo < bar)
            std::cout << "foo is less than bar" << std::endl;
        if (foo > bar)
            std::cout << "foo is greater than bar" << std::endl;
        if (foo <= bar)
            std::cout << "foo is less than or equal to bar" << std::endl;
        if (foo >= bar)
            std::cout << "foo is greater than or equal to bar" << std::endl;
        NS::vector<int> baz;
        baz.push_back(200);
        baz.push_back(200);
        baz.push_back(300);
        baz.push_back(400);
        if (foo == baz)
            std::cout << "foo and baz are equal" << std::endl;
        if (foo != baz)
            std::cout << "foo and baz are not equal" << std::endl;
        if (foo < baz)
            std::cout << "foo is less than baz" << std::endl;
        if (foo > baz)
            std::cout << "foo is greater than baz" << std::endl;
        if (foo <= baz)
            std::cout << "foo is less than or equal to baz" << std::endl;
        if (foo >= baz)
            std::cout << "foo is greater than or equal to baz" << std::endl;
    }

    std::cout << "\n\n\n*************************************************************************" << std::endl;
    std::cout << "\t\t\t\tMap" << std::endl;
    std::cout << "*************************************************************************" << std::endl;

    //
    {
        std::cout << "\n------------- FT Pair (constructor) -------------" << std::endl;
        NS::pair<std::string, double> product1;
        NS::pair<std::string, double> product2("tomatoes", 2.30);
        NS::pair<std::string, double> product3(product2);
        product2.first = "shoes";
        product2.second = 39.90;
        std::cout << "The price of " << product1.first << " is $" << product1.second << std::endl;
        std::cout << "The price of " << product2.first << " is $" << product2.second << std::endl;
        std::cout << "The price of " << product3.first << " is $" << product3.second << std::endl;
    }

    {
        std::cout << "\n------------- FT Pair (operator=) -------------" << std::endl;
        NS::pair<std::string, int> planet("Earth", 6371), homeplanet;
        planet = NS::make_pair("Earth", 6371);
        homeplanet = planet;
        std::cout << "Home planet (should be Earth): " << homeplanet.first << std::endl;
        std::cout << "Planet radius in km (should be 6371): " << homeplanet.second << std::endl;
    }

    {
        std::cout << "\n------------- FT Pair (make_pair) -------------" << std::endl;
        NS::pair<int, int> foo;
        NS::pair<int, int> bar;
        foo = NS::make_pair(10, 20);
        bar = NS::make_pair(10.5, 'A'); // implicit conversion
        std::cout << "foo (should be 10, 20): " << foo.first << ", " << foo.second << std::endl;
        std::cout << "bar (should be 10, 65): " << bar.first << ", " << bar.second << std::endl;
    }

    {
        std::cout << "\n------------- FT Pair (relational operators) -------------" << std::endl;
        NS::pair<int, char> foo(10, 'z');
        NS::pair<int, char> bar(10, 'z');
        if (foo == bar)
            std::cout << "foo and bar are equal" << std::endl;
        if (foo != bar)
            std::cout << "foo and bar are not equal" << std::endl;
        if (foo < bar)
            std::cout << "foo is less than bar" << std::endl;
        if (foo > bar)
            std::cout << "foo is greater than bar" << std::endl;
        if (foo <= bar)
            std::cout << "foo is less than or equal to bar" << std::endl;
        if (foo >= bar)
            std::cout << "foo is greater than or equal to bar" << std::endl;

        NS::pair<int, char> baz(90, 'a');
        if (foo == baz)
            std::cout << "foo and baz are equal" << std::endl;
        if (foo != baz)
            std::cout << "foo and baz are not equal" << std::endl;
        if (foo < baz)
            std::cout << "foo is less than baz" << std::endl;
        if (foo > baz)
            std::cout << "foo is greater than baz" << std::endl;
        if (foo <= baz)
            std::cout << "foo is less than or equal to baz" << std::endl;
        if (foo >= baz)
            std::cout << "foo is greater than or equal to baz" << std::endl;
    }

    {
        std::cout << "\n------------- FT Map (construct) -------------" << std::endl;
        NS::map<char, int> first;
        std::cout << "First map is :" <<std::endl;
        for (NS::map<char, int>::iterator i = first.begin(); i != first.end(); i++)
            std::cout << i->first << "\t" << i->second << std::endl;
        first['a'] = 10;
        first['b'] = 30;
        first['c'] = 50;
        first['d'] = 70;

        NS::map<char, int> second(first.begin(), first.end());
        std::cout << "Second map is :" <<std::endl;
        for (NS::map<char, int>::iterator i = second.begin(); i != second.end(); i++)
            std::cout << i->first << "\t" << i->second << std::endl;

        NS::map<char, int> third(second);
        std::cout << "Third map is :" <<std::endl;
        for (NS::map<char, int>::iterator i = third.begin(); i != third.end(); i++)
            std::cout << i->first << "\t" << i->second << std::endl;
    }

    {
        std::cout << "\n------------- FT Map (operator=) -------------" << std::endl;
        NS::map<char, int> first;
        NS::map<char, int> second;
        first['x'] = 8;
        first['y'] = 16;
        first['z'] = 32;
        second = first;
        first = NS::map<char, int>();
        std::cout << "Size of first (should now be 0):                " << first.size() << std::endl;
        std::cout << "Size of second (should now contain 3 elements): " << second.size() << std::endl;
    }

    {
        std::cout << "\n------------- FT Map (operator[]) -------------" << std::endl;
        NS::map<char, std::string> mymap;
        mymap['a'] = "an element";
        mymap['b'] = "another element";
        mymap['c'] = mymap['b'];
        std::cout << "mymap['a'] is " << mymap['a'] << std::endl;
        std::cout << "mymap['b'] is " << mymap['b'] << std::endl;
        std::cout << "mymap['c'] is " << mymap['c'] << std::endl;
        std::cout << "mymap['d'] is " << mymap['d'] << std::endl;
        std::cout << "mymap now contains " << mymap.size() << " elements." << std::endl;
    }

    {
        std::cout << "\n------------- FT Map (empty) -------------" << std::endl;
        NS::map<char, int> mymap;
        mymap['a'] = 10;
        mymap['b'] = 20;
        mymap['c'] = 30;
        while (!mymap.empty())
        {
            std::cout << "Erasing pair " << mymap.begin()->first << " => " << mymap.begin()->second << std::endl;
            mymap.erase(mymap.begin());
        }
        std::cout << "Is map now empty (should be 1)? " << mymap.empty();
    }

    {
        std::cout << "\n------------- FT Map (max_size) -------------" << std::endl;
        NS::map<int, int> mymap;
        std::cout << "The maximum size our map could grow up to is " << mymap.max_size() << std::endl;
    }

    {
        std::cout << "\n------------- FT Map (insert) -------------" << std::endl;
        // insert value
        NS::map<char, int> mymap;
        mymap.insert(NS::pair<char, int>('a', 100));
        mymap.insert(NS::pair<char, int>('z', 200));
        NS::pair<NS::map<char, int>::iterator, bool> ret = mymap.insert(NS::pair<char, int>('z', 500));
        if (ret.second == false)
            std::cout << "element 'z' already existed with a value of " << ret.first->second << std::endl;
        std::cout << "mymap is of size (should be 2): " << mymap.size() << std::endl << std::endl;

        NS::map<char, int>::iterator it = mymap.begin();
        mymap.insert(it, NS::pair<char, int>('b', 300));
        mymap.insert(it, NS::pair<char, int>('c', 400));
        std::cout << "mymap now contains a, b, c and z:" << std::endl;
        for (it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << std::endl;

        NS::map<char, int> anothermap;
        anothermap.insert(mymap.begin(), mymap.end());
        std::cout << "\nanothermap now also contains a, b, c and z:" << std::endl;
        for (NS::map<char, int>::iterator i = anothermap.begin(); i != anothermap.end(); i++)
        {
            std::cout << i->first << "=>" << i->second << std::endl;
        }
    }

    {
        std::cout << "\n------------- FT Map (clear) -------------" << std::endl;
        NS::map<char, int> mymap;
        mymap['x'] = 100;
        mymap['y'] = 200;
        mymap['z'] = 300;
        std::cout << "mymap contains:" << std::endl;
        for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << std::endl;
        mymap.clear();
        std::cout << "CLEAR!" << std::endl;
        std::cout << "mymap contains:" << std::endl;
        for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << std::endl;
        mymap['a'] = 1101;
        mymap['b'] = 2202;
        std::cout << "mymap contains:" << std::endl;
        for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << std::endl;
    }

    {
        std::cout << "\n------------- FT Map (erase) -------------" << std::endl;
        NS::map<char, int> mymap;
        mymap['a'] = 10;
        mymap['b'] = 20;
        mymap['c'] = 30;
        mymap['d'] = 40;
        mymap['e'] = 50;
        mymap['f'] = 60;
        mymap.erase(mymap.find('b'));
        mymap.erase('c');
        mymap.erase(mymap.find('e'), mymap.end());
        std::cout << "Map should now only contain a and d" << std::endl;
        for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
        {
            std::cout << it->first << " => " << it->second << std::endl;
        }
    }

    {
        std::cout << "\n------------- FT Map (swap) -------------" << std::endl;
        NS::map<char, int> foo, bar;
        foo['x'] = 100;
        foo['y'] = 200;
        bar['a'] = 11;
        bar['b'] = 22;
        bar['c'] = 33;
        foo.swap(bar);
        std::cout << "foo contains now (should be 3 elements):" << std::endl;
        for (NS::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
           std::cout << it->first << " => " << it->second << std::endl;
        std::cout << "bar contains now (should be 2 elements):" << std::endl;
        for (NS::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
            std::cout << it->first << " => " << it->second << std::endl;
    }

    {
        std::cout << "\n------------- FT Map (key_comp) -------------" << std::endl;
        NS::map<char, int> mymap;
        mymap['a'] = 100;
        mymap['b'] = 200;
        mymap['c'] = 300;
        std::cout << "browsing mymap using its key_comp funciton object:" << std::endl;
        char highest = mymap.rbegin()->first;
        NS::map<char, int>::iterator it = mymap.begin();
        while (mymap.key_comp()((*it).first, highest))
        {
            std::cout << it->first << " => " << it->second << std::endl;
            ++it;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "\n------------- FT Map (value_comp subclass) -------------" << std::endl;
        NS::map<char, int> mymap;
        mymap['x'] = 1001;
        mymap['y'] = 2002;
        mymap['z'] = 3003;
        std::cout << "mymap contains:" << std::endl;
        NS::pair<char, int> highest = *mymap.rbegin(); // last element
        NS::map<char, int>::iterator it = mymap.begin();
        while (mymap.value_comp()(*it, highest))
        {
            std::cout << it->first << " => " << it->second << std::endl;
            ++it;
        }
    }

    {
        std::cout << "\n------------- FT Map (find) -------------" << std::endl;
        NS::map<char, int> mymap;
        NS::map<char, int>::iterator it;
        mymap['a'] = 50;
        mymap['b'] = 100;
        mymap['c'] = 150;
        mymap['d'] = 200;
        it = mymap.find('b');
        if (it != mymap.end())
            mymap.erase(it);
        std::cout << "elements in mymap:" << std::endl;
        std::cout << "a => " << mymap.find('a')->second << std::endl;
        std::cout << "c => " << mymap.find('c')->second << std::endl;
        std::cout << "d => " << mymap.find('d')->second << std::endl;
        std::cout << "x => end() iterator ? (should be 1): " << (mymap.find('x') == mymap.end()) << std::endl;
    }

    {
        std::cout << "\n------------- FT Map (count) -------------" << std::endl;
        NS::map<char, int> mymap;
        mymap['a'] = 101;
        mymap['c'] = 202;
        mymap['f'] = 303;
        std::cout << "mymap contains:" << std::endl;
        for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << std::endl;

        for (char c = 'a'; c < 'h'; c++)
        {
            std::cout << c;
            if (mymap.count(c) > 0)
                std::cout << " is an element of mymap." << std::endl;
            else
                std::cout << " is not an element of mymap." << std::endl;
        }
    }

    {
        std::cout << "\n------------- FT Map (bounds) -------------" << std::endl;
        NS::map<char, int> mymap;
        NS::map<char, int>::iterator itlow, itup;
        mymap['a'] = 20;
        mymap['b'] = 40;
        mymap['c'] = 60;
        mymap['d'] = 80;
        mymap['e'] = 100;
        std::cout << "mymap contains " << std::endl;
        for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << std::endl;
        itlow = mymap.lower_bound('b');
        itup = mymap.upper_bound('d');
        mymap.erase(itlow, itup);
        std::cout << "The range [b, d] has been erased, the map should now only contain \'a\' and \'e\'" << std::endl;
        for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << std::endl;
    }

    {
        std::cout << "\n------------- FT Map (equal_range) -------------" << std::endl;
        NS::map<char, int> mymap;
        mymap['a'] = 10;
        mymap['b'] = 20;
        mymap['c'] = 30;
        std::cout << "mymap contains " << std::endl;
        for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << std::endl;

        NS::pair<NS::map<char, int>::iterator, NS::map<char, int>::iterator> ret;
        ret = mymap.equal_range('b');
        std::cout << "lower bound to b points to: ";
        std::cout << ret.first->first << " => " << ret.first->second << std::endl;
        std::cout << "upper bound to b points to: ";
        std::cout << ret.second->first << " => " << ret.second->second << std::endl;
    }

}