function clone (t) -- deep-copy a table
    if type(t) ~= "table" then return t end
    local meta = getmetatable(t)
    local target = {}
    for k, v in pairs(t) do
        if type(v) == "table" then
            target[k] = clone(v)
        else
            target[k] = v
        end
    end
    setmetatable(target, meta)
    return target
end

WORLD.a = 5
WORLD.b = "test string"
WORLD.c = {}
WORLD.c.a = 6
WORLD.c.b = "other string"
WORLD.c.c = {}
WORLD.c.c.a = 7
WORLD.c.c.b = "you didnt expect that table, did you?"
WORLD.d = "surprise string!"
WORLD.e = false

print("ok")