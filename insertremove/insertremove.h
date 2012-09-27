/**
   @author Doronin Stanislav <mugisbrows@gmail.com>

   This file is part of InsertRemovePanel.

   InsertRemovePanel is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as published
   by the Free Software Foundation, either version 3 of the License, or (at
   your option) any later version.

   InsertRemovePanel is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
   Public License for more details.

   You should have received a copy of the GNU General Public License along
   with InsertRemovePanel. If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef INSERTREMOVE_H
#define INSERTREMOVE_H

#include <qnamespace.h>

namespace InsertRemove {

/**
 Button type
 */
enum Type {
    Insert,
    Remove
};

/**
 Insert and remove policy applicable to dimension (horizontal | vertical)
 */
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
