#include<iostream>
#include<list>
#include<stdio.h>
#include<stdlib.h>
using namespace std;


template <class T> class malloc_allocator
{

public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    template <class U>
    struct rebind
    {
        typedef malloc_allocator<U> other;
    };
    malloc_allocator() {}
    malloc_allocator(const malloc_allocator&) {}
    template <class U>
    malloc_allocator(const malloc_allocator<U>&) {}
    ~malloc_allocator() {}
    pointer address(reference x) const
    {
        return &x;
    }
    const_pointer address(const_reference x) const
    {
        return x;
    }
    pointer allocate(size_type n, const_pointer = 0)
    {
        void* p = malloc(n * sizeof(T));
        if (!p)
            throw std::bad_alloc();
        return static_cast<pointer>(p);
    }
    void deallocate(pointer p, size_type)
    {
        free(p);
    }
    size_type max_size() const
    {
        return static_cast<size_type>(-1) / sizeof(T);
    }
    void construct(pointer p, const value_type& x)
    {
        new(p) value_type(x);
    }
    void destroy(pointer p)
    {
        p->~value_type();
    }
private:
    void operator=(const malloc_allocator&);
};



template<> class malloc_allocator<void>
{

    typedef void value_type;
    typedef void* pointer;
    typedef const void* const_pointer;

    template <class U>
    struct rebind
    {
        typedef malloc_allocator<U> other;
    };

};


template <class T>
inline bool operator==(const malloc_allocator<T>&,
                       const malloc_allocator<T>&)
{
    return true;
}

template <class T>
inline bool operator!=(const malloc_allocator<T>&,
                       const malloc_allocator<T>&)
{
    return false;
}

#include<set>
//#define Node int

struct Node
{
    uint32_t src;
    uint32_t dst;
    uint16_t sport;
    uint16_t dport;

    Node(uint32_t src,uint32_t dst,uint16_t sport,uint16_t dport):
        src(src),dst(dst),sport(sport),dport(dport)
    {
    }
    /*
    Node(struct tuple4 addr):
        src(addr.saddr),dst(addr.daddr),sport(addr.source),dport(addr.dest)
    {
    }
    */
    bool operator < (const Node& b)const
    {
        if(src!=b.src)
            return src<b.src;
        if(dst!=b.dst)
            return dst<b.dst;
        if(sport!=b.sport)
            return sport<b.sport;
        return dport<b.dport;
    }

    bool operator == (const Node& b)const
    {
        if(src==b.src&&dst==b.dst&&sport==b.sport&&dport==b.dport)
            return true;
        return false;
    }

    void show() const
    {
        fprintf(stdout,"%u %u %u %u\n",src,dst,sport,dport);
    }

};
int main()
{
    set< Node, less<Node>, malloc_allocator<Node> > S;
    set< Node, less<Node>, malloc_allocator<Node> > S2;

    for(int i=0; i<10; ++i)
    {
        Node n(i,i,i,i);
        S.insert(n);
    }
    S.insert( Node(5,2,7,7) );
    S2.insert( Node(5,3,6,7) );
    for(int i=0; i<10; ++i)
    {
        Node n(i*2,i*2,i*2,i*2);
        S2.insert(n);
    }

    std::set<Node , std::less<Node> , malloc_allocator<Node> >::iterator it =      S.begin();
    std::set<Node , std::less<Node> , malloc_allocator<Node > >::iterator it2 =   S2.begin();

    fprintf(stdout,"compare %u %u\n",S.size(),S2.size());
    while(it!=S.end()&&it2!=S2.end())
    {
        while( it!=S.end() && it2!=S2.end()  && *it == *it2  )
        {
            ++it;
            ++it2;
        }

        while( it!=S.end() && it2!=S2.end()  && *it2 < *it  )
        {
            it2->show();
            //cout<<*it2<<endl;
            ++it2;
        }

        while( it!=S.end() && it2!=S2.end()  && *it < *it2  )
        {
            it->show();
            //cout<<*it<<endl;
            ++it;
        }
    }
    return 0;
}
