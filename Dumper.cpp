#include <Windows.h>
#include <string>


#define aslr(x) (x - 0x400000 + reinterpret_cast<const std::uintptr_t>(GetModuleHandleW(0)));

DWORD addr_magic = aslr(0x222D870);

namespace toSet {
    
    DWORD R_LUA_TNIL_ = -1;
	DWORD R_LUA_TUSERDATA_ = -1;
	DWORD R_LUA_TLIGHTUSERDATA_ = -1;
	DWORD R_LUA_TNUMBER_ = -1;
	DWORD R_LUA_TBOOLEAN_ = -1;
	DWORD R_LUA_TSTRING_ = -1;
	DWORD R_LUA_TTHREAD_ = -1;
	DWORD R_LUA_TFUNCTION_ = -1;
	DWORD R_LUA_TTABLE_ = -1;
    DWORD R_LUA_TVECTOR_ = -1;
}



void DumpLuaTypes(DWORD rL)
{
    char** found = (char**)addr_magic;
    int count = 0;
    do
    {
        if (!strcmp(*found, "nil"))
            toSet::R_LUA_TNIL_ = count;
        else if (!strcmp(*found, "userdata"))
        {
            if (R_LUA_TLIGHTUSERDATA_ != -1)
                toSet::R_LUA_TUSERDATA_ = count;
            else
                toSet::R_LUA_TLIGHTUSERDATA_ = count;
        }
        else if (!strcmp(*found, "vector"))
            toSet::R_LUA_TVECTOR_ = count;
        else if (!strcmp(*found, "number"))
            toSet::R_LUA_TNUMBER_ = count;
        else if (!strcmp(*found, "boolean"))
            toSet::R_LUA_TBOOLEAN_ = count;
        else if (!strcmp(*found, "string"))
            toSet::R_LUA_TSTRING_ = count;
        else if (!strcmp(*found, "thread"))
            toSet::R_LUA_TTHREAD_ = count;
        else if (!strcmp(*found, "function"))
            toSet::R_LUA_TFUNCTION_ = count;
        else if (!strcmp(*found, "table"))
            toSet::R_LUA_TTABLE_ = count;
        count++;
        found++;
    } while (((char)(*found)) != 0 && strncmp(*found, "__", 2) != 0);
}

    //DumpLuaTypes(states::roblox);
	
    //std::printf("R_LUA_TNIL %i \n", toSet::R_LUA_TNIL_);
    //std::printf("R_LUA_TUSERDATA %i \n", toSet::R_LUA_TUSERDATA_);
    //std::printf("R_LUA_TLIGHTUSERDATA %i \n", toSet::R_LUA_TLIGHTUSERDATA_);
    //std::printf("R_LUA_TNUMBER %i \n", toSet::R_LUA_TNUMBER_);
    //std::printf("R_LUA_TBOOLEAN %i \n", toSet::R_LUA_TBOOLEAN_);
    //std::printf("R_LUA_TSTRING %i \n", toSet::R_LUA_TSTRING_);
    //std::printf("R_LUA_TTHREAD %i \n", toSet::R_LUA_TTHREAD_);
    //std::printf("R_LUA_TFUNCTION %i \n", toSet::R_LUA_TFUNCTION_);
    //std::printf("R_LUA_TTABLE %i \n", toSet::R_LUA_TTABLE_);
    //std::printf("R_LUA_TVECTOR %i \n", toSet::R_LUA_TVECTOR_);

    // ^ Usage.
