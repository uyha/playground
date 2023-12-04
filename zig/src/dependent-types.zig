fn Other(Type: type) type {
    return Type;
}
fn Generator(comptime Val: type, comptime SomeConst: i32) type {
    return struct {
        const This = @This();
        const SubType = Other(Generator(Val, SomeConst));
        const other = SomeConst % 10;

        v: Val,

        pub fn foo(x: i32) i32 {
            return SomeConst + other + x;
        }
        pub fn bar(this: *This, x: i32) SubType {
            return SubType(x + this.v);
        }
    };
}
pub fn main() void {}
