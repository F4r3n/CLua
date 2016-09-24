#include <string>
#include <luajit-2.0/lua.hpp>
#include <iostream>
extern "C" {
#include <luajit-2.0/lua.h>
#include <luajit-2.0/lualib.h>
#include <luajit-2.0/lauxlib.h>
}

class CLua {
public:
    CLua() {
    }
    ~CLua() {
    }

    void init() {
        lua = luaL_newstate();
        luaL_openlibs(lua);
    }

    void insertField() {
    }

    void push_value(int t) {
        lua_pushnumber(lua, t);
    }
    void push_value(float t) {
        lua_pushnumber(lua, t);
    }
    void push_value(double t) {
        lua_pushnumber(lua, t);
    }

    template <typename First, typename Second, typename... Args>
    void insertField(First first, Second second, Args... args) {
        lua_pushstring(lua, first);
        push_value(second);
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

    void loadFile(const std::string& name) {
        int status = luaL_loadfile(lua, name.c_str());
      
        if(status) {
            throw std::string(lua_tostring(lua, -1));
            return;
        }
        try {
            executeFile();
        } catch(std::string msg) {
            throw msg;
        }
    }

    static CLua& get() {
        return _instance;
    }

private:
    lua_State* lua;
    void executeFile() {
        int status = lua_pcall(lua, 0, LUA_MULTRET, 0);
        if(status) {
            throw "Failed to run script" + std::string(lua_tostring(lua, -1));
        }
    }

    static CLua _instance;
};