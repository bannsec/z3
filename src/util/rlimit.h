/*++
Copyright (c) 2015 Microsoft Corporation

Module Name:

    rlimit.h

Abstract:

    Resource limit container.

Author:

    Nikolaj Bjorner (nbjorner) 2015-09-28

Revision History:

--*/
#ifndef RLIMIT_H_
#define RLIMIT_H_

#include "vector.h"

class reslimit {
    volatile bool   m_cancel;
    uint64          m_count;
    uint64          m_limit;
    svector<uint64> m_limits;
    ptr_vector<reslimit> m_children;
public:    
    reslimit();
    void push(unsigned delta_limit);
    void pop();
    void push_child(reslimit* r) { m_children.push_back(r); }
    void pop_child() { m_children.pop_back(); }

    bool inc();
    bool inc(unsigned offset);
    uint64 count() const; 


    bool cancel_flag_set() { return m_cancel; }
    void cancel();
    void reset_cancel();
};

class scoped_rlimit {
    reslimit& m_limit;
public:
    scoped_rlimit(reslimit& r, unsigned l): m_limit(r) {
        r.push(l);
    }
    ~scoped_rlimit() { m_limit.pop(); }

};

#endif
