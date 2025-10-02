#include "global.h"
#include "modding.h"

// Forward declaration
void func_80938284(void* this);

// Hook to make 1 bug trigger the reward AND prevent error state
RECOMP_HOOK("func_80938298") void func_80938298_Init(void* this, void* play) {
    u8* unk_1E0 = (u8*)((u8*)this + 0x1E0);
    s32* unk_1E4 = (s32*)((u8*)this + 0x1E4);
    
    // Never allow error state
    if (*unk_1E4 == 4) {
        *unk_1E4 = 2;  // Force back to counting
        *unk_1E0 = 3;   // Force completion
    }
    
    // If 1 or 2 bugs entered, set to 3 for reward
    if (*unk_1E0 >= 1 && *unk_1E0 < 3) {
        *unk_1E0 = 3;
    }
}

// Replacing func_809381C4 to skip cutscene that happens when bugs detected. 
RECOMP_PATCH void func_809381C4(void* this, void* play) {
    s32* unk_1E4 = (s32*)((u8*)this + 0x1E4);
    
    // Never allow that really annoying buzz error state when you scoop the bug back up.
    *unk_1E4 = 2;
    func_80938284(this);
}
