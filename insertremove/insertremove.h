#ifndef INSERTREMOVE_H
#define INSERTREMOVE_H

#include <qnamespace.h>

namespace InsertRemove {

enum Type {
    Insert,
    Remove
};

enum PolicyFlag {
    NothingAllowed = 0x0,
    RemoveAllowed  = 0x1,
    AppendAllowed  = 0x2,
    PrependAllowed = 0x4,
    InsertAllowed  = 0x8,
    EverythingAllowed = RemoveAllowed | InsertAllowed | AppendAllowed | PrependAllowed
};

Q_DECLARE_FLAGS(PolicyFlags, PolicyFlag)

}


#endif // INSERTREMOVE_H