#include <string>
#include <luajit-2.0/lua.hpp>
extern "C" {
#include <luajit-2.0/lua.h>
#include <luajit-2.0/lualib.h>
#include <luajit-2.0/lauxlib.h>
}

class CLua {
public:
    CLua() {
        lua = luaL_newstate();
        luaL_openlibs(lua);
    }
    ~CLua() {
    }

    void insertField() {
    }
    template <typename First, typename Second, typename... Args>
    void insertField(First first, Second second, Args... args) {
        lua_pushstring(lua, first);
        lua_pushnumber(lua, second);
        lua_rawset(lua, -3);

        insertField(std::forward<Args>(args)...);
    }

    template <typename... Args> void createTable(const std::string& name, Args... args) {
        lua_newtable(lua);
        insertField(args...);
        lua_setglobal(lua, name.c_str());
    }
    
    lua_State* getState() {
        return lua;
    }
    
    static CLua& get() {
        return _instance;
    }

private:
    lua_State* lua;
    
    static CLua _instance;
};