#ifndef LIST_H
#define LIST_H

#include <iterator>
#include <memory>

class CList{
    protected:
        class CImplementation;
        std::unique_ptr< CImplementation > DData;
        
    public:
        typedef typename std::allocator<int>::value_type value_type; 
        typedef typename std::allocator<int>::reference reference;
        typedef typename std::allocator<int>::const_reference const_reference;
        typedef typename std::allocator<int>::difference_type difference_type;
        typedef typename std::allocator<int>::size_type size_type;
        class const_iterator;
        class iterator{
            friend class CList;
            friend class const_iterator;
            protected:
                class CImplementation;
                std::unique_ptr< CImplementation > DData;
                
            public:
                typedef typename std::allocator<int>::difference_type difference_type;
                typedef typename std::allocator<int>::value_type value_type;
                typedef typename std::allocator<int>::reference reference;
                typedef typename std::allocator<int>::pointer pointer;
                typedef std::random_access_iterator_tag iterator_category;
            
                iterator();
                iterator(const iterator&);
                ~iterator();
            
                iterator& operator=(const iterator&);
                bool operator==(const iterator&) const;
                bool operator!=(const iterator&) const;
            
                iterator& operator++();
                iterator operator++(int);
                iterator& operator--();
                iterator operator--(int);
                iterator& operator+=(size_type);
                iterator operator+(size_type) const;
                friend iterator operator+(size_type, const iterator&);
                iterator& operator-=(size_type);
                iterator operator-(size_type) const;
            
                reference operator*() const;
                pointer operator->() const;
        };
        class const_iterator{
            friend class CList;
            protected:
                class CImplementation;
                std::unique_ptr< CImplementation > DData;
                
            public:
                typedef typename std::allocator<int>::difference_type difference_type;
                typedef typename std::allocator<int>::value_type value_type;
                typedef typename std::allocator<int>::const_reference reference;
                typedef typename std::allocator<int>::const_pointer pointer;
                typedef std::random_access_iterator_tag iterator_category;
            
                const_iterator();
                const_iterator(const const_iterator&);
                const_iterator(const iterator&);
                ~const_iterator();
            
                const_iterator& operator=(const const_iterator&);
                bool operator==(const const_iterator&) const;
                bool operator!=(const const_iterator&) const;
            
                const_iterator& operator++();
                const_iterator operator++(int);
                const_iterator& operator--();
                const_iterator operator--(int);
                const_iterator& operator+=(size_type);
                const_iterator operator+(size_type) const;
                friend const_iterator operator+(size_type, const const_iterator&);
                const_iterator& operator-=(size_type);
                const_iterator operator-(size_type) const;
            
                reference operator*() const;
                pointer operator->() const;
        };
        
        CList();
        ~CList();
        
        bool IsEmpty() const noexcept;
        int Count() const noexcept;      
        
        reference Front();
        const_reference Front() const;
        
        reference Back();
        const_reference Back() const;
        
        void PushFront(int val);
        void PushBack(int val);
        
        void PopFront();
        void PopBack();
        
        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const;
        iterator end();
        const_iterator end() const;
        const_iterator cend() const;

};

#endif
